package wordstealclient.controllers.correlated_requests;

import wordstealclient.controllers.xml_handlers.TableResponseHandler;
import wordstealclient.util.GUIUpdater;
import ks.client.interfaces.IController;
import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

/**
 * Request: join<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Request to join table. -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <join table="99"/>}<br/>
 * 	{@literal </request>}
 * 
 * @author jbodah
 */
public class JoinRequestController implements IController {
	ILobby lobby ;
	
	public JoinRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send request
	 * @author jbodah
	 */
	public void process(int tableID) {
		Message m = new Message(Message.construct (writeXMLForRequest(tableID)));
		lobby.getContext().getClient().sendToServer(lobby, m, this);
		System.out.println("JoinRequestController.process(): Request sent");
	}
	
	/**
	 *  process correlated response (to given request) when received from server
	 *	@author jbodah
	 */
	@Override
	public void process(ILobby lobby, Message request, Message response) {		
		System.out.println("JoinRequestController.process(ILobby, Message, Message): Received " + response + " in response to " + request);
		TableResponseHandler.parseXML( response ) ;
		GUIUpdater.updateGUIWithTableOrTables() ;
	}
	
	private String writeXMLForRequest(int tableID) {
		String s = Message.requestHeader() +
				"<join table='" + tableID + "'/></request>" ;
		return s;
	}
}
