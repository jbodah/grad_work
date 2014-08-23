package wordstealclient.controllers.xml_handlers;

import ks.framework.common.Message;

import org.w3c.dom.Node;

import wordstealclient.entities.Player;
import wordstealclient.entities.Room;
import wordstealclient.entities.Table;
import wordstealclient.entities.Table.TABLE_STATE;
import wordstealclient.util.NodeHelper;

/**
 * This code handles the parsing of XML and middle-layer logic with respect to the response received.
 * This code was factored out to keep code DRY between correlated and uncorrelated responses.
 * 
 * @author jbodah
 *
 */
public class TableResponseHandler {
	
	/**
	 * Parse XML response and extract the nodes we need
	 * @author jbodah
	 */
	public static void parseXML(Message response) {
		Node responseNode = response.contents() ; // Root's children
		while( responseNode.hasChildNodes() ) {	
			setupTableTierOne(responseNode.getFirstChild());
			responseNode.removeChild(responseNode.getFirstChild());
		}
	}

	/**
	 * Parse first "tier" of XML
	 * @author jbodah
	 * @param tableNode
	 */
	private static void setupTableTierOne(Node tableNode) {
		Table table = Room.getInstance().getTable( NodeHelper.intAttribute(tableNode, "id")) ;
		
		table.clear() ;
		
		table.setSeed( NodeHelper.intAttribute(tableNode, "seed")) ;
		
		setTableType(tableNode, table);
		
		//table.setFull( ) ;
		
		table.setGame( NodeHelper.strAttribute(tableNode, "game")) ;
		table.setOptions( NodeHelper.strAttribute(tableNode, "options")) ;

		while( tableNode.hasChildNodes()) {
			setupTableTierTwo(tableNode.getFirstChild(), table) ;
			tableNode.removeChild(tableNode.getFirstChild());
		}

		table.setModerator( NodeHelper.intAttribute(tableNode, "moderator")) ;
	}

	private static void setTableType(Node tableNode, Table table) {
		String type = NodeHelper.strAttribute(tableNode, "type") ;
		if( type.equals( "public" ))
			table.setTableState(TABLE_STATE.PUBLIC) ;
		else if( type.equals( "private" ))
			table.setTableState(TABLE_STATE.PRIVATE) ;
		else if( type.equals( "inPlay" )) 
			table.setTableState(TABLE_STATE.INGAME);
		else if( type.equals( "byInvitation" )) 
			table.setTableState(TABLE_STATE.BYINVITATION);
	}
	
	/**
	 * Parse second "tier" of XML
	 * @author jbodah
	 * @param player
	 * @param ratingNode
	 */
	private static void setupTableTierTwo(Node player_idNode, Table table) {
		Player playerToAdd = Room.getInstance().getPlayer( NodeHelper.intAttribute(player_idNode, "player" )) ;
		if( playerToAdd == null )
			System.out.println("DEBUG: TableResponseHandler: XML trying to add player that does not exist!");
		else if( table.addPlayer( playerToAdd ) == false )
			// TODO: Warning, this could be because of stale information; table is full based on what client says, jbodah 4/10
			System.out.println("DEBUG: TableResponseHandler: Unable to add player to table during initialization, table is full!");
	}
}
