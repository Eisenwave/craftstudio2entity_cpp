package es.razzleberri.util;

public class Vec3i {
    
    public final static Vec3i ZERO = new Vec3i(0, 0, 0);
    
    private final int x, y, z;
    
    public Vec3i(int x, int y, int z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    
    public int getX() {
        return x;
    }
    
    public int getY() {
        return y;
    }
    
    public int getZ() {
        return z;
    }
    
}
