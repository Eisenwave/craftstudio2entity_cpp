package es.razzleberri.io;

import com.google.gson.*;
import es.razzleberri.*;
import es.razzleberri.util.*;
import org.jetbrains.annotations.NotNull;

import java.io.*;

public class CraftStudioDeserializer implements TextDeserializer<CraftStudioModel> {
    
    @NotNull
    @Override
    public CraftStudioModel fromReader(Reader reader) throws IOException {
        JsonObject root;
        try {
            root = new JsonParser().parse(reader).getAsJsonObject();
        } catch (JsonParseException ex) {
            throw new IOException(ex);
        }
        
        String title = root.get("title").getAsString();
        JsonArray tree = root.get("tree").getAsJsonArray();
        
        CraftStudioBlock[] blocks = new CraftStudioBlock[tree.size()];
        int index = 0;
        for (JsonElement blockElement : tree) {
            JsonObject block = blockElement.getAsJsonObject();
            blocks[index++] = parseBlock(block);
        }
        
        CraftStudioModel model = new CraftStudioModel(title);
        for (CraftStudioBlock block : blocks)
            model.addBlock(block);
        
        return model;
    }
    
    private static CraftStudioBlock parseBlock(JsonObject json) throws IOException {
        String name = json.get("name").getAsString();
        Vec3 position = parseVec3d(json.getAsJsonArray("position"));
        Vec3 offsetFromPivot = parseVec3d(json.getAsJsonArray("offsetFromPivot"));
        Vec3i size = parseVec3i(json.getAsJsonArray("size"));
        Vec3 rotation = parseVec3d(json.getAsJsonArray("rotation"));
        Vec2i texOffset = parseVec2i(json.getAsJsonArray("texOffset"));
        
        JsonArray jsonChildren = json.getAsJsonArray("children");
        CraftStudioBlock block = new CraftStudioBlock(name, position, offsetFromPivot, size, rotation, texOffset);
        
        for (JsonElement childElement : jsonChildren) {
            CraftStudioBlock child = parseBlock(childElement.getAsJsonObject());
            block.addChild(child);
        }
        
        if (json.has("vertexCoords"))
            System.err.println("WARNING: Cube \"" + name + "\" has stretch which must be ignored.");
        
        return block;
    }
    
    private static Vec3 parseVec3d(JsonArray json) throws IOException {
        if (json.size() != 3)
            throw new IOException("vec3d must be 3 elements long");
        return new Vec3(
            json.get(0).getAsDouble(),
            json.get(1).getAsDouble(),
            json.get(2).getAsDouble()
        );
    }
    
    private static Vec3i parseVec3i(JsonArray json) throws IOException {
        if (json.size() != 3)
            throw new IOException("vec3i must be 3 elements long");
        return new Vec3i(
            json.get(0).getAsInt(),
            json.get(1).getAsInt(),
            json.get(2).getAsInt()
        );
    }
    
    private static Vec2i parseVec2i(JsonArray json) throws IOException {
        if (json.size() != 2)
            throw new IOException("vec2i must be 2 elements long");
        return new Vec2i(
            json.get(0).getAsInt(),
            json.get(1).getAsInt()
        );
    }
    
}
