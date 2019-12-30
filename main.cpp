//
//  main.cpp
//  CS285_Assignment_2.2
//
//  Created by 喀相明 on 2019/5/3.
//  Copyright © 2019 喀相明. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "Ri.hpp"
#include "My_Ri.h"
#include "math.h"
#include <eigen3/Eigen/Eigen>
#include <cmath>
#include <opencv2/opencv.hpp>

void TextureMap0()
{
    texture(0);
}

/********************************************/
/********************************************/
// Texture lookup

/********************************************/
/********************************************/
void TransparencyTest()
{
    RiBegin(RI_NULL);
    //RiFormat(960, 720, 1.0);
    RiFormat(400, 300, 1.0);
    //RiFormat(200, 150, 1.0);
    RiDisplay("TransparencyTest.png", "", "");
    RiPixelSamples(2,2);
    
    RiFrameBegin(0);
    /* set the perspective transformation */
    float fov = 45.0;
    RiProjection(RI_PERSPECTIVE, "fov", &fov);
    //RiProjection(RI_ORTHOGRAPHIC);
    
    RiWorldBegin();
    RiTransformBegin();
    RtColor color = {1,0,0};
    RtColor opacity = {.4,.4,.4};
    RiOpacity(opacity);
    RiColor(color);
    RiTranslate(0, 0.5, 7.0);
    RiRotate(60, 1, 0, 0);
    RiTorus(1, .25, 0, 250, 270);
    RiTransformEnd();
    RiTransformBegin();
    color[0] = 0; color[1] = 1;
    opacity[0] = 0.4; opacity[1] = 0.4; opacity[2] = 0.4;
    RiOpacity(opacity);
    RiColor(color);
    RiTranslate(0, 0, 8.0);
    RiRotate(60, 1, 0, 0);
    RiRotate(30, 0, 1, 0);
    RiCylinder(1, -1, 1, 300);
    RiTransformEnd();
    RiTransformBegin();
    color[1] = 0; color[2] = 1;
    opacity[0] = .7; opacity[1] = .7; opacity[2] = .7;
    RiOpacity(opacity);
    RiColor(color);
    RiTranslate(0, 1, 9.0);
    RiRotate(60, 1, 0, 0);
    RiSphere(1.8, -1.0, 1.0, 250);
    RiTransformEnd();
    RiTransformBegin();
    color[0] = 1; color[1] = .6; color[2] = .6;
    RiColor(color);
    opacity[0] = .6; opacity[1] = .6; opacity[2] = .6;
    RiOpacity(opacity);
    RiTranslate(0, -1, 8.5);
    RiRotate(-160, 1, 0, 0);
    RiRotate(30, 0, 1, 0);
    RiRotate(140, 0, 0, 1);
    RiCone(2.5, 1, 270);
    RiTransformEnd();
    RiWorldEnd();
    
    RiFrameEnd();
    
    RiEnd();
}

/********************************************/
/********************************************/
void ShaderTest()
{
    RiBegin(RI_NULL);
    //RiFormat(960, 720, 1.0);
    RiFormat(400, 300, 1.0);
    //RiFormat(200, 150, 1.0);
    RiDisplay("ShaderTest.png", "", "");
    RiPixelSamples(2,2);
    
    RiFrameBegin(0);
    /* set the perspective transformation */
    float fov = 45.0;
    RiProjection(RI_PERSPECTIVE, "fov", &fov);
    //RiProjection(RI_ORTHOGRAPHIC);
    
    RiWorldBegin();
    RiTransformBegin();
    RtColor color = {1,0,0};
    RtColor opacity = {.4,.4,.4};
    RiOpacity(opacity);
    RiColor(color);
    //CHECK_SIZE_X = 20;
    //CHECK_SIZE_Y = 10;
    //RiSurface(CHECKERBOARD);
    RiTranslate(0, 0.5, 11);
    RiRotate(70, 0, 1, 0);
    RiTorus(2.5, .5, 0, 360, 360);
    RiTransformEnd();
    RiTransformBegin();
    color[0] = 0; color[1] = 1; color[2] = 0;
    opacity[0] = 1; opacity[1] = 1; opacity[2] = 1;
    RiOpacity(opacity);
    RiSurface(NULL);
    RiColor(color);
    RiTranslate(3, -1.5, 11);
    RiRotate(90, 1, 0, 0);
    RiCylinder(1, -1, 1, 360);
    RiTransformEnd();
    RiTransformBegin();
    opacity[0] = 1; opacity[1] = 1; opacity[2] = 1;
    RiOpacity(opacity);
    RiMakeTexture("earth.jpg", 0);
    void (*earthShader)(void) = TextureMap0;
    RiSurface(earthShader);
    BUMP_AMPLITUDE = 1;
    BUMP_MIN_FREQ_EXP = 2;
    BUMP_MAX_FREQ_EXP = 6;
    RiDisplacement(BUMPY);
    RiTranslate(3, 1, 11.0);
    RiRotate(-40, 0, 0, 1);
    RiRotate(-100, 0, 1, 0);
    RiRotate(110, 1, 0, 0);
    RiSphere(1, -1.5, 1.5, 360);
    RiTransformEnd();
    RiTransformBegin();
    opacity[0] = .8; opacity[1] = .8; opacity[2] = .8;
    RiOpacity(opacity);
    RiSurface(earthShader);
    RiDisplacement(NULL);
    RiTranslate(-2.5, 1, 11.0);
    RiRotate(-175, 0, 1, 0);
    RiRotate(110, 1, 0, 0);
    RiSphere(1.5, -1.5, 1.5, 360);
    RiTransformEnd();
    RiTransformBegin();
    color[0] = 0.4; color[1] = 0.2; color[2] = 0;
    RiColor(color);
    opacity[0] = 1; opacity[1] = 1; opacity[2] = 1;
    RiOpacity(opacity);
    RiSurface(NULL);
    BUMP_AMPLITUDE = .5;
    BUMP_MAX_FREQ_EXP = 8;
    RiDisplacement(BUMPY);
    RiTranslate(-2.5, -2.5, 11);
    RiRotate(-90, 1, 0, 0);
    RiRotate(90, 0, 0, 1);
    RiCone(2.5, 1, 360);
    RiTransformEnd();
    RiWorldEnd();
    
    RiFrameEnd();
    
    RiEnd();
}

/********************************************/
/********************************************/
void Rocket()
{
    RiBegin(RI_NULL);
    //RiFormat(960, 720, 1.0);
    RiFormat(400, 300, 1.0);
    //RiFormat(200, 150, 1.0);
    RiDisplay("Rocket.png", "", "");
    RiPixelSamples(2,2);
    
    RiFrameBegin(0);
    /* set the perspective transformation */
    float fov = 45.0;
    RiProjection(RI_PERSPECTIVE, "fov", &fov);
    //RiProjection(RI_ORTHOGRAPHIC);
    
        RiWorldBegin();
            RiTransformBegin();
    // water
                RtColor color = {0,0,1};
                RtColor opacity = {.6,.6,.6};
                RiOpacity(opacity);
                RiColor(color);
                BUMP_AMPLITUDE = .05;
                BUMP_MIN_FREQ_EXP = 2;
                BUMP_MAX_FREQ_EXP = 6;
                RiDisplacement(BUMPY);
                RiRotate(180, 0, 1, 0);
                RiRotate(110, 1, 0, 0);
                RiRotate(180, 1, 0, 0);
                RiScale(7, 1.15, 1);
                RiTranslate(0, -0.75, 4);
                RiTranslate(0, 0, 1);
    
                RiSphere(1, .9, 1, 360);
    // mountain
                color[0] = 0.6; color[1] = 0.3; color[2] = 0;
                opacity[0] = 1; opacity[1] = 1; opacity[2] = 1;
                RiColor(color);
                RiOpacity(opacity);
                RiDisplacement(NULL);
                BUMP_AMPLITUDE = 2;
                BUMP_MIN_FREQ_EXP = 3;
                BUMP_MAX_FREQ_EXP = 9;
                RiDisplacement(BUMPY);
                RiRotate(15, 1, 0, 0);
                RiTranslate(0, 4, -6);
                RiSphere(7, 6.8, 7, 360);
        RiTransformEnd();
    
        RiTransformBegin();
    // rocket
            RiDisplacement(NULL);
            color[0] = .8; color[1] = 0.8; color[2] = .8;
            RiColor(color);
            RiRotate(40, 0, 0, 1);
            RiRotate(150, 0, 1, 0);
            RiRotate(-90, 1, 0, 0);
            RiTranslate(-.25, .25, 2);
            RiScale(1, 2, 1);
            RiSphere(.1, -.1, .1, 360);
    
            RiTranslate(0, 0, .07);
            RiCone(.075, .075, 360);
    
            RiSurface(NULL);
            BUMP_AMPLITUDE = .1;
            BUMP_MIN_FREQ_EXP = 5;
            BUMP_MAX_FREQ_EXP = 7;
            RiDisplacement(BUMPY);
            color[0] = 1; color[1] = 0.27; color[2] = 0;
            opacity[0] = .4; opacity[1] = .4; opacity[2] = .4;
            RiOpacity(opacity);
            RiColor(color);
            RiTranslate(0, 0, -.45);
            RiCone(.3, .1, 360);
    
            color[1] = .1;
            RiColor(color);
            opacity[0] = 1; opacity[1] = 1; opacity[2] = 1;
            RiOpacity(opacity);
            RiDisplacement(NULL);
            RiScale(20, .5, 1);
            RiTranslate(0, 0, .375);
            RiSphere(.025, -.025, .025, 360);
    
            RiScale(1/40, 16, 1);
            RiTranslate(0, -0.015, -.075);
            RiSphere(.025, -.025, .025, 360);
        RiTransformEnd();
    RiWorldEnd();
    
    RiFrameEnd();
    
    RiEnd();
}

/********************************************/
/********************************************/
void Tunnel()
{
    RiBegin(RI_NULL);
    //RiFormat(960, 720, 1.0);
    RiFormat(400, 300, 1.0);
    RiDisplay("Tunnel.png", "", "");
    RiPixelSamples(2,2);
    
    RiFrameBegin(0);
    /* set the perspective transformation */
    float fov = 45.0;
    RiProjection(RI_PERSPECTIVE, "fov", &fov);
    //RiProjection(RI_ORTHOGRAPHIC);
    
    RiTranslate(0, 0, 0);//new
    //RiScale(0.3, 0.3, 0.3);//new
    
        RiWorldBegin();
            RiTransformBegin();
    RtColor color = {1,0,0};
    
    RiTransformBegin();
    CHECK_SIZE_X = 10;
    CHECK_SIZE_Y = 10;
    RiSurface(CHECKERBOARD);
    RiTranslate(0, 0, 7.0);
    //RiCylinder(3, -100, 100, 360);
    RiCone(10, 5, 360);
    RiTransformEnd();
    RiWorldEnd();
    
    
        RiTransformBegin();
                color[0] = 0; color[1] = 1;
                RiColor(color);
    RtColor opacity = {.6,.6,.6};
    RiOpacity(opacity);
    RiRotate(60, 1, 0, 0);
    RiRotate(30, 0, 1, 0);
                RiTranslate(0, 0, 8.0);
    
                RiCylinder(1, -1, 1, 360);
            RiTransformEnd();
    
            RiTransformBegin();
                color[1] = 0; color[2] = 1;
                RiColor(color);
    RiRotate(60, 1, 0, 0);
                RiTranslate(0, 1, 9.0);
    
                RiSphere(1.0, -1.0, 1.0, 360);
            RiTransformEnd();
    
            RiTransformBegin();
                color[0] = 1; color[1] = .4; color[2] = .4;
                RiColor(color);
                CHECK_SIZE_X = 10;
                CHECK_SIZE_Y = 10;
                RiSurface(CHECKERBOARD);
    RiRotate(-160, 1, 0, 0);
                RiTranslate(0, -1, 8.5);
    
                RiRotate(30, 0, 1, 0);
                RiCone(2, 1, 360);
            RiTransformEnd();
    
    color[0] =1; color[1] = 0; color[2] = 0; 
    RiColor(color);
    RiRotate(60, 1, 0, 0);
    RiTranslate(0, 0.5, 7.0);
    
    RiTorus(1, .25, 0, 360, 360);
    RiTransformEnd();
    
    RiFrameEnd();
    
    RiEnd();
}

/********************************************/
/********************************************/
void Tornado()
{
    RiBegin(RI_NULL);
    //RiFormat(960, 720, 1.0);
    RiFormat(400, 300, 1.0);
    //RiFormat(200, 150, 1.0);
    RiDisplay("Tornado.png", "", "");
    RiPixelSamples(2,2);
    
    RiFrameBegin(0);
    /* set the perspective transformation */
    float fov = 45.0;
    RiProjection(RI_PERSPECTIVE, "fov", &fov);
    //RiProjection(RI_ORTHOGRAPHIC);
    
    RiWorldBegin();
    RiTransformBegin();
    RtColor gray = { .4, .4, .4 };
    RtColor opacity = { 0.5, 0.5, 0.5 };
    RiColor(gray);
    RiOpacity(opacity);
    BUMP_AMPLITUDE = 1;
    BUMP_MIN_FREQ_EXP = 3;
    BUMP_MAX_FREQ_EXP = 10;
    RiDisplacement(BUMPY);
    RiTranslate(0, 0, 5.0);
    RiRotate(90, 0, 1, 0);
    RiRotate(80, 1, 0, 0);
    RiTranslate(0, 0, -1.5);
    RiCone(3, 1, 360);
    RiTransformEnd();
    RiWorldEnd();
    
    RiFrameEnd();
    
    RiEnd();
}

/********************************************/
/********************************************/


void Earth()
{
    RiBegin(RI_NULL);
    //RiFormat(960, 720, 1.0);
    RiFormat(400, 300, 1.0);
    //RiFormat(200, 150, 1.0);
    RiDisplay("Earth.png", "", "");
    RiPixelSamples(2,2);
    
    RiFrameBegin(0);
    /* set the perspective transformation */
    float fov = 45.0;
    RiProjection(RI_PERSPECTIVE, "fov", &fov);
    //RiProjection(RI_ORTHOGRAPHIC);
    
    RiWorldBegin();
    RiTransformBegin();
    RiMakeTexture("earth.jpg", 0);
    void (*earthShader)(void) = TextureMap0;
    RiSurface(earthShader);
    RtColor blue = { 0, 0, 1 };
    RtColor opacity = { .9, .9, .9 };
    RiColor(blue);
    RiOpacity(opacity);
    BUMP_AMPLITUDE = .02;
    BUMP_MIN_FREQ_EXP = 14;
    BUMP_MAX_FREQ_EXP = 16;
    RiDisplacement(BUMPY);
    RiTranslate(1, 0.5, 5.0);
    RiRotate(-175, 0, 1, 0);
    RiRotate(110, 1, 0, 0);
    RiSphere(0.7,-0.7, 10.7, 360);
    RiTransformEnd();
    
    RiTransformBegin();
    CHECK_SIZE_X = 10;
    CHECK_SIZE_Y = 10;
    RiSurface(CHECKERBOARD);
    UsingTexture=false;
    UsingCheckBoard = true;
    RiTranslate(-1, 0.5, 5.0);
    RiRotate(-175, 0, 1, 0);
    RiRotate(110, 1, 0, 0);
    RiSphere(0.7,-0.7, 0.7, 360);
    RiTransformEnd();
    
    RiTransformBegin();
    Bumpy=true;
    RiTranslate(0, -1, 5.0);
    RiRotate(-175, 0, 1, 0);
    RiRotate(110, 1, 0, 0);
    RiSphere(0.7,-0.7, 0.7, 360);
    RiTransformEnd();
    
    RiWorldEnd();
    
    RiFrameEnd();
    
    RiEnd();
}


int main(int argc, const char * argv[]) {
    
    Earth();
    //Rocket();
    //Tunnel();
    return 0;
}
