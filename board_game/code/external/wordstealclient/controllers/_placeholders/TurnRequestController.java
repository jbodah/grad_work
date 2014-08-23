package wordstealclient.controllers._placeholders;

import ks.client.interfaces.IController;
import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

/**
 * Request: turn<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Submit completed turn -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <turn table="99" skip="false" move="(5/5)=L,(5/7)=E,(5/6)=I" complete="false">}<br/>
 * 	{@literal <gameState player="1284" score="35" game="special=value,client=only"/>}<br/>
 * 	{@literal <gameState player="335" score="135" game="special=value,client=only"/>}<br/>
 * 	{@literal </turn>}<br/>
 * 	{@literal </request>}
 * 
 * @author jbodah
 */
public class TurnRequestController implements IController {
	ILobby lobby ;
	
	public TurnRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send request
	 * @author jbodah
	 */
	public void process() {
		Message m = new Message(Message.construct (writeXMLForRequest()));
		lobby.getContext().getClient().sendToServer(lobby, m, this);
		System.out.println("TurnRequestController.process(): Request sent");
	}
	
	/**
	 *  process correlated response (to given request) when received from server
	 *	@author jbodah
	 */
	@Override
	public void process(ILobby lobby, Message request, Message response) {		
		System.out.println("TurnRequestController.process(ILobby, Message, Message): Received " + response + " in response to " + request);
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
