package wordstealclient.entities;

import static org.junit.Assert.*;

import org.junit.*;

/**
 * @author jbodah
 */
public class PlayerTest {

	private Player player ;
	
	@Before
	public void setUp() {
		player = new Player() ;
	}
	
	@After
	public void tearDown() {
		player = null ;
	}
	
	@Test
	public void testLogin() {	
		assertEquals( player.getLogin(), 0 ) ;
		player.setLogin( 300 ) ;
		assertEquals( player.getLogin(), 300 ) ;
	}
	
	@Test
	public void testAlias() {	
		assertEquals( player.getAlias(), "User 0" ) ;
		player.setAlias( "testcase" ) ;
		assertEquals( player.getAlias(), "testcase" ) ;
	}
	
	@Test
	public void testWSRatings() {	
		assertEquals( player.getWordstealRating(), 0 ) ;
		assertEquals( player.getWordstealWins(), 0 ) ;
		assertEquals( player.getWordstealLosses(), 0 ) ;
		player.setWordstealRating( 1400 ) ;
		player.setWordstealWins( 20 ) ;
		player.setWordstealLosses( 10 ) ;
		assertEquals( player.getWordstealRating(), 1400 ) ;
		assertEquals( player.getWordstealWins(), 20 ) ;
		assertEquals( player.getWordstealLosses(), 10 ) ;
	}
	
	@Test
	public void testSLRatings() {	
		assertEquals( player.getSolitaireRating(), 0 ) ;
		assertEquals( player.getSolitaireWins(), 0 ) ;
		assertEquals( player.getSolitaireLosses(), 0 ) ;
		player.setSolitaireRating( 1400 ) ;
		player.setSolitaireWins( 20 ) ;
		player.setSolitaireLosses( 10 ) ;
		assertEquals( player.getSolitaireRating(), 1400 ) ;
		assertEquals( player.getSolitaireWins(), 20 ) ;
		assertEquals( player.getSolitaireLosses(), 10 ) ;
	}
	
	@Test
	public void testSKRatings() {	
		assertEquals( player.getSudokuRating(), 0 ) ;
		assertEquals( player.getSudokuWins(), 0 ) ;
		assertEquals( player.getSudokuLosses(), 0 ) ;
		player.setSudokuRating( 1400 ) ;
		player.setSudokuWins( 20 ) ;
		player.setSudokuLosses( 10 ) ;
		assertEquals( player.getSudokuRating(), 1400 ) ;
		assertEquals( player.getSudokuWins(), 20 ) ;
		assertEquals( player.getSudokuLosses(), 10 ) ;
	}
	
	@Test
	public void testConstructors() {
		Player player = new Player( 578, "Some Guy", 1500, 20, 10) ;
		assertEquals( player.getLogin(), 578 ) ;
		assertEquals( player.getAlias(), "Some Guy" ) ;
		assertEquals( player.getWordstealRating(), 1500 ) ;
		assertEquals( player.getWordstealWins(), 20 ) ;
		assertEquals( player.getWordstealLosses(), 10 ) ;
		
		Player player2 = new Player( 789, "Superman",
									 99999, 99999, 0,
									 99999, 99999, -1,
									 99999, 99999, -2) ;
		assertEquals( player2.getLogin(), 789 ) ;
		assertEquals( player2.getAlias(), "Superman" ) ;
		assertEquals( player2.getWordstealRating(), 99999 ) ;
		assertEquals( player2.getWordstealWins(), 99999 ) ;
		assertEquals( player2.getWordstealLosses(), 0 ) ;
		assertEquals( player2.getSolitaireRating(), 99999 ) ;
		assertEquals( player2.getSolitaireWins(), 99999 ) ;
		assertEquals( player2.getSolitaireLosses(), -1 ) ;
		assertEquals( player2.getSudokuRating(), 99999 ) ;
		assertEquals( player2.getSudokuWins(), 99999 ) ;
		assertEquals( player2.getSudokuLosses(), -2 ) ;
	}
	
	@Test
	public void testGetTableID() {
		Player player = new Player() ;
		Table table = new Table(50) ;
		table.addPlayer(player);
		assertEquals(player.getTableID(), 50) ;
	}
	
	@Test
	public void testGetSplitPlayerInfo() {
		Player player = new Player( 789, "Superman",
									99999, 99999, 0,
									99999, 99999, -1,
									99999, 99999, -2) ;
		String[] testStrings = player.getSplitPlayerInfo() ;
		testStrings[0].equals("99999");
		testStrings[1].equals("99999");
		testStrings[2].equals("0");
		
		String testString = player.getPlayerInfo() ;
		testString.equals("Superman - 99999 (99999/0)");
		
	}
}
