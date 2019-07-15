package com.example.openglbyndk;

import android.content.Context;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


public class MyRender implements GLSurfaceView.Renderer {

    private final Context context;
    int texture;
    public MyRender(Context context) {
        this.context = context;
    }
    public void onDrawFrame(GL10 gl) {
        //GL2JNILib.stringFromJNI();
        GL2JNILib.step();
        //GLES10.glClear(GLES10.GL_COLOR_BUFFER_BIT);

    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        texture = TextureHelper.loadTexture(context, R.drawable.stone_wall_public_domain);
        GL2JNILib.init(width, height, texture);

        int a = 0;
        int b = 0;
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        // Do nothing.
    }
}