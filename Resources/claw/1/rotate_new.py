import cv2
import numpy as np
import os

dir_path = os.path.dirname(os.path.realpath(__file__))
filelist = os.listdir(dir_path)


def rotate_img(img,angle):
    
    M = np.float32([[1, 0, 476], [0, 1, 0]])

    #img = cv2.resize(img)
    img2 = cv2.warpAffine(img, M, (1100, 800))

    
    center = (550,85)
    M2 = cv2.getRotationMatrix2D(center, angle, 1.0)
    rotate_img = cv2.warpAffine(img2, M2, (1100, 800))
    
    return rotate_img


if __name__ == "__main__":
    
    # 讀取
    for file in filelist:
        name, ext = os.path.splitext(file)

        if ext == ".png":
            
            print(file)
            filepath = dir_path + '/' + file
            img = cv2.imread(filepath)


            num = 0

            for angle in range(70,5,-5):

                img_rotated = rotate_img(img, -angle)

                if not os.path.isdir(dir_path+"/rotate/"):
                    os.mkdir(dir_path+"/rotate/")
                if not os.path.isdir(dir_path+"/rotate/"+str(-angle)):
                    os.mkdir(dir_path+"/rotate/"+str(-angle))

                newfilepath = dir_path + "/rotate/" + str(-angle) + "/" + file
                cv2.imwrite(newfilepath, img_rotated)

            angle = 0
            img_rotated = rotate_img(img, angle)

            if not os.path.isdir(dir_path+"/rotate/"):
                os.mkdir(dir_path+"/rotate/")
            if not os.path.isdir(dir_path+"/rotate/"+str(angle)):
                os.mkdir(dir_path+"/rotate/"+str(angle))

            newfilepath = dir_path + "/rotate/" + str(angle) + "/" + file
            cv2.imwrite(newfilepath, img_rotated)
            
            for angle in range(5,71,5):

                img_rotated = rotate_img(img, angle)

                if not os.path.isdir(dir_path+"/rotate/"):
                    os.mkdir(dir_path+"/rotate/")
                if not os.path.isdir(dir_path+"/rotate/"+str(angle)):
                    os.mkdir(dir_path+"/rotate/"+str(angle))

                newfilepath = dir_path + "/rotate/" + str(angle) + "/" + file
                cv2.imwrite(newfilepath, img_rotated)
            
            

            
            
            
            
            