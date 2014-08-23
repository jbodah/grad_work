package wordstealclient.controllers.uncorrelated_requests;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import org.w3c.dom.Node;

import arch.WSClientArchitecture;

import wordstealclient.controllers.uncorrelated_responses.ConfirmResponseController;
import wordstealclient.entities.Player;
import wordstealclient.entities.Room;
import wordstealclient.util.NodeHelper;
import ks.client.interfaces.ILobby;
import ks.client.interfaces.IProcessClientMessage;
import ks.framework.common.Message;

/**
 * Request: confirm<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Moderator is asked to confirm the request from player "129382" to join table 100 -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <confirm table="100" player="129382"/>}<br/>
 * 	{@literal </request>}
 * 
 * @author cbelhumeur
 */
public class ConfirmRequestController  implements IProcessClientMessage {
	ILobby lobby ;
	
	public ConfirmRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	@Override
	public boolean process(ILobby lobby, Message m) {
		System.out.println("ConfirmRequestController.process(ILobby, Message): Received " + m);
		Node responseNode = m.contents() ; // Root's children
		String player = NodeHelper.strAttribute(responseNode, "player");
		Player user = Room.getInstance().getPlayer(Integer.parseInt(player));
		
		// User is not at a table if == 0
		if (user.getTableID() != 0)	{ parseInTableXML(m); } 
		else {	parseOutTableXML( m ) ;	}
		return true;
	}
	
	/**
	 * Parse XML response and extract the nodes we need
	 * @author cbelhumeur
	 */
	private void parseOutTableXML(Message response) {
		Node responseNode = response.contents() ; // Root's children
		String player = NodeHelper.strAttribute(responseNode, "player");
		String tableID = NodeHelper.strAttribute(responseNode, "table");
		/* 
	    These are a list of STATIC MODAL dialogs
	    int return codes of button pressed:
	        -1 - WINDOW CLOSED - the X PRESSED
	         0 - YES and OK
	         1 - NO
	         2 - CANCEL
	     */
		int result = JOptionPane.showConfirmDialog(new JFrame("Confirm Player?"), "Would you like to confirm " + player + "'s request to join this table (#" + tableID + ")?");
		new ConfirmResponseController().process(tableID, player, (result == 0));
	}
	
	/**
	 * Parse XML response and extract the nodes we need
	 * @author cbelhumeur
	 */
	private void parseInTableXML(Message response) {
		Node responseNode = response.contents() ; // Root's children
		String player = NodeHelper.strAttribute(responseNode, "player");
		String tableID = NodeHelper.strAttribute(responseNode, "table");
		int result = JOptionPane.showConfirmDialog(new JFrame("Join table?"), player + " would like to invite you to join table (#" + tableID + "). Do you want to accept?");
		new ConfirmResponseController().process(tableID, "" + WSClientArchitecture.getThisPlayer().getLogin(), (result == 0));
	}
}
