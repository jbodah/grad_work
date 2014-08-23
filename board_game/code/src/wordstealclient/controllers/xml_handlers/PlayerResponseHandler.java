package wordstealclient.controllers.xml_handlers;

import ks.framework.common.Message;

import org.w3c.dom.Node;

import wordstealclient.entities.Player;
import wordstealclient.entities.Room;
import wordstealclient.util.NodeHelper;

/**
 * This code handles the parsing of XML and middle-layer logic with respect to the response received.
 * This code was factored out to keep code DRY between correlated and uncorrelated responses.
 * 
 * @author jbodah
 *
 */
public class PlayerResponseHandler {
	
	/**
	 * Parse XML response and extract the nodes we need
	 * @author jbodah
	 */
	public static void parseXML(Message response) {
		Node responseNode = response.contents() ; // Root's children
		while( responseNode.hasChildNodes() ) {	
			addPlayerToRoom(responseNode.getFirstChild());
			responseNode.removeChild(responseNode.getFirstChild());
		}
	}

	/**
	 * @author jbodah
	 * @param playerNode
	 */
	private static void addPlayerToRoom(Node playerNode) {
		Player player = new Player() ;
		setupPlayerTierOne(playerNode, player);
		Room.getInstance().addPlayer( player ) ;
	}

	/**
	 *	Parse second "tier" of XML
	 *	@author jbodah
	 */
	private static void setupPlayerTierOne(Node playerNode, Player player) {
		player.setLogin( NodeHelper.intAttribute(playerNode, "player")) ;
		player.setAlias( NodeHelper.strAttribute(playerNode, "realName")) ;
		
		while( playerNode.hasChildNodes()) {
			setupPlayerTierTwo(playerNode.getFirstChild(), player) ;
			playerNode.removeChild(playerNode.getFirstChild());
		}
	}
	
	/**
	 * @author jbodah
	 * @param player
	 * @param ratingNode
	 */
	private static void setupPlayerTierTwo(Node ratingNode, Player player) {	
		if( NodeHelper.strAttribute(ratingNode, "category").equals("solitaire"))
			player.setSolitaireRating( NodeHelper.intAttribute(ratingNode, "value")) ;
		else if( NodeHelper.strAttribute(ratingNode, "category").equals("wordsteal"))
			player.setWordstealRating( NodeHelper.intAttribute(ratingNode, "value")) ;
		else if( NodeHelper.strAttribute(ratingNode, "category").equals("sudoku"))
			player.setSudokuRating( NodeHelper.intAttribute(ratingNode, "value")) ;
	}
}
