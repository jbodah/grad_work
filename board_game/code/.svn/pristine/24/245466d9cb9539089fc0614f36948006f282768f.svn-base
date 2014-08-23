package wordstealclient.boundaries;

import java.util.Collection;

import javax.swing.JDialog;
import javax.swing.JFrame;

import arch.WSClientArchitecture;

import wordstealclient.controllers.uncorrelated_requests.InviteRequestController;
import wordstealclient.entities.Player;
import wordstealclient.entities.Room;
import wordstealclient.entities.Table;
import wordstealclient.util.GUIHelper;

public class WSInviteFrame extends JFrame {

	private javax.swing.JLabel headerLabel;
    private javax.swing.JButton inviteButton;
    private javax.swing.JScrollPane jScrollPane;
    private javax.swing.JLabel noteLabel;
    private javax.swing.JList playerList;
    private javax.swing.JPanel newPanel;
    private Player[] players;
    private JDialog dialog;
	
	public WSInviteFrame(Collection<Player> players)
	{
		super();
		
		
		this.players = players.toArray(new Player[players.size()]);
		initComponents();
		
		dialog = new JDialog(new JFrame(), "Invitations", true);  
	    dialog.getContentPane().add(newPanel);
	    dialog.pack();
	    dialog.setLocationRelativeTo(null);
	    dialog.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	    dialog.setVisible(true);
	}
	
	private void inviteButtonActionPerformed(java.awt.event.ActionEvent evt) {
		// TODO: actions regarding inviting players
		Object[] list = playerList.getSelectedValues();
		Player[] selectedPlayers = new Player[list.length];
		for (int i = 0; i < list.length; i++)
		{
			for (int j = 0; j < players.length; j++)
			{
				// Match the lists and make sure the player is not us
				if (list[i].equals(players[j].getAlias())/* && (list[i] != WSClientArchitecture.getThisPlayer())*/)
				{
					selectedPlayers[i] = players[j];
					break;
				}
			}
		}
		
		Table table = Room.getInstance().getTable(WSClientArchitecture.getThisPlayer().getTableID());
		for (int i = 0; i < selectedPlayers.length; i++)
		{
			new InviteRequestController(WSClientArchitecture.getLobby()).process(table.getTableID(), selectedPlayers[i].getLogin());
		}
		dialog.dispose();
    }
	
	private void initComponents() {

        newPanel = new javax.swing.JPanel();
        noteLabel = new javax.swing.JLabel();
        jScrollPane = new javax.swing.JScrollPane();
        playerList = new javax.swing.JList();
        headerLabel = new javax.swing.JLabel();
        inviteButton = new javax.swing.JButton();

        noteLabel.setText("<html>NOTE: You may only invite as many players as vacant spots. Exceeeding requests in descending alphabetical order will be ignored.</html>");
        noteLabel.setPreferredSize(new java.awt.Dimension(300, 14));

        playerList.setModel(new javax.swing.AbstractListModel() {
        	String[] strings = GUIHelper.formatPlayerListWithoutMe(players);
            public int getSize() { return strings.length; }
            public Object getElementAt(int i) { return strings[i]; }
        });
        playerList.setDragEnabled(true);
        jScrollPane.setViewportView(playerList);

        headerLabel.setText("Select players to invite:");

        inviteButton.setText("Invite");
        inviteButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                inviteButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout newPanelLayout = new javax.swing.GroupLayout(newPanel);
        newPanel.setLayout(newPanelLayout);
        newPanelLayout.setHorizontalGroup(
            newPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(newPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(newPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(newPanelLayout.createSequentialGroup()
                        .addGroup(newPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(headerLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jScrollPane)
                            .addComponent(noteLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 113, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, newPanelLayout.createSequentialGroup()
                        .addGap(0, 0, Short.MAX_VALUE)
                        .addComponent(inviteButton)))
                .addContainerGap())
        );
        newPanelLayout.setVerticalGroup(
            newPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(newPanelLayout.createSequentialGroup()
                .addContainerGap()
                .addComponent(headerLabel)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(noteLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 126, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(inviteButton)
                .addContainerGap())
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(newPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(newPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
    }
}
