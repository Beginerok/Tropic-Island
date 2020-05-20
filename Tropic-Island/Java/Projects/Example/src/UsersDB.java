
import java.sql.*;
import java.util.ArrayList;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author User
 */
public class UsersDB {
    
 
    //private static String url = "jdbc:mysql://localhost/test?serverTimezone=Europe/Moscow";
    private static String url = "jdbc:mysql://185.26.122.49/host6491_test?serverTimezone=Europe/Moscow";
    private static String username = "host6491_root";
    private static String password = "R0oT";
    
    public static ArrayList<Users> select() {
         
        ArrayList<Users> users = new ArrayList<Users>();
        try{
            Class.forName("com.mysql.cj.jdbc.Driver").getDeclaredConstructor().newInstance();
            try (Connection conn = DriverManager.getConnection(url, username, password)){
                  
                Statement statement = conn.createStatement();
                ResultSet resultSet = statement.executeQuery("SELECT * FROM users");
                while(resultSet.next()){
                      
                    int id = resultSet.getInt(1);
                    String nickname = resultSet.getString(2);
                    String email = resultSet.getString(3);
                    String pass = resultSet.getString(4);
                    String reg_date = resultSet.getString(5);
                    String ip = resultSet.getString(6);
                    String user_agent = resultSet.getString(7);
                    String phone = resultSet.getString(8);
                    Users user = new  Users(id, nickname, email,pass,false,reg_date,ip,user_agent,phone);
                    users.add(user);
                }
            }
        }
        catch(Exception ex){
            System.out.println(ex);
        }
        return users;
    }
    public static Users selectOne(int id) {
         
        Users user = null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver").getDeclaredConstructor().newInstance();
            try (Connection conn = DriverManager.getConnection(url, username, password)){
                  
                String sql = "SELECT * FROM users WHERE id=?";
                try(PreparedStatement preparedStatement = conn.prepareStatement(sql)){
                    preparedStatement.setInt(1, id);
                    ResultSet resultSet = preparedStatement.executeQuery();
                    if(resultSet.next()){
 
                        int userId = resultSet.getInt(1);
                        String nickname = resultSet.getString(2);
                        String email = resultSet.getString(3);
                        String pass = resultSet.getString(4);
                        String reg_date = resultSet.getString(5);
                        String ip = resultSet.getString(6);
                        String user_agent = resultSet.getString(7);
                        String phone = resultSet.getString(8);
                        user = new Users(userId, nickname, email,pass,false,reg_date,ip,user_agent,phone);
                    }
                }
            }
        }
        catch(Exception ex){
            System.out.println(ex);
        }
        return user;
    }
    public static int insert(Users users) {
         
        try{
            Class.forName("com.mysql.cj.jdbc.Driver").getDeclaredConstructor().newInstance();
            try (Connection conn = DriverManager.getConnection(url, username, password)){
                  
                String sql = "INSERT INTO users (nickname,email,password,reg_date,ip,user_agent,phone) Values (?, ?, ?, ?,?,?,?)";
                try(PreparedStatement preparedStatement = conn.prepareStatement(sql)){
                    preparedStatement.setString(1, users.getnickname());
                    preparedStatement.setString(2, users.getEmail());
                    preparedStatement.setString(3, users.getPassword());
                    
                    preparedStatement.setString(4, users.getReg_date());
                    preparedStatement.setString(5, users.getIp());
                    preparedStatement.setString(6, users.getUser_agent());
                    preparedStatement.setString(7, users.getPhone());
                    return  preparedStatement.executeUpdate();
                }
            }
        }
        catch(Exception ex){
            System.out.println(ex);
        }
        return 0;
    }
     
    public static int update(Users users) {
         
        try{
            Class.forName("com.mysql.cj.jdbc.Driver").getDeclaredConstructor().newInstance();
            try (Connection conn = DriverManager.getConnection(url, username, password)){
                  
                String sql = "UPDATE users SET nickname = ?,email = ?, password = ?, phone = ? WHERE id = ?";
                try(PreparedStatement preparedStatement = conn.prepareStatement(sql)){
                    preparedStatement.setString(1, users.getnickname());
                    preparedStatement.setString(2, users.getEmail());
                    preparedStatement.setString(3, users.getPassword());
                    preparedStatement.setString(3, users.getPhone());
                    preparedStatement.setInt(4, users.getId());
                      
                    return  preparedStatement.executeUpdate();
                }
            }
        }
        catch(Exception ex){
            System.out.println(ex);
        }
        return 0;
    }
    public static int delete(int id) {
         
        try{
            Class.forName("com.mysql.cj.jdbc.Driver").getDeclaredConstructor().newInstance();
            try (Connection conn = DriverManager.getConnection(url, username, password)){
                  
                String sql = "DELETE FROM users WHERE id = ?";
                try(PreparedStatement preparedStatement = conn.prepareStatement(sql)){
                    preparedStatement.setInt(1, id);
                      
                    return  preparedStatement.executeUpdate();
                }
            }
        }
        catch(Exception ex){
            System.out.println(ex);
        }
        return 0;
    }
}
