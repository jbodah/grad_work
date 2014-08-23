package wordstealclient.controllers.requests;

import ks.client.UserContext;
import ks.client.ipc.MockServer;
import ks.client.lobby.LobbyFrame;

import ks.framework.common.Configure;
import ks.framework.common.Message;

import org.junit.*;

import arch.MyLobbyInitialization;

import wordstealclient.controllers.uncorrelated_requests.ConfirmRequestController;
import wordstealclient.controllers.uncorrelated_requests.InviteRequestController;
import wordstealclient.entities.Player;
import wordstealclient.entities.Room;
import static org.junit.Assert.*;

public class ContextRequestControllerTests {
	
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
			fail ("Unable to perform setup for InviteRequestControllerTest");
		}		
	}
	
	@After
	public void tearDown() {
		lobby.dispose();
	}
	
	@Test
	public void doRequestTests()
	{
		processConfirmRequest();
		processInviteRequest();
	}
	
	public void processConfirmRequest()
	{
		try {			
			String tableID = "1";
			String playerID = user;
			Player p2 = new Player(Integer.parseInt(playerID));
			p2.setTableID(Integer.parseInt(tableID));
			Room.getInstance().addPlayer(p2);
			
			MyLobbyInitialization mli2;
			mli2 = new MyLobbyInitialization(null, null);
			mli2.initializeLobby(lobby);
			
			String s = Message.requestHeader() + "<confirm table='" + tableID + "' player='" + playerID + "'/></request>" ;
			Message message = new Message(Message.construct (s));
			ConfirmRequestController crc = new ConfirmRequestController(lobby);
			crc.process(lobby, message);
			
			Message req2 = mockServer.firstRequest();	
			assertNotNull(req2);				
			
			p2.setTableID(0);
			s = Message.requestHeader() + "<confirm table='" + tableID + "' player='" + playerID + "'/></request>" ;
			message = new Message(Message.construct (s));
			crc.process(lobby, message);
			
			req2 = mockServer.firstRequest();		
			assertNotNull(req2);	
		}
		catch (Exception e){
			fail(e.getMessage());
		}
	}
	
	public void processInviteRequest()
	{
		try {			
			String tableID = "1";
			String playerID = user;
			Player p = new Player(Integer.parseInt(playerID));
			p.setTableID(Integer.parseInt(tableID));
			Room.getInstance().addPlayer(p);
			
			MyLobbyInitialization mli;
			mli = new MyLobbyInitialization(null, null);
			mli.initializeLobby(lobby);
			
			String s = Message.requestHeader() + "<invite table='" + tableID + "' player='" + playerID + "'/></request>";
			Message message = new Message(Message.construct (s));
			InviteRequestController irc = new InviteRequestController(lobby);
			irc.process(Integer.parseInt(tableID), Integer.parseInt(playerID));
			
			Message req = mockServer.firstRoundTripRequest();
			
			assertNotNull(req);	
			
			p.setTableID(0);
			s = Message.requestHeader() + "<confirm table='" + tableID + "' player='" + playerID + "'/></request>" ;
			message = new Message(Message.construct (s));
			irc.process(lobby, null, message);
			
			req = mockServer.firstRequest();		
			assertNotNull(req);	
		}
		catch (Exception e){
			fail(e.getMessage());
		}
	}
}