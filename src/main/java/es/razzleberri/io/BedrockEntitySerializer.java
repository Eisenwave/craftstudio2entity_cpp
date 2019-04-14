package es.razzleberri.io;

import com.google.gson.*;
import es.razzleberri.*;
import es.razzleberri.util.*;

import java.io.*;
import java.util.Map;

public class BedrockEntitySerializer implements TextSerializer<BedrockEntityModel> {
    
    private final static String FORMAT_VERSION = "1.8.0";
    
    @Override
    public void toWriter(BedrockEntityModel model, Writer writer) throws IOException {
        JsonObject root = new JsonObject();
        root.addProperty("format_version", FORMAT_VERSION);
        
        for (Map.Entry<String, BedrockEntityGeometry> entry : model.getGeometryEntries())
            root.add(entry.getKey(), serializeGeometry(entry.getValue()));
    
        Gson gson = new GsonBuilder().setPrettyPrinting().create();
        try {
            gson.toJson(root, writer);
        } catch (JsonIOException ex) {
            throw new IOException(ex);
        }
    }
    
    private static JsonObject serializeGeometry(BedrockEntityGeometry geometry) {
        JsonObject json = new JsonObject();
        
        Vec2i visibleBounds = geometry.getVisibleBounds();
        json.addProperty("visible_bounds_width", visibleBounds.getX());
        json.addProperty("visible_bounds_height", visibleBounds.getY());
        
        json.add("visible_bounds_offset", serializeVec3d(geometry.getVisibleBoundsOffset()));
        
        Vec2i textureSize = geometry.getTextureSize();
        json.addProperty("texturewidth", textureSize.getX());
        json.addProperty("textureheight", textureSize.getY());
        
        JsonArray jsonBones = new JsonArray(geometry.size());
        for (BedrockEntityBone bone : geometry)
            jsonBones.add(serializeBone(bone));
        json.add("bones", jsonBones);
        
        return json;
    }
    
    private static JsonObject serializeBone(BedrockEntityBone bone) {
        JsonObject json = new JsonObject();
        json.addProperty("name", bone.getName());
        if (bone.hasParent())
            json.addProperty("parent", bone.getParent());
        if (bone.hasPivot()) {
            assert bone.getPivot() != null;
            json.add("pivot", serializeVec3d(bone.getPivot()));
        }
        if (bone.hasRotation()) {
            if (!bone.hasPivot())
                System.err.println("WARNING: Bone \"" + bone.getName() + "\" has a rotation but no pivot");
            assert bone.getRotation() != null;
            json.add("rotation", serializeVec3d(bone.getRotation()));
        }
        
        JsonArray jsonCubes = new JsonArray();
        for (BedrockEntityCube cube : bone)
            jsonCubes.add(serializeCube(cube));
        json.add("cubes", jsonCubes);
        
        return json;
    }
    
    private static JsonObject serializeCube(BedrockEntityCube cube) {
        JsonObject json = new JsonObject();
        json.add("origin", serializeVec3d(cube.getOrigin()));
        json.add("size", serializeVec3i(cube.getSize()));
        json.add("uv", serializeVec2i(cube.getUv()));
        return json;
    }
    
    @SuppressWarnings("Duplicates")
    private static JsonArray serializeVec3d(Vec3 v) {
        JsonArray json = new JsonArray(3);
        json.add(new JsonPrimitive(v.getX()));
        json.add(new JsonPrimitive(v.getY()));
        json.add(new JsonPrimitive(v.getZ()));
        return json;
    }
    
    @SuppressWarnings("Duplicates")
    private static JsonArray serializeVec3i(Vec3i v) {
        JsonArray json = new JsonArray(3);
        json.add(new JsonPrimitive(v.getX()));
        json.add(new JsonPrimitive(v.getY()));
        json.add(new JsonPrimitive(v.getZ()));
        return json;
    }
    
    private static JsonArray serializeVec2i(Vec2i v) {
        JsonArray json = new JsonArray(2);
        json.add(new JsonPrimitive(v.getX()));
        json.add(new JsonPrimitive(v.getY()));
        return json;
    }
    
}
