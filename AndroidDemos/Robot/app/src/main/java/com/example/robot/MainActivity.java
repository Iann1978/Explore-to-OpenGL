package com.example.robot;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

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

        glSurfaceView.setEGLContextClientVersion(3);
        glSurfaceView.setRenderer(new Renderer(getApplication()));
        glSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
    }

    class Renderer implements  GLSurfaceView.Renderer {
        private final Context context;
        public Renderer(Context context) {
            this.context = context;
        }

        private final String VERTEX_SHADER = "#version 300 es\n" +
                "layout(location = 0) in vec4 vPosition;\n" +
                "layout(location = 1) in vec2 input_vertexTexcoord;\n" +
                "out vec2 uv;\n" +
                "void main() {\n" +
                "  gl_Position = vPosition;\n" +
                "  uv = input_vertexTexcoord;\n" +
                "}\n";

        private final String FRAGMENT_SHADER = "#version 300 es\n" +
                "precision mediump float;\n" +
                "uniform sampler2D myTextureSampler;\n" +
                "in vec2 uv;\n" +
                "out vec4 outColor;\n" +
                "void main() {\n" +
                "   outColor = texture(myTextureSampler, uv);\n" +
                "}\n";


        int mGLProgram;

        final int[] vbo = new int[1];
        final int[] uv = new int[1];
        final int[] ibo = new int[1];
        ByteBuffer indiceBuffer;

        Texture texture;
        int textureID;
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

            final float uvData[] = {
                    0.0f, 0.0f,
                    0.0f, 1.0f,
                    1.0f, 1.0f,
            };
            FloatBuffer uvBuffer = ByteBuffer.allocateDirect(uvData.length * 4)
                    .order(ByteOrder.nativeOrder())
                    .asFloatBuffer()
                    .put(uvData);
            uvBuffer.position(0);

            GLES20.glGenBuffers(1, uv, 0);
            GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, uv[0]);
            GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, uvBuffer.capacity()
                    * 4, uvBuffer, GLES20.GL_STATIC_DRAW);

            final byte indicesData[] = {
                    0,1,2
            };
            indiceBuffer = ByteBuffer.allocateDirect(indicesData.length)
                    .order(ByteOrder.nativeOrder())
                    .put(indicesData);
            indiceBuffer.position(0);

            GLES20.glGenBuffers(1,ibo,0);
            GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, ibo[0]);
            GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, indiceBuffer.capacity(),
                   indiceBuffer, GLES20.GL_STATIC_DRAW);


            texture = Texture.LoadTexture(context, R.drawable.stone_wall_public_domain);
            textureID = GLES20.glGetUniformLocation(mGLProgram, "myTextureSampler");

        }

        @Override
        public void onSurfaceChanged(GL10 gl10, int i, int i1) {
            //GLES20.glViewport(0, 0, p1, p2)
        }

        @Override
        public void onDrawFrame(GL10 gl10) {
            GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
            GLES20.glUseProgram(mGLProgram);

            GLES20. glActiveTexture(GLES20.GL_TEXTURE0);
            GLES20. glBindTexture(GLES20.GL_TEXTURE_2D, texture.texture);
//    // Set our "myTextureSampler" sampler to use Texture Unit 0
            GLES20.glUniform1i(textureID, 0);

            GLES20.glEnableVertexAttribArray(0);
            GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, vbo[0]);
            GLES20.glVertexAttribPointer(
                    0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    2,                  // size
                    GLES20.GL_FLOAT,           // type
                    false,           // normalized?
                    0,
                    0);

            GLES20.glEnableVertexAttribArray(1);
            GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, uv[0]);
            GLES20.glVertexAttribPointer(
                    1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                    2,                  // size
                    GLES20.GL_FLOAT,           // type
                    false,           // normalized?
                    0,
                    0);

            //GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, ibo[0]);
           // glDrawArrays(GL_TRIANGLES, 0, 3); // 12*3 indices starting at 0 -> 12 triangles
            //GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, 3);
            //GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, ibo[0]);
            GLES20.glDrawElements(GLES20.GL_TRIANGLES, 3,GLES20.GL_UNSIGNED_BYTE,indiceBuffer);
        }
    }

}
