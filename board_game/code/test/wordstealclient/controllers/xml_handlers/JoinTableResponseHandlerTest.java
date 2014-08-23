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
import wordstealclient.controllers.correlated_requests.JoinRequestController;
import wordstealclient.entities.Room;

public class JoinTableResponseHandlerTest {
	Message mOne ;
	Message mTwo ;
	Message mThree ;
	Message mFour ;
	Message rTwo ;
	Message rThree ;
	Message rFour ;
	
	@Before
	public void setUp() {
		// Create a message to test parsing
		// 1000 is just a random id number		
		mOne 	= Utilities.makeTestMessage(TestData.samplePlayerResponse("1000"));
		mTwo 	= Utilities.makeTestMessage(TestData.sampleTableResponseSuccesfulJoin("2000"));
		mThree 	= Utilities.makeTestMessage(TestData.sampleTableEmptyResponse("3000"));
		mFour 	= Utilities.makeTestMessage(TestData.sampleRejectResponse("4000"));
		
		// Create test requests
		rTwo 	= Utilities.makeTestMessage("<request version='1.0' id='2000'>" + "<join table='" + 1 + "'/></request>" );
		rThree 	= Utilities.makeTestMessage("<request version='1.0' id='3000'>" + "<join table='" + 1 + "'/></request>" );
		rFour 	= Utilities.makeTestMessage("<request version='1.0' id='4000'>" + "<join table='" + 1 + "'/></request>" );
	}
	
	@After
	public void tearDown() {
		mOne	= null ;
		mTwo 	= null ;
		mThree 	= null ;
		mFour 	= null ;
		rTwo	= null ;
		rThree	= null ;
		rFour	= null ;
	}
	
	@Test
	public void test() {
		context.getClient().process(mOne);

		JoinRequestController jrc = new JoinRequestController(lobby);
		// Attempt to join table
		lobby.getContext().getClient().sendToServer(lobby, rTwo, jrc) ;
		// Receive OK response
		jrc.process(lobby, rTwo, mTwo);
		// Assert that table was joined
		assertEquals(Room.getInstance().getTable(1).getPlayer(1213).getAlias(), "George Heineman") ;
		// Remove from table
		Room.getInstance().getTable(1).removePlayer(1213) ;
		assertEquals(Room.getInstance().getTable(1).getNumberOfPlayers(), 0) ;
		
		// Attempt to join table
		lobby.getContext().getClient().sendToServer(lobby, rThree, jrc) ;
		// Receive denial response
		jrc.process(lobby, rThree, mThree);
		// Assert that table wasn't joined
		assertTrue(Room.getInstance().getTable(1).getPlayer(1213) == null) ;
		// Assert nobody is at the table
		assertEquals(Room.getInstance().getTable(1).getNumberOfPlayers(), 0) ;
		
		// Attempt to join table
		lobby.getContext().getClient().sendToServer(lobby, rThree, jrc) ;
		// Receive denial response
		jrc.process(lobby, rFour, mFour);
		// Assert that table wasn't joined
		assertTrue(Room.getInstance().getTable(1).getPlayer(1213) == null) ;
		// Assert nobody is at the table
		assertEquals(Room.getInstance().getTable(1).getNumberOfPlayers(), 0) ;
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
