package wordstealclient.util;

import java.util.ArrayList;
import java.util.List;

import arch.WSClientArchitecture;

import wordstealclient.entities.Player;
import wordstealclient.entities.Table;
import wordstealclient.entities.Table.TABLE_STATE;

/**
 * 
 * @author cbelhumeur
 *
 */
public class GUIHelper {

	public static String[][] formatPlayerInfo(Player[] players)
	{
		List<String[]> list = new ArrayList<String[]>();
		for (Player p : players)
		{
			if (p != null){list.add(p.getSplitPlayerInfo());}
		}
		return list.toArray(new String[players.length][]);
	}
	
	public static String[] formatColumnHeaders()
	{
		return new String[]{"Alias", "Rating", "Wins", "Losses"};
	}
	
	public static String[] formatTableStatuses()
	{
		String[] statuses = new String[3];
		statuses[0] = Table.TABLE_STATE.PUBLIC.toString();
		statuses[1] = Table.TABLE_STATE.PRIVATE.toString();
		statuses[2] = Table.TABLE_STATE.BYINVITATION.toString();
		return statuses;
	}
	
	public static TABLE_STATE resolveTableStatus(String status)
	{
		if (TABLE_STATE.PUBLIC.toString().equals(status)) {return TABLE_STATE.PUBLIC;}
		else if (TABLE_STATE.PRIVATE.toString().equals(status)) {return TABLE_STATE.PRIVATE;}
		else if (TABLE_STATE.INGAME.toString().equals(status)) {return TABLE_STATE.INGAME;}
		else if (TABLE_STATE.BYINVITATION.toString().equals(status)) {return TABLE_STATE.BYINVITATION;}
		return TABLE_STATE.UNKNOWN;
	}
	
	public static String[] formatPlayerList(Player[] players)
	{
		String[] list = new String[players.length];
		for (int i = 0; i < players.length; i++)
		{
			list[i] = players[i].getAlias();
		}
		return list;
	}
	
	public static String[] formatPlayerListWithoutMe(Player[] players)
	{
		String[] list = new String[players.length];
		for (int i = 0; i < players.length; i++)
		{
			if (players[i] != WSClientArchitecture.getThisPlayer())
				list[i] = players[i].getAlias();
		}
		return list;
	}
	
	public static boolean containsOnlyNumbers(String str) {
        
        //It can't contain only numbers if it's null or empty...
        if (str == null || str.length() == 0)
            return false;
        
        for (int i = 0; i < str.length(); i++) {

            //If we find a non-digit character we return false.
            if (!Character.isDigit(str.charAt(i)))
                return false;
        }
        
        return true;
    }

	public static boolean containsOnlyLetters(String str) {
        
        //It can't contain only numbers if it's null or empty...
        if (str == null || str.length() == 0)
            return false;
        
        for (int i = 0; i < str.length(); i++) {

            //If we find a non-digit character we return false.
            if (!Character.isLetter(str.charAt(i)))
                return false;
        }
        
        return true;
    }


}
