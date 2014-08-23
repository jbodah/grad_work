package wordstealclient.boundaries;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

import arch.WSClientArchitecture;

import wordstealclient.controllers.uncorrelated_requests.LeaveRequestController;
import wordstealclient.controllers.uncorrelated_requests.OptionsRequestController;
import wordstealclient.controllers.uncorrelated_requests.StartRequestController;
import wordstealclient.entities.Room;
import wordstealclient.entities.Table;
import wordstealclient.entities.Table.TABLE_STATE;
import wordstealclient.interfaces.IGameProvider;
import wordstealclient.util.GUIHelper;
import wordstealclient.util.GUIUpdater;

/**
 * 
 * @author cbelhumeur
 *
 */
public class WSTablePanel extends JPanel {

	protected Table mTable;
	protected int  serial;
	protected JLabel id, state, playerCount;
	private float[] rgbDefault, rgbPublic, rgbPrivate, rgbIngame;
	private JButton cancel;
	private ImagePanel background;
	protected IGameProvider provider;
	
	private javax.swing.JButton inviteButton;
    private javax.swing.JScrollPane jScrollPane;
    private javax.swing.JButton leaveButton;
    private javax.swing.JLabel mod;
    private javax.swing.JLabel modLabel;
    private javax.swing.JCheckBox nosCheck;
    private javax.swing.JLabel optionsLabel;
    private javax.swing.JCheckBox pinkCheck;
    private javax.swing.JTable playerTable;
    private javax.swing.JLabel playersLabel;
    private javax.swing.JLabel pointsLabel;
    private javax.swing.JTextField pointsText;
    private javax.swing.JButton readyButton;
    private javax.swing.JLabel status;
    private javax.swing.JComboBox statusCombo;
    private javax.swing.JLabel statusLabel;
    private javax.swing.JLabel statusLabel1;
    private javax.swing.JLabel timeLabel;
    private javax.swing.JTextField timeText;
    private javax.swing.JLabel titleLabel;
	
	public WSTablePanel(Table table)
	{
		super();
		mTable = table;
		this.provider = provider;
		
		initComponents();
		initModComponents();
		setColorScheme();
		
		background = new ImagePanel(new ImageIcon("resources/blueWhiteBg.jpg").getImage());
		background.setLayout(new BorderLayout());
		background.setMinimumSize(new Dimension(100,100));
		background.setMaximumSize(new Dimension(100,100));
		add(background);
	}
	
	private void setColorScheme()
	{
		rgbDefault = Color.RGBtoHSB(200, 200, 200, null); // gray
		rgbPublic = Color.RGBtoHSB(147, 185, 241, null);  // blue
		rgbPrivate = Color.RGBtoHSB(255, 167, 34, null);  // orange
		rgbIngame = Color.RGBtoHSB(48, 238, 88, null);    // green
	}
	
	public void update()
	{
		new OptionsRequestController(WSClientArchitecture.getLobby()).process(
				mTable.getTableID(), mTable.getTableState(), mTable.getSeed(), "wordsteal.Wordsteal");
	}
	
	private void readyButtonActionPerformed(java.awt.event.ActionEvent evt) {
		if (verifyOptions())
		{
			new StartRequestController(WSClientArchitecture.getLobby()).process();
		}
    }
	
	private void leaveButtonActionPerformed(java.awt.event.ActionEvent evt) {
		new LeaveRequestController(WSClientArchitecture.getLobby()).process();
		GUIUpdater.updateGUIWithTableOrTables();
    }

    private void inviteButtonActionPerformed(java.awt.event.ActionEvent evt) {
        new WSInviteFrame(Room.getInstance().getPlayers());
    }
    
    private void statusComboActionPerformed(java.awt.event.ActionEvent evt) {
    	mTable.setTableState(GUIHelper.resolveTableStatus(statusCombo.getSelectedItem().toString()));
    	status.setText(mTable.getTableState().toString());
    	update();
    }
    
    private void initModComponents()
    {
    	boolean opt = (WSClientArchitecture.getThisPlayer() == mTable.getModerator());
		nosCheck.setEnabled(opt);
		pinkCheck.setEnabled(opt);
		timeText.setEnabled(opt);
		pointsText.setEnabled(opt);
		statusCombo.setEnabled(opt);
		inviteButton.setEnabled(opt);
		readyButton.setEnabled(opt);
    }
    
    private boolean verifyOptions()
    {
    	if (timeText.getText() == null) {return false;}
    	else if (pointsText.getText() == null) {return false;}
    	else if (timeText.getText().equals("")){return false;}
    	else if (pointsText.getText().equals("")){return false;}
    	else if (!GUIHelper.containsOnlyNumbers(pointsText.getText())) {return false;}
    	else if (!GUIHelper.containsOnlyNumbers(timeText.getText())) {return false;}
    	return true;
    }
    
    private void initComponents() {

        readyButton = new javax.swing.JButton();
        titleLabel = new javax.swing.JLabel();
        statusLabel = new javax.swing.JLabel();
        modLabel = new javax.swing.JLabel();
        playersLabel = new javax.swing.JLabel();
        leaveButton = new javax.swing.JButton();
        jScrollPane = new javax.swing.JScrollPane();
        playerTable = new javax.swing.JTable();
        inviteButton = new javax.swing.JButton();
        status = new javax.swing.JLabel();
        pointsLabel = new javax.swing.JLabel();
        timeLabel = new javax.swing.JLabel();
        pointsText = new javax.swing.JTextField();
        timeText = new javax.swing.JTextField();
        nosCheck = new javax.swing.JCheckBox();
        pinkCheck = new javax.swing.JCheckBox();
        mod = new javax.swing.JLabel();
        statusCombo = new javax.swing.JComboBox();
        optionsLabel = new javax.swing.JLabel();
        statusLabel1 = new javax.swing.JLabel();

        setBackground(new java.awt.Color(137, 182, 227));

        readyButton.setFont(new java.awt.Font("Tahoma", 1, 11)); // NOI18N
        readyButton.setText("Ready!");
        readyButton.setMaximumSize(new java.awt.Dimension(150, 50));
        readyButton.setMinimumSize(new java.awt.Dimension(150, 50));
        readyButton.setPreferredSize(new java.awt.Dimension(150, 50));
        readyButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                readyButtonActionPerformed(evt);
            }
        });

        titleLabel.setFont(new java.awt.Font("Tahoma", 0, 36)); // NOI18N
        titleLabel.setText("WordSteal ");

        statusLabel.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        statusLabel.setText("Table Status: ");

        modLabel.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        modLabel.setText("Moderator:");

        playersLabel.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        playersLabel.setText("Players:");

        leaveButton.setText("Leave Table");
        leaveButton.setMaximumSize(new java.awt.Dimension(150, 50));
        leaveButton.setMinimumSize(new java.awt.Dimension(150, 50));
        leaveButton.setPreferredSize(new java.awt.Dimension(150, 50));
        leaveButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                leaveButtonActionPerformed(evt);
            }
        });

        playerTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null},
                {null, null, null, null}
            },
            new String [] {
                "Title 1", "Title 2", "Title 3", "Title 4"
            }
        ));
        jScrollPane.setViewportView(playerTable);

        inviteButton.setText("Invite Players");
        inviteButton.setMaximumSize(new java.awt.Dimension(150, 50));
        inviteButton.setMinimumSize(new java.awt.Dimension(150, 50));
        inviteButton.setPreferredSize(new java.awt.Dimension(150, 50));
        inviteButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                inviteButtonActionPerformed(evt);
            }
        });

        status.setBackground(new java.awt.Color(255, 255, 255));
        status.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        status.setText("PUBLIC");

        pointsLabel.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        pointsLabel.setText("Points To Win:");

        timeLabel.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        timeLabel.setText("Turn Time:");

        pointsText.setText("30");
        pointsText.setPreferredSize(new Dimension(60, 20));

        timeText.setText("30");
        timeText.setPreferredSize(new Dimension(60, 20));

        nosCheck.setText("No 's'");

        pinkCheck.setText("Pink");

        mod.setBackground(new java.awt.Color(255, 255, 255));
        mod.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N

        optionsLabel.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        optionsLabel.setText("Options:");

        statusLabel1.setFont(new java.awt.Font("Tahoma", 0, 14)); // NOI18N
        statusLabel1.setText("Table Status: ");
        
        statusCombo.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                statusComboActionPerformed(evt);
            }
        });
        
        if (mTable != null) {
	        playerTable.setModel(new javax.swing.table.DefaultTableModel(
	            GUIHelper.formatPlayerInfo(mTable.getPlayers()), GUIHelper.formatColumnHeaders()));
	        statusCombo.setModel(new javax.swing.DefaultComboBoxModel(GUIHelper.formatTableStatuses()));
	        status.setText(mTable.getTableState().toString());
	        titleLabel.setText("WordSteal [#" + mTable.getTableID() + "]");
	        mod.setText(mTable.getModerator().getAlias());
        }
        else {
        	playerTable.setModel(new javax.swing.table.DefaultTableModel(null, GUIHelper.formatColumnHeaders()));
        	statusCombo.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Item 1", "Item 2", "Item 3", "Item 4" }));
        	status.setText(TABLE_STATE.UNKNOWN.toString());
        	titleLabel.setText("WordSteal [#000]");
        	mod.setText("MODERATOR");
        }

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 445, Short.MAX_VALUE)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(statusLabel)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(status))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(modLabel)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                .addComponent(mod))
                            .addComponent(titleLabel))
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(playersLabel)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(10, 10, 10)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                                            .addComponent(pointsLabel)
                                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                            .addComponent(pointsText, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addGroup(layout.createSequentialGroup()
                                            .addComponent(timeLabel)
                                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                            .addComponent(timeText, javax.swing.GroupLayout.PREFERRED_SIZE, 82, javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addGroup(layout.createSequentialGroup()
                                            .addComponent(nosCheck)
                                            .addGap(18, 18, 18)
                                            .addComponent(pinkCheck)))
                                    .addGroup(layout.createSequentialGroup()
                                        .addComponent(statusLabel1)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                        .addComponent(statusCombo, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
                            .addComponent(optionsLabel))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(leaveButton, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(readyButton, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(inviteButton, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(titleLabel)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(statusLabel)
                    .addComponent(status))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(modLabel)
                    .addComponent(mod))
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(26, 26, 26)
                        .addComponent(inviteButton, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(readyButton, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(leaveButton, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(18, 18, 18)
                        .addComponent(optionsLabel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(statusLabel1)
                            .addComponent(statusCombo, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(7, 7, 7)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(pointsLabel)
                            .addComponent(pointsText, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(timeLabel)
                            .addComponent(timeText, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(nosCheck)
                            .addComponent(pinkCheck))
                        .addGap(15, 15, 15)
                        .addComponent(playersLabel)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 94, Short.MAX_VALUE)
                .addContainerGap())
        );
    }
}
