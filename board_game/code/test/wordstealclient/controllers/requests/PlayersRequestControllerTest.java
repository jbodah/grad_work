package wordstealclient.controllers.requests;

import ks.client.UserContext;
import ks.client.interfaces.IController;
import ks.client.ipc.MockServer;
import ks.client.lobby.LobbyFrame;

import ks.framework.common.Configure;
import ks.framework.common.Message;

import org.junit.*;
import org.w3c.dom.Document;

import wordstealclient.controllers.correlated_requests.PlayersRequestController;
import wordstealclient.entities.Room;
import static org.junit.Assert.*;

public class PlayersRequestControllerTest {
	
	public static final String localhost = "localhost";
	public static final String user = "123";
	public static final String password = "password";
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
			fail ("Unable to perform setup for ConfirmRequestControllerTest");
		}		
	}
	
	@After
	public void tearDown() {
		lobby.dispose();
		mockServer.disconnect();
		context = null;
		mockServer = null;
	}
	
	@Test
	public void processConfirmRequest()
	{
		try {			
			PlayersRequestController prc = new PlayersRequestController(lobby);
			prc.process();
			
			Message req = mockServer.firstRoundTripRequest();
			IController ic = mockServer.firstRoundTripController();
			
			assertNotNull(req);	
			
			/*
			 * <response version="1.0" id="589a39591271844e3fbe32bbb9281ad9" success="true">
				- <playerResponse>
				- 	<player player="1213" realName="George Heineman">
				  		<rating category="solitaire" value="229" /> 
				  		<rating category="wordsteal" value="1234" /> 
				  	</player>
				- 	<player player="1217">
				  		<rating category="solitaire" value="2983" /> 
				  	</player>
				  </playerResponse>
				</response>
			 */
			String playerID = "123";
			String name = "Hello World";
			String s = "<player player=\"" + playerID + "\" realName=\"" + name + "\">" + 
					     "<rating category=\"solitaire\" value=\"229\"/>" + 
					     "<rating category=\"wordsteal\" value=\"330\"/>" + 
					     "<rating category=\"sudoku\" value=\"440\"/>" +
					   "</player>";
			String xmlString = Message.responseHeader(true) + "<playerResponse>" + s + "</playerResponse>" + "</response>";
			Document d = Message.construct (xmlString);
			Message resp = new Message(d);
			prc.process(lobby, null, resp);	
			
			req = mockServer.firstRoundTripRequest();
			ic = mockServer.firstRoundTripController();

			assertNotNull(req);
			assertNotNull(ic);
			
			Room.getInstance().getPlayer(123).setTableID(1);
		}
		catch (Exception e){
			fail(e.getMessage());
		}
	}
}