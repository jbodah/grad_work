package wordstealclient.controllers.requests;

import ks.client.UserContext;
import ks.client.interfaces.IController;
import ks.client.ipc.MockServer;
import ks.client.lobby.LobbyFrame;
import ks.framework.common.Configure;
import ks.framework.common.Message;

import org.junit.*;
import org.w3c.dom.Document;

import wordstealclient.controllers.uncorrelated_requests.OptionsRequestController;
import wordstealclient.entities.Table.TABLE_STATE;
import wordstealclient.util.XMLSchema;
import static org.junit.Assert.*;

public class OptionsRequestControllerTest {
	
	public static final String localhost = "localhost";
	public static final String user = "11323";
	public static final String password = "password";
	public static final int tableID = 1;
	public static final int seed = 50;
	public static final String game = "wordsteal.Wordsteal";
	public static final TABLE_STATE state = TABLE_STATE.PUBLIC;
	UserContext context;
	LobbyFrame lobby;
	MockServer mockServer;
	
	@Before
	public void setUp() {
		
		try {
			Message.unconfigure();
			assertTrue (Configure.configure());
			
			// create client to connect
			context = new UserContext();  
			lobby = new LobbyFrame (context);
			lobby.setVisible(true);
			
			context.setUser(user);
			context.setPassword(password);
			context.setSelfRegister(false);
			
			mockServer = new MockServer(lobby);
			context.setClient(mockServer);
			
			
		} catch (Exception e) {
			fail ("Unable to perform setup for OptionsRequestControllerTest");
		}
	}
	
	@After
	public void tearDown() {
		lobby.dispose();
	}
	
	@Test
	public void processOptionsRequest()
	{
		try {			
			OptionsRequestController orc = new OptionsRequestController(lobby);
			orc.process(tableID, state, seed, game);
			
			Message req = mockServer.firstRoundTripRequest();
			IController ic = mockServer.firstRoundTripController();
						
			String s = "<table id=\"" + tableID + "\" seed=\"" + seed + "\" type=\"" + XMLSchema.convertTableState(state) + "\" full=\"false\" moderator=\"1213\" game=\"" + game + "\" options=\"turnTime=30,noS=true,maxScore=50\">" + 
			  "<player-id player=\"11\"/>" + 
			  "<player-id player=\"1213\"/>" +
			  "</table>";
		
			String xmlString = Message.responseHeader(true, req.id) + "<tableResponse>" + s + "</tableResponse></response>";
			Document d = Message.construct (xmlString);
			Message resp = new Message(d);
			mockServer.process(resp);
			
			assertNotNull(resp);			
		}
		catch (Exception e){
			fail(e.getMessage());
		}
	}
}