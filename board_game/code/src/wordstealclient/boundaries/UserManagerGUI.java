package wordstealclient.boundaries;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.util.Collection;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

import wordstealclient.entities.Player;

public class UserManagerGUI {
	
	protected static JLabel userDetails;
	protected static WSUsersTable usersTable;
	protected static WSUserPanel userPanel;
	
	/**
	 * @author cbelhumeur
	 * @return
	 */
	public static JPanel create(Collection<Player> players) {
		JPanel tempUserManagerGUI = new JPanel();
		tempUserManagerGUI.setLayout(new BorderLayout());
		//tempUserManagerGUI.setMaximumSize(new Dimension(220, 600));
		
		userPanel = new WSUserPanel();
		if (players != null)
		{
			usersTable = new WSUsersTable(players.toArray(new Player[players.size()]), userPanel);	
		}
		else 
		{
			usersTable = new WSUsersTable(new Player[0], userPanel);
		}
		usersTable.setMaximumSize(new Dimension(200, 600));
		JScrollPane pane = new JScrollPane(usersTable);
		tempUserManagerGUI.add(pane, BorderLayout.PAGE_START);		
		tempUserManagerGUI.add(userPanel, BorderLayout.LINE_START);
		return tempUserManagerGUI;
	}
}
