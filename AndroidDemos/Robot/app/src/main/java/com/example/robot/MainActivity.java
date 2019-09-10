package com.example.robot;

import androidx.appcompat.app.AppCompatActivity;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends AppCompatActivity {

    GLSurfaceView glSurfaceView;
    //RobotView robotView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //robotView = new RobotView(getApplication());


        glSurfaceView = new GLSurfaceView(getApplication());
        setContentView(glSurfaceView);

        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(new Renderer());
        glSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }

    class Renderer implements  GLSurfaceView.Renderer {

        private final String VERTEX_SHADER =
                "void main() {\n" +
                        "gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n" +
                        "gl_PointSize = 20.0;\n" +
                        "}\n";

        private final String FRAGMENT_SHADER =
                "void main() {\n" +
                        "gl_FragColor = vec4(1., 0., 0.0, 1.0);\n" +
                        "}\n";


        int mGLProgram;
        @Override
        public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

            final int[] compileStatus = new int[1];
            int vsh = GLES20.glCreateShader(GLES20.GL_VERTEX_SHADER);
            GLES20.glShaderSource(vsh, VERTEX_SHADER);
            GLES20.glCompileShader(vsh);
            GLES20.glGetShaderiv(vsh, GLES20.GL_COMPILE_STATUS, compileStatus, 0);

            int fsh = GLES20.glCreateShader(GLES20.GL_FRAGMENT_SHADER);
            GLES20.glShaderSource(fsh, FRAGMENT_SHADER);
            GLES20.glCompileShader(fsh);

            mGLProgram = GLES20.glCreateProgram();
            GLES20.glAttachShader(mGLProgram, vsh);
            GLES20.glAttachShader(mGLProgram, fsh);
            GLES20.glLinkProgram(mGLProgram);

            GLES20.glValidateProgram(mGLProgram);

            final int[] status = new int[1];
            GLES20.glGetProgramiv(mGLProgram, GLES20.GL_VALIDATE_STATUS, status, 0);
            Log.d("Robot", "validate shader program: " + GLES20.glGetProgramInfoLog(mGLProgram));




        }

        @Override
        public void onSurfaceChanged(GL10 gl10, int i, int i1) {
            //GLES20.glViewport(0, 0, p1, p2)
        }

        @Override
        public void onDrawFrame(GL10 gl10) {
            GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
            GLES20.glUseProgram(mGLProgram);

            GLES20.glDrawArrays(GLES20.GL_POINTS, 0, 1);


        }
    }

}
