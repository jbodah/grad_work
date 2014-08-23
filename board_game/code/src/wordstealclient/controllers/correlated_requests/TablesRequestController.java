package wordstealclient.controllers.correlated_requests;

import ks.client.interfaces.IController;
import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

import wordstealclient.controllers.xml_handlers.TableResponseHandler;
import wordstealclient.util.GUIUpdater;

/**
 * Request: tables<br/>
 * Initiated by client<br/>
 * Expects correlated response: <br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Retrieve list of all tables. -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <tables/>}<br/>
 * 	{@literal </request>}
 * 
 * @author jbodah
 */
public class TablesRequestController implements IController {
	ILobby lobby ;
	
	public TablesRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send request
	 * @author jbodah
	 */
	public void process() {
		Message m = new Message(Message.construct (writeXMLForRequest()));
		lobby.getContext().getClient().sendToServer(lobby, m, this);
		System.out.println("TablesRequestController.process(): Request sent");
	}

	private String writeXMLForRequest() {
		String s = Message.requestHeader() +
				new String(	"<tables/>" + 
				"</request>");
		return s;
	}
	
	/**
	 *  process correlated response (to given request) when received from server
	 *	@author jbodah
	 */
	@Override
	public void process(ILobby lobby, Message request, Message response) {		
		System.out.println("TablesRequestController.process(ILobby, Message, Message): Received " + response + " in response to " + request);
		TableResponseHandler.parseXML( response ) ;
		GUIUpdater.updateGUIWithTableOrTables();
	}
}
