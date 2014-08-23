package test;

import java.util.Hashtable;
import wordstealclient.entities.Player;
import wordstealclient.entities.Table;
import wordstealclient.entities.Table.TABLE_STATE;

/**
 * 
 * @author cbelhumeur, jbodah
 * 
 */
public class TestData {

	public static Hashtable<Integer, Player> getUsers()
	{
		int maxUsers = 100;
		Hashtable<Integer, Player> players = new Hashtable<Integer, Player>(maxUsers);
		for (int i = 0; i < maxUsers; i++)
		{
			players.put(i, new Player(i, ("Player "+i), 1, 2, 3, 4, 5, 6, 7, 8, 9));
		}
		return players;
	}
	
	/**
	 * Gets a set of tables for test purposes.
	 * @author cbelhumeur
	 * @return
	 */
	public static Table[] getTables()
	{
		int maxTables = 100;
		Table[] tables = new Table[maxTables];
		for (int i = 0; i < maxTables; i++)
		{
			if (i % 17 == 0)
			{
				tables[i] = new Table(i, TABLE_STATE.PRIVATE, new Player[1]);
			}
			else if (i % 7 ==0)
			{
				tables[i] = new Table(i, TABLE_STATE.INGAME, new Player[4]);
			}
			else
			{
				tables[i] = new Table(i, TABLE_STATE.PUBLIC, null);
			}
		}	
		return tables;
	}
	
	/* *************** XML TESTING ******************** */
	
	public static String samplePlayerResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<playerResponse>" +
				"<player player='1213' realName='George Heineman'>" + 
				"<rating category='solitaire' value='229'/>" + 
				"<rating category='wordsteal' value='1234'/>" + 
				"</player>" + 
				"<player player='1456' realName='Bob Smith'>" + 
				"<rating category='sudoku' value='9000'/>" + 
				"<rating category='wordsteal' value='1231'/>" + 
				"</player>" +
				"<player player='100' realName='Bob Dole'>" + 
				"<rating category='solitaire' value='229'/>" + 
				"<rating category='wordsteal' value='1234'/>" + 
				"</player>" +
				"<player player='200' realName='Neil'>" + 
				"<rating category='solitaire' value='229'/>" + 
				"<rating category='wordsteal' value='1234'/>" + 
				"</player>" +
				"<player player='600' realName='A'>" + 
				"<rating category='solitaire' value='229'/>" + 
				"<rating category='wordsteal' value='1234'/>" + 
				"</player>" +
				"<player player='700' realName='B'>" + 
				"<rating category='solitaire' value='229'/>" + 
				"<rating category='wordsteal' value='1234'/>" + 
				"</player>" +
				"<player player='800' realName='C'>" + 
				"<rating category='solitaire' value='229'/>" + 
				"<rating category='wordsteal' value='1234'/>" + 
				"</player>" +
				"<player player='900' realName='D'>" + 
				"<rating category='solitaire' value='229'/>" + 
				"<rating category='wordsteal' value='1234'/>" + 
				"</player>" +
				"<player player='1000' realName='E'>" + 
				"<rating category='solitaire' value='229'/>" + 
				"<rating category='wordsteal' value='1234'/>" + 
				"</player>" +
				"</playerResponse>" + 
				"</response>") ;
	}
	
	public static String sampleConfirmResponseFalse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='false'>" +
				"<confirmResponse table='1' player='1213'/>" +
				"</response>") ;
	}
	
	public static String sampleConfirmResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<confirmResponse table='1' player='1213'/>" +
				"</response>") ;
	}
	
	public static String sampleTableResponseSuccesfulJoin( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<tableResponse>" +
				"<table id='1' seed='12944' type='public' full='false' moderator='1213' game='wordsteal' options='turnTime=30,noS=true,maxScore=50'>" +
				"<player-id player='1213'/>" +
				"</table>" +
				"</tableResponse>" +
				"</response>") ;
	}
	
	public static String sampleTableResponseUnsuccesfulJoin( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<tableResponse>" +
				"<table id='1' seed='12944' type='public' full='false' moderator='1456' game='wordsteal' options='turnTime=30,noS=true,maxScore=50'>" +
				"<player-id player='1456'/>" +
				"</table>" +
				"</tableResponse>" +
				"</response>") ;
	}
	
	public static String sampleGameResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<gameResponse table='1' turn='12995'>" +
				"<gameState player='1213' score='10' game='numWins=5'/>" +
				"<gameState player='1456' score='10'/>" +
				"</gameResponse>" +
				"</response>") ;
	}
	
	public static String sampleGameResponse2( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<gameResponse table='13' turn='12995' move='(5/5)=L,(5/7)=E,(5/6)=I' from='113'>" +
				"<gameState player='85' score='10'/>" +
				"<gameState player='113' score='10' game='numWins=5'/>" +
				"<gameState player='12995' score='0'/>" +
				"</gameResponse>" +
				"</response>") ;
	}
	
	public static String sampleRejectResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<rejectResponse table='1' player='1213'/>" +
				"</response>") ;
	}
	
	public static String sampleTableChatResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<tableChatResponse table='100' player='19834'>" +
				"<text>You are all going DOWN My friend</text>" +
				"</tableChatResponse>" +
				"</response>") ;
	}
	
	public static String sampleTableEmptyResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<tableEmpty table='1'/>" +
				"</response>") ;
	}
	
	public static String sampleTableResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<tableResponse>" +
				"<table id='1' seed='12944' type='public' full='false' moderator='1213' game='wordsteal' options='turnTime=30,noS=true,maxScore=50'>" +
				"<player-id player='1456'/>" +
				"<player-id player='1213'/>" +
				"</table>" +
				"<table id='2' seed='11144' type='private' full='false' moderator='100' game='solitaire' options='undo=true,newHand=true,time=500'>" +
				"<player-id player='100'/>" +
				"</table>" +
				"<table id='3' seed='11144' type='inPlay' full='false' moderator='200' game='solitaire' options='undo=true,newHand=true,time=500'>" +
				"<player-id player='200'/>" +
				"</table>" +
				"<table id='4' seed='11144' type='byInvitation' full='false' moderator='300' game='solitaire' options='undo=true,newHand=true,time=500'>" +
				"<player-id player='300'/>" +
				"</table>" +
				"<table id='5' seed='11144' type='byInvitation' full='false' moderator='300' game='solitaire' options='undo=true,newHand=true,time=500'>" +
				"<player-id player='600'/>" +
				"<player-id player='700'/>" +
				"<player-id player='800'/>" +
				"<player-id player='900'/>" +
				"<player-id player='1000'/>" +
				"</table>" +
				"</tableResponse>" +
				"</response>") ;
	}

	public static String sampleUpdateResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<updateResponse table='100' score='99' game='wins=2,hands=3' finished='true'/>" +
				"</response>") ;
	}
	
	public static String samplePublicChatResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<output from='1213'>" +
				"<text>This is where the message goes</text>" +
				"</output>" +
				"</response>") ;
	}
	
	public static String samplePrivateChatResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<output from='1213' public='false'>" +
				"<text>This is where the (private) message goes</text>" +
				"</output>" +
				"</response>") ;
	}
	
	public static String sampleSystemChatResponse( String id ) {
		return	new String ("<response version='1.0' id='" + id + "' success='true'>" +
				"<output system='true'>" +
				"<text>This Message is generates from the system.</text>" +
				"</output>" +
				"</response>") ;
	}
}
