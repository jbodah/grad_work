package wordstealclient.controllers.uncorrelated_requests;

import wordstealclient.entities.Room;
import ks.client.interfaces.ILobby;
import ks.client.interfaces.IProcessLobbyInput;
import ks.framework.common.Message;

/**
 * Request: chat<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- submit public Chat Message. -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <chat>}<br/>
 *  {@literal <text>Here is where the message goes.</text>}<br/>
 *  {@literal </chat>}<br/>
 * 	{@literal </request>}
 * 
 * @example2
 * 	{@literal <!-- Submit Private Chat Message. -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <chat>}<br/>
 * 	{@literal <player-id player="11345"/>}<br/>
 *  {@literal <!-- private people -->}<br/>
 *  {@literal <player-id player="1983"/>}<br/>
 *  {@literal <text>Here is where the private message goes.</text>}<br/>
 *  {@literal </chat>}<br/>
 * 	{@literal </request>}
 * 
 * @author jbodah
 */
public class ChatRequestController implements IProcessLobbyInput {
	ILobby lobby ;
	
	public ChatRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send request
	 * @author jbodah
	 */
	public void process(String text) {
		String s ;
		
		if( isPrivateMessage(text) ) {
			if( isRecipientOnline(text) )
				s = writePrivateXMLForRequest(text);
			else {
				lobby.append("This player is not online!");
				return ;
			}		
		}
		else
			s = writeXMLForRequest(text);
		Message m = new Message(Message.construct(s));
		lobby.getContext().getClient().sendToServer(m);
		System.out.println("ChatRequestController.process(): Request sent");
	}

	// Make sure recipient is logged on
	private boolean isRecipientOnline(String text) {
		int recipientID = Integer.parseInt( text.split(" ")[1] );
		return ( Room.getInstance().getPlayer(recipientID) != null ) ;
	}
	 	
	private String writeXMLForRequest(String text) {
		String s = Message.requestHeader() +
				"<chat>" +
				"<text>" + text + "</text>" +
				"</chat>" + 
				"</request>" ;
		return s;
	}

	private String writePrivateXMLForRequest(String text) {
		String s = Message.requestHeader() + 
				"<chat>" +
				"<player-id>" + text.split(" ")[1] + "</player-id>" +
				// Offset to ignore "/p PLAYER-ID "
				"<text>" + text.substring(4 + text.split(" ")[1].length()) + "</text>" +
				"</chat>" +
				"</response>" ;
		return s;
	}
	
	private boolean isPrivateMessage( String text ) {
		return text.startsWith("/p ") ;
	}
}
