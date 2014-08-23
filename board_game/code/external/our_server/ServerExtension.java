package our_server;

import ks.framework.common.Message;
import ks.framework.communicator.Communicator;
import ks.server.controllers.ChatController;
import ks.server.controllers.ServerControllerChain;

/**
 * Sample code showing how to integrate "Chat" capability to the server. 
 * <p>
 * To add one (or more) controllers you need to create a new ServerControllerChain subclass
 * which will act as one of the "links" in the chain. 
 * 
 * @author George Heineman
 */
public class ServerExtension extends ServerControllerChain {
	
	/**
	 * This extension understands Chat and that's it.
	 */
	@Override
	public boolean process(Communicator com, Message m) {
		if (m.getName().equals ("chat")) {
			return new ChatController().process(com, m);
		}
		
		// try the next one in the chain...
		return next (com, m);
	}
}
