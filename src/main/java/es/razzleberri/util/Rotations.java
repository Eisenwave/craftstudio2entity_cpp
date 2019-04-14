package es.razzleberri.util;

public final class Rotations {
    
    private final static double
        EPSILON = 1E-10,
        RAD_TO_DEG = Math.toDegrees(1),
        DEG_TO_RAD = Math.toRadians(1);
    
    private final static Vec3 _360 = new Vec3(360, 360, 360);
    
    public static Vec3 craftStudioRotationToEntityRotation(Vec3 xyzDegrees) {
        xyzDegrees = xyzDegrees.times(DEG_TO_RAD);
        Matrix3x3d transformYXZ = Matrix3x3d.fromEulerYXZ(xyzDegrees);
        transformYXZ = new Matrix3x3d(1, 0, 0, 0, 1, 0, 0, 0, -1).times(transformYXZ);
        xyzDegrees = transformYXZ.getLZYXEulerRotation();
        return xyzDegrees.times(RAD_TO_DEG);
    }
    
    public static boolean isZeroRotation(Vec3 anglesDeg) {
        anglesDeg = anglesDeg
            .modulo(_360)  // get the angles into a -360..360 range
            .plus(_360)    // add 360 to get angles into a 0..720 range
            .modulo(_360); // get the angles into a 0..360 range
        return anglesDeg.getX() < EPSILON
            && anglesDeg.getY() < EPSILON
            && anglesDeg.getZ() < EPSILON;
    }
    
}
