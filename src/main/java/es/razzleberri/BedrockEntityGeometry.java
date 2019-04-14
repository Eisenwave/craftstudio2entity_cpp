package es.razzleberri;

import es.razzleberri.util.*;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.*;

public class BedrockEntityGeometry implements Iterable<BedrockEntityBone> {
    
    @NotNull
    private final Vec2i visibleBounds;
    @NotNull
    private final Vec3 visibleBoundsOffset;
    @NotNull
    private final Vec2i textureSize;
    @NotNull
    private final List<BedrockEntityBone> bones = new ArrayList<>(16);
    
    public BedrockEntityGeometry(@NotNull Vec2i visibleBounds,
                                 @NotNull Vec3 visibleBoundsOffset,
                                 @NotNull Vec2i textureSize) {
        this.visibleBounds = visibleBounds;
        this.visibleBoundsOffset = visibleBoundsOffset;
        this.textureSize = textureSize;
    }
    
    @NotNull
    public Vec2i getVisibleBounds() {
        return visibleBounds;
    }
    
    @NotNull
    public Vec3 getVisibleBoundsOffset() {
        return visibleBoundsOffset;
    }
    
    @NotNull
    public Vec2i getTextureSize() {
        return textureSize;
    }
    
    @NotNull
    public Collection<BedrockEntityBone> getBones() {
        return Collections.unmodifiableList(bones);
    }
    
    public void addBone(@NotNull BedrockEntityBone bone) {
        bones.add(bone);
    }
    
    public void addBones(@NotNull Iterable<BedrockEntityBone> iterable) {
        iterable.forEach(this::addBone);
    }
    
    public int size() {
        return bones.size();
    }
    
    @NotNull
    @Override
    public Iterator<BedrockEntityBone> iterator() {
        return bones.iterator();
    }
    
}
