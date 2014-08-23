package wordstealclient.controllers.uncorrelated_responses;

import wordstealclient.controllers.xml_handlers.GameResponseHandler;
import ks.client.interfaces.ILobby;
import ks.client.interfaces.IProcessClientMessage;
import ks.framework.common.Message;

/**
 * TECHNICALLY RECEIVES A REQUEST<br/>
 * Request: start<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Start table. -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <start table="100"/>}<br/>
 * 	{@literal </request>}
 * 
 * @author jbodah
 */
public class GameResponseController implements IProcessClientMessage {
	@Override
	public boolean process(ILobby lobby, Message m) {
		GameResponseHandler.parseXML(m);
		return true;
	}
}
