package wordstealclient.controllers._placeholders;

import ks.client.interfaces.IController;
import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

/**
 * Request: tableChat<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Submit chat message to all players on table -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <tableChat table="100">}<br/>
 * 	{@literal <text>Here is where the message goes.</text>}<br/>
 * 	{@literal </tableChat>}<br/>
 * 	{@literal </request>}
 * 
 * @author jbodah
 */
public class TableChatRequestController implements IController {
	ILobby lobby ;
	
	public TableChatRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send request
	 * @author jbodah
	 */
	public void process() {
		Message m = new Message(Message.construct (writeXMLForRequest()));
		lobby.getContext().getClient().sendToServer(lobby, m, this);
		System.out.println("TableChatRequestController.process(): Request sent");
	}
	
	/**
	 *  process correlated response (to given request) when received from server
	 *	@author jbodah
	 */
	@Override
	public void process(ILobby lobby, Message request, Message response) {		
		System.out.println("TableChatRequestController.process(ILobby, Message, Message): Received " + response + " in response to " + request);
		parseXML( response ) ;
	}
	
	private String writeXMLForRequest() {
		String s = Message.requestHeader();
		return s;
	}
	
	/**
	 * Parse XML response and extract the nodes we need
	 * @author jbodah
	 */
	private void parseXML(Message response) {
	}
}
