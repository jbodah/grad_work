package arch;


import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JPanel;

import ks.client.controllers.ClientControllerChain;
import ks.client.interfaces.ILobby;
import ks.client.interfaces.ILobbyInitialize;
import ks.client.lobby.ConnectFrame;
import ks.client.processor.ClientProcessor;

import wordstealclient.controllers.ChatControllerChainLink;
import wordstealclient.controllers.GameControllerChainLink;
import wordstealclient.controllers.RoomControllerChainLink;
import wordstealclient.controllers.TailControllerChainLink;
import wordstealclient.entities.Player;
import wordstealclient.entities.Room;
import wordstealclient.interfaces.IGameProvider;
import wordstealclient.util.XMLSchema;
import wordstealclient.boundaries.TableManagerGUI;
import wordstealclient.boundaries.UserManagerGUI;

/**
 * This is a sample class that shows how to configure the client to function.
 * Copy (and rename) this into your appropriate location and then you can 
 * begin the process of building up your own server implementation.
 * <p>
 * Note that you will have to provide your response to requests to close the 
 * window. Here it just exits but that may not be what you want.
 * 
 * @author George Heineman, jbodah, cbelhumeur
 */
public class WSClientArchitecture {
	
	/** Entity created for client. */
	static ConnectFrame cf;
	static ILobby lobby;
	static IGameProvider provider;
	
	/**
	 * Launch client app.
	 * 
	 * @param args
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception {
		if( !XMLSchema.foundValid() )
			return ;
				
		setupConnectFrame(initLobby());
		setupControllerChain();
		
		Room.getInstance() ;
		
		// running...
	}
	
	/**
	 * initialization callback. Client-side groups can pass in 
	 * an object that provides this interface into the ConnectFrame
	 * constructor and it will be called at the proper time.
	 */
	private static ILobbyInitialize initLobby() {
		JPanel tempUserManagerGUI 	= UserManagerGUI.create(null);
		JPanel tempTableManagerGUI 	= TableManagerGUI.create(Room.getInstance().getTables());

		MyLobbyInitialization init = new MyLobbyInitialization(tempTableManagerGUI, tempUserManagerGUI);
		lobby = init.getLobby();
		provider = init;
		return init;
	}

	public static ILobby getLobby()
	{
		if (lobby == null) {
			ILobbyInitialize init = initLobby();
			lobby = ((MyLobbyInitialization)init).getLobby();
		}
		return lobby;
	}
	
	public static IGameProvider getGameProvider()
	{
		if (provider == null) {
			ILobbyInitialize init = initLobby();
			provider = (IGameProvider)init;
		}
		return provider;
	}
	
	/**
	 * Return the player that is currently logged in
	 * @return
	 * @author jbodah
	 */
	public static Player getThisPlayer() {
		if( getLobby() != null )
			return Room.getInstance().getPlayer(Integer.valueOf(getLobby().getContext().getUser()));
		return null ;
	}
	
	/**
	 * all action on this (default) local host. Should there be a need
	 * to connect to a different host computer, then you would need 
	 * to pass in command-line argument values from 'args' into the 
	 * constructor of UserContext so the client knows to which server
	 * to connect.
	 * @param init
	 */
	private static void setupConnectFrame(ILobbyInitialize init) {
		cf = new ConnectFrame(init);
		cf.addWindowListener(new WindowAdapter() {

			// Override the closing method to exit from the VM.
			// we need no check because this is before user 
			// has actually connected.
			@Override
			public void windowClosing(WindowEvent arg0) {
				System.exit(0);			
			}

		});
		cf.setVisible(true);
	}

	/**
	 * here is where you can augment the chain of client-side controllers
	 * Public for testing
	 * @author jbodah
	 */
	public static void setupControllerChain() {
		ClientControllerChain head = ClientProcessor.head();
		head.append(new ChatControllerChainLink());
		head.append(new RoomControllerChainLink());
		head.append(new GameControllerChainLink());
		head.append(new TailControllerChainLink());
	}
}
