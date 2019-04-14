package es.razzleberri;

import es.razzleberri.util.Vec3;
import org.jetbrains.annotations.*;

import java.util.*;

public class BedrockEntityBone implements Iterable<BedrockEntityCube> {
    
    @NotNull
    private final String name;
    @Nullable
    private final String parent;
    @Nullable
    private final Vec3 pivot;
    @Nullable
    private final Vec3 rotation;
    
    private final List<BedrockEntityCube> cubes = new ArrayList<>(2);
    
    public BedrockEntityBone(@NotNull String name,
                             @Nullable String parent,
                             @Nullable Vec3 pivot,
                             @Nullable Vec3 rotation) {
        this.name = name;
        this.parent = parent;
        this.pivot = pivot;
        this.rotation = rotation;
    }
    
    @NotNull
    public String getName() {
        return name;
    }
    
    @Nullable
    public String getParent() {
        return parent;
    }
    
    public boolean hasParent() {
        return parent != null;
    }
    
    @Nullable
    public Vec3 getPivot() {
        return pivot;
    }
    
    public boolean hasPivot() {
        return pivot != null;
    }
    
    @Nullable
    public Vec3 getRotation() {
        return rotation;
    }
    
    public boolean hasRotation() {
        return rotation != null;
    }
    
    public void addCube(@NotNull BedrockEntityCube cube) {
        this.cubes.add(cube);
    }
    
    public List<BedrockEntityCube> getCubes() {
        return Collections.unmodifiableList(cubes);
    }
    
    public int size() {
        return cubes.size();
    }
    
    @NotNull
    @Override
    public Iterator<BedrockEntityCube> iterator() {
        return cubes.iterator();
    }
    
}
