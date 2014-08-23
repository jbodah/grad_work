package wordstealclient.entities;

public class Table {
	public static final int MAX_PLAYERS = 4 ;
	
	public enum TABLE_STATE {PUBLIC, PRIVATE, INGAME, BYINVITATION, UNKNOWN};
	
	protected Player[] 		players ;
	protected TABLE_STATE 	tableState ;
	protected int 			tableID; 		// TODO: Need to double think if ID is necessary given Room.tables[i], jbodah 4/5
	protected int 			seed;
	protected String		type ; 			// TODO: This should be an enum; might be the same thing as TABLE_STATE
	protected String		game ;			// TODO: This should be a different type or an enum
	protected String		options ;
	
	// Specific game options set by the moderator
	protected boolean nos;
	protected boolean pink;
	protected int turnTime;
	protected int pointsToWin;
	
	/***************************************** BEG CONSTRUCTORS ******************************************/
	/**
	 * @author jbodah
	 */
	public Table() {
		initTable();
	}
	
	// For Room to initialize ID's
	public Table(int id) {
		initTable() ;
		this.tableID = id;
	} 
	
	public Table(int id, TABLE_STATE state, Player[] players) {
		this.players = players;
		tableState = state;
		tableID = id;
		seed = 0;
	}

	private void initTable() {
		this.players = new Player[MAX_PLAYERS] ;
			
		for(int i = 0 ; i < MAX_PLAYERS ; i++) {
			players[i] = null ;
		}
		
		this.tableState = TABLE_STATE.PUBLIC;
		this.tableID = 0;
	} 
	/***************************************** END CONSTRUCTORS ******************************************/
	
	/**************************************** BEG GETTERS/SETTERS ****************************************/	
	/**
	 * @author cbelhumeur
	 */
	public int getTableID()
	{
		return tableID;
	}
	
	public TABLE_STATE getTableState()
	{
		if (tableState == TABLE_STATE.UNKNOWN){
			try {throw new Exception("Table state cannot be UNKNOWN.");} 
			catch (Exception e) {e.printStackTrace();}
		}
		return tableState;
	}

	public void setTableState(TABLE_STATE state) {
		this.tableState = state;
	}
	
	public Player[] getPlayers()
	{
		return players;
	}
	
	public Player getPlayerAt(int position) {
		return players[position] ;
	}
		
	public void setSeed(int newSeed) {
		seed = newSeed ;
	}
	
	public int getSeed() {
		return seed ;
	}
	
	public void setType(String newType) {
		type = newType ;
	}
	
	public String getType() {
		return type ;
	}
	
	public void setGame(String newGame) {
		game = newGame ;
	}
	
	public String getGame() {
		return game ;
	}
	
	public void setOptions(String newOptions) {
		options = newOptions ;
	}
	
	public String getOptions() {
		return options ;
	}
	
	public boolean isNos() {
		return nos;
	}

	public void setNos(boolean nos) {
		this.nos = nos;
	}

	public boolean isPink() {
		return pink;
	}

	public void setPink(boolean pink) {
		this.pink = pink;
	}

	public int getTurnTime() {
		return turnTime;
	}

	public void setTurnTime(int turnTime) {
		this.turnTime = turnTime;
	}

	public int getPointsToWin() {
		return pointsToWin;
	}

	public void setPointsToWin(int pointsToWin) {
		this.pointsToWin = pointsToWin;
	}
	
	/**************************************** END GETTERS/SETTERS ****************************************/

	public boolean isFull() {
		return getNumberOfPlayers() >= MAX_PLAYERS ;
	}
	
	/**
	 * Return moderator. Moderator is always at position 0
	 * @author jbodah
	 * @return
	 */
	public Player getModerator() {
		return getPlayerAt(0) ;
	}
	
	/**
	 * Returns true if adding player to table was successful, else returns false
	 * @param player
	 * @return
	 * @author jbodah
	 */
	public boolean addPlayer( Player player ) {
		if( getNumberOfPlayers() < MAX_PLAYERS ) {
			players[getNumberOfPlayers()] = player ;
			player.setTableID(tableID);
			return true ;
		}
		return false ;
	}
	
	/**
	 * Removes player at position from table and shifts the positions of the rest of the players<br/>
	 * Returns removed player or null.
	 * @param position
	 * @return Player
	 * @author jbodah
	 */
	public Player removePlayerAt(int position) {
		if( position > MAX_PLAYERS ) return null ;
		Player removedPlayer = players[position] ;
		while( position < (MAX_PLAYERS - 1)) {
			players[position] = players[position + 1] ;
			players[position + 1] = null ;
			position++ ;
		}
		players[3] = null ;
		if( removedPlayer != null )
			removedPlayer.setTableID(0);
		return removedPlayer ;
	}
	
	/**
	 * Attempts to remove player with login provided. Returns the removed player or null if no player is found.
	 * @param login
	 * @return
	 * @author jbodah
	 */
	public Player removePlayer(int login) {
		for(int i = 0; i < MAX_PLAYERS ; i++) {
			if( getPlayerAt(i) == null )
				break ;
			else if( getPlayerAt(i).getLogin() == login )
				return removePlayerAt(i) ;
		}
		return null ;
	}
	
	/**
	 * Attempts to find player with a given login. Returns the first match or null.
	 * @param login
	 * @return
	 * @author jbodah
	 */
	public Player getPlayer(int login) {
		for(int i = 0 ; i < MAX_PLAYERS ; i++ )
			if( getPlayerAt(i) != null && getPlayerAt(i).getLogin() == login )
				return getPlayerAt(i) ;
		return null ;
	}
	
	/**
	 * Returns number of players at table
	 * @author jbodah
	 */
	public int getNumberOfPlayers() {
		int count = 0 ;
		for(int i = 0 ; i < MAX_PLAYERS ; i++) {
			if( (players == null) || (players[i] == null) )
				break ;
			count++ ;
		}
		return count ;
	}

	/**
	 * Attempts to set user with given login to moderator of table.
	 * Removes new moderator from table and then inserts at head.
	 * Returns new moderator or null if player can't be found.
	 * @param login
	 * @author jbodah
	 */
	public Player setModerator(int login) {
		Player newMod = removePlayer(login) ;
		if( newMod == null )
			return null ;
		insertPlayer(newMod) ;
		return getModerator() ;
	}
	
	/**
	 * Tries to insert given player into head of table.
	 * Returns boolean telling whether or not the transaction was successful.
	 * @author jbodah
	 */
	protected boolean insertPlayer(Player player) {
		if( getNumberOfPlayers() >= MAX_PLAYERS )
			return false ;
		for(int i = MAX_PLAYERS - 1 ; i > 0 ; i--)
			players[i] = players[i-1] ;
		players[0] = player ;
		player.setTableID(tableID);
		return true ;
	}
	
	/**
	 * Reinitializes table.
	 * I don't think this will create memory leaks with old "players" arrays since the
	 * reference is dropped => the array is eligible for garbage collection, but I could be wrong
	 * @author jbodah
	 */
	public void clear() {
		int id = tableID ;
		for(int i = 0 ; i < MAX_PLAYERS ; i++)
			removePlayerAt(i);
		initTable() ;
		tableID = id ;
	}
}
