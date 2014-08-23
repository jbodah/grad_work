package arch;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;
import ks.client.UserContext;
import ks.client.ipc.MockServer;
import ks.client.lobby.LobbyFrame;
import ks.framework.common.Configure;
import ks.framework.common.Message;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class ConsolidatedClientProfileControllerTest {

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
	public void consolidatedClientProfileControllerTest()
	{
		try {
			ConsolidatedClientProfileController ccpc = new ConsolidatedClientProfileController(lobby);
			ccpc.process();
			ccpc.process(lobby, null);
			ccpc.process(lobby, null, null);	
			
			lobby.dispose();
		}
		catch (Exception e) {
			fail(e.getMessage());
		}
	}
}
