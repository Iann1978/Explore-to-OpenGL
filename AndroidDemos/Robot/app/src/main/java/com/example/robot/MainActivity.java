package com.example.robot;

import androidx.appcompat.app.AppCompatActivity;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

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
                "#version 300 es\n" +
                "layout(location = 0) in vec4 vPosition;\n" +
                "void main() {\n" +
                "  gl_Position = vPosition;\n" +
                "}\n";

        private final String FRAGMENT_SHADER =
                "void main() {\n" +
                        "gl_FragColor = vec4(1., 0.8, 0.0, 1.0);\n" +
                        "}\n";


        int mGLProgram;

        final int[] vbo = new int[1];
        final int[] ibo = new int[1];
        @Override
        public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

            mGLProgram = Shader.LoadShaderFromSourceCode(VERTEX_SHADER, FRAGMENT_SHADER);

            final float vertexData[] = {
                    0.0f, 0.5f,
                    -0.5f, -0.5f,
                    0.5f, -0.5f,
            };
            FloatBuffer vertexBuffer = ByteBuffer.allocateDirect(vertexData.length * 4)
                    .order(ByteOrder.nativeOrder())
                    .asFloatBuffer()
                    .put(vertexData);
            vertexBuffer.position(0);

            GLES20.glGenBuffers(1, vbo, 0);
            GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, vbo[0]);
            GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, vertexBuffer.capacity()
                    * 4, vertexBuffer, GLES20.GL_STATIC_DRAW);


        }

        @Override
        public void onSurfaceChanged(GL10 gl10, int i, int i1) {
            //GLES20.glViewport(0, 0, p1, p2)
        }

        @Override
        public void onDrawFrame(GL10 gl10) {
            GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
            GLES20.glUseProgram(mGLProgram);

            GLES20.glEnableVertexAttribArray(0);
            GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, vbo[0]);
            GLES20.glVertexAttribPointer(
                    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    2,                  // size
                    GLES20.GL_FLOAT,           // type
                    false,           // normalized?
                    0,
                    0);

           // glDrawArrays(GL_TRIANGLES, 0, 3); // 12*3 indices starting at 0 -> 12 triangles
            GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, 3);


        }
    }

}
