package com.example.robot;

import android.opengl.GLES20;
import android.util.Log;

public class Shader
{
    public static int LoadShaderFromSourceCode(String vertexShaderCode, String fragmentShaderCode)
    {
        int vertexShader = GLES20.glCreateShader(GLES20.GL_VERTEX_SHADER);
        int fragmentShader = GLES20.glCreateShader(GLES20.GL_FRAGMENT_SHADER);

        final int[] compileStatus = new int[1];

        // Compiling vertex shader.
        GLES20.glShaderSource(vertexShader,vertexShaderCode);
        GLES20.glCompileShader(vertexShader);
        GLES20.glGetShaderiv(vertexShader, GLES20.GL_COMPILE_STATUS, compileStatus, 0);
        if (compileStatus[0] == 0)
        {
            Log.v("Robot", "Results of compiling source:" + "\n" + vertexShaderCode + "\n:"
                    + GLES20.glGetShaderInfoLog(vertexShader));
        }



        // Compiling fragment shader.
        GLES20.glShaderSource(fragmentShader,fragmentShaderCode);
        GLES20.glCompileShader(fragmentShader);
        GLES20.glGetShaderiv(fragmentShader, GLES20.GL_COMPILE_STATUS, compileStatus, 0);
        if (compileStatus[0] == 0)
        {
            Log.v("Robot", "Results of compiling source:" + "\n" + fragmentShaderCode + "\n:"
                    + GLES20.glGetShaderInfoLog(fragmentShader));
        }

        final int program = GLES20.glCreateProgram();
        GLES20.glAttachShader(program, vertexShader);
        GLES20.glAttachShader(program, fragmentShader);
        GLES20.glLinkProgram(program);


        final int[] linkStatus = new int[1];
        GLES20.glGetProgramiv(program, GLES20.GL_LINK_STATUS, linkStatus, 0);


        return program;
    }
}
