import os
from PIL import Image


dir_path = os.path.dirname(os.path.realpath(__file__))
filelist = os.listdir(dir_path)
# filelist.sort(key=lambda x: int(x[:-4]))
print(filelist)



for file in filelist:
    filepath = dir_path + '/' + file


    name, ext = os.path.splitext(file)

    if ext == ".png":
        
        img = Image.open(filepath)

        (w, h) = img.size
        img = img.resize((int(w*1.07), int(h*2)))



        if not os.path.isdir(dir_path+"/bmp/"):
            os.mkdir(dir_path+"/bmp/")

        newfilepath = dir_path + "/bmp/" + name
        img.save(newfilepath+".bmp")

        print(file)

