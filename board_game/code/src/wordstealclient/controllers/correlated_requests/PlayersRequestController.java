package wordstealclient.controllers.correlated_requests;

import ks.client.interfaces.ILobby;
import ks.framework.common.Message;
import ks.client.interfaces.IController;

import wordstealclient.util.GUIUpdater;
import wordstealclient.controllers.xml_handlers.PlayerResponseHandler;

/**
 * This code manages the communications and top-level decisions of the request.
 * Lower level logic is passed to the Handler
 * 
 * Request: players<br/>
 * Initiated by client<br/>
 * Expects correlated response: playerResponse<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Retrieve list of all players. -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <players/>}<br/>
 * 	{@literal </request>}
 * 
 * @author jbodah
 */
public class PlayersRequestController implements IController {
	ILobby lobby ;
	
	public PlayersRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send request
	 * @author jbodah
	 */
	public void process() {
		Message m = new Message(Message.construct (writeXMLForRequest()));
		lobby.getContext().getClient().sendToServer(lobby, m, this);
		System.out.println("PlayersRequestController.process(): Request sent");
	}
	
	/**
	 *  process correlated response (to given request) when received from server
	 *	@author jbodah
	 */
	@Override
	public void process(ILobby lobby, Message request, Message response) {		
		System.out.println("PlayersRequestController.process(ILobby, Message, Message): Received " + response + " in response to " + request);
		PlayerResponseHandler.parseXML( response ) ;
		GUIUpdater.updateUserListGUI(lobby);
	}
	
	private String writeXMLForRequest() {
		String s = Message.requestHeader() +
				new String(	"<players/>" + 
				"</request>");
		return s;
	}
}
