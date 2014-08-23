package wordstealclient.controllers.uncorrelated_requests;

import wordstealclient.entities.Table.TABLE_STATE;
import wordstealclient.util.XMLSchema;
import ks.client.interfaces.IController;
import ks.client.interfaces.ILobby;
import ks.framework.common.Message;

/**
 * Request: options<br/>
 * Initiated by client<br/>
 * Expects correlated response: ??<br/> 
 * <br/>
 * 
 * @example
 * 	{@literal <!-- Set the options for the given table; more options are available than just here (see ks.xsd) -->}<br/>
 * 	{@literal <request version="1.0" id="589a39591271844e3fbe32bbb9281ad9">}<br/>
 * 	{@literal <options table="100" game="solitaire/Klondike"/>}<br/>
 * 	{@literal </request>}
 * 
 * <xs:element name="options">
 * <xs:complexType>
 * <xs:attribute name="table" type="table-id" use="required" /> 
 * <xs:attribute name="options" type="options-string" use="optional" /> 
 * <xs:attribute name="seed" type="xs:integer" use="optional" /> 
 * <xs:attribute name="game" type="xs:string" use="optional" /> 
 * <xs:attribute name="type" type="tableChoice" default="private" /> 
 * </xs:complexType>
 * </xs:element>
 *
 *  
 * @author cbelhumeur
 */
public class OptionsRequestController implements IController {
	ILobby lobby ;
	
	public OptionsRequestController(ILobby lobby) {
		this.lobby = lobby;
	}
	
	/**
	 * Create and send request
	 * @author cbelhumeur
	 */
	public void process(int tableID, TABLE_STATE state, int seed, String game) {
		Message m = new Message(Message.construct (writeXMLForRequest(tableID, state, seed, game)));
		lobby.getContext().getClient().sendToServer(lobby, m, this);
		System.out.println("OptionsRequestController.process(): Request sent");
	}
	
	private String writeXMLForRequest(int tableID, TABLE_STATE state, int seed, String game) {
		String s = Message.requestHeader() +
				"<options table='" + tableID + "' " +
						 "seed='" + seed + "' " +
						 "game='" + game + "' " +
						 "type='" + XMLSchema.convertTableState(state) + "'/></request>" ;
		return s;
	}

	@Override
	public void process(ILobby lobby, Message request, Message response) {
		// TODO Auto-generated method stub
		
	}
}
