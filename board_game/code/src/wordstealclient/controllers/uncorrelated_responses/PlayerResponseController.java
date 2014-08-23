package wordstealclient.controllers.uncorrelated_responses;

import wordstealclient.controllers.xml_handlers.PlayerResponseHandler;
import wordstealclient.util.GUIUpdater;
import ks.client.interfaces.IProcessClientMessage;
import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

/**
 * This class manages top-level logic with respect to an uncorrelated response.
 * Lower level logic is forwarded to a Handler.
 * 
 * @author jbodah, heineman
 */
public class PlayerResponseController implements IProcessClientMessage {
	// process independent response received from server
	@Override
	public boolean process(ILobby lobby, Message m) {
		System.out.println("PlayerResponseController.process(ILobby, Message): Received " + m);
		PlayerResponseHandler.parseXML( m ) ;
		GUIUpdater.updateUserListGUI(lobby);
		return true;
	}

}
