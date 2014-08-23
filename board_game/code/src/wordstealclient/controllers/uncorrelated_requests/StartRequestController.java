package wordstealclient.controllers.uncorrelated_requests;

import arch.WSClientArchitecture;
import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

/**
 * Request: start<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Start table. -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <start table="100"/>}<br/>
 * 	{@literal </request>}
 * 
 * @author jbodah
 */
public class StartRequestController {
	ILobby lobby ;
	
	public StartRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send request
	 * @author jbodah
	 */
	public void process() {
		Message m = new Message(Message.construct (writeXMLForRequest()));
		lobby.getContext().getClient().sendToServer(m);
		System.out.println("StartRequestController.process(): Request sent");
	}
	
	private String writeXMLForRequest() {
		String s = Message.requestHeader() + "<start table='" + WSClientArchitecture.getThisPlayer().getTableID() + "'/></request>" ;
		return s;
	}
}
