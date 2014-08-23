package wordstealclient.boundaries;

import static org.junit.Assert.*;

import java.util.Hashtable;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import test.TestData;
import wordstealclient.entities.Player;
import wordstealclient.entities.Table;

public class ManagerGUITest {
	
	@Before
	public void setUp() {
	
	}
	
	@After
	public void tearDown() {
		
	}

	@Test
	public void testUserManagerGUI()
	{
		Hashtable<Integer, Player> players = TestData.getUsers();
		assertNotNull(UserManagerGUI.create(players.values()));
	}
	
	@Test
	public void testTableManagerGUI()
	{
		Table[] tables = TestData.getTables();
		assertNotNull(TableManagerGUI.create(tables));
		
		Player p = new Player(123, "Bob", 234, 345, 456);
		tables[0].addPlayer(p);
		assertNotNull(TableManagerGUI.create(tables[0]));
	}
	
	@Test
	public void testInvitePanel()
	{
		Hashtable<Integer, Player> players = TestData.getUsers();
		assertNotNull(new WSInviteFrame(players.values()));
	}
	
	@Test
	public void testUserPanel()
	{
		Hashtable<Integer, Player> players = TestData.getUsers();
		WSUserPanel up = new WSUserPanel(players.get(0));
		up.update(players.get(1));
		assertNotNull(up);
		
	}
}
