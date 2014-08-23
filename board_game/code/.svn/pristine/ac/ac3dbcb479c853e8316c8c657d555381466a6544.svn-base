package wordstealclient.controllers.requests;

import ks.client.UserContext;
import ks.client.ipc.MockServer;
import ks.client.lobby.LobbyFrame;

import ks.framework.common.Configure;
import ks.framework.common.Message;

import org.junit.*;

import arch.MyLobbyInitialization;

import wordstealclient.controllers.uncorrelated_requests.LeaveRequestController;
import wordstealclient.entities.Player;
import wordstealclient.entities.Room;
import static org.junit.Assert.*;

public class LeaveRequestControllerTest {
	
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
			fail ("Unable to perform setup for LeaveRequestControllerTest");
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
	public void processLeaveRequest()
	{
		try {			
			String tableID = "10";
			String playerID = user;
			Player p = new Player(Integer.parseInt(playerID));
			p.setTableID(Integer.parseInt(tableID));
			Room.getInstance().addPlayer(p);
			
			MyLobbyInitialization mli;
			mli = new MyLobbyInitialization(null, null);
			mli.initializeLobby(lobby);
			
			LeaveRequestController lrc = new LeaveRequestController(lobby);
			lrc.process();
			
			Message req = mockServer.firstRequest();			
			assertNotNull(req);	
			
			lrc.process(lobby, null, req);
			
			lobby.dispose();
		}
		catch (Exception e){
			fail(e.getMessage());
		}
	}
}