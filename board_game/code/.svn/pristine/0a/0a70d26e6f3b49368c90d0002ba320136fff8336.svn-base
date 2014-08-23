package wordstealclient.controllers.xml_handlers;

import static org.junit.Assert.*;

import ks.client.UserContext;
import ks.client.controllers.ConnectController;
import ks.client.controllers.DisconnectController;
import ks.client.lobby.LobbyFrame;
import ks.framework.common.Configure;
import ks.framework.common.Message;
import org.junit.*;

import org.junit.Test;

import arch.WSClientArchitecture;


import test.TestData;
import test.Utilities;
import wordstealclient.entities.Room;

/**
 * Tests the XML Handler of a controller. Does this by sending a response to the client.
 * Note that errors occur when processing message due to a lack GUI initialization.
 * 
 * I wish I didn't have to initialize a server for nothing and could just test the Handler,
 * but Message.construct() prevents me from doing this. Not sure exactly why.
 * 
 * @author jbodah, heineman
 */
public class PlayerResponseHandlerTest {
	Message mOne ;
	
	@Before
	public void setUp() {
		// Create a message to test parsing
		// 1192 is just a random id number		
		mOne = Utilities.makeTestMessage(TestData.samplePlayerResponse("1192"));
	}
	
	@After
	public void tearDown() {
		mOne = null ;
	}
	
	@Test
	public void test() {
		context.getClient().process(mOne);
		assertTrue( Room.getInstance().getPlayer(1213) != null ) ;
		assertEquals( Room.getInstance().getPlayer(1213).getAlias(), "George Heineman" ) ;
		assertEquals( Room.getInstance().getPlayer(1213).getSolitaireRating(), 229 ) ;
		assertEquals( Room.getInstance().getPlayer(1213).getWordstealRating(), 1234 ) ;
		assertTrue( Room.getInstance().getPlayer(1456) != null ) ;
		assertEquals( Room.getInstance().getPlayer(1456).getAlias(), "Bob Smith" ) ;
		assertEquals( Room.getInstance().getPlayer(1456).getSudokuRating(), 9000 ) ;
		assertEquals( Room.getInstance().getPlayer(1456).getWordstealRating(), 1231 ) ;
	}

	
	/********************* BOILERPLATE CODE *********************/
	
	// host
	public static final String localhost = "localhost";
	
	// sample credentials (really meaningless in the testing case)
	public static final String user = "11323";
	public static final String password = "password";
	
	/** Constructed objects for this test case. */
	UserContext context;
	LobbyFrame lobby;
	
	// random port 8000-10000 to avoid arbitrary conflicts
	int port;
	
	/**
	 * setUp() method is executed by the JUnit framework prior to each 
	 * test case.
	 */
	@Before
	public void setUpTwo() {
		// Determine the XML schema we are going to use
		try {
			Message.unconfigure();
			assertTrue (Configure.configure());
		} catch (Exception e) {
			fail ("Unable to setup Message tests."); 
		}
		
		WSClientArchitecture.setupControllerChain();
		
		// create client to connect
		context = new UserContext();  // by default, localhost
		lobby = new LobbyFrame (context);
		lobby.setVisible(true);
		
		context.setPort(port);
		context.setUser(user);
		context.setPassword(password);
		context.setSelfRegister(false);
		
		// connect client to server
		assertTrue (new ConnectController(lobby).process(context));
		
		// wait for things to settle down. As your test cases become more
		// complex, we may find it necessary to include additional waiting 
		// times.
		waitASecond();
	}

	/**
	 * tearDown() is executed by JUnit at the conclusion of each individual
	 * test case.
	 */
	@After
	public void tearDownTwo() {
		// the other way to leave is to manually invoke controller.
		assertTrue (new DisconnectController (lobby).process(context));
		
		lobby.setVisible(false);
		lobby.dispose();
	}
	
	// helper function to sleep for a second.
	private void waitASecond() {
		// literally wait a second.
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			
		}
	}
}
