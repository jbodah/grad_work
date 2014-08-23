package wordstealclient.util;

import static org.junit.Assert.*;
import org.junit.*;

import wordstealclient.entities.Player;
import wordstealclient.entities.Table.TABLE_STATE;

public class GUIHelperTest {
	@Test
	public void testContainsOnlyLetters() {
		assertFalse(GUIHelper.containsOnlyLetters(null));
		assertFalse(GUIHelper.containsOnlyLetters(new String("")));
		assertFalse(GUIHelper.containsOnlyLetters(new String("dkasljdslakdjlaskjd4")));
		assertFalse(GUIHelper.containsOnlyLetters(new String("asdasdasdsa ")));
		assertTrue(GUIHelper.containsOnlyLetters(new String("sadsadsadasd")));
	}
	
	@Test
	public void testContainsOnlyNumbers() {
		assertFalse(GUIHelper.containsOnlyNumbers(null));
		assertFalse(GUIHelper.containsOnlyNumbers(new String("")));
		assertFalse(GUIHelper.containsOnlyNumbers(new String("238976217846237846283a")));
		assertFalse(GUIHelper.containsOnlyNumbers(new String("2321321376218376 ")));
		assertTrue(GUIHelper.containsOnlyNumbers(new String("2329178389271398712")));
	}
	
	@Test
	public void testFormatPlayerList() {
		Player[] players = new Player[3];
		players[0] = new Player(0);
		players[1] = new Player(1);
		players[2] = new Player(2);
		String[] playersString = GUIHelper.formatPlayerList(players);
		for( int i = 0 ; i < playersString.length ; i++ ) {
			assertEquals( playersString[i], "User " + i ) ;
		}
	}
	
	@Test
	public void testResolveTableStatus() {
		assertEquals( GUIHelper.resolveTableStatus("PUBLIC"), TABLE_STATE.PUBLIC ) ;
		assertEquals( GUIHelper.resolveTableStatus("PRIVATE"), TABLE_STATE.PRIVATE ) ;
		assertEquals( GUIHelper.resolveTableStatus("INGAME"), TABLE_STATE.INGAME ) ;
		assertEquals( GUIHelper.resolveTableStatus("BYINVITATION"), TABLE_STATE.BYINVITATION ) ;
		assertEquals( GUIHelper.resolveTableStatus("HAMBURGERS"), TABLE_STATE.UNKNOWN ) ;
	}
	
	@Test
	public void testFormatTableStatuses() {
		assertTrue(GUIHelper.formatTableStatuses()[0].equals( "PUBLIC" )) ;
		assertTrue(GUIHelper.formatTableStatuses()[1].equals( "PRIVATE" )) ;
		assertTrue(GUIHelper.formatTableStatuses()[2].equals( "BYINVITATION" )) ;
	}
	
	@Test
	public void testFormatColumnHeaders() {
		assertTrue(GUIHelper.formatColumnHeaders()[0].equals( "Alias" )) ;
		assertTrue(GUIHelper.formatColumnHeaders()[1].equals( "Rating" )) ;
		assertTrue(GUIHelper.formatColumnHeaders()[2].equals( "Wins" )) ;
		assertTrue(GUIHelper.formatColumnHeaders()[3].equals( "Losses" )) ;
	}
}
