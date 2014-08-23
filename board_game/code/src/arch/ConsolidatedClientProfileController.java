package arch;

import java.util.UUID;

import org.w3c.dom.Document;

import ks.client.interfaces.IController;
import ks.client.interfaces.ILobby;
import ks.client.interfaces.IProcessClientMessage;
import ks.framework.common.Message;

/**
 * SAMPLE INFORMATION TO SHOW HOW TO GET THINGS STARTED. THIS IS NOT REAL!
 * 
 * take getProfile request and produce playerResponse 
 *
 */
public class ConsolidatedClientProfileController implements IProcessClientMessage, IController {

	/** Lobby over which controller is active. */
	ILobby lobby;
	
	public ConsolidatedClientProfileController (ILobby lobby) {
		this.lobby = lobby;
	}
	
	/** GUi-based event handler to respond to the selection of the menu item. */
	public void process() { 
		// make a getProfile request
		String id = UUID.randomUUID().toString();
		String s = new String ("<request version='1.0' id='" + id + "'>\n" +
				"<getProfile player='1213'/>\n" + 
				"</request>");
		
		Document d = Message.construct (s);
		Message m = new Message(d);
		lobby.getContext().getClient().sendToServer(lobby, m, this);
	}


	// process correlated response (to given request) when received from server
	@Override
	public void process(ILobby lobby, Message request, Message response) {
		System.out.println("Received " + response + " in response to " + request);
	}

	
	// process independent response received from server
	@Override
	public boolean process(ILobby lobby, Message m) {
		System.out.println("Received " + m);
		return true;
	}

	
}
