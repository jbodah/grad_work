package wordstealclient.controllers.requests;

import ks.client.UserContext;
import ks.client.interfaces.IController;
import ks.client.ipc.MockServer;
import ks.client.lobby.LobbyFrame;

import ks.framework.common.Configure;
import ks.framework.common.Message;

import org.junit.*;
import org.w3c.dom.Document;

import wordstealclient.controllers.correlated_requests.TablesRequestController;
import wordstealclient.entities.Table.TABLE_STATE;
import wordstealclient.util.XMLSchema;
import static org.junit.Assert.*;

public class TablesRequestControllerTest {
	
	public static final String localhost = "localhost";
	public static final String user = "123";
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
			TablesRequestController trc = new TablesRequestController(lobby);
			trc.process();
			
			Message req = mockServer.firstRoundTripRequest();
			IController ic = mockServer.firstRoundTripController();
			
			assertNotNull(req);	
			
			/*
			 * <response version="1.0" id="589a39591271844e3fbe32bbb9281ad9" success="true">
				- <tableResponse>
				- 	<table id="13" seed="12944" type="public" full="false" moderator="1213" game="WordSteal" options="turnTime=30,noS=true,maxScore=50">
				  		<player-id player="11" /> 
				  		<player-id player="1213" /> 
				  	</table>
				- 	<table id="17" seed="11144" type="private" full="true" moderator="18" game="solitaire/freeCell" options="undo=true,newHand=true,time=500">
				  		<player-id player="18" /> 
				  		<player-id player="17" /> 
				  	</table>
				  </tableResponse>
				</response>
			 */
			
			String s = "<table id=\"" + tableID + "\" seed=\"" + seed + "\" type=\"" + XMLSchema.convertTableState(state) + "\" full=\"false\" moderator=\"1213\" game=\"" + game + "\" options=\"turnTime=30,noS=true,maxScore=50\">" + 
					  		"<player-id player=\"11\"/>" + 
					  		"<player-id player=\"1213\"/>" +
					   "</table>";
				
			String xmlString = Message.responseHeader(true, req.id) + "<tableResponse>" + s + "</tableResponse></response>";
			Document d = Message.construct (xmlString);
			Message resp = new Message(d);
			trc.process(lobby, null, resp);	
			
			req = mockServer.firstRoundTripRequest();
			ic = mockServer.firstRoundTripController();

			assertNotNull(req);
			assertNotNull(ic);
		}
		catch (Exception e){
			fail(e.getMessage());
		}
	}
}