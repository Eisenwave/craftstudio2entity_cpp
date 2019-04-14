package es.razzleberri.util;

import org.jetbrains.annotations.NotNull;

import java.text.DecimalFormat;
import java.util.Arrays;

public class Matrix3x3d {
    
    /**
     * <p>
     * Returns a 3x3 rotation matrix representing a counter-clockwise rotation around the x-axis.
     * </p>
     * <p>
     * For easier understanding, see: <a href="https://en.wikipedia.org/wiki/Right-hand_rule">Right Hand Rule</a>.
     * </p>
     *
     * @param angle the angle in radians
     * @return a new rotation matrix
     */
    @NotNull
    public static Matrix3x3d fromRotX(double angle) {
        double sin = Math.sin(angle), cos = Math.cos(angle);
        return new Matrix3x3d(
            1, 0, 0,
            0, cos, -sin,
            0, sin, cos);
    }
    
    /**
     * <p>
     * Returns a 3x3 rotation matrix representing a counter-clockwise rotation around the y-axis.
     * </p>
     * <p>
     * For easier understanding, see: <a href="https://en.wikipedia.org/wiki/Right-hand_rule">Right Hand Rule</a>.
     * </p>
     *
     * @param angle the angle in radians
     * @return a new rotation matrix
     */
    @NotNull
    public static Matrix3x3d fromRotY(double angle) {
        double sin = Math.sin(angle), cos = Math.cos(angle);
        return new Matrix3x3d(
            cos, 0, sin,
            0, 1, 0,
            -sin, 0, cos);
    }
    
    /**
     * <p>
     * Returns a 3x3 rotation matrix representing a counter-clockwise rotation around the z-axis.
     * </p>
     * <p>
     * For easier understanding, see: <a href="https://en.wikipedia.org/wiki/Right-hand_rule">Right Hand Rule</a>.
     * </p>
     *
     * @param angle the angle in radians
     * @return a new rotation matrix
     */
    @NotNull
    public static Matrix3x3d fromRotZ(double angle) {
        double sin = Math.sin(angle), cos = Math.cos(angle);
        return new Matrix3x3d(
            cos, -sin, 0,
            sin, cos, 0,
            0, 0, 1);
    }
    
    // X Y Z
    
    public static Matrix3x3d fromEulerXYZ(double x, double y, double z) {
        return fromRotX(x).times(fromRotY(y)).times(fromRotZ(z));
    }
    
    public static Matrix3x3d fromEulerXYZ(Vec3 v) {
        return fromEulerXYZ(v.getX(), v.getY(), v.getZ());
    }
    
    // Z X Y
    
    public static Matrix3x3d fromEulerZXY(double x, double y, double z) {
        return fromRotZ(z).times(fromRotX(x)).times(fromRotY(y));
    }
    
    public static Matrix3x3d fromEulerZXY(Vec3 v) {
        return fromEulerZXY(v.getX(), v.getY(), v.getZ());
    }
    
    // Y X Z
    
    public static Matrix3x3d fromEulerYXZ(double x, double y, double z) {
        return fromRotY(y).times(fromRotX(x)).times(fromRotZ(z));
    }
    
    public static Matrix3x3d fromEulerYXZ(Vec3 v) {
        return fromEulerYXZ(v.getX(), v.getY(), v.getZ());
    }
    
    // Z Y X
    
    public static Matrix3x3d fromEulerZYX(double x, double y, double z) {
        return from_euler_rz(z).times(from_euler_ry(y)).times(from_euler_rx(x));
    }
    
    public static Matrix3x3d fromEulerZYX(Vec3 v) {
        return fromEulerZYX(v.getX(), v.getY(), v.getZ());
    }
    
    private final double[] content;
    
    private Matrix3x3d(double... content) {
        this.content = content;
    }
    
    public Matrix3x3d(double m00, double m01, double m02,
                      double m10, double m11, double m12,
                      double m20, double m21, double m22) {
        this.content = new double[] {m00, m01, m02, m10, m11, m12, m20, m21, m22};
    }
    
    public Matrix3x3d() {
        this(new double[9]);
    }
    
    // GETTERS
    
    public double get(int i, int j) {
        return content[i * 3 + j];
    }
    
    /**
     * Special case formula for 3x3 matrices. (Using <a href="https://en.wikipedia.org/wiki/Cramer%27s_rule">Cramer's
     * Rule</a>)
     *
     * @return the determinant of the matrix
     */
    private double getDeterminant() {
        return get(0, 0) * get(1, 1) * get(2, 2)
            + get(0, 1) * get(1, 2) * get(2, 0)
            + get(0, 2) * get(1, 0) * get(2, 1)
            - get(0, 2) * get(1, 1) * get(2, 0)
            - get(0, 0) * get(1, 2) * get(2, 1)
            - get(0, 1) * get(1, 0) * get(2, 2);
    }
    
    public Vec3 getXYZEulerRotation() {
        double x = Math.atan2(get(1, 2), get(2, 2));
        double cosY = Math.hypot(get(0, 0), get(0, 1));
        double y = Math.atan2(-get(0, 2), cosY);
        double sinX = Math.sin(x);
        double cosX = Math.cos(x);
        double z = Math.atan2(sinX * get(2, 0) - cosX * get(1, 0), cosX * get(1, 1) - sinX * get(2, 1));
        return new Vec3(-x, -y, -z);
    }
    
    public Vec3 getXYLZEulerRotation() {
        double x = Math.atan2(-get(1, 2), get(2, 2));
        double cosY = Math.hypot(get(0, 0), get(0, 1));
        double y = Math.atan2(get(0, 2), cosY);
        double sinX = Math.sin(x);
        double cosX = Math.cos(x);
        double z = Math.atan2(-cosX * get(1, 0) - sinX * get(2, 0), cosX * get(1, 1) + sinX * get(2, 1));
        return new Vec3(x, y, z);
    }
    
    public Vec3 getLZYXEulerRotation() {
        double z = Math.atan2(-get(1, 0), get(0, 0));
        double cosY = Math.hypot(get(2, 1), get(2, 2));
        double y = Math.atan2(-get(2, 0), cosY);
        double sinZ = Math.sin(z);
        double cosZ = Math.cos(z);
        double x = Math.atan2(-sinZ * get(0, 2) - cosZ * get(1, 2), sinZ * get(0, 1) + cosZ * get(1, 1));
        return new Vec3(x, y, z);
    }
    
    /**
     * Multiplies this matrix with another matrix which will be the right hand side of the matrix multiplication.
     *
     * @param m the right hand side matrix
     */
    @NotNull
    public Matrix3x3d times(Matrix3x3d m) {
        double[] result = new double[3 * 3];
        
        /* outer loop for acquiring the position (i, j) in the product matrix */
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                final int index = i * 3 + j;
                
                /* inner loop for calculating the result at (i, j) */
                for (int k = 0, l = 0; k < 3 && l < 3; k++, l++)
                    result[index] += this.get(i, k) * m.get(l, j);
            }
        
        return new Matrix3x3d(result);
    }
    
    public Vec3 times(Vec3 v) {
        return new Vec3(
            get(0, 0) * v.getX() + get(0, 1) * v.getY() + get(0, 2) * v.getZ(),
            get(1, 0) * v.getX() + get(1, 1) * v.getY() + get(1, 2) * v.getZ(),
            get(2, 0) * v.getX() + get(2, 1) * v.getY() + get(2, 2) * v.getZ()
        );
    }
    
    // SETTERS
    
    public void set(int i, int j, double value) {
        content[i * 3 + j] = value;
    }
    
    public void swap(int i0, int j0, int i1, int j1) {
        final int from = i0 * 3 + j0, to = i1 * 3 + j1;
        
        double swap = content[to];
        content[to] = content[from];
        content[from] = swap;
    }
    
    public void scale(double factor) {
        for (int k = 0; k < content.length; k++)
            content[k] *= factor;
    }
    
    // MISC
    
    @Override
    public String toString() {
        return Arrays.toString(content);
    }
    
    public String toString(DecimalFormat format) {
        StringBuilder builder = new StringBuilder("[")
            .append(format.format(content[0]));
        for (int i = 1; i < content.length; i++)
            builder
                .append(", ")
                .append(format.format(content[i]));
        return builder.append(']').toString();
    }
    
    public boolean equals(Matrix3x3d other, double epsilon) {
        for (int i = 0; i < content.length; i++)
            if (Math.abs(this.content[i] - other.content[i]) > epsilon)
                return false;
        return true;
    }
    
}
