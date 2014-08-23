package wordstealclient.entities;

import static org.junit.Assert.*;

import org.junit.Test;

import wordstealclient.entities.Table.TABLE_STATE;
import static wordstealclient.entities.Room.MAX_TABLES ;

/**
 * @author jbodah
 */
public class RoomTest {

	@Test
	public void testRoom() {
		for( int i = 1 ; i < MAX_TABLES ; i++ ) {
			Room.getInstance().tables[i].setTableState( TABLE_STATE.PRIVATE ) ;
			assertEquals( Room.getInstance().tables[i].getTableState(), TABLE_STATE.PRIVATE ) ;
		}
	}
	
	@Test
	public void testGetPlayerAndRemovePlayer() {
		// getPlayer
		// Player exists
		Player playerA = new Player(6000) ;
		assertEquals( Room.getInstance().addPlayer(playerA), playerA ) ;
		assertEquals( playerA, Room.getInstance().getPlayer(6000)) ;
		
		// Player doesn't exist
		assertEquals( null, Room.getInstance().getPlayer(5)) ;
		
		// removePlayer
		// Remove existing player
		assertEquals( playerA, Room.getInstance().removePlayer(6000) ) ;
		
		// Remove player that isn't in room
		assertEquals( null, Room.getInstance().removePlayer(20) ) ;
	}
	
	@Test
	public void testAddPlayer() {
		Player playerA = new Player(5000) ;
		assertEquals( Room.getInstance().addPlayer(playerA), playerA ) ;
		assertEquals( Room.getInstance().addPlayer(null), null ) ;
		
		Player playerB = new Player(5000) ;
		assertFalse( playerB == playerA ) ;
		assertEquals( Room.getInstance().addPlayer(playerA), null ) ;
		assertEquals( Room.getInstance().addPlayer(playerB), null ) ;
		assertEquals( Room.getInstance().getPlayer(5000), playerA ) ;
	}
	
	@Test
	public void testTableIDs() {
		for(int i = 1 ; i < MAX_TABLES ; i++) {
			assertEquals( Room.getInstance().getTable(i).getTableID(), i ) ;
		}
	}
}
