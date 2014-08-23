package wordstealclient.controllers;

import wordstealclient.controllers.uncorrelated_responses.ChatResponseController;
import ks.client.controllers.ClientControllerChain;
import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

/**
 * Sample code showing how to integrate "Output" capability to the client. 
 * <p>
 * To add one (or more) controllers you need to create a new ClientControllerChain subclass
 * which will act as one of the "links" in the chain. 
 * 
 * @author George Heineman
 */
public class ChatControllerChainLink extends ClientControllerChain {
	
	/**
	 * This extension understands Chat and that's it.
	 */
	@Override
	public boolean process(ILobby lobby, Message m) {		
		/*
		if (m.getName().equalsIgnoreCase("output")) {
			return new LobbyOutputController().process(lobby, m);
		} 
		*/
		
		if (m.getName().equalsIgnoreCase("output")) {
			return new ChatResponseController().process(lobby, m);
		}

		// try the next one in the chain...
		return next (lobby, m);
	}
}
