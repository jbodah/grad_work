package wordstealclient.controllers;

import ks.framework.common.Message;
import ks.client.interfaces.ILobby;
import ks.client.controllers.ClientControllerChain;

/**
 * Use this instead of having to have each end chain link return true
 * @author jbodah
 *
 */
public class TailControllerChainLink extends ClientControllerChain {

	@Override
	public boolean process( ILobby lobby, Message m ) {
		return true;
	}
}