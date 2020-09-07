/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cars;

import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.util.texture.Texture;
import com.jogamp.opengl.util.texture.TextureIO;
import java.io.File;
import java.io.IOException;
import java.util.Vector;

/**
 *
 * @author Евгений
 */
public class Scene1 { 
    class Image
    {
	int IndexTexture;
	String Name;
	int number;

        private Image(int textureObject, String auto1, int i) {
        this.IndexTexture = textureObject;
        this.Name = auto1;
        this.number = i;
        }
    }
    static final int CountDrum = 5;
    static final int CountTextureOnDrum = 6;
    static final int CountTexture = 1;
    public Vector<String> vectordrum;
    int CountIndexTexture;
    Image[] image;
    File im;
    Texture t;
    float xl, xr, yd, yu;
    
    float[] rotate;
    volatile boolean[] startrotate;
    int Scene()
    {
	image = new Image[CountTexture];
        CountIndexTexture = 0;
        vectordrum = new Vector<String>();
        rotate = new float[5];
        for(int i=0;i<5;i++)
            rotate[i] = 360.0f;
        
        startrotate = new boolean[5];
        for(int i=0;i<5;i++)
            startrotate[i] = false;
        return 0;
    }
    int LoadDrum(GLAutoDrawable drawable) throws IOException
    {
        Image img;
        final GL2 gl = drawable.getGL().getGL2();
        //if (iter == 0)
	{
		vectordrum.add("auto1");//1
                CountIndexTexture++;
		im = new File("C:\\Users\\Евгений\\Desktop\\Tropic-Island\\Tropic-Island\\Cars\\content\\drum\\auto1.png");
                t = TextureIO.newTexture(im, true);
                img = new Image(t.getTextureObject(gl),"auto1",CountIndexTexture - 1);
                image[CountIndexTexture - 1] = img;
               
	}
        /*
	//if (iter == 1)
	{
		vectordrum.add("auto2");//2
		im = new File("content\\drum\\auto2.png");
                t = TextureIO.newTexture(im, true);
                image[CountIndexTexture - 1].IndexTexture = t.getTextureObject(gl);
		image[CountIndexTexture - 1].Name = "auto2";
		image[CountIndexTexture - 1].number = CountIndexTexture - 1;
	}
	//if (iter == 2)
	{

		vectordrum.add("auto3");//3
		im = new File("content\\drum\\auto3.png");
                t = TextureIO.newTexture(im, true);
                image[CountIndexTexture - 1].IndexTexture = t.getTextureObject(gl);
		image[CountIndexTexture - 1].Name = "auto3";
		image[CountIndexTexture - 1].number = CountIndexTexture - 1;
	}
	//if (iter == 3)
	{
		vectordrum.add("auto4");//4
		im = new File("content\\drum\\auto4.png");
                t = TextureIO.newTexture(im, true);
                image[CountIndexTexture - 1].IndexTexture = t.getTextureObject(gl);
		image[CountIndexTexture - 1].Name = "auto4";
		image[CountIndexTexture - 1].number = CountIndexTexture - 1;
	}
	//if (iter == 4)
	{
		vectordrum.add("auto5");//5
		im = new File("content\\drum\\auto5.png");
                t = TextureIO.newTexture(im, true);
                image[CountIndexTexture - 1].IndexTexture = t.getTextureObject(gl);
		image[CountIndexTexture - 1].Name = "auto5";
		image[CountIndexTexture - 1].number = CountIndexTexture - 1;
	}
        //if (iter == 15)
	{
		vectordrum.add("bonus");//16
		im = new File("content\\drum\\bonus.png");
                t = TextureIO.newTexture(im, true);
                image[CountIndexTexture - 1].IndexTexture = t.getTextureObject(gl);
		image[CountIndexTexture - 1].Name = "bonus";
		image[CountIndexTexture - 1].number = CountIndexTexture - 1;
	}
	//if (iter == 16)
	{
		vectordrum.add("wild");//17
		im = new File("content\\drum\\wild.jpg");
                t = TextureIO.newTexture(im, true);
                image[CountIndexTexture - 1].IndexTexture = t.getTextureObject(gl);
		image[CountIndexTexture - 1].Name = "wild";
		image[CountIndexTexture - 1].number = CountIndexTexture - 1;
	}
        */
	//if (iter > 15)
		return 0;
	//else
	//	return 1;
    }
    int FindTexture(String name)
    {
	int result = -1;
	for (int i = 0; i<CountTexture; i++)
	{
		if (image[i].Name.equals(name))
		{
			result = image[i].number;
                        break;
		}
	}
	return result;
    }
    void Rotate()
    {
        for (int i = 0; i<CountDrum; i++)
	{
		if (startrotate[i])
		{
			if (rotate[i]<1800.0f)
                            rotate[i] += 50.0f;       
                        else
                            startrotate[i]=false;   
                }
        }
    }
    void StartRotate()
    {
	for (int i = 0; i < CountDrum; i++)
	{
		if (startrotate[i] && rotate[i] != 0.0f)
			continue;
		if (rotate[i] >= 360.0f)
		{
			startrotate[i] = true;
			rotate[i] = 0.0f;
		}
	}
}
    void ShowDrum(int countdrums, int counttextureondrums,Vector<String> drum,final GL2 gl)
    {
	int k = -1;
        Rotate();
	for (int i = 0; i<countdrums; i++)
	{
		gl.glPushMatrix();
		gl.glRotatef(rotate[i], 1, 0, 0);
		for (int j = 0; j < counttextureondrums; j++)
		{
			gl.glBindTexture(GL2.GL_TEXTURE_2D, image[FindTexture(drum.get(++k))].IndexTexture);
			EnableTexture(i, j,gl);
		}
		gl.glPopMatrix();
	}
    }
    void EnableTexture(int n, int m,final GL2 gl)
    {
        if(n == 0)
        {
            if(m == 0){
                xl = -0.78f;//08
                xr = -0.48f;
                yd = 0.3f;
                yu = 0.68f;//09
                EnablePolygonFrontUp(xl, xr, yd, yu,gl);
            }
            if (m == 1) {
                xl = -0.78f;
                xr = -0.48f;
                yd = -0.3f;
                yu = 0.3f;
                EnablePolygonFrontMiddle(xl, xr, yd, yu,gl);
            }
            if (m == 2) {
                xl = -0.78f;
                xr = -0.48f;
                yd = -0.68f;
                yu = -0.3f;
                EnablePolygonFrontDown(xl, xr, yd, yu,gl);
            }
            if (m == 3) {
                xl = -0.78f;
                xr = -0.48f;
                yd = 0.3f;
                yu = 0.68f;
                EnablePolygonBackUp(xl, xr, yd, yu,gl);
            }
            if (m == 4) {
                xl = -0.78f;
                xr = -0.48f;
                yd = -0.3f;
                yu = 0.3f;
                EnablePolygonBackMiddle(xl, xr, yd, yu,gl);
            }
            if (m == 5) {
                xl = -0.78f;
                xr = -0.48f;
                yd = -0.68f;
                yu = -0.3f;
                EnablePolygonBackDown(xl, xr, yd, yu,gl);
            }
        }
            //front up
            //front middle
        if(n == 1)
        {
            if (m == 0) {
                xl = -0.48f;
                xr = -0.16f;
                yd = 0.3f;
                yu = 0.68f;
                EnablePolygonFrontUp(xl, xr, yd, yu,gl);
            }
            if(m == 1){
                xl = -0.48f;
                xr = -0.16f;
                yd = -0.3f;
                yu = 0.3f;
                EnablePolygonFrontMiddle(xl, xr, yd, yu,gl);
            }
            if (m == 2) {
                xl = -0.48f;
                xr = -0.16f;
                yd = -0.68f;
                yu = -0.3f;
                EnablePolygonFrontDown(xl, xr, yd, yu,gl);
            }
            if (m == 3) {
                xl = -0.48f;
                xr = -0.16f;
                yd = 0.3f;
                yu = 0.68f;
                EnablePolygonBackUp(xl, xr, yd, yu,gl);
            }
            if (m == 4) {
                xl = -0.48f;
                xr = -0.16f;
                yd = -0.3f;
                yu = 0.3f;
                EnablePolygonBackMiddle(xl, xr, yd, yu,gl);
            }
            if (m == 5) {
                xl = -0.48f;
                xr = -0.16f;
                yd = -0.68f;
                yu = -0.3f;
                EnablePolygonBackDown(xl, xr, yd, yu,gl);
            }
        }
            //front middle
            //front down
        if(n == 2)
        {
            if (m == 0) {
                xl = -0.16f;
                xr = 0.16f;
                yd = 0.3f;
                yu = 0.68f;
                EnablePolygonFrontUp(xl, xr, yd, yu,gl);
            }
            if (m == 1) {
                xl = -0.16f;
                xr = 0.16f;
                yd = -0.3f;
                yu = 0.3f;
                EnablePolygonFrontMiddle(xl, xr, yd, yu,gl);
            }
            if(m == 2){
                xl = -0.16f;
                xr = 0.16f;
                yd = -0.68f;
                yu = -0.3f;
                EnablePolygonFrontDown(xl, xr, yd, yu,gl);
            }
            if (m == 3) {
                xl = -0.16f;
                xr = 0.16f;
                yd = 0.3f;
                yu = 0.68f;
                EnablePolygonBackUp(xl, xr, yd, yu,gl);
            }
            if (m == 4) {
                xl = -0.16f;
                xr = 0.16f;
                yd = -0.3f;
                yu = 0.3f;
                EnablePolygonBackMiddle(xl, xr, yd, yu,gl);
            }
            if (m == 5) {
                xl = -0.16f;
                xr = 0.16f;
                yd = -0.68f;
                yu = -0.3f;
                EnablePolygonBackDown(xl, xr, yd, yu,gl);
            }
        }
            //front down
            //back up
        if(n == 3)
        {
            if (m == 0) {
                xl = 0.16f;
                xr = 0.48f;
                yd = 0.3f;
                yu = 0.68f;
                EnablePolygonFrontUp(xl, xr, yd, yu,gl);
            }
            if (m == 1) {
                xl = 0.16f;
                xr = 0.48f;
                yd = -0.3f;
                yu = 0.3f;
                EnablePolygonFrontMiddle(xl, xr, yd, yu,gl);
            }
            if (m == 2) {
                xl = 0.16f;
                xr = 0.48f;
                yd = -0.68f;
                yu = -0.3f;
                EnablePolygonFrontDown(xl, xr, yd, yu,gl);
            }
            if(m == 3){
                xl = 0.16f;
                xr = 0.48f;
                yd = 0.3f;
                yu = 0.68f;
                EnablePolygonBackUp(xl, xr, yd, yu,gl);
            }
            if (m == 4) {
                xl = 0.16f;
                xr = 0.48f;
                yd = -0.3f;
                yu = 0.3f;
                EnablePolygonBackMiddle(xl, xr, yd, yu,gl);
            }
            if (m == 5) {
                xl = 0.16f;
                xr = 0.48f;
                yd = -0.68f;
                yu = -0.3f;
                EnablePolygonBackDown(xl, xr, yd, yu,gl);
            }
        }
            //back up
            //back middle
        if(n == 4)
        {
            if (m == 0) {
                xl = 0.48f;
                xr = 0.78f;
                yd = 0.3f;
                yu = 0.68f;
                EnablePolygonFrontUp(xl, xr, yd, yu,gl);
            }
            if (m == 1) {
                xl = 0.48f;
                xr = 0.78f;
                yd = -0.3f;
                yu = 0.3f;
                EnablePolygonFrontMiddle(xl, xr, yd, yu,gl);
            }
            if (m == 2) {
                xl = 0.48f;
                xr = 0.78f;
                yd = -0.68f;
                yu = -0.3f;
                EnablePolygonFrontDown(xl, xr, yd, yu,gl);
            }
            if (m == 3) {
                xl = 0.48f;
                xr = 0.78f;
                yd = 0.3f;
                yu = 0.68f;
                EnablePolygonBackUp(xl, xr, yd, yu,gl);
            }
            if(m == 4){
                xl = 0.48f;
                xr = 0.78f;
                yd = -0.3f;
                yu = 0.3f;
                EnablePolygonBackMiddle(xl, xr, yd, yu,gl);
            }
            if (m == 5) {
            
                xl = 0.48f;
                xr = 0.78f;
                yd = -0.68f;
                yu = -0.3f;
                EnablePolygonBackDown(xl, xr, yd, yu,gl);
            }
        }
	//back middle
    }
    void EnablePolygonFrontUp(float xleft, float xright, float ydown, float yup,final GL2 gl)
    {
	gl.glBegin(GL2.GL_POLYGON);
	gl.glTexCoord2f(1.0f, 1.0f);
	gl.glVertex3f(xleft, yup, 0.0f);
	gl.glTexCoord2f(1.0f, 0.0f);
	gl.glVertex3f(xleft, ydown, .6f);
	gl.glTexCoord2f(0.0f, 0.0f);
	gl.glVertex3f(xright, ydown, .6f);
	gl.glTexCoord2f(0.0f, 1.0f);
	gl.glVertex3f(xright, yup, 0.0f);
	gl.glEnd();

}
void EnablePolygonFrontMiddle(float xleft, float xright, float ydown, float yup,final GL2 gl)
{
	gl.glBegin(GL2.GL_POLYGON);

	gl.glTexCoord2f(1.0f, 1.0f);
	gl.glVertex3f(xleft, yup, .6f);

	gl.glTexCoord2f(1.0f, 0.0f);
	gl.glVertex3f(xleft, ydown, .6f);

	gl.glTexCoord2f(0.0f, 0.0f);
	gl.glVertex3f(xright, ydown, .6f);

	gl.glTexCoord2f(0.0f, 1.0f);
	gl.glVertex3f(xright, yup, .6f);

	gl.glEnd();
}
void EnablePolygonFrontDown(float xleft, float xright, float ydown, float yup,final GL2 gl)
{
	gl.glBegin(GL2.GL_POLYGON);

	gl.glTexCoord2f(1.0f, 1.0f);
	gl.glVertex3f(xleft, yup, .6f);

	gl.glTexCoord2f(1.0f, 0.0f);
	gl.glVertex3f(xleft, ydown, 0.0f);

	gl.glTexCoord2f(0.0f, 0.0f);
	gl.glVertex3f(xright, ydown, 0.0f);

	gl.glTexCoord2f(0.0f, 1.0f);
	gl.glVertex3f(xright, yup, .6f);

	gl.glEnd();
}
void EnablePolygonBackUp(float xleft, float xright, float ydown, float yup,final GL2 gl)
{
	gl.glBegin(GL2.GL_POLYGON);

	gl.glTexCoord2f(1.0f, 1.0f);
	gl.glVertex3f(xleft, ydown, -.6f);

	gl.glTexCoord2f(1.0f, 0.0f);
	gl.glVertex3f(xleft, yup, 0.0f);

	gl.glTexCoord2f(0.0f, 0.0f);
	gl.glVertex3f(xright, yup, 0.0f);

	gl.glTexCoord2f(0.0f, 1.0f);
	gl.glVertex3f(xright, ydown, -.6f);

	gl.glEnd();
}
void EnablePolygonBackMiddle(float xleft, float xright, float ydown, float yup,final GL2 gl)
{
	gl.glBegin(GL2.GL_POLYGON);

	gl.glTexCoord2f(1.0f, 1.0f);
	gl.glVertex3f(xleft, ydown, -.6f);

	gl.glTexCoord2f(1.0f, 0.0f);
	gl.glVertex3f(xleft, yup, -.6f);

	gl.glTexCoord2f(0.0f, 0.0f);
	gl.glVertex3f(xright, yup, -.6f);

	gl.glTexCoord2f(0.0f, 1.0f);
	gl.glVertex3f(xright, ydown, -.6f);

	gl.glEnd();
}
void EnablePolygonBackDown(float xleft, float xright, float ydown, float yup,final GL2 gl)
{
	gl.glBegin(GL2.GL_POLYGON);

	gl.glTexCoord2f(1.0f, 1.0f);
	gl.glVertex3f(xleft, ydown, 0.0f);

	gl.glTexCoord2f(1.0f, 0.0f);
	gl.glVertex3f(xleft, yup, -.6f);

	gl.glTexCoord2f(0.0f, 0.0f);
	gl.glVertex3f(xright, yup, -.6f);

	gl.glTexCoord2f(0.0f, 1.0f);
	gl.glVertex3f(xright, ydown, 0.0f);

	gl.glEnd();
    }
}
