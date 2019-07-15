package com.example.openglbyndk;


// Wrapper for native library

public class GL2JNILib {

    static {
        //System.loadLibrary("gl2jni");
        System.loadLibrary("native-lib");

    }

    /**
     * @param width the current view width
     * @param height the current view height
     */
    public static native void init(int width, int height, int texture);
    public static native void step();
    public static native String stringFromJNI();
}
