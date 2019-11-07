package example;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author User
 */
public class GeneratePlaylist {
    
        class Type implements Comparable <Type>
        {
            float length;
            String name;
            @Override
            public int compareTo(Type tmp)
            {
                return (int)(this.length - tmp.length);
            }
            @Override
            public String toString() 
            {
                return "{" +
                "name='" + name + '\'' +
                ", age=" + length +
                '}';
            }
        }
        //public Map<Float, String> music,talk;
        public ArrayList<Type> music,talk;
        
        SecureRandom random;
        public GeneratePlaylist()
        {
            //music = new HashMap<Float, String>();
            //talk = new HashMap<Float, String>();
            music = new ArrayList<Type>();
            talk = new ArrayList<Type>();
            random = new SecureRandom(/*System.currentTimeMillis()*/);
        }
        public void LoadFromFiles()
        {
            try {
            File file = new File("C:\\Users\\User\\Desktop\\Tropic-Island\\Tropic-Island\\C++\\Project1\\Project1\\playlist4.m3u8");
            //создаем объект FileReader для объекта File
            //FileReader fr = new FileReader(file);
            
	    FileInputStream fStream = new FileInputStream(file);
            InputStreamReader fr = new InputStreamReader(fStream, "windows-1251");
            //создаем BufferedReader с существующего FileReader для построчного считывания
            BufferedReader reader = new BufferedReader(fr);
            // считаем сначала первую строку
            Type tmp = new Type();
            tmp.length = (float) 0.0;
            tmp.name = "";
            String line = reader.readLine();
            while (line != null) {
                tmp.name = line;
                line = reader.readLine();
                tmp.length = Float.parseFloat(line);
                music.add(tmp);
                //System.out.println(tmp.name+"\n"+tmp.length);
                // считываем остальные строки в цикле
                line = reader.readLine();
                tmp = new Type();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
           
            try {
            File file = new File("C:\\Users\\User\\Desktop\\Tropic-Island\\Tropic-Island\\C++\\Project1\\Project1\\playlist5.m3u8");
            //создаем объект FileReader для объекта File
            //FileReader fr = new FileReader(file);
            
	    FileInputStream fStream = new FileInputStream(file);
            InputStreamReader fr = new InputStreamReader(fStream, "windows-1251");
            //создаем BufferedReader с существующего FileReader для построчного считывания
            BufferedReader reader = new BufferedReader(fr);
            // считаем сначала первую строку
            Type tmp = new Type();
            tmp.length = (float) 0.0;
            tmp.name = "";
            String line = reader.readLine();
            while (line != null) {
                tmp.name = line;
                line = reader.readLine();
                tmp.length = Float.parseFloat(line);
                talk.add(tmp);
                //System.out.println(tmp.name+"\n"+tmp.length);
                // считываем остальные строки в цикле
                line = reader.readLine();
                tmp = new Type();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
          Collections.sort(music);
          
            Collections.sort(talk);
       /*
           for(Type t:music)
           {
               System.out.println(t.name+"\n"+t.length);
           }
           */
           //for (int i = 0; i < music.size(); i++)
             //System.out.print(music.get(i).length + " ");
           ArrayList<Type>  vec ;
           for(int j=0;j<5;j++)
           {
           
            float length = (float) 3600.0, currentlength = 0.0f;
            vec = new ArrayList<Type> ();

            //srand(time(0));
            currentlength = AddMusic(music, vec, currentlength, length);
            //System.out.println("vec: ");
            //for (int i = 0; i < vec.size(); i++)
		//System.out.print(vec.get(i).length +" ");
            System.out.println("\n+cl:"+ currentlength);
	
            //for (int i = 0; i < talk.size(); i++)
		//System.out.print(talk.get(i).length + " ");
            
            length = (float) (2.5 * 3600.0);
            currentlength = AddTalk(talk, vec, currentlength, length);
            currentlength = AddMusic(music, vec, currentlength, length);
	//System.out.println("vec: ");
	//for (int i = 0; i < vec.size(); i++)
		//System.out.print(vec.get(i).length + " ");
	System.out.println("\n+cl:" + currentlength);

	length = (float) 10800.0;
	//
	currentlength = AddTalk(talk, vec, currentlength, length);
	//
	currentlength = AddMusic(music, vec, currentlength, length);
	//System.out.println("vec: ");
	//for (int i = 0; i < vec.size(); i++)
		//System.out.print(vec.get(i).length+ " ");
	System.out.println("\n+cl:"+ currentlength);
        
        //try(FileWriter writer = new FileWriter("playlist.m3u8", false))
        try(Writer writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("playlist"+Integer.toString(j)+".m3u8"), "windows-1251")))
        {
            
            writer.write("#EXTM3U\n");
	for (int i = 0; i < vec.size(); i++)
	{
		writer.write("#EXTINF:");
		writer.write(Integer.toString((int)vec.get(i).length));
		writer.write(",");
		writer.write(vec.get(i).name);
		writer.write("\n");
		writer.write(vec.get(i).name);
		writer.write("\n");
	}    
            writer.flush();
        }
        catch(IOException ex){
             
            System.out.println(ex.getMessage());
        } 
        vec.clear();
           }
       }
       public float AddMusic(ArrayList<Type> src, ArrayList<Type> dst,float currentlength, float maxlength)
        {
            int num;
            for (int i = 0; i < 100; i++)
            {
		num = Random(src);
                //System.out.print(Integer.toString(num)+" ");
		if (src.get(num).length + currentlength <= maxlength)
		{
			dst.add(src.get(num));
			currentlength += dst.get(dst.size()-1).length;
		}
            }   
            
            for (int ii = 0; ii < src.size(); ii++)
            for (int i = 0; i < src.size(); i++)
            {   
		if (src.get(i).length + currentlength <= maxlength)
		{
			dst.add(src.get(i));
			currentlength += dst.get(dst.size()-1).length;
		}
            }
            return currentlength;
        }
        public int Random(ArrayList<Type> vector)
        {
            int min = 0, max = vector.size()-1;
            return min + random.nextInt(max - min + 1);
        }
        float AddTalk(ArrayList<Type> src,ArrayList<Type> dst, float currentlength,float maxlength)
        {
            int num;
            boolean b = false;
            for (int i = 0; i < 1; i++)
            {
		num = Random(src);
		if (src.get(num).length + currentlength <= maxlength)
		{
			b = true;
			dst.add(src.get(num));
			currentlength += dst.get(dst.size()-1).length;
		}
		if (!b)
			AddTalk(src, dst, currentlength, maxlength);
            }
            return currentlength;
        }
}
