package es.razzleberri.io;

import es.razzleberri.CraftStudioModel;
import org.junit.Test;

import java.io.IOException;
import java.io.InputStream;

import static org.junit.Assert.*;

public class CraftStudioDeserializerTest {
    
    @Test
    public void testDeserializeTestModel() throws IOException {
        try (InputStream stream = getClass().getClassLoader().getResourceAsStream("model.csjsmodel")) {
            CraftStudioModel model = new CraftStudioDeserializer().fromStream(stream);
            
            assertEquals("geometry.test", model.getTitle());
            assertEquals(8, model.size());
        }
    }
    
}
