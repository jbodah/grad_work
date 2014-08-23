package wordstealclient.controllers.requests;

import ks.client.UserContext;
import ks.client.ipc.MockServer;
import ks.client.lobby.LobbyFrame;

import ks.framework.common.Configure;
import ks.framework.common.Message;

import org.junit.*;

import wordstealclient.controllers.uncorrelated_requests.ChatRequestController;
import static org.junit.Assert.*;

public class ChatRequestControllerTest {
	
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
			fail ("Unable to perform setup for ChatRequestControllerTest");
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
	public void processChatRequest()
	{
		try {			
			String tableID = "1";
			
			ChatRequestController chrc = new ChatRequestController(lobby);
			chrc.process("here is a string of text!");
			
			Message req = mockServer.firstRequest();			
			assertNotNull(req);	
			
			chrc.process("/a 0 This is a message");		
			req = mockServer.firstRequest();
			assertNotNull(req);	
			
			chrc.process("/p 0 This is a private message");	
			req = mockServer.firstRequest();			
			assertNotNull(req);	
			
			lobby.dispose();
		}
		catch (Exception e){
			fail(e.getMessage());
		}
	}
}