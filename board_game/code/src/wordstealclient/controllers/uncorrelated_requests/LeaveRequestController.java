package wordstealclient.controllers.uncorrelated_requests;

import wordstealclient.entities.Player;
import wordstealclient.entities.Room;
import arch.WSClientArchitecture;
import ks.client.interfaces.IController;
import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

/**
 * Request: leave<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Player (on own initiative) requests to leave given table -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <leave table="100"/>}<br/>
 * 	{@literal </request>}
 * 
 * @example2
 * 	{@literal <!-- Moderator forced player 'poorSoul' (11324) from table 100 -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <leave table="100" player="11324"/>}<br/>
 * 	{@literal </request>} 
 * 
 * @author jbodah
 */
public class LeaveRequestController implements IController {
	ILobby lobby ;
	
	public LeaveRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send request
	 * @author jbodah
	 */
	public void process() {
		Message m = new Message(Message.construct (writeXMLForRequest()));
		lobby.getContext().getClient().sendToServer(m);
		System.out.println("LeaveRequestController.process(): Request sent");
		removePlayerFromTable();
	}

	/**
	 * Removed current player from table (current player is the one logged in on this machine)
	 * @author jbodah
	 */
	private void removePlayerFromTable() {
		Player thisPlayer = WSClientArchitecture.getThisPlayer() ;
		if( thisPlayer != null )
			Room.getInstance().getTable(thisPlayer.getTableID()).removePlayer(thisPlayer.getLogin());
	}
	
	/**
	 *  process correlated response (to given request) when received from server
	 *	@author jbodah
	 */
	@Override
	public void process(ILobby lobby, Message request, Message response) {		
		System.out.println("LeaveRequestController.process(ILobby, Message, Message): Received " + response + " in response to " + request);
		parseXML( response ) ;
	}
	
	private String writeXMLForRequest() {
		String s = Message.requestHeader() +
				"<leave table='" + WSClientArchitecture.getThisPlayer().getTableID() + "'/>" +
				"</request>";
		return s;
	}
	
	/**
	 * Parse XML response and extract the nodes we need
	 * @author jbodah
	 */
	private void parseXML(Message response) {
	}
}