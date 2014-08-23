package arch;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Properties;

import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;

import ks.client.game.GameManager;
import ks.client.interfaces.IGameInterface;
import ks.client.interfaces.ILobby;
import ks.client.interfaces.ILobbyInitialize;
import ks.client.lobby.LobbyFrame;
import wordstealclient.controllers.correlated_requests.*;
import wordstealclient.entities.Player;
import wordstealclient.entities.Table;
import wordstealclient.interfaces.IGameProvider;

/**
 * My sample shows how to integrate the client code with the GameManager I am
 * providing.
 * 
 * Note: Don't edit this class here. Rather copy this sample code into your
 * own project and (1) rename it; and (2) modify as you need
 * 
 * @author George Heineman, cbelhumeur
 */
public class MyLobbyInitialization implements ILobbyInitialize, IGameInterface, IGameProvider {
	
	/** Panels. */
	JPanel tmgui;
	JPanel umgui;
	
	/** Enclosing lobby. */
	static ILobby lobby;
	
	public MyLobbyInitialization (JPanel tm, JPanel um) {
		this.tmgui = tm;
		this.umgui = um;
	}
	
	public ILobby getLobby()
	{
		return lobby;
	}
	
	// How to launch a game? (From the button click, controller to use? how to get MLI to respond accordingly)
	// Which controllers are necessary for game management? (skip, turn, start, won[in xml], etc.)
	// How to get moderator parameters, then pass along prior to game start?
	//
	// Switch between table and room view? (through controllers, during button clicks)
	//
	//
	public void startGame(Table table)
	{
		// Launch wordsteal
		GameManager gm = GameManager.instance();
		Properties options = new Properties();
		
		// Default game options
		options.setProperty("seed", ""+table.getSeed());
		options.setProperty("game", "wordsteal.Wordsteal");
	
		// Wordsteal game options
		Properties gameOptions = new Properties();
		gameOptions.setProperty("noS", ""+table.isNos());
		gameOptions.setProperty("pink", ""+table.isPink());
		gameOptions.setProperty("turnTime", ""+table.getTurnTime());
		gameOptions.setProperty("pointsToWin", ""+table.getPointsToWin());
		
		// Players to add in game
		Properties players = new Properties();
		ArrayList<String> order = new ArrayList<String>();
		for (int i = 0; i < table.getPlayers().length; i++)
		{
			Player p = table.getPlayerAt(i);
			if (p != null) {
				players.setProperty(""+p.getLogin(), p.getAlias());
				order.add(""+p.getLogin());
			}
		}
		
		// request creation of game window. Will start in locked mode.
		gm.createGameWindow(table.getTableID(), ""+lobby.getContext().getUser(), options, gameOptions, order, players, MyLobbyInitialization.this);
		
		// go ahead and activate this person's turn (presumably as moderator).
		gm.activateTurn(Integer.toString(table.getModerator().getLogin()));
		//gm.skipTurn("982");
	}
	
	@Override
	public void initializeLobby(final LobbyFrame frame) {
		// remember this lobby for later use
		this.lobby = frame;
		
		// install the two manager GUIs and callback
		frame.setUserManagerGUI(umgui);
		frame.setTableManagerGUI(tmgui);
		frame.setLobbyInitialization(this);
		
		// callback object will likely need to know about things.
		frame.getContext();
		
		// grab the menu bar and make an update 
		JMenuBar menu = frame.getJMenuBar();
		JMenu help = new JMenu("Debug");
		
		addMenuItemsForControllers(help);	
		
		menu.add(help);
	}

	/**
	 * Debug menu items for controllers
	 * @author jbodah
	 * @param menu
	 */
	private void addMenuItemsForControllers(JMenu menu) {
		JMenuItem item ;
		
		/*
		// ban request
		item = new JMenuItem("generate 'ban' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new BanRequestController(lobby).process() ;
			}
		});
		menu.add(item);
				
		// chat request
		item = new JMenuItem("generate 'chat' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new ChatRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		// confirm request
		item = new JMenuItem("generate 'confirm' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new ConfirmRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		// getProfile request
		item = new JMenuItem("generate 'getProfile' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new GetProfileRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		// invite request
		item = new JMenuItem("generate 'invite' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new InviteRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		// join request
		item = new JMenuItem("generate 'join' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new JoinRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		// leave request
		item = new JMenuItem("generate 'leave' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new LeaveRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		// options request
		item = new JMenuItem("generate 'options' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new OptionsRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		// playerInfo request
		item = new JMenuItem("generate 'playerInfo' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new PlayerInfoRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		*/
		
		// players request
		item = new JMenuItem("generate 'players' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new PlayersRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		/*
		// start request
		item = new JMenuItem("generate 'start' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new StartRequestController(lobby).process() ;
			}
		});
		menu.add(item);		
		
		// tableChat request
		item = new JMenuItem("generate 'tableChat' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new TableChatRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		*/
		
		// tables request
		item = new JMenuItem("generate 'tables' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new TablesRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		/*
		// turn request
		item = new JMenuItem("generate 'turn' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new TurnRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		// unregister request
		item = new JMenuItem("generate 'unregister' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new UnregisterRequestController(lobby).process() ;
			}
		});
		menu.add(item);
		
		// updaterequest
		item = new JMenuItem("generate 'update' request");
		item.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				new UpdateRequestController(lobby).process() ;
			}
		});
		menu.add(item);
	*/
	}

	@Override
	public void sendTableChat(int tableID, String text) {
		System.err.println("Table Chat request:" + text);	
		System.err.println("Do something about it!");
	}

	@Override
	public void update(int tableID, int score, String game, boolean complete) {
		System.err.println("Update request:" + score + ", complete=" + complete);
		System.err.println("Do something about it!");
	}

	@Override
	public void leaveGame(int tableID) {
		System.err.println("Player leaves table " + tableID);
		System.err.println("Do something about it!");
	}

	@Override
	public void turn(int tableID, Properties scores, String move, boolean complete) {
		System.err.println("Player makes move, complete=" + complete);
		System.err.println("Move:" + move);
		for (Object p : scores.keySet()) {
			String value = scores.getProperty((String)p);
			System.err.println("player " + p + ", score=" + value);
		}
		System.err.println("Do something about it!");
	}

	@Override
	public void skip(int tableNumber) {
		System.err.println("Player has skipped on table " + tableNumber);
		System.err.println("Do something about it!");
	}

	@Override
	public void connected(boolean status) {
		if (!status) {
			lobby.append("Server connection lost");
		} else {
			lobby.append("My Initializer welcomes you");
			new PlayersRequestController(lobby).process() ;
			new TablesRequestController(lobby).process() ;
		}
		
	}
}
