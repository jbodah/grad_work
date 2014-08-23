package wordstealclient.boundaries;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JLabel;
import javax.swing.JPanel;

import arch.WSClientArchitecture;

import wordstealclient.controllers.correlated_requests.JoinRequestController;
import wordstealclient.entities.Table;
import wordstealclient.entities.Table.TABLE_STATE;

public class WSTablesPanel extends JPanel {

	protected Table mTable;
	protected int  serial;
	protected JLabel id, state, playerCount;
	private float[] rgbDefault, rgbPublic, rgbPrivate, rgbIngame, rgbByInvitation;
	
	public WSTablesPanel(Table table)
	{
		super();
		mTable = table;
		this.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				if (e.getClickCount() == 2){
					new JoinRequestController(WSClientArchitecture.getLobby()).process(serial);
					System.out.println(" Table selected - " + id.getText());
				}
			}     
		});
		
		setColorScheme();
		this.setLayout(new GridLayout(3, 1, 2, 0));
		this.setBackground(getTableColor(table.getTableState()));
		
		serial = table.getTableID();
		id = new JLabel("Table: " + table.getTableID());
		state = new JLabel("State: " + table.getTableState());
		playerCount = new JLabel("Players: " + table.getNumberOfPlayers() + "/4");
		
		add(id);
		add(state);
		add(playerCount);
	}
	
	private void setColorScheme()
	{
		rgbDefault = Color.RGBtoHSB(200, 200, 200, null); 			// gray
		rgbPublic = Color.RGBtoHSB(147, 185, 241, null);  			// blue
		rgbPrivate = Color.RGBtoHSB(255, 167, 34, null);  			// orange
		rgbIngame = Color.RGBtoHSB(48, 238, 88, null);    			// green
		rgbByInvitation = Color.RGBtoHSB(204, 147, 241, null);    	// purple
	}
	
	private Color getTableColor(TABLE_STATE state)
	{
		if (state == TABLE_STATE.PUBLIC) {return Color.getHSBColor(rgbPublic[0], rgbPublic[1], rgbPublic[2]);}
		else if (state == TABLE_STATE.PRIVATE) {return Color.getHSBColor(rgbPrivate[0], rgbPrivate[1], rgbPrivate[2]);}
		else if (state == TABLE_STATE.INGAME) {return Color.getHSBColor(rgbIngame[0], rgbIngame[1], rgbIngame[2]);}
		else if (state == TABLE_STATE.BYINVITATION) {return Color.getHSBColor(rgbByInvitation[0], rgbByInvitation[1], rgbByInvitation[2]);}
		else {return Color.getHSBColor(rgbDefault[0], rgbDefault[1], rgbDefault[2]);}
	}
	
	public void update(Table table)
	{
		serial = table.getTableID();
		id.setText("Alias: " + table.getTableID());
		state.setText("Rating: " + table.getTableState());
		playerCount.setText("Wins: " + table.getPlayers().length);
	}
}
