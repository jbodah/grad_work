package wordstealclient.entities;

import java.util.Hashtable;
import java.util.Collection;

/**
 * Singleton class which represents room
 * @author jbodah
 */
public class Room {
	public static final int MAX_PLAYERS = 400 ;
	public static final int MAX_TABLES = 101 ;
	
	protected static Table[] tables ;
	protected static Hashtable<Integer, Player> playerHash ; 
	
	protected static Room room ;
	
	/**
	 *  Constructor
	 *  @author jbodah, cbelhumeur
	 */
	private Room() {
		this.tables = new Table[MAX_TABLES] ;
		tables[0] = null ;
	 	for( int i = 1 ; i < MAX_TABLES ; i++ ) {
			tables[i] = new Table(i) ;	 			 
		}
		this.playerHash =  new Hashtable<Integer, Player>(MAX_PLAYERS);
	}

	/**************************************** BEG GETTERS/SETTERS ****************************************/
	
	/**
	 * Get instance of singleton Room
	 * @return
	 */
	public static Room getInstance() {
		if( room == null )
			room = new Room() ;
		return room ;		
	}
	
	public static void dispose() {
		tables = null;
		playerHash = null;
		room = null;
	}
	
	public Collection<Player> getPlayers() {
		return playerHash.values() ;
	}
	
	/**
	 * Returns player with given login. Returns null if player doesn't exist.
	 * @param login
	 * @return
	 */
	public Player getPlayer(int login) {
		return playerHash.get(login) ;
	}
	
	public Table[] getTables()
	{
		Table[] tablesToReturn = new Table[MAX_TABLES-1]  ;
		for(int i = 1 ; i < MAX_TABLES ; i++)
			tablesToReturn[i-1] = tables[i] ;
		return tablesToReturn;
	}
	
	public Table getTable(int id) {
		return tables[id] ;
	}
	
	/**
	 * Add player with given ID to playerHash
	 * @param hash
	 * @param player
	 */
	private void storePlayer( int hash, Player player ) {
		playerHash.put( hash, player ) ;
	}
	
	/**************************************** END GETTERS/SETTERS ****************************************/
	
	/**
	 * Returns added player or null.
	 * @param player
	 * @return
	 * @author jbodah
	 */
	public Player addPlayer( Player player ) {
		if( player == null ) return null ;
		// If player is already in room, return null
		// TODO: make this an exception
		if( getPlayer(player.getLogin()) != null ) return null ;
		storePlayer( player.getLogin(), player ) ;
		return player ;
	}
	
	/**
	 * Remove player with given login from room.
	 * @param login
	 * @return
	 * @author jbodah
	 */
	public Player removePlayer( int login ) {
		Player removedPlayer = getPlayer(login) ;
		playerHash.remove(login) ;
		return removedPlayer ;
	}
}
