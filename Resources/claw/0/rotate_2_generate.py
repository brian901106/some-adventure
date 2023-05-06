import cv2
import numpy as np
import os
import math

dir_path = os.path.dirname(os.path.realpath(__file__))
filelist = os.listdir(dir_path)


def rotate_img(img,angle):
    
    M = np.float32([[1, 0, 476], [0, 1, 0]])

    #img = cv2.resize(img)
    full_img = cv2.warpAffine(img, M, (1100, 800))

    
    center = (550,85)

    
    M2 = cv2.getRotationMatrix2D(center, angle, 1.0)
    rotate_img = cv2.warpAffine(full_img, M2, (1100, 800))
    
    scale = 1.5
    center = (550*scale,85*scale)
    resize_img = cv2.resize(rotate_img,(0,0),fx=scale,fy=scale,interpolation=cv2.INTER_AREA)

    # 裁切區域的 x 與 y 座標（左上角）
    x = int(550*(scale-1))
    y = int(85*(scale-1))

    # 裁切區域的長度與寬度
    w = 1100
    h = 800

    # 裁切圖片
    crop_img = resize_img[y:y+h, x:x+w]

    return crop_img


if __name__ == "__main__":
    
    # 讀取
    for file in filelist:
        name, ext = os.path.splitext(file)

        if ext == ".png":
            
            print(file)
            filepath = dir_path + '/' + file
            img = cv2.imread(filepath)


            num = 1

            # for angle in range(70,5,-5):

            #     img_rotated = rotate_img(img, -angle)

            #     if not os.path.isdir(dir_path+"/rotate/"):
            #         os.mkdir(dir_path+"/rotate/")


            #     newfilepath = dir_path + "/rotate/" + str(num) +".png"
            #     cv2.imwrite(newfilepath, img_rotated)
            #     num = num + 1

            # angle = 0
            # img_rotated = rotate_img(img, angle)

            # if not os.path.isdir(dir_path+"/rotate/"):
            #     os.mkdir(dir_path+"/rotate/")


            # newfilepath = dir_path + "/rotate/" + str(num) +".png"
            # cv2.imwrite(newfilepath, img_rotated)

            # num = num + 1
            
            #angles_a_round = [70, 69, 67, 64, 60, 56, 50, 44, 36, 28, 20, 15, 8, 2, -5, -14, -23, -30, -36, -42, -48, -53, -57, -61, -65, -67, -68, -68, -68, -67, -66, -63, -59, -54, -48, -42, -35, -28, -20, -12, -5, 2, 10, 17, 25, 33, 39, 46, 52, 57, 61, 64, 67, 69, 70]
            angles_a_round = angles_a_round =[70, 70, 70, 70, 70, 69, 68, 66, 64, 62, 59, 55, 51, 47, 42, 37, 32, 27, 21, 15, 9, 3, -2, -8, -15, -20, -26, -32, -37, -42, -46, -50, -54, -57, -60, -63, -65, -67, -68, -68, -68, -68, -67, -66, -65, -63, -60, -57, -53, -50, -45, -40, -35, -29, -24, -18, -12, -6, 0, 5, 11, 17, 23, 29, 34, 39, 44, 49, 53, 57, 60, 63, 65, 67, 69, 70, 70] 
            

            for angle in angles_a_round:

                img_rotated = rotate_img(img, angle)

                if not os.path.isdir(dir_path+"/rotate/"):
                    os.mkdir(dir_path+"/rotate/")


                newfilepath = dir_path + "/rotate/" + str(num) +".png"
                cv2.imwrite(newfilepath, img_rotated)

                num = num + 1
            

            
            
            
            
            