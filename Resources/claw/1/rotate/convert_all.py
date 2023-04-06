import os
from PIL import Image


def convert_files(dir_path):
    filelist = os.listdir(dir_path)

    for file in filelist:
        filepath = dir_path + '/' + file


        name, ext = os.path.splitext(file)

        if ext == ".png":
            
            img = Image.open(filepath)

            (w, h) = img.size
            img = img.resize((int(w*1), int(h*1)))



            if not os.path.isdir(dir_path+"/bmp/"):
                os.mkdir(dir_path+"/bmp/")

            newfilepath = dir_path + "/bmp/" + name
            img.save(newfilepath+".bmp")

            print(file)

if __name__ == '__main__':

    dir_path = os.path.dirname(os.path.realpath(__file__))
    print(dir_path)
    filelist = os.listdir(dir_path)
    # filelist.sort(key=lambda x: int(x[:-4]))
    print(filelist)

    for file in filelist:
        dir_path = os.path.dirname(os.path.realpath(__file__))
        filelist = os.listdir(dir_path)
        filepath = dir_path + '/' + file

        if (os.path.isdir(filepath)):
            dir_path = os.path.dirname(os.path.realpath(__file__))+ '/' + file
            
            print(dir_path)
            convert_files(dir_path)

