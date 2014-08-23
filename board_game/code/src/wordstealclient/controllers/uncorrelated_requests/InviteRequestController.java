package wordstealclient.controllers.uncorrelated_requests;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import org.w3c.dom.Node;

import wordstealclient.controllers.uncorrelated_responses.ConfirmResponseController;
import wordstealclient.util.NodeHelper;
import ks.client.interfaces.IController;
import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

/**
 * Request: invite<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * {@literal <!-- Request a player to join an invitation-only table. -->}<br/>
 * {@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * {@literal <invite table="99" player="83293"/>}<br/>
 * {@literal </request>}<br/>
 * 
 * @author cbelhumeur
 */
public class InviteRequestController implements IController {
	ILobby lobby ;
	
	public InviteRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send request
	 * @author cbelhumeur
	 */
	public void process(int tableID, int playerID) {
		Message m = new Message(Message.construct (writeXMLForRequest(tableID, playerID)));
		lobby.getContext().getClient().sendToServer(lobby, m, this);
		System.out.println("InviteRequestController.process(): Request sent");
	}
	
	/**
	 *  process correlated response (to given request) when received from server
	 *	@author cbelhumeur
	 */
	@Override
	public void process(ILobby lobby, Message request, Message response) {		
		System.out.println("InviteRequestController.process(ILobby, Message, Message): Received " + response + " in response to " + request);
		parseXML( response ) ;
	}
	
	private String writeXMLForRequest(int tableID, int playerID) {
		String s = Message.requestHeader() +
				"<invite table='" + tableID + "' " +
				 		"player='" + playerID + "'/></request>" ;
		return s;
	}
	
	/**
	 * Parse XML response and extract the nodes we need
	 * @author cbelhumeur
	 */
	private void parseXML(Message response) {
		Node responseNode = response.contents() ; // Root's children
		String player = NodeHelper.strAttribute(responseNode, "player");
		String tableID = NodeHelper.strAttribute(responseNode, "table");
		int result = JOptionPane.showConfirmDialog(new JFrame("Join table?"), player + " would like to invite you to join table (#" + tableID + "). Do you want to accept?");
		new ConfirmResponseController().process(tableID, player, (result == 0));		
	}
}
