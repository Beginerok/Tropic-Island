/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cars;

/**
 *
 * @author Евгений
 */
//import com.jogamp.newt.event.MouseAdapter;
//import com.jogamp.newt.event.MouseEvent;


import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
//import com.jogamp.newt.event.MouseListener;

import java.awt.DisplayMode;
import java.io.File;
import java.io.IOException;

/*
import javax.media.opengl.GL2;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.GLProfile;
import javax.media.opengl.awt.GLCanvas;
import javax.media.opengl.glu.GLU;
*/

import com.jogamp.opengl.*;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.awt.GLJPanel;
import com.jogamp.opengl.glu.*;


import javax.swing.JFrame;

import com.jogamp.opengl.util.FPSAnimator;
import com.jogamp.opengl.util.texture.Texture;
import com.jogamp.opengl.util.texture.TextureIO;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Window;
import java.awt.event.MouseListener;
import javax.swing.JPanel;




public class Cars extends JPanel implements GLEventListener {

   public static DisplayMode dm, dm_old;
   private GLU glu = new GLU();
   private float xrot,yrot,zrot;
   private int texture;
   
   @Override
   public void display(GLAutoDrawable drawable) {
   
      // TODO Auto-generated method stub
      final GL2 gl = drawable.getGL().getGL2();
      gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);
      gl.glLoadIdentity(); // Reset The View
      gl.glTranslatef(0f, 0f, -5.0f);
		
      gl.glRotatef(xrot, 1.0f, 1.0f, 1.0f);
      gl.glRotatef(yrot, 0.0f, 1.0f, 0.0f);
      gl.glRotatef(zrot, 0.0f, 0.0f, 1.0f);
		
      gl.glBindTexture(GL2.GL_TEXTURE_2D, texture);
      gl.glBegin(GL2.GL_QUADS);

      // Front Face
      gl.glTexCoord2f(0.0f, 0.0f); gl.glVertex3f(-1.0f, -1.0f, 1.0f);
      gl.glTexCoord2f(1.0f, 0.0f); gl.glVertex3f( 1.0f, -1.0f, 1.0f);
      gl.glTexCoord2f(1.0f, 1.0f); gl.glVertex3f( 1.0f, 1.0f, 1.0f);
      gl.glTexCoord2f(0.0f, 1.0f); gl.glVertex3f(-1.0f, 1.0f, 1.0f);

      // Back Face
      gl.glTexCoord2f(1.0f, 0.0f); gl.glVertex3f(-1.0f, -1.0f, -1.0f);
      gl.glTexCoord2f(1.0f, 1.0f); gl.glVertex3f(-1.0f, 1.0f, -1.0f);
      gl.glTexCoord2f(0.0f, 1.0f); gl.glVertex3f( 1.0f, 1.0f, -1.0f);
      gl.glTexCoord2f(0.0f, 0.0f); gl.glVertex3f( 1.0f, -1.0f, -1.0f);

      // Top Face
      gl.glTexCoord2f(0.0f, 1.0f); gl.glVertex3f(-1.0f, 1.0f, -1.0f);
      gl.glTexCoord2f(0.0f, 0.0f); gl.glVertex3f(-1.0f, 1.0f, 1.0f);
      gl.glTexCoord2f(1.0f, 0.0f); gl.glVertex3f( 1.0f, 1.0f, 1.0f);
      gl.glTexCoord2f(1.0f, 1.0f); gl.glVertex3f( 1.0f, 1.0f, -1.0f);

      // Bottom Face
      gl.glTexCoord2f(1.0f, 1.0f); gl.glVertex3f(-1.0f, -1.0f, -1.0f);
      gl.glTexCoord2f(0.0f, 1.0f); gl.glVertex3f( 1.0f, -1.0f, -1.0f);
      gl.glTexCoord2f(0.0f, 0.0f); gl.glVertex3f( 1.0f, -1.0f, 1.0f);
      gl.glTexCoord2f(1.0f, 0.0f); gl.glVertex3f(-1.0f, -1.0f, 1.0f);

      // Right face
      gl.glTexCoord2f(1.0f, 0.0f); gl.glVertex3f( 1.0f, -1.0f, -1.0f);
      gl.glTexCoord2f(1.0f, 1.0f); gl.glVertex3f( 1.0f, 1.0f, -1.0f);
      gl.glTexCoord2f(0.0f, 1.0f); gl.glVertex3f( 1.0f, 1.0f, 1.0f);
      gl.glTexCoord2f(0.0f, 0.0f); gl.glVertex3f( 1.0f, -1.0f, 1.0f);

      // Left Face
      gl.glTexCoord2f(0.0f, 0.0f); gl.glVertex3f(-1.0f, -1.0f, -1.0f);
      gl.glTexCoord2f(1.0f, 0.0f); gl.glVertex3f(-1.0f, -1.0f, 1.0f);
      gl.glTexCoord2f(1.0f, 1.0f); gl.glVertex3f(-1.0f, 1.0f, 1.0f);
      gl.glTexCoord2f(0.0f, 1.0f); gl.glVertex3f(-1.0f, 1.0f, -1.0f);
      gl.glEnd();
      gl.glFlush();

      //change the speeds here
      xrot += .1f;
      yrot += .1f;
      zrot += .1f;
   }
   
   @Override
   public void dispose(GLAutoDrawable drawable) {
      // method body
   }
   
   @Override
   public void init(GLAutoDrawable drawable) {
	
      final GL2 gl = drawable.getGL().getGL2();
		
      gl.glShadeModel(GL2.GL_SMOOTH);
      gl.glClearColor(0f, 0f, 0f, 0f);
      gl.glClearDepth(1.0f);
      gl.glEnable(GL2.GL_DEPTH_TEST);
      gl.glDepthFunc(GL2.GL_LEQUAL);
      gl.glHint(GL2.GL_PERSPECTIVE_CORRECTION_HINT, GL2.GL_NICEST);
      
      //
      gl.glEnable(GL2.GL_TEXTURE_2D);
      
      
      try{
		
         File im = new File("C:\\Users\\Евгений\\Desktop\\Screenshot_1.png ");
         Texture t = TextureIO.newTexture(im, true);
         texture= t.getTextureObject(gl);
          
      }catch(IOException e){
         e.printStackTrace();
      }
   }
      
   @Override
   public void reshape(GLAutoDrawable drawable, int x, int y, int width, int height) {
   
      // TODO Auto-generated method stub
      final GL2 gl = drawable.getGL().getGL2();
      if(height <= 0)
         height = 1;
			
      final float h = (float) width / (float) height;
      gl.glViewport(0, 0, width, height);
      gl.glMatrixMode(GL2.GL_PROJECTION);
      gl.glLoadIdentity();
		
      glu.gluPerspective(45.0f, h, 1.0, 20.0);
      gl.glMatrixMode(GL2.GL_MODELVIEW);
      gl.glLoadIdentity();
   }
   private GLJPanel display;
 
   public static void main(String[] args) {
   
      // TODO Auto-generated method stub
      final GLProfile profile = GLProfile.get(GLProfile.GL2);
      GLCapabilities capabilities = new GLCapabilities(profile);
      
      // The canvas
      final GLCanvas glcanvas = new GLCanvas(capabilities);
      Cars r = new Cars();
		
      glcanvas.addGLEventListener(r);
      
      glcanvas.setSize(400, 400);
		
      final JFrame frame = new JFrame (" Textured Cube");
      
      frame.getContentPane().add(glcanvas);
      frame.setSize(frame.getContentPane().getPreferredSize());
      frame.setVisible(true);
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      glcanvas.addMouseListener(new MouseAdapter()
      {
          public void mousePressed/*Clicked*/(MouseEvent e)
          {
              System.out.println(e.getX() + " " + e.getY());
          }
      });
      /*
      frame.addMouseListener( new MouseAdapter()
      {
          public void mouseClicked(MouseEvent e)
          {
              System.out.println(e.getX() + " " + e.getY());
          }
      });
      */
      final FPSAnimator animator = new FPSAnimator(glcanvas, 300, true);
      animator.start();
   }
	
}
