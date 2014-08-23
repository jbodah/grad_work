package wordstealclient.entities;

public class Player {

	protected int 		login ;
	protected String 	alias ;
	protected int 		wordstealRating ;
	protected int 		wordstealWins ;
	protected int 		wordstealLosses ;
	protected int 		solitaireRating ;
	protected int 		solitaireWins ;
	protected int 		solitaireLosses ;
	protected int 		sudokuRating ;
	protected int 		sudokuWins ;
	protected int 		sudokuLosses ;
	protected int		tableID ;
	
	/**
	 *  Constructor
	 *	@author jbodah
	 */
	public Player() {
		this.login = 0 ;
		this.alias = new String() ;
		this.tableID = 0 ;
		this.wordstealRating = 0 ;
		this.wordstealWins = 0 ;
		this.wordstealLosses = 0 ;
		this.solitaireRating = 0 ;
		this.solitaireWins = 0 ;
		this.solitaireLosses = 0 ;
		this.sudokuRating = 0 ;
		this.sudokuWins = 0 ;
		this.sudokuLosses = 0 ;
	}
	
	public Player(int login) {
		this.login = login ;
		this.alias = new String() ;
		this.tableID = 0 ;
		this.wordstealRating = 0 ;
		this.wordstealWins = 0 ;
		this.wordstealLosses = 0 ;
		this.solitaireRating = 0 ;
		this.solitaireWins = 0 ;
		this.solitaireLosses = 0 ;
		this.sudokuRating = 0 ;
		this.sudokuWins = 0 ;
		this.sudokuLosses = 0 ;
	}
	
	public Player(int login, String alias, int rating, int wins, int losses)
	{
		this.login = login ;
		this.alias = alias ;
		this.wordstealRating = rating ;
		this.wordstealWins = wins ;
		this.wordstealLosses = losses ;
	}
	
	public Player(int login, String alias,
				  int woRating, int woWins, int woLosses,
				  int soRating, int soWins, int soLosses,
				  int suRating, int suWins, int suLosses) {
		this.login = login ;
		this.alias = alias ;
		this.wordstealRating = woRating ;
		this.wordstealWins = woWins ;
		this.wordstealLosses = woLosses ;
		this.solitaireRating = soRating ;
		this.solitaireWins = soWins ;
		this.solitaireLosses = soLosses ;
		this.sudokuRating = suRating ;
		this.sudokuWins = suWins ;
		this.sudokuLosses = suLosses ;
	}
	
	/**************************************** BEG GETTERS/SETTERS ****************************************/
	
	public int getLogin() {
		return login;
	}

	public void setLogin(int login) {
		this.login = login;
	}

	public String getAlias() {
		if( alias.equals( "" ) )
			return "User " + getLogin() ;
		return alias;
	}

	public void setAlias(String alias) {
		this.alias = alias;
	}

	public int getWordstealRating() {
		return wordstealRating;
	}

	public void setWordstealRating(int wordstealRating) {
		this.wordstealRating = wordstealRating;
	}

	public int getWordstealWins() {
		return wordstealWins;
	}

	public void setWordstealWins(int wordstealWins) {
		this.wordstealWins = wordstealWins;
	}

	public int getWordstealLosses() {
		return wordstealLosses;
	}

	public void setWordstealLosses(int wordstealLosses) {
		this.wordstealLosses = wordstealLosses;
	}

	public int getSolitaireRating() {
		return solitaireRating;
	}

	public void setSolitaireRating(int solitaireRating) {
		this.solitaireRating = solitaireRating;
	}

	public int getSolitaireWins() {
		return solitaireWins;
	}

	public void setSolitaireWins(int solitaireWins) {
		this.solitaireWins = solitaireWins;
	}

	public int getSolitaireLosses() {
		return solitaireLosses;
	}

	public void setSolitaireLosses(int solitaireLosses) {
		this.solitaireLosses = solitaireLosses;
	}

	public int getSudokuRating() {
		return sudokuRating;
	}

	public void setSudokuRating(int sudokuRating) {
		this.sudokuRating = sudokuRating;
	}

	public int getSudokuWins() {
		return sudokuWins;
	}

	public void setSudokuWins(int sudokuWins) {
		this.sudokuWins = sudokuWins;
	}

	public int getSudokuLosses() {
		return sudokuLosses;
	}

	public void setSudokuLosses(int sudokuLosses) {
		this.sudokuLosses = sudokuLosses;
	}

	/**
	 * tableID = 0 => not at a table
	 * @param table_id
	 */
	public void setTableID( int table_id ) {
		tableID = table_id ;
	}
	
	/**
	 * tableID = 0 => not at a table
	 * @return
	 */
	public int getTableID() {
		return tableID ;
	}
	
	/**************************************** END GETTERS/SETTERS ****************************************/
	
	// TODO: Probably want these in a helper, jbodah 4/10
	/**
	 * Format player info into array for display
	 * @author cbelhumeur
	 * @return
	 */
	public String[] getSplitPlayerInfo()
	{
		return new String[]{getAlias(), Integer.toString(getWordstealRating()), 
				Integer.toString(getWordstealWins()), Integer.toString(getWordstealLosses())};
	}
	
	/**
	 * Format player info for display
	 * @author cbelhumeur
	 * @return
	 */
	public String getPlayerInfo()
	{
		return new String(getAlias() + " - " + Integer.toString(getWordstealRating()) + " (" +
				Integer.toString(getWordstealWins()) + "/" + Integer.toString(getWordstealLosses()) + ")");
	}	
}

