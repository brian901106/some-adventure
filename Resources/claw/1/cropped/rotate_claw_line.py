import cv2
import numpy as np
import os
import math

dir_path = os.path.dirname(os.path.realpath(__file__))
filelist = os.listdir(dir_path)


def rotate_img(img,angle):
    
    M = np.float32([[1, 0, 0], [0, 1, 0]])

    #img = cv2.resize(img)
    full_img = cv2.warpAffine(img, M, (24, 20))

    
    center = (12,0)

    
    M2 = cv2.getRotationMatrix2D(center, angle, 1.0)
    rotate_img = cv2.warpAffine(full_img, M2, (36, 30))
    
    scale = 1.5
    center = (12*scale,12*scale)
    resize_img = cv2.resize(rotate_img,(0,0),fx=scale,fy=scale,interpolation=cv2.INTER_AREA)

    # 裁切區域的 x 與 y 座標（左上角）
    x = int(0*(scale-1))
    y = int(0*(scale-1))

    # 裁切區域的長度與寬度
    w = 36
    h = 30

    # 裁切圖片
    crop_img = resize_img[y:y+h, x:x+w]

    return crop_img

def rotate_img_line(img,angle):
    
    M = np.float32([[1, 0, 10], [0, 1, 10]])

    #img = cv2.resize(img)
    full_img = cv2.warpAffine(img, M, (22, 30))

    
    center = (1+10,5+10)

    
    M2 = cv2.getRotationMatrix2D(center, angle, 1.0)
    rotate_img = cv2.warpAffine(full_img, M2, (22, 30))
    
    scale = 1.5
    center = (11*scale,15*scale)
    resize_img = cv2.resize(rotate_img,(0,0),fx=scale,fy=scale,interpolation=cv2.INTER_AREA)

    # 裁切區域的 x 與 y 座標（左上角）
    x = int(0*(scale-1))
    y = int(0*(scale-1))

    # 裁切區域的長度與寬度
    w = 22
    h = 30

    # 裁切圖片
    crop_img = resize_img[y:y+h, x:x+w]

    return crop_img

if __name__ == "__main__":
    
    # 讀取
    for file in filelist:
        name, ext = os.path.splitext(file)

        if ext == ".png":
            if name =="0_claw":
            
                print(file)
                filepath = dir_path + '/' + file
                img = cv2.imread(filepath)


                angles_a_round = [70, 69, 67, 64, 60, 56, 50, 44, 36, 28, 20, 15, 8, 2, -5, -14, -23, -30, -36, -42, -48, -53, -57, -61, -65, -67, -68, -68, -68, -67, -66, -63, -59, -54, -48, -42, -35, -28, -20, -12, -5, 2, 10, 17, 25, 33, 39, 46, 52, 57, 61, 64, 67, 69, 70]
                
                num = 1
                for angle in angles_a_round:

                    img_rotated = rotate_img(img, angle)

                    if not os.path.isdir(dir_path+"/rotate/"):
                        os.mkdir(dir_path+"/rotate/")
                    if not os.path.isdir(dir_path+"/rotate/"+str(angle)):
                        os.mkdir(dir_path+"/rotate/"+str(angle))

                    newfilepath = dir_path + "/rotate/" + str(angle) + "/" + file
                    cv2.imwrite(newfilepath, img_rotated)
                    num = num + 1
            
            if name =="0_line":
            
                print(file)
                filepath = dir_path + '/' + file
                img = cv2.imread(filepath)


                angles_a_round = [70, 69, 67, 64, 60, 56, 50, 44, 36, 28, 20, 15, 8, 2, -5, -14, -23, -30, -36, -42, -48, -53, -57, -61, -65, -67, -68, -68, -68, -67, -66, -63, -59, -54, -48, -42, -35, -28, -20, -12, -5, 2, 10, 17, 25, 33, 39, 46, 52, 57, 61, 64, 67, 69, 70]
                
                num = 1
                for angle in angles_a_round:

                    img_rotated = rotate_img_line(img, angle)

                    if not os.path.isdir(dir_path+"/rotate/"):
                        os.mkdir(dir_path+"/rotate/")
                    if not os.path.isdir(dir_path+"/rotate/"+str(angle)):
                        os.mkdir(dir_path+"/rotate/"+str(angle))

                    newfilepath = dir_path + "/rotate/" + str(angle) + "/" + file
                    cv2.imwrite(newfilepath, img_rotated)
                    num = num + 1
            
            

            
            
            
            
            