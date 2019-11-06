package example;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

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
    
        public Map<Float, String> music,talk;
        public GeneratePlaylist()
        {
            music = new HashMap<Float, String>();
            talk = new HashMap<Float, String>();
        }
        public void LoadFromFiles()
        {
            try {
            File file = new File("C:\\Users\\User\\source\\repos\\Project1\\Project1\\playlist4.m3u8");
            //создаем объект FileReader для объекта File
            FileReader fr = new FileReader(file);
            //создаем BufferedReader с существующего FileReader для построчного считывания
            BufferedReader reader = new BufferedReader(fr);
            // считаем сначала первую строку
            String str="";
            float length=(float) 0.0;
            String line = reader.readLine();
            while (line != null) {
                str = line;
                line = reader.readLine();
                length = Float.parseFloat(line);
                music.put(length,str);
                System.out.println(str+"\n"+length);
                // считываем остальные строки в цикле
                line = reader.readLine();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
            try {
            File file = new File("C:\\Users\\User\\source\\repos\\Project1\\Project1\\playlist5.m3u8");
            //создаем объект FileReader для объекта File
            FileReader fr = new FileReader(file);
            //создаем BufferedReader с существующего FileReader для построчного считывания
            BufferedReader reader = new BufferedReader(fr);
            // считаем сначала первую строку
            String str="";
            float length=(float) 0.0;
            String line = reader.readLine();
            while (line != null) {
                str = line;
                line = reader.readLine();
                length = Float.parseFloat(line);
                talk.put(length,str);
                System.out.println(str+"\n"+length);
                // считываем остальные строки в цикле
                line = reader.readLine();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        }
       public void GeneratePart()
       {
           float length = (float) 3600.0, currentlength = (float) 0.0;
       
       }
       public void AddMusic(Map<Float, String> src, Map<Float, String> dst, float currentlength, float maxlength)
        {
	int num;
	for (int i = 0; i < 10; i++)
	{
		num = Random(src);
                src.
		if (src.at(num).length + currentlength <= maxlength)
		{
			dst.push_back(src.at(num));
			currentlength += dst.back().length;
		}
	}
	for (int i = 0; i < src->size(); i++)
	{
		if (src.at(i).length + currentlength <= maxlength)
		{
			dst.push_back(src.at(i));
			currentlength += dst.back().length;
		}
	}
}
}
