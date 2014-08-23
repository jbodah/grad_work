package wordstealclient.boundaries;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JPanel;

import wordstealclient.entities.Table;

/**
 * @author cbelhumeur
 * @return
 */
public class TableManagerGUI {
	
	public static JPanel create(Table[] tables) {
		JPanel tempTableManagerGUI = new JPanel();
		tempTableManagerGUI.setLayout(new GridLayout(10, 4, 4, 4));
			
		if (tables != null)
		{
			List<WSTablesPanel> pTables = createTables(tables);
			for (WSTablesPanel table : pTables)
			{
				tempTableManagerGUI.add(table, Component.LEFT_ALIGNMENT);
			}	
		}
		return tempTableManagerGUI;
	}
	
	public static JPanel create(Table table) {
		JPanel tempTableManagerGUI = new JPanel();
		tempTableManagerGUI.setLayout(new BorderLayout());
		
		WSTablePanel wstp = new WSTablePanel(table);
		tempTableManagerGUI.add(wstp);
		return tempTableManagerGUI;
	}

	/**
	 * @author cbelhumeur
	 * @return
	 */
	private static List<WSTablesPanel> createTables(Table[] tables)
	{
		List<WSTablesPanel> jTables = new ArrayList<WSTablesPanel>();
		
		for (Table table : tables)
		{
			WSTablesPanel panel = new WSTablesPanel(table);
			jTables.add(panel);
		}	
		return jTables;
	}
}
