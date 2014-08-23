package our_server;

import ks.framework.common.Message;
import ks.framework.communicator.Communicator;
import ks.server.controllers.ServerControllerChain;

/**
 * This is a class for testing. It simulates a server by adding a
 * controller to the controller chain. Since this class won't be in the
 * final implementation, it should be okay to just make it a huge
 * if/else statement.
 */
public class SControllerChainLink extends ServerControllerChain {

	/**
	 * @author jbodah
	 */
	@Override
	public boolean process(Communicator com, Message m) {
		if (m.getName().equals ("players")) {
			return new SPlayerResponse().process(com, m);
		}
		
		if (m.getName().equals ("tables")) {
			return new STableResponse().process(com, m);
		}
		
		// try the next one in the chain...
		return next (com, m);
	}
}
