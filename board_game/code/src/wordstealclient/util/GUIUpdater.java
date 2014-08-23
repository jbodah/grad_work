package wordstealclient.util;

import arch.WSClientArchitecture;
import wordstealclient.boundaries.TableManagerGUI;
import wordstealclient.boundaries.UserManagerGUI;
import wordstealclient.entities.Room;
import wordstealclient.entities.Table;
import ks.client.interfaces.ILobby;

/**
 * 
 * @author cbelhumeur, jbodah
 *
 */
public class GUIUpdater {

	/**
	 * Refreshes the user side panel
	 * @param lobby
	 */
	public static void updateUserListGUI(ILobby lobby) {
		if( lobby != null && lobby.getUserManagerGUI() != null) {
			lobby.getUserManagerGUI().removeAll();
			lobby.getUserManagerGUI().add(UserManagerGUI.create(Room.getInstance().getPlayers()));
			lobby.getUserManagerGUI().updateUI();
		}
	}
	
	/**
	 * Intention is to encapsulate the logic for deciding which view we need to display for the current user
	 * @author jbodah
	 */
	public static void updateGUIWithTableOrTables() {
		if( WSClientArchitecture.getThisPlayer() != null && WSClientArchitecture.getThisPlayer().getTableID() != 0 ) {
			Table table = Room.getInstance().getTable(WSClientArchitecture.getThisPlayer().getTableID()) ;
			updateTableGUI(WSClientArchitecture.getLobby(), table);
		}
		else
			updateTableListGUI(WSClientArchitecture.getLobby()) ;
	}
	
	/**
	 * Redraws the room of tables window
	 * @param lobby
	 */
	private static void updateTableListGUI(ILobby lobby) {
		if( lobby != null && lobby.getTableManagerGUI() != null ) {
			lobby.getTableManagerGUI().removeAll();
			lobby.getTableManagerGUI().add(TableManagerGUI.create(Room.getInstance().getTables()));
			lobby.getTableManagerGUI().updateUI();
		}
	}
	
	/**
	 * Redraws a specific table view
	 * @param lobby
	 * @param table
	 */
	private static void updateTableGUI(ILobby lobby, Table table) {
		if( lobby != null && lobby.getTableManagerGUI() != null ) {
			lobby.getTableManagerGUI().removeAll();
			lobby.getTableManagerGUI().add(TableManagerGUI.create(table));
			lobby.getTableManagerGUI().updateUI();
		}
	}
	
	/**
	 * Currently non-functional, but would be here to centralize chat formatting logic
	 * @param isPublic
	 * @param fromSystem
	 * @param sender
	 * @param text
	 * @param lobby
	 */
	public static void updateChatPanel( boolean isPublic, boolean fromSystem, String sender, String text, ILobby lobby ) {
		if( !isPublic )
			writeChat( sender, text, "blue", lobby ) ;
		else if( fromSystem )
			writeSystemChat( text, lobby ) ;
		else
			writeChat( sender, text, "black", lobby ) ;
	}
	
	private static void writeSystemChat(String text, ILobby lobby) {
		writeChat( "SYSTEM", text, "green", lobby ) ;
	}
	
	private static void writeChat( String sender, String text, String color, ILobby lobby ) {
		// TODO: Routine to write text jbodah 4/11
		lobby.append(sender + ": " + text) ;
	}
	
	public static void displayErrorTableFull(ILobby lobby) {
		writeSystemChat("Unable to join table! Table is full!", lobby) ;
	}
}
