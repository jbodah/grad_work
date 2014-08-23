package wordstealclient.controllers.xml_handlers;

import static org.junit.Assert.assertEquals;
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
import wordstealclient.entities.Player;
import wordstealclient.entities.Room;
import wordstealclient.entities.Table;
import wordstealclient.entities.Table.TABLE_STATE;

public class TableResponseHandlerTest {
	Message mOne ;
	Message mTwo ;
	
	@Before
	public void setUp() {
		// Create a message to test parsing
		// 1192 is just a random id number		
		mOne = Utilities.makeTestMessage(TestData.samplePlayerResponse("1192"));
		mTwo = Utilities.makeTestMessage(TestData.sampleTableResponse("2000"));
	}
	
	@After
	public void tearDown() {
		mOne = null ;
		mTwo = null ;
	}
	
	@Test
	public void test() {
		context.getClient().process(mOne);
		
		Player bob 		= Room.getInstance().getPlayer(1456) ;
		Player george 	= Room.getInstance().getPlayer(1213) ;
		
		assertTrue( bob != null ) ;
		assertEquals( bob.getAlias(), "Bob Smith" ) ;
		assertEquals( bob.getSudokuRating(), 9000 ) ;
		assertEquals( bob.getWordstealRating(), 1231 ) ;
		assertTrue( george != null ) ;
		assertEquals( george.getAlias(), "George Heineman" ) ;
		assertEquals( george.getSolitaireRating(), 229 ) ;
		assertEquals( george.getWordstealRating(), 1234 ) ;
		
		context.getClient().process(mTwo);
		
		Table tableOne = Room.getInstance().getTable(1) ;
		
		assertEquals( tableOne.getPlayer(1456), bob );
		assertEquals( tableOne.getPlayer(1213), george );
		assertEquals( tableOne.getModerator(), george );
		assertEquals( tableOne.getGame(), "wordsteal" );
		assertEquals( tableOne.getSeed(), 12944 );
		assertEquals( tableOne.getOptions(), "turnTime=30,noS=true,maxScore=50" );
		assertEquals( tableOne.getNumberOfPlayers(), 2 );
		assertEquals( tableOne.getTableState(), TABLE_STATE.PUBLIC );
		
		Table tableTwo = Room.getInstance().getTable(2);
		
		assertEquals( tableTwo.getTableState(), TABLE_STATE.PRIVATE ) ;

		Table tableThree = Room.getInstance().getTable(3) ;
		
		assertEquals( tableThree.getTableState(), TABLE_STATE.INGAME ) ;
		
		Table tableFour = Room.getInstance().getTable(4) ;
		
		assertEquals( tableFour.getTableState(), TABLE_STATE.BYINVITATION ) ;
		
		Table tableFive = Room.getInstance().getTable(5) ;
		
		assertEquals( tableFive.getTableState(), TABLE_STATE.BYINVITATION ) ;
		assertEquals( tableFive.getNumberOfPlayers(), Table.MAX_PLAYERS );
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
