package wordstealclient.controllers.xml_handlers;

import org.w3c.dom.Node;

import wordstealclient.entities.Room;
import wordstealclient.util.GUIUpdater;
import wordstealclient.util.NodeHelper;

import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

/**
 * This code handles the parsing of XML and middle-layer logic with respect to the response received.
 * 
 * @author jbodah
 *
 */
public class ChatResponseHandler {

	public static void parseXML(Message response, ILobby lobby) {
		Node 	outputNode 		= response.contents() ; 	// Root's children
		boolean isPublic 		= true ;
		String	outputText		= new String() ;
		boolean fromSystem		= false ;
		String	sender 			= new String() ;
		
		if( NodeHelper.strAttribute(outputNode, "from") != null )
			sender = Room.getInstance().getPlayer(NodeHelper.intAttribute( outputNode, "from" )).getAlias();
		
		if( NodeHelper.strAttribute(outputNode, "public") != null )
			isPublic = NodeHelper.boolAttribute(outputNode, "public") ;
		
		if( NodeHelper.strAttribute(outputNode, "system") != null ) {
			fromSystem = NodeHelper.boolAttribute(outputNode, "system" ) ;
			sender = "SYSTEM" ;
		}
		
		while( outputNode.hasChildNodes() ) {	
			outputText += parseTierOne(outputNode.getFirstChild()) ;
			outputNode.removeChild(outputNode.getFirstChild()) ;
		}
		
		GUIUpdater.updateChatPanel(isPublic, fromSystem, sender, outputText, lobby);
	}
	
	private static String parseTierOne( Node textNode ) {
		return textNode.getTextContent() ;
	}
}
