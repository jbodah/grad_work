package wordstealclient.util;

import wordstealclient.entities.Table.TABLE_STATE;
import ks.framework.common.Configure;

public class XMLSchema {
	/**
	 * Determine the XML schema we are going to use
	 */
	public static boolean foundValid() {
		if (!Configure.configure()) {
			System.err.println("Unable to configure Message XML");
			return false;
		}
		return true;
	}
	
	/**
	 * Convert table state to appropriate XML
	 * @param state
	 * @return
	 */
	public static String convertTableState(TABLE_STATE state)
	{
		if (state.equals(TABLE_STATE.PUBLIC)) { return "public"; }
		else if (state.equals(TABLE_STATE.PRIVATE)) { return "private"; }
		else if (state.equals(TABLE_STATE.INGAME)) { return "inPlay"; }
		else if (state.equals(TABLE_STATE.BYINVITATION)) { return "byInvitation"; }
		return null;
	}
}
