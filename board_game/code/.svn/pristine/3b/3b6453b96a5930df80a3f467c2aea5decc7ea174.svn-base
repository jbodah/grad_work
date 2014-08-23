package wordstealclient.entities;

import static org.junit.Assert.*;

import org.junit.*;
import static wordstealclient.entities.Table.MAX_PLAYERS;


/**
 * @author jbodah
 */
public class TableTest {
	private Table table ;
	
	@Before
	public void setUp() {
		table = new Table() ;
	}
	
	@After
	public void tearDown() {
		table = null ;
	}
	
	@Test
	public void testSuite() {
		testAddPlayer() ;
		testIsFull(true) ;
		testRemovePlayerAt() ;
		testIsFull(false) ;
		testGetNumberOfPlayers() ;
		testGettersSetters();
		testGetPlayer() ;
		testGetModerator() ;
		testRemovePlayer() ;
		testInsertPlayerAndSetModerator() ;
		testClear();
	}
	
	private void testAddPlayer() {
		for( int i = 0 ; i < MAX_PLAYERS ; i++ ) {
			Player player = new Player() ;
			assertTrue(table.addPlayer(player)) ;
		}
		Player player = new Player() ;
		assertFalse(table.addPlayer(player)) ;
	}
	
	private void testIsFull(boolean bool) {
		if( bool )
			assertTrue(table.isFull());
		else
			assertFalse(table.isFull());
	}
	
	private void testRemovePlayerAt() {
		// Remove from back
		Player expectedPlayer = table.players[3] ;
		Player removedPlayer = table.removePlayerAt(3) ;
		assertTrue( removedPlayer == expectedPlayer ) ;
		assertTrue( table.players[3] == null ) ;
		
		// Remove from front
		expectedPlayer = table.players[1];
		removedPlayer = table.removePlayerAt(1) ;
		assertTrue( removedPlayer == expectedPlayer ) ;
		assertTrue( table.players[3] == null ) ;
		assertTrue( table.players[2] == null ) ;
		assertEquals( table.removePlayerAt(5), null ) ;
	}
	
	private void testGetNumberOfPlayers() {
		// Reinitialize
		table = null ;
		table = new Table() ;
		assertEquals( table.getNumberOfPlayers(), 0 ) ;
		
		// Add players
		for(int i = 0 ; i < MAX_PLAYERS ; i++) {
			table.addPlayer(new Player()) ;
			assertEquals( table.getNumberOfPlayers(), i + 1 ) ;
		}
		
		// Add more than max
		table.addPlayer(new Player()) ;
		assertEquals( table.getNumberOfPlayers(), MAX_PLAYERS ) ;
		
		// Remove players
		for(int i = 0 ; i < MAX_PLAYERS ; i++) {
			table.removePlayerAt(0) ;
			assertEquals( table.getNumberOfPlayers(), MAX_PLAYERS - ( i + 1 )) ;
		}
		
		// Remove more players than min
		table.removePlayerAt(0) ;
		assertEquals( table.getNumberOfPlayers(), 0 ) ;
	}
	
	private void testGettersSetters() {
		table.setSeed( 500 ) ;
		assertEquals( table.getSeed(), 500 ) ;
		
		table.setType("type") ;
		assertEquals( table.getType(), "type" ) ;
		
		table.setGame("game") ;
		assertEquals( table.getGame(), "game" ) ;

		table.setOptions("options") ;
		assertEquals( table.getOptions(), "options" ) ;
	}
	
	private void testGetPlayer() {
		// Initialize full table
		table = null ;
		table = new Table() ;
		
		Player player1 = new Player() ;
		player1.setLogin(1) ;
		table.addPlayer(player1) ;
		
		Player player2 = new Player() ;
		player2.setLogin(2) ;
		table.addPlayer(player2) ;
		
		Player player3 = new Player() ;
		player3.setLogin(3) ;
		table.addPlayer(player3) ;
		
		Player player4 = new Player() ;
		player4.setLogin(4) ;
		table.addPlayer(player4) ;
		
		assertEquals( player2, table.getPlayer(2)) ;
		assertEquals( null, table.getPlayer(5)) ;
	}
	
	private void testGetModerator() {
		table = null ;
		table = new Table() ;
		assertEquals(null, table.getModerator()) ;
		
		Player playerA = new Player() ;
		table.addPlayer(playerA) ;
		assertEquals(playerA, table.getModerator()) ;
		
		Player playerB = new Player() ;
		table.addPlayer(playerB) ;
		assertEquals(playerA, table.getModerator()) ;
		
		table.removePlayerAt(0) ;
		assertEquals(playerB, table.getModerator()) ;		
	}
	
	private void testRemovePlayer() {
		table = null ;
		table = new Table() ;
		
		Player playerA = new Player() ;
		playerA.setLogin(50) ;
		table.addPlayer(playerA) ;
		assertEquals(table.removePlayer(50), playerA) ;
		assertEquals(table.removePlayer(50), null) ;
	}
	
	private void testInsertPlayerAndSetModerator() {
		table = null ;
		table = new Table() ;
		
		Player playerA = new Player() ;
		Player playerB = new Player() ;
		Player playerC = new Player() ;
		Player playerD = new Player() ;
		Player playerE = new Player() ;
		playerA.setLogin(1) ;
		playerB.setLogin(2) ;
		playerC.setLogin(3) ;
		playerD.setLogin(4) ;
		playerE.setLogin(5) ;
		
		// insertPlayer
		// Keep inserting and checking until full table
		assertTrue(table.insertPlayer(playerA)) ;
		assertEquals(table.getModerator(), playerA) ;
		assertTrue(table.insertPlayer(playerB)) ;
		assertEquals(table.getModerator(), playerB) ;
		assertTrue(table.insertPlayer(playerC)) ;
		assertEquals(table.getModerator(), playerC) ;
		assertTrue(table.insertPlayer(playerD)) ;
		assertEquals(table.getModerator(), playerD) ;
		
		// Table is full, so we should escape insert and return previous state
		assertFalse(table.insertPlayer(playerE)) ;
		assertEquals(table.getModerator(), playerD) ;
		
		// setModerator
		assertEquals(table.setModerator(playerB.getLogin()), playerB) ;
		assertEquals(table.setModerator(playerE.getLogin()), null) ; 
	}
	
	private void testClear() {
		table.addPlayer(new Player());
		table.clear() ;
		assertTrue( table.getNumberOfPlayers() == 0 ) ;
	}
}