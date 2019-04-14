package es.razzleberri;

import es.razzleberri.util.*;
import org.jetbrains.annotations.*;

public final class CraftStudioToBedrockEntity {
    
    private final static Vec2i VISIBLE_BOUNDS = new Vec2i(1, 2);
    private final static Vec3 VISIBLE_BOUNDS_OFFSET = new Vec3(0, 0, 0);
    private final static Vec2i TEXTURE_SIZE = new Vec2i(128, 128);
    
    @NotNull
    public static BedrockEntityModel convert(@NotNull CraftStudioModel csModel) {
        BedrockEntityModel result = new BedrockEntityModel();
        BedrockEntityGeometry geometry = new BedrockEntityGeometry(
            VISIBLE_BOUNDS,
            VISIBLE_BOUNDS_OFFSET,
            TEXTURE_SIZE);
        
        for (CraftStudioBlock block : csModel.getBlocks())
            blockToBone(geometry, block, null);
        
        result.putGeometry(csModel.getTitle(), geometry);
        return result;
    }
    
    /**
     * Converts a {@link CraftStudioBlock} to a {@link BedrockEntityBone} and adds the bone to the given
     * {@link BedrockEntityGeometry}.
     * <p>
     * If the given block has a parent, the parent will be referenced by the block in the geometry.
     * <p>
     * If the given block has children, these children will be appended, referencing the given block as a parent.
     *
     * @param geometry the entity geometry
     * @param block the block to be converted
     * @param parent the parent of the block, can be {@code null}
     */
    private static void blockToBone(@NotNull BedrockEntityGeometry geometry,
                                    @NotNull CraftStudioBlock block,
                                    @Nullable CraftStudioBlock parent) {
        String name = block.getName();
        String parentName = parent == null? null : parent.getName();
        /* if (geometry.hasBone(name)) {
            if (parentName != null)
                name = parentName + '.' + name;
            if (geometry.hasBone(name)) {
                System.err.println("ERROR: Bone \"" + name + "\" appears multiple times");
            }
        } */
        
        Vec3 pivot = block.getPosition();
        if (parent != null)
            pivot = pivot.plus(parent.getPosition());
        pivot = new Vec3(
            pivot.getX(),
            pivot.getY(),
            -pivot.getZ()
            //pivot.getZ()
        );
        
        Vec3 rotation = Rotations.craftStudioRotationToEntityRotation(block.getRotation());
        
        //System.err.println(name);
        BedrockEntityBone bone = new BedrockEntityBone(name, parentName, pivot, rotation);
        bone.addCube(blockToCube(block, parent));
        geometry.addBone(bone);
        
        for (CraftStudioBlock child : block.getChildren()) {
            if (Rotations.isZeroRotation(child.getRotation()))
                bone.addCube(blockToCube(child, block));
            else
                blockToBone(geometry, child, block);
        }
    }
    
    private static BedrockEntityCube blockToCube(@NotNull CraftStudioBlock block,
                                                 @Nullable CraftStudioBlock parent) {
        Vec3i size = block.getSize();
        Vec3 position = block.getPosition().plus(block.getOffsetFromPivot());
        if (parent != null)
            position = position.plus(parent.getPosition().plus(parent.getOffsetFromPivot()));
        position = new Vec3(
            //-(position.getX() - size.getX() / 2d) - size.getX(),
            position.getX() - size.getX() / 2d,
            position.getY() - size.getY() / 2d,
            //position.getZ() - size.getZ() / 2d
            -(position.getZ() - size.getZ() / 2d) - size.getZ()
        );
        
        return new BedrockEntityCube(
            position,
            size,
            block.getTexOffset()
        );
    }
    
    /* @Nullable
    private static String prefixOf(String name) {
        int index = name.indexOf('.');
        return index == -1? null : name.substring(0, index);
    }
    
    private static String prefixOrNameOf(String name) {
        int index = name.indexOf('.');
        return index == -1? name : name.substring(0, index);
    } */
    
}
