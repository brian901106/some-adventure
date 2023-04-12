import cv2
import numpy as np
import os

dir_path = os.path.dirname(os.path.realpath(__file__)) + "/cropped"
filelist = os.listdir(dir_path)


def split(img_path,angle):
    
    # M = np.float32([[1, 0, 476], [0, 1, 0]])

    # #img = cv2.resize(img)
    # full_img = cv2.warpAffine(img, M, (1100, 800))

    
    # center = (550,85)

    
    # M2 = cv2.getRotationMatrix2D(center, angle, 1.0)
    # rotate_img = cv2.warpAffine(full_img, M2, (1100, 800))
    
    # scale = 1.5
    # center = (550*scale,85*scale)
    # resize_img = cv2.resize(rotate_img,(0,0),fx=scale,fy=scale,interpolation=cv2.INTER_AREA)

    center = (12,10)
    # print(img_path)
    img = cv2.imread(img_path)
    # 裁切區域的 x 與 y 座標（左上角）
    line_x = 11
    line_y = 0

    claw_x = 0
    claw_y = 10

    # 裁切區域的長度與寬度
    line_w = 2
    line_h = 10

    claw_w = 24
    claw_h = 20

    # 裁切圖片
    line_img = img[line_y:line_y+line_h, line_x:line_x+line_w]
    claw_img = img[claw_y:claw_y+claw_h, claw_x:claw_x+claw_w]

    return line_img,claw_img


if __name__ == "__main__":
    
    # 讀取
    for file in filelist:
        name, ext = os.path.splitext(file)

        if ext == ".png":
            
            print(file)

            if file == "03.png":
                angle = 0

                filepath = dir_path + '/' + file
                # rdimg = cv2.imread(filepath)

                newfilepath = dir_path + "/" +  str(angle) + "_" + "line" + ".png"
                cv2.imwrite(newfilepath, split(filepath,angle)[0])

                print(newfilepath)

                newfilepath = dir_path + "/" +  str(angle) + "_" + "claw" + ".png"
                cv2.imwrite(newfilepath, split(filepath,angle)[1])

                
                
                    
            




            # img_rotated = split_img(img, 0)

            
            # newfilepath = dir_path + "/rotate/" + str(angle) + "/" + file
            # cv2.imwrite(newfilepath, img_rotated)
            
            

            
            
            
            
            