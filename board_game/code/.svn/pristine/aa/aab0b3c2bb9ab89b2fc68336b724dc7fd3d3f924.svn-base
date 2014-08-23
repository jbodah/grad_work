package wordstealclient.controllers._placeholders;

import java.util.UUID;

import org.w3c.dom.Document;

import ks.client.interfaces.ILobby;
import ks.framework.common.Message;
import ks.client.interfaces.IController;

/**
 * Request: playerInfo<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Request to change player password. -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <playerInfo password="2g3jg3hjg" new-password="somePassword"/>}<br/>
 * 	{@literal </request>}
 * 
 * @example2
 * 	{@literal <!-- Request to change player information. -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <playerInfo password="89uoj93fuf" new-realName="George Heineman"/>}<br/>
 * 	{@literal </request>}
 * 
 * @author jbodah
 */
public class PlayerInfoRequestController implements IController {
	ILobby lobby ;
	
	public PlayerInfoRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send a playerRequest
	 * @author jbodah
	 */
	public void process() {
		String id = UUID.randomUUID().toString();
		String s = new String ("<request version='1.0' id='" + id + "'>" +
				"<playerInfo password=" + 
				"</request>");
		Document d = Message.construct (s);
		Message m = new Message(d);
		lobby.getContext().getClient().sendToServer(lobby, m, this);
		System.out.println("PlayerInfoRequestController.process(): Request sent");
	}
	
	/**
	 *  process correlated response (to given request) when received from server
	 *	@author jbodah
	 */
	@Override
	public void process(ILobby lobby, Message request, Message response) {
		System.out.println("PlayerInfoRequestController.process(ILobby, Message, Message): Received " + response + " in response to " + request);
	}
}
