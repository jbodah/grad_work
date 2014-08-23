package wordstealclient.controllers.uncorrelated_responses;

import arch.WSClientArchitecture;
import ks.framework.common.Message;

/**
 * This class manages top-level logic with respect to an uncorrelated response.
 * Lower level logic is forwarded to a Handler.
 * 
 * @author jbodah, heineman
 */
public class ConfirmResponseController {
	
	public void process(String tableID, String player, boolean isConfirmed) {
		Message m = new Message(Message.construct (writeXMLForRequest(tableID, player, isConfirmed)));
		WSClientArchitecture.getLobby().getContext().getClient().sendToServer(m);
		System.out.println("ConfirmResponseController.process(): Response sent");
	}
	
	private String writeXMLForRequest(String tableID, String player, boolean isConfirmed) {
		String s = Message.responseHeader(isConfirmed) +
				"<confirmResponse table='" + tableID + "' player='" + player + "'/></response>" ;
		return s;
	}

}
