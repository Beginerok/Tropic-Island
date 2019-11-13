print('hello world!')
from mutagen.mp3 import MP3
ff = open('C:\\Users\\User\\source\\repos\\Project1\\Project1\\playlist3.m3u8', 'r')
array_of_strings = ff.read().split('\n')
ff.close()
ff = open('C:\\Users\\User\\source\\repos\\Project1\\Project1\\playlist5.m3u8','w')
for i in range(len(array_of_strings)):
    if i % 2 == 0:
        f = MP3(array_of_strings[i])
        ff.write(array_of_strings[i]+'\n')
        ff.write(str(f.info.length)+'\n')
ff.close()
print('hello world!')