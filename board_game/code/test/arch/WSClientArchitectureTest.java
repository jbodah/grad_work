package arch;

import org.junit.*;
import static org.junit.Assert.*;

public class WSClientArchitectureTest {
	@Test
	public void testClient() {
		try {
			WSClientArchitecture.main(new String[]{});
			assertTrue (WSClientArchitecture.cf != null);
			
			assertTrue(WSClientArchitecture.cf.isVisible());
			
			// close it down
			WSClientArchitecture.cf.setVisible(false);
			WSClientArchitecture.cf.dispose();
			
		} catch (Exception e) {
			fail (e.getMessage());
		}	
	}
}
