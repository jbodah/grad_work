package arch;

import java.util.Properties;

import ks.client.UserContext;
import ks.client.ipc.MockServer;
import ks.client.lobby.LobbyFrame;

import ks.framework.common.Configure;
import ks.framework.common.Message;

import org.junit.*;

import arch.MyLobbyInitialization;

import wordstealclient.entities.Player;
import wordstealclient.entities.Room;
import wordstealclient.entities.Table;
import wordstealclient.entities.Table.TABLE_STATE;
import static org.junit.Assert.*;

public class MyLobbyInitializationTest {
	
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
		mockServer.disconnect();
		context = null;
		mockServer = null;
	}
	
	@Test
	public void processInviteRequest()
	{
		try {			
	
			MyLobbyInitialization mli;
			mli = new MyLobbyInitialization(null, null);
			mli.initializeLobby(lobby);
			
			mli.sendTableChat(0, "");
			mli.update(12, 132, "wordsteal.Wordsteal", false);
			mli.leaveGame(0);
			mli.turn(0, new Properties(), "move", false);
			mli.skip(0);
			mli.connected(false);
			
			Player q = new Player(123, "name" , 234, 345, 456);
			Player[] s = new Player[1];
			s[0] = q;
			Table t = new Table(1, TABLE_STATE.PUBLIC, s);
			mli.startGame(t);
			
			lobby.dispose();
			mli = null;
			Room.getInstance().dispose();
		}
		catch (Exception e){
			fail(e.getMessage());
		}
	}
}