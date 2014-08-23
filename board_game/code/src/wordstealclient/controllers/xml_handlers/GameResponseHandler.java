package wordstealclient.controllers.xml_handlers;

import arch.WSClientArchitecture;

import wordstealclient.entities.Room;
import wordstealclient.entities.Table.TABLE_STATE;
import wordstealclient.util.NodeHelper;
import ks.framework.common.Message;

public class GameResponseHandler {

	/**
	 * Parse XML response and extract the nodes we need
	 * @author jbodah
	 */
	public static void parseXML(Message response) {
		int tableID = NodeHelper.intAttribute( response.contents(), "table" ) ;
		if( Room.getInstance().getTable(tableID).getTableState() == TABLE_STATE.PUBLIC )
			beginGame(tableID);
		else;
			// TODO: NYI processTurn();		
	}
	
	/**
	 *  Set table state to INGAME then start game
	 *  TODO: I originally didn't want to pass tableID and just wanted to use getThisPlayer().getTableID(),
	 *  but this isn't initialized by tests!
	 *  @author jbodah
	 */
	private static void beginGame(int tableID) {
		Room.getInstance().getTable(tableID).setTableState(TABLE_STATE.INGAME);
		WSClientArchitecture.getGameProvider().startGame(Room.getInstance().getTable(WSClientArchitecture.getThisPlayer().getTableID()));
	}
	
	private static void processTurn() {
		
	}
}
