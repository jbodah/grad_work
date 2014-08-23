package wordstealclient.controllers.uncorrelated_responses;

import ks.client.interfaces.ILobby;
import ks.client.interfaces.IProcessClientMessage;
import ks.framework.common.Message;
import wordstealclient.controllers.xml_handlers.TableEmptyHandler;
import wordstealclient.util.GUIUpdater;

/**
 * This class manages top-level logic with respect to an uncorrelated response.
 * Lower level logic is forwarded to a Handler.
 * 
 * @author jbodah, heineman
 */
public class TableEmptyController implements IProcessClientMessage {
	// process independent response received from server
	@Override
	public boolean process(ILobby lobby, Message m) {
		System.out.println("TableEmptyResponseController.process(ILobby, Message): Received " + m);
		TableEmptyHandler.parseXML( m ) ;
		GUIUpdater.updateGUIWithTableOrTables();
		return true;
	}
}
