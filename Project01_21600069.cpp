//
//  main.cpp
//  opencv_project
//
//  Created by 김민지 on 02/09/2020.
//  Copyright © 2020 김민지. All rights reserved.
//

#include "cv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main() {
    Mat lena, colorful, balancing;
    Mat table(1, 256, CV_8U);
    uchar* p;
    Mat channels_01[3];
    Mat channels_02[3];
    Mat channels_03[3];
    Mat channels_04[3];

    int u_input;
    
    lena = imread("lena.png");
    colorful = imread("colorful.jpg");
    balancing = imread("balancing.jpg");
    
    imshow("lena", lena);
    imshow("colorful", colorful);
    imshow("balancing", balancing);
    
    
    
    u_input = waitKey(0);
    
    while(u_input!=27){
        switch (u_input) {
            case 27:
                //break
                break;
                
            case 110:
                //u_input = n
                for(int i = 0; i < lena.cols; i++){
                    for(int j = 0; j < lena.rows; j++){
                        lena.at<Vec3b>(j, i)[0] = 255 - lena.at<Vec3b>(j, i)[0];
                        lena.at<Vec3b>(j, i)[1] = 255 - lena.at<Vec3b>(j, i)[1];
                        lena.at<Vec3b>(j, i)[2] = 255 - lena.at<Vec3b>(j, i)[2];
                    }
                }
                imshow("lena", lena);
                break;
                
            case 103:
                //u_input = g
                p = table.ptr();
                for( int i = 0; i < 256; ++i) p[i] = saturate_cast<uchar>(pow(i / 255.0, 2.5) * 255.0);
                LUT(lena, table, lena);
                imshow("lena", lena);
                break;
                
            case 104:
                //u_input = h
                cvtColor(lena, lena, CV_BGR2HSV);
                split(lena, channels_01);
                equalizeHist(channels_01[2], channels_01[2]);
                merge(channels_01, 3, lena);
                cvtColor(lena, lena, CV_HSV2BGR);
                imshow("lena", lena);
                break;
                
            case 115:
                //u_input = s
                cvtColor(colorful, colorful, CV_BGR2HSV);
                split(colorful, channels_02);
                for(int i = 0; i < channels_02[0].cols; i++) {
                    for(int j = 0; j < channels_02[0].rows; j++){
                        if(channels_02[0].at<uchar>(j, i)<=9 || channels_02[0].at<uchar>(j, i)>=23){
                            channels_02[1].at<uchar>(j, i) = 0;
                        }
                    }
                }
                merge(channels_02, 3, colorful);
                cvtColor(colorful, colorful, CV_HSV2BGR);
                imshow("colorful", colorful);
                break;
            
            case 99:
                //u_input = c
                cvtColor(colorful, colorful, CV_BGR2HSV);
                split(colorful, channels_03);
                for(int i = 0; i < channels_03[0].cols; i++) {
                    for(int j = 0; j < channels_03[0].rows; j++){
                        
                        if(channels_03[0].at<uchar>(j, i)>129){
                            channels_03[0].at<uchar>(j, i) = channels_03[0].at<uchar>(j, i)-129;
                        }else{
                            channels_03[0].at<uchar>(j, i) = channels_03[0].at<uchar>(j, i)+50;
                        }
                    }
                }
                merge(channels_03, 3, colorful);
                cvtColor(colorful, colorful, CV_HSV2BGR);
                imshow("colorful", colorful);
                break;
                
            case 97:
                //u_input = a
                blur(balancing, balancing, Size(9,9));
                imshow("balancing", balancing);
                break;
                
            case 119:
                //u_input = w
                int sum_R, sum_G, sum_B;
                float avg_R, avg_G, avg_B;

                sum_R = 0;
                sum_G = 0;
                sum_B = 0;

                for(int i = 0; i < balancing.cols; i++){
                    for(int j = 0; j < balancing.rows; j++){
                        sum_B = sum_B + balancing.at<Vec3b>(j, i)[0];
                        sum_G = sum_G + balancing.at<Vec3b>(j, i)[1];
                        sum_R = sum_R + balancing.at<Vec3b>(j, i)[2];
                    }
                }
                
                avg_B = sum_B/(balancing.cols*balancing.rows);
                avg_G = sum_G/(balancing.cols*balancing.rows);
                avg_R = sum_R/(balancing.cols*balancing.rows);
                
                for(int i = 0; i < balancing.cols; i++){
                    for(int j = 0; j < balancing.rows; j++){
                        balancing.at<Vec3b>(j, i)[0] = 128.0/avg_B*balancing.at<Vec3b>(j, i)[0];
                        balancing.at<Vec3b>(j, i)[1] = 128.0/avg_G*balancing.at<Vec3b>(j, i)[1];
                        balancing.at<Vec3b>(j, i)[2] = 128.0/avg_R*balancing.at<Vec3b>(j, i)[2];
                    }
                }
                
                normalize(balancing, balancing, 0, 255, NORM_MINMAX);
                
                imshow("balancing", balancing);
                break;
                
            case 114:
                //u_input = r
                lena = imread("lena.png");
                colorful = imread("colorful.jpg");
                balancing = imread("balancing.jpg");
                
                imshow("lena", lena);
                imshow("colorful", colorful);
                imshow("balancing", balancing);
                break;
                
            default:
                break;
        }
        u_input = waitKey(0);
    }
    
    
    
    return 0;
}

