package es.razzleberri;

import org.jetbrains.annotations.NotNull;

import java.util.*;

public class BedrockEntityModel implements Iterable<BedrockEntityGeometry> {

    private final Map<String, BedrockEntityGeometry> geometries = new LinkedHashMap<>(4);
    
    public BedrockEntityGeometry getGeometry(String name) {
        return geometries.get(name);
    }
    
    public Set<Map.Entry<String, BedrockEntityGeometry>> getGeometryEntries() {
        return geometries.entrySet();
    }
    
    public void putGeometry(@NotNull String name, @NotNull BedrockEntityGeometry geometry) {
        geometries.put(name, geometry);
    }
    
    public void clear() {
        geometries.clear();
    }
    
    @NotNull
    @Override
    public Iterator<BedrockEntityGeometry> iterator() {
        return geometries.values().iterator();
    }
    
}
