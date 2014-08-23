package wordstealclient.controllers.uncorrelated_responses;

import wordstealclient.controllers.xml_handlers.TableResponseHandler;
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
public class TableResponseController implements IProcessClientMessage {
	// process independent response received from server
	@Override
	public boolean process(ILobby lobby, Message m) {
		System.out.println("TableResponseController.process(ILobby, Message): Received " + m);
		TableResponseHandler.parseXML( m ) ;
		GUIUpdater.updateGUIWithTableOrTables();
		return true;
	}

}
