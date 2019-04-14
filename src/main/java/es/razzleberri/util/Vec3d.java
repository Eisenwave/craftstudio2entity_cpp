package es.razzleberri.util;

import java.text.DecimalFormat;

public class Vec3 {
    
    public final static Vec3 ZERO = new Vec3(0, 0, 0);
    
    private final double x, y, z;
    
    public Vec3(double x, double y, double z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    
    public double getX() {
        return x;
    }
    
    public double getY() {
        return y;
    }
    
    public double getZ() {
        return z;
    }
    
    public Vec3 plus(Vec3 v) {
        return new Vec3(this.x + v.x, this.y + v.y, this.z + v.z);
    }
    
    public Vec3 minus(Vec3 v) {
        return new Vec3(this.x - v.x, this.y - v.y, this.z - v.z);
    }
    
    public Vec3 modulo(Vec3 v) {
        return new Vec3(this.x % v.x, this.y % v.y, this.z % v.z);
    }
    
    public Vec3 times(double s) {
        return new Vec3(this.x * s, this.y * s, this.z * s);
    }
    
    @Override
    public String toString() {
        return "[" + x + ", " + y + ", " + z + "]";
    }
    
    public String toString(DecimalFormat format) {
        return "[" + format.format(x) + ", " + format.format(y) + ", " + format.format(z) + "]";
    }
    
    public boolean equals(Vec3 v, double epsilon) {
        return Math.abs(this.x - v.x) < epsilon
            && Math.abs(this.y - v.y) < epsilon
            && Math.abs(this.z - v.z) < epsilon;
    }
    
}
