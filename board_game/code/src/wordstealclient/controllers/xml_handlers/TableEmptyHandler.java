package wordstealclient.controllers.xml_handlers;

import ks.framework.common.Message;

import wordstealclient.entities.Room;
import wordstealclient.util.GUIUpdater;
import wordstealclient.util.NodeHelper;

/**
 * This code handles the parsing of XML and middle-layer logic with respect to the response received.
 * This code was factored out to keep code DRY between correlated and uncorrelated responses.
 * 
 * @author jbodah
 *
 */
public class TableEmptyHandler {
	
	/**
	 * Parse XML response and extract the nodes we need
	 * @author jbodah
	 */
	public static void parseXML(Message response) {
		// Clear table with parsed id
		Room.getInstance().getTable( NodeHelper.intAttribute( response.contents(), "table" )).clear() ;
		GUIUpdater.updateGUIWithTableOrTables();
	}
}
