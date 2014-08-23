package wordstealclient.controllers.xml_handlers;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;
import ks.client.UserContext;
import ks.client.controllers.ConnectController;
import ks.client.controllers.DisconnectController;
import ks.client.lobby.LobbyFrame;
import ks.framework.common.Configure;
import ks.framework.common.Message;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import arch.WSClientArchitecture;

import test.TestData;
import test.Utilities;
import wordstealclient.entities.Room;
import wordstealclient.entities.Table;
import wordstealclient.entities.Table.TABLE_STATE;

public class GameResponseHandlerTest {
	Message mOne ;
	Message mTwo ;
	Message mThree ;
	
	@Before
	public void setUp() {
		// Create a message to test parsing
		// 1192 is just a random id number		
		mOne 	= Utilities.makeTestMessage(TestData.samplePlayerResponse("1192")) ;	
		mTwo 	= Utilities.makeTestMessage(TestData.sampleTableResponse("2000"));
		mThree 	= Utilities.makeTestMessage(TestData.sampleGameResponse("3000"));
	}
	
	@After
	public void tearDown() {
		mOne = null ;
		mTwo = null ;
	}
	
	@Test
	public void test() {
		context.getClient().process(mOne);					// Add players to room
		context.getClient().process(mTwo);					// Add players to table
				
		Table tableOne = Room.getInstance().getTable(1) ;

		assertTrue( tableOne.getTableState() == TABLE_STATE.PUBLIC ) ;	
		
		context.getClient().process(mThree);				// Start game
		
		assertTrue( tableOne.getTableState() == TABLE_STATE.INGAME ) ;	
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
