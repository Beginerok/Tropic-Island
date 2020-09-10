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

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import java.awt.DisplayMode;
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
import com.jogamp.opengl.glu.*;


import javax.swing.JFrame;

import com.jogamp.opengl.util.FPSAnimator;
import java.security.SecureRandom;

import java.util.ArrayList;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;





public class Cars implements GLEventListener {

   public static DisplayMode dm, dm_old;
   private GLU glu = new GLU();
   private float xrot,yrot,zrot;
   private int texture;
   static Scene1 scene;
   static Vector<String> drum;
   static boolean b;
   static SecureRandom random;
   @Override
   public void display(GLAutoDrawable drawable) {
      final GL2 gl = drawable.getGL().getGL2();
      gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);
      gl.glLoadIdentity(); // Reset The View
      gl.glTranslatef(0f, 0f, -3.0f);
      scene.ShowDrum(5, 6, drum, gl);
      scene.ShowBorder(gl);
      
      gl.glFlush();
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
      
      gl.glEnable(GL2.GL_TEXTURE_2D);
      
      try {
           scene.LoadDrum(drawable);
           scene.LoadBorder(drawable);
      } catch (IOException ex) {
           Logger.getLogger(Cars.class.getName()).log(Level.SEVERE, null, ex);
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
      //gl.glMatrixMode(GL2.GL_MODELVIEW);
      gl.glMatrixMode(GL2.GL_PROJECTION);
      gl.glLoadIdentity();
      //gl.glOrtho(1, -1, -1, 1, -3, 3);
      glu.gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
      glu.gluPerspective(45.0f, h, 1.0, 20.0);
      gl.glMatrixMode(GL2.GL_MODELVIEW);
      gl.glLoadIdentity();
   }
   static int Random(ArrayList<String> vector)
   {
        int min = 0, max = vector.size()-1;
        return min + random.nextInt(max - min + 1);
   }
   public static void main(String[] args) {
      ArrayList<String> vector = new ArrayList<String>();
      vector.add("auto1");
      vector.add("auto2");
      vector.add("auto3");
      vector.add("auto4");
      vector.add("auto5");
      vector.add("bonus");
      vector.add("wild");
      random = new SecureRandom();
      b = false;
      Cars r = new Cars();
      scene = new Scene1();
      scene.Scene();
      drum = new Vector<String>();
     
      for(int i=0;i<30;i++)
          drum.add("auto1");
      // TODO Auto-generated method stub
      final GLProfile profile = GLProfile.get(GLProfile.GL2);
      GLCapabilities capabilities = new GLCapabilities(profile);
      
      // The canvas
      final GLCanvas glcanvas = new GLCanvas(capabilities);
      
		
      glcanvas.addGLEventListener(r);
      
      glcanvas.setSize(400, 400);
		
      final JFrame frame = new JFrame ("Cars");
      
      frame.getContentPane().add(glcanvas);
      frame.setSize(frame.getContentPane().getPreferredSize());
      frame.setVisible(true);
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      glcanvas.addMouseListener(new MouseAdapter()
      {
          public void mouseClicked(MouseEvent e)
          {
              drum.clear();
              int r;
               for(int i=0;i<30;i++)
               {
                   r = Random(vector);
                   //System.out.println(r);
                   drum.add(vector.get(r));
               }
            
             //  b=true;
              //if(b)
                  scene.StartRotate();
              System.out.println(e.getX() + " " + e.getY());
          }
      });
      final FPSAnimator animator = new FPSAnimator(glcanvas, 300, true);
      animator.start();

    }
	
}
