package wordstealclient.controllers.uncorrelated_responses;

import wordstealclient.controllers.xml_handlers.ChatResponseHandler;
import ks.client.interfaces.ILobby;
import ks.client.interfaces.IProcessClientMessage;
import ks.framework.common.Message;

public class ChatResponseController implements IProcessClientMessage {
	// process independent response received from server
	@Override
	public boolean process(ILobby lobby, Message m) {
		System.out.println("ChatResponseController.process(ILobby, Message): Received " + m);
		ChatResponseHandler.parseXML( m, lobby ) ;
		return true;
	}
}