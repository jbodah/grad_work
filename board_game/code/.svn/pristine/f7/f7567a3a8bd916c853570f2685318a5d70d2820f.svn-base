package our_server;

import ks.framework.common.Message;
import ks.framework.communicator.Communicator;
import ks.server.interfaces.IProcessServerMessage;

import org.w3c.dom.Document;

import test.TestData;

/**
 * This class is for testing. It simulates the server.
 * Code here is responsible for returning a confirmResponse.
 * @author jbodah
 */
public class SConfirmResponse implements IProcessServerMessage {
	public boolean process(Communicator com, Message m) {	
		System.out.println("SConfirmResponse().process(Communicator, Message): " + m);
	
		String s = TestData.sampleConfirmResponse(m.id) ;
	
		Document d = Message.construct (s);
		Message r = new Message(d);
	
		// send right back to (and only to) originating client.
		r.setRecipient(m.getOriginator());
		com.distribute(r);
		System.out.println("SConfirmResponse().process(Communicator, Message): Response sent" );
		return true;
	}
}
