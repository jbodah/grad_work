package wordstealclient.boundaries;

import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

import wordstealclient.entities.Player;

/**
 * 
 * @author cbelhumeur
 *
 */
public class WSUserPanel extends JPanel {

	protected JLabel alias;
	protected JLabel soWins, soLosses, soRating;
	protected JLabel woWins, woLosses, woRating;
	protected JLabel suWins, suLosses, suRating;
	
	public WSUserPanel()
	{
		super();
		this.setMaximumSize(new Dimension(300, 100));
		this.setLayout(new GridLayout(10, 1, 0, 0));
		add(alias = new JLabel());
		add(soWins = new JLabel());
		add(soLosses = new JLabel());
		add(soRating = new JLabel());
		add(woWins = new JLabel());
		add(woLosses = new JLabel());
		add(woRating = new JLabel());
		add(suWins = new JLabel());
		add(suLosses = new JLabel());
		add(suRating = new JLabel());
	}
	
	public WSUserPanel(Player player)
	{
		super();
		this.setMaximumSize(new Dimension(300, 100));
		this.setLayout(new GridLayout(10, 1, 0, 0));	
		add(alias =    new JLabel("Alias: "             + player.getAlias()));
		add(soWins =   new JLabel("Solitare Wins: "     + player.getSolitaireWins()));
		add(soLosses = new JLabel("Solitare Losses: "   + player.getSolitaireLosses()));
		add(soRating = new JLabel("Solitare Rating: "   + player.getSolitaireRating()));
		add(woWins =   new JLabel("Word Steal Wins: "   + player.getWordstealWins()));
		add(woLosses = new JLabel("Word Steal Losses: " + player.getWordstealLosses()));
		add(woRating = new JLabel("Word Steal Rating: " + player.getWordstealRating()));
		add(suWins =   new JLabel("Sudoku Wins: "       + player.getSudokuWins()));
		add(suLosses = new JLabel("Sudoku Losses: "     + player.getSudokuLosses()));
		add(suRating = new JLabel("Sudoku Rating: "     + player.getSudokuRating()));
	}
	
	public void update(Player player)
	{
		alias.setText(   "Alias: "             + player.getAlias());
		soWins.setText(  "Solitare Wins: "     + player.getSolitaireWins());
		soLosses.setText("Solitare Losses: "   + player.getSolitaireLosses());
		soRating.setText("Solitare Rating: "   + player.getSolitaireRating());
		woWins.setText(  "Word Steal Wins: "   + player.getWordstealWins());
		woLosses.setText("Word Steal Losses: " + player.getWordstealLosses());
		woRating.setText("Word Steal Rating: " + player.getWordstealRating());
		suWins.setText(  "Sudoku Wins: "       + player.getSudokuWins());
		suLosses.setText("Sudoku Losses: "     + player.getSudokuLosses());
		suRating.setText("Sudoku Rating: "     + player.getSudokuRating());
	}
}
