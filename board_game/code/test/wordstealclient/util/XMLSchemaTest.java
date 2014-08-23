package wordstealclient.util;

import wordstealclient.entities.Table.TABLE_STATE;
import static org.junit.Assert.*;
import org.junit.*;

public class XMLSchemaTest {
	@Test
	public void testConvertTableState()
	{
		assertTrue( XMLSchema.convertTableState(TABLE_STATE.PUBLIC).equals("public"));
		assertTrue( XMLSchema.convertTableState(TABLE_STATE.PRIVATE).equals("private"));
		assertTrue( XMLSchema.convertTableState(TABLE_STATE.INGAME).equals("inPlay"));
		assertTrue( XMLSchema.convertTableState(TABLE_STATE.BYINVITATION).equals("byInvitation"));
		assertTrue( XMLSchema.convertTableState(TABLE_STATE.UNKNOWN) == null );
	}
}
