/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author User
 */
import java.io.File;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
 
@WebServlet("/ftp")
public class FTP extends HttpServlet {
    List<String> listpaths;
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        listpaths = new ArrayList<String>();
        String currentWorkingDir = System.getProperty("user.dir");
        File file = new File(currentWorkingDir);
        //System.out.println(currentWorkingDir);
        showFilesAndDirectoryes(file);
        response.setContentType("text/html");
        PrintWriter writer = response.getWriter();
        try {
            writer.println("<h2>Hello from HelloServlet</h2>");
            for(int i=0;i<listpaths.size();i++)
                writer.println("<p>"+listpaths.get(i)+"</p>");
        } finally {
            writer.close();  
        }
        listpaths.clear();
    }
    
      public void showFilesAndDirectoryes (File f) {
    
        File[] files = f.listFiles();
        for(File p:files){
            if (!p.isDirectory ()) {
                System.out.println (p.getName ());
                listpaths.add(p.getName());
                System.out.println (p.getAbsolutePath());
            }
            if (p.isDirectory ()) { 
            try {
                showFilesAndDirectoryes (p); 
            }
            catch(Exception e){
                 e.printStackTrace();
              }
            }
        }
    }
}