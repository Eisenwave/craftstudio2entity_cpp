package es.razzleberri.io;

import es.razzleberri.BedrockEntityBone;
import es.razzleberri.BedrockEntityCube;
import es.razzleberri.BedrockEntityGeometry;
import es.razzleberri.BedrockEntityModel;
import es.razzleberri.util.Vec2i;
import es.razzleberri.util.Vec3;
import es.razzleberri.util.Vec3i;
import org.junit.Test;

import java.io.IOException;

import static org.junit.Assert.*;

public class BedrockEntitySerializerTest {
    
    @Test
    public void toWriter() throws IOException {
        BedrockEntityModel model = new BedrockEntityModel();
        BedrockEntityGeometry geometry = new BedrockEntityGeometry(
            new Vec2i(1, 2),
            new Vec3(0, 0.75, 0),
            new Vec2i(64, 32)
        );
    
        BedrockEntityBone body = new BedrockEntityBone("body", null, null, null);
        body.addCube(new BedrockEntityCube(new Vec3(0, 0, 0), new Vec3i(16, 16, 16), new Vec2i(16, 16)));
        geometry.addBone(body);
        
        model.putGeometry("geometry.test", geometry);
        
        new BedrockEntitySerializer().toStream(model, System.out);
    }
}
