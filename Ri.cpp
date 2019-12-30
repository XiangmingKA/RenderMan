//
//  Ri.cpp
//  CS285_Assignment_2.2
//
//  Created by 喀相明 on 2019/5/3.
//  Copyright © 2019 喀相明. All rights reserved.
//

#include "Ri.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Ri.h"
#include "My_Ri.h"
#include "math.h"
#include "Transformation.h"
#include "Primes.h"
#include "Projection.h"
#include "Display.h"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
using namespace Eigen;

RtFloat aspectRatio=4/3;
Matrix4f projectionMatrix;
Matrix4f transformMatrix;
Matrix4f current_transMatrix;
Matrix4f worldMatrix;

Vector3f current_Color;
Vector3f current_Opacity;

bool Bumpy = false;
bool UsingTexture = false;
bool UsingCheckBoard = false;
bool UsingOpicity = false;

RtFloat yon=50;
RtFloat hither=-10;
RtInt w;
RtInt h;

int CHECK_SIZE_X =5;
int CHECK_SIZE_Y =5;


RtFloat BUMP_AMPLITUDE=0;
RtFloat BUMP_MIN_FREQ_EXP=0;
RtFloat BUMP_MAX_FREQ_EXP=0;
RtToken BUMPY;
RtToken RI_PERSPECTIVE;


int numOfMicoPolygons =0;
//320 240
newFrameBuffer myBuffer(400,300);
//newFrameBuffer mySampleBuffer(640,640);
newFrameBuffer mySampleBuffer(400,300);
newMicoPolygon myMicoPolygon[100000];
newMesh myMesh[Mesh_Size*Mesh_Size];
Light myLight;
std::vector<Eigen::Vector3f> myTexture;


void formatMicopolygon(int u, int v, newMesh *m){
    
    for (int i =0; i< v; i++) {
        for (int j =0; j<u; j++) {
            /*
             micoPolygons[numOfMicoPolygons].points[0] = &m[i*v+j];
             micoPolygons[numOfMicoPolygons].points[1] = &m[i*v+j+1];
             micoPolygons[numOfMicoPolygons].points[2] = &m[(i+1)*v+j];
             micoPolygons[numOfMicoPolygons].points[3] = &m[(i+1)*v+1+j];
             */
            
            myMicoPolygon[numOfMicoPolygons].castMicoPolygon(&m[i*v+j], &m[i*v+j+1], &m[(i+1)*v+j+1], &m[(i+1)*v+j]);
            //new
            myMicoPolygon[numOfMicoPolygons].Meshs[0].Normal = myMicoPolygon[numOfMicoPolygons].getNormal(0, 0);
            numOfMicoPolygons++;
        }
    }
    
    
}

Vector3f castToTexture(int u, int v, int numofX, int numofY){
    float x,y;
    Vector3f temp {0,0,255};
    x = ((float)u/numofX);
    y = ((float)v/numofY);
    std::cout<<(int)(x*1024) <<","<<(int)(y*512)<<std::endl;
    //if((int)(x*1024+(int)(y*512*1024))<=30 ||abs((int)(x*1024+(int)(y*512*1024))-1024/4*3)<=30||abs((int)(x*1024+(int)(y*512*1024))-1024/4)<=30|| abs((int)(x*1024+(int)(y*512*1024))-1024/2)<=10)
    //return temp;
    //else
    return myTexture[((int)(x*1024)+((int)(y*512))*1024)];
}

RtVoid RiBegin(RtToken name){
    
}

RtVoid RtFormat (RtInt a, RtInt b, RtFloat asp){
    std::string filename = "output.png";
    Vector3f Pos ;
    Vector3f Col {0,0,0};
    for(float i =0; i<400;i++){
        for (float j =0; j<400; j++) {
            Pos ={ i/200-1,1-j/200,20};
            myBuffer.set_pixel(Pos, Col,255);
        }
    }
}

RtVoid RiDisplacement(RtToken name,...){
    if (name != NULL)
    {
        Bumpy = true;
    }
}

RtVoid RiOpacity(RtColor color){
    current_Opacity[0] = color[2];
    current_Opacity[1] = color[1];
    current_Opacity[2] = color[0];
}

RtVoid RiSurface(void (*earthShader)(void)){
    Vector3f lightPos = {1,1,-1};
    Vector3f lightCol = {255,255,255};
    
    myLight.setLight(lightPos, lightCol,0.9, 0.2, 1);
    UsingCheckBoard = true;
}


RtVoid RiMakeTexture(char *pic, int a, ...){
    UsingTexture = true;
    cv::Mat image = cv::imread("/Users/kaxiangming/CS285_Assignment_2.1/CS285_Assignment_2.1/earth.jpg", CV_LOAD_IMAGE_UNCHANGED);
    uchar* myimage = image.data;
    
    myTexture.resize(1024 * 512);
    for (int i = 0; i<512; i++) {
        for (int  j=0; j<1024; j++) {
            myTexture[i*1024+j] << myimage[3*(i*1024+j)],myimage[1+3*(i*1024+j)],myimage[2+3*(i*1024+j)];
        }
    }
}

void texture(int a){
    
}

void checkBoard(){
    UsingCheckBoard = true;
    UsingTexture = false;
    std::cout <<"using checkboard"<<std::endl;
}

void (*CHECKERBOARD)(void) = checkBoard;
