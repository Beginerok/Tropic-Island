
import java.io.Serializable;
import org.apache.commons.codec.digest.DigestUtils;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author User
 */
public class Users implements Serializable {
 
    private static final long serialVersionUID = 1L;
 
    private int id;
    private String nickname;
    private String password;
    private String email;
    private String reg_date;
    private String ip;
    private String user_agent;
    private String phone;
     
    public Users(){ }
    public Users(String nickname,String email,String password,String reg_date,String ip,String user_agent,String phone){
        this.nickname = nickname;
        this.email = email;
        this.password = md5Apache(password);
        this.reg_date = reg_date;
        this.ip=ip;
        this.user_agent=user_agent;
        this.phone=phone;
    }
    public Users(int id, String nickname,String email,String password,boolean hash,String reg_date,String ip,String user_agent,String phone){
        this.id = id;
        this.nickname = nickname;
        this.email = email;
        if(hash)
            this.password = md5Apache(password);
        else
            this.password = password;    
    }
     
    public int getId() {
        return id;
    }
     
    public String getnickname() {
        return nickname;
    }
 
    public void setnickname(String nickname) {
        this.nickname = nickname;
    }
 
    public String getPassword() {
        return password;
    }
 
    public void setPassword(String password) {
        this.password = md5Apache(password);
    }
 
    public String getEmail() {
        return email;
    }
 
    public void setEmail(String email) {
        this.email = email;
    }
    public String getPhone()
    {
        return this.phone;
    }  public String getIp()
    {
        return this.ip;
    }  public String getUser_agent()
    {
        return this.user_agent;
    }  public String getReg_date()
    {
        return this.reg_date;
    }
    public static String md5Apache(String st) {
        String md5Hex = DigestUtils.md5Hex(st);
        return md5Hex;
    }
 }
