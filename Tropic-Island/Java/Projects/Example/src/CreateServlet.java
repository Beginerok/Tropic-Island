
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author User
 */
@WebServlet("/create")
public class CreateServlet extends HttpServlet{
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException {
        getServletContext().getRequestDispatcher("/create.jsp").forward(request, response);
    }
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException {
        try {
            String nickname = request.getParameter("nickname");
            String  email = request.getParameter("email");
            String  password = request.getParameter("password");
            Users users = new Users(nickname,email, password);
            UsersDB.insert(users);
            response.sendRedirect(/*request.getContextPath()+*/"/index.html");
        }
        catch(Exception ex) {
            getServletContext().getRequestDispatcher("/create.jsp").forward(request, response); 
        }
    }
}
