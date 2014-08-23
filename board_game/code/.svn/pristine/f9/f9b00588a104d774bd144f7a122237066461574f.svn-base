package wordstealclient.controllers;

import wordstealclient.controllers.uncorrelated_requests.ConfirmRequestController;
import wordstealclient.controllers.uncorrelated_responses.PlayerResponseController;
import wordstealclient.controllers.uncorrelated_responses.TableEmptyController;
import wordstealclient.controllers.uncorrelated_responses.TableResponseController;
import ks.framework.common.Message;
import ks.client.interfaces.ILobby;
import ks.client.controllers.ClientControllerChain;

/**
 * This class process NONcorrelated responses. This means that this
 * response is not part of a request/response pair
 * @author jbodah
 */
public class RoomControllerChainLink extends ClientControllerChain {

	@Override
	public boolean process( ILobby lobby, Message m ) {
		if( m.getName().equalsIgnoreCase("playerResponse"))
			return new PlayerResponseController().process(lobby, m) ;
		
		if( m.getName().equalsIgnoreCase("tableResponse"))
			return new TableResponseController().process(lobby, m) ;
		
		if( m.getName().equalsIgnoreCase("tableEmpty"))
			return new TableEmptyController().process(lobby, m) ;
		
		if( m.getName().equalsIgnoreCase("confirm"))
			return new ConfirmRequestController(lobby).process(lobby, m) ;
		
		return next (lobby, m);
	}
}
