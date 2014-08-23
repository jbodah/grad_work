package our_server;

import arch.SampleServerExtension;
import wordstealclient.util.XMLSchema;
import ks.framework.communicator.Communicator;
import ks.framework.interfaces.IAuthorization;
import ks.server.controllers.ServerControllerChain;
import ks.server.ipc.Server;
import ks.server.processor.ServerProcessor;
import ks.framework.common.Message;


/**
 * This is a sample class that shows how to configure the server to function.
 * Copy (and rename) this into your appropriate location and then you can 
 * begin the process of building up your own server implementation.
 * 
 * Note that you will have to provide your own manager that implements
 * {@link IAuthorization}.
 * 
 * @author George Heineman
 */
public class WSServerArchitecture {


	/** Instantiated server. */
	static Server srv;
	
	/**
	 * Launch server app.
	 * 
	 * @param args
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception {
		// Determine the XML schema we are going to use
		if (!XMLSchema.foundValid()) {
			System.err.println("Unable to configure Message XML");
			return;
		}

		// HACK: You'll need to come up with something better than this.
		IAuthorization auth = new IAuthorization() {
			int ctr = 1000000;

			public boolean authorize(String who, String pwd) {
				return true;
			}

			// (not-so) random accounts
			public String selfRegister(String pwd) {
				ctr++;
				return "" + ctr;
			}	

			public void login(Communicator com, Message m) {
				System.out.println(m.getOriginator() + " has logged in");
			}

			public void logout(Communicator com, Message m) {
				System.out.println(m.getOriginator() + " has logged out");
			}
		};


		srv = new Server(auth);

		// here is where you can augment the chain of server-side controllers
		ServerControllerChain head = ServerProcessor.head();
		
		head.append(new SampleServerExtension());
		head.append(new ServerExtension());
		head.append(new SControllerChainLink());

		srv.activate();
	}
}
