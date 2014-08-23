package wordstealclient.boundaries;

import java.awt.Color;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;

import wordstealclient.entities.Player;
import wordstealclient.util.GUIHelper;

/**
 * @author: cbelhumeur
 */
public class WSUsersTable extends JTable {

	protected WSUserPanel userInfo;
	protected static int selectedColumn;
	
	public WSUsersTable(final Player[] players, WSUserPanel panel)
	{
		super();
		
		String[][] info = GUIHelper.formatPlayerInfo(players);
		DefaultTableModel model = new DefaultTableModel(info, GUIHelper.formatColumnHeaders());
		this.setModel(model);
		
		this.userInfo = panel;	
		this.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		this.getColumnModel().getColumn(0).setPreferredWidth(150);
		this.getColumnModel().getColumn(1).setPreferredWidth(50);
		this.getColumnModel().getColumn(2).setPreferredWidth(50);
		this.getColumnModel().getColumn(3).setPreferredWidth(50);
		this.setCellSelectionEnabled(false);
		
		this.addMouseListener(new MouseAdapter(){
			public void mouseClicked(MouseEvent e){
				if (e.getClickCount() == 2){
					userInfo.update(players[selectedColumn]);
					System.out.println(" User selected - " + selectedColumn);
				}
			}     
		});
		
		JTableHeader header = this.getTableHeader();
		header.setBackground(Color.LIGHT_GRAY);
	}
	
	@Override 
	public boolean isCellEditable(int row, int column) 
	{
		return false;
	}
	
	@Override 
	public void valueChanged(ListSelectionEvent e)
	{
		selectedColumn = getSelectedRow();
	}
}
