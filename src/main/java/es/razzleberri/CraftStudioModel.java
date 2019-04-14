package es.razzleberri;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class CraftStudioModel {
    
    @NotNull
    private final String title;
    private final List<CraftStudioBlock> blocks = new ArrayList<>(32);
    
    public CraftStudioModel(@NotNull String title) {
        this.title = title;
    }
    
    @NotNull
    public String getTitle() {
        return title;
    }
    
    public void addBlock(@NotNull CraftStudioBlock block) {
        this.blocks.add(block);
    }
    
    @NotNull
    public List<CraftStudioBlock> getBlocks() {
        return Collections.unmodifiableList(blocks);
    }
    
    public int size() {
        return blocks.size();
    }
    
}
