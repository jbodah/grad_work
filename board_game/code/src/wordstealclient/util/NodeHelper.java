package wordstealclient.util;

import org.w3c.dom.Node;

/**
 * This class is here to clean up the code for parsing XML nodes
 * 
 * @author jbodah
 *
 */
public class NodeHelper {
	/**
	 * Given the name of some attribute, returns the value of that attribute in string form
	 * @param name
	 * @return
	 */
	public static String strAttribute( Node node, String name ) {
		// TODO: This is a bit of a hack, jbodah 4/11
		if( node.getAttributes().getNamedItem(name) == null )
			return null ;
		return node.getAttributes().getNamedItem(name).getNodeValue() ;
	}
	
	/**
	 * Given the name of some attribute, returns that attribute in integer form
	 * @param name
	 * @return
	 */
	public static int intAttribute( Node node, String name ) {
		return Integer.parseInt(strAttribute( node, name )) ;
	}
	
	public static boolean boolAttribute( Node node, String name ) {
		return Boolean.parseBoolean(strAttribute(node,name));
	}
}
