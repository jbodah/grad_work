package wordstealclient.controllers;

import wordstealclient.controllers.uncorrelated_responses.GameResponseController;
import ks.framework.common.Message;
import ks.client.interfaces.ILobby;
import ks.client.controllers.ClientControllerChain;

/**
 * This class process NONcorrelated responses. This means that this
 * response is not part of a request/response pair
 * @author jbodah
 */
public class GameControllerChainLink extends ClientControllerChain {

	@Override
	public boolean process( ILobby lobby, Message m ) {
		if( m.getName().equalsIgnoreCase("gameResponse"))
			return new GameResponseController().process(lobby, m) ;
		
		return next (lobby, m);
	}
}
