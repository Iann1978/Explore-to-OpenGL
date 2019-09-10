package com.example.robot;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLUtils;

public class Texture
{
    int texture;
    int width;
    int height;

    public static Texture LoadTexture(Context context, int resourceId)
    {
        Texture texture = new Texture();
        final int[] textureArray = new int[1];
        GLES20.glGenTextures(1,textureArray,0);

        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inScaled = false;

        Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), resourceId, options);

        // 2. 将纹理绑定到OpenGL对象上
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureArray[0]);

        // 3. 设置纹理过滤参数:解决纹理缩放过程中的锯齿问题。若不设置，则会导致纹理为黑色
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR_MIPMAP_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_REPEAT);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_REPEAT);
        // 4. 通过OpenGL对象读取Bitmap数据，并且绑定到纹理对象上，之后就可以回收Bitmap对象
        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);

        // Note: Following code may cause an error to be reported in the
        // ADB log as follows: E/IMGSRV(20095): :0: HardwareMipGen:
        // Failed to generate texture mipmap levels (error=3)
        // No OpenGL error will be encountered (glGetError() will return
        // 0). If this happens, just squash the source image to be
        // square. It will look the same because of texture coordinates,
        // and mipmap generation will work.
        // 5. 生成Mip位图
        GLES20.glGenerateMipmap(GLES20.GL_TEXTURE_2D);

        // 6. 回收Bitmap对象
        texture.width = bitmap.getWidth();
        texture.height = bitmap.getHeight();
        bitmap.recycle();

        // 7. 将纹理从OpenGL对象上解绑
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);

        // 所以整个流程中，OpenGL对象类似一个容器或者中间者的方式，将Bitmap数据转移到OpenGL纹理上
        texture.texture = textureArray[0];

        return texture;

    }

}
