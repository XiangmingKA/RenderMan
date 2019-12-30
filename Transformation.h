//
//  Transformation.h
//  CS285_Assignment_2.2
//
//  Created by 喀相明 on 2019/5/3.
//  Copyright © 2019 喀相明. All rights reserved.
//

#ifndef Transformation_h
#define Transformation_h

#include <eigen3/Eigen/Eigen>

using namespace Eigen;

RtVoid RiTransformBegin(){
    current_transMatrix = worldMatrix*current_transMatrix;
};

RtVoid RiTransformEnd(){
    current_transMatrix.setIdentity();
    //projectionMatrix.setIdentity();
    UsingCheckBoard = false;
};


Matrix4f Rotate(RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz){
    angle = angle/180*Pi;
    RtFloat d1 = sqrtf(dy*dy + dz*dz) ;
    RtFloat a1 = d1 != (RtFloat)0.0 ? dx/d1 : 1 ;
    RtFloat b1 = d1 != (RtFloat)0.0 ? dy/d1 : 0 ;
    RtFloat c1 = d1 != (RtFloat)0.0 ? dz/d1 : 1 ;
    
    RtFloat d2 = sqrtf(dy*dy + dz*dz + dx*dx);
    RtFloat a2 = d2 != (RtFloat)0.0 ? dx/d2 : 1 ;
    RtFloat b2 = d2 != (RtFloat)0.0 ? dy/d2 : 0 ;
    RtFloat c2 = d2 != (RtFloat)0.0 ? dz/d2 : 1 ;
    RtFloat s = sqrtf(d2*d2 - dx*dx);
    s = s/d2;
    double r = angle ;
    Matrix4f m1;
    Matrix4f m2;
    Matrix4f m3;
    Matrix4f m4;
    Matrix4f m5;
    
    m1<<1 , 0 , 0 , 0 ,
    0 , c1 , -b1, 0 ,
    0 , b1 , c1 ,0 ,
    0 , 0 , 0 , 1 ;
    
    m2<<s , 0 , -a2, 0 ,
    0 , 1 , 0 , 0 ,
    a2 , 0 , s , 0 ,
    0 , 0 , 0 , 1;
    
    m3<<cos(r),-sin(r),0,0,
    sin(r),cos(r), 0,0,
    0     , 0     ,1,0,
    0     , 0     ,0,1;
    
    m4<<s , 0 , a2, 0 ,
    0 , 1 , 0 , 0 ,
    -a2 , 0 , s , 0 ,
    0 , 0 , 0 , 1;
    
    m5<<1 , 0 , 0 , 0 ,
    0 , c1 , b1 ,0 ,
    0 , -b1 , c1 ,0 ,
    0 , 0 , 0 , 1;
    
    Matrix4f resMat;
    resMat = m5*m4*m3*m2*m1;
    return resMat;
}

Matrix4f Translate(RtFloat dx, RtFloat dy, RtFloat dz){
    Matrix4f tempTrans;
    tempTrans <<  1, 0, 0, dx,
    0, 1, 0, dy,
    0, 0, 1, dz,
    0, 0, 0, 1;
    return tempTrans;
}

RtVoid RiRotate(RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz)
{
    current_transMatrix=current_transMatrix*Rotate(angle,dx, dy, dz);
}

RtVoid RiTranslate(RtFloat dx, RtFloat dy, RtFloat dz){
    current_transMatrix=Translate(dx, dy, dz)*current_transMatrix;
}

RtVoid RiScale(RtFloat sx, RtFloat sy, RtFloat sz){
    Matrix4f tempTrans;
    tempTrans <<  sx, 0, 0, 0,
    0, sy, 0, 0,
    0, 0, sz, 0,
    0, 0, 0, 1;
    current_transMatrix = current_transMatrix * tempTrans;
}

RtVoid RiWorldBegin(){
    worldMatrix << current_transMatrix;
    current_transMatrix.setIdentity();
    projectionMatrix.setIdentity();
}

void castToProjection(newMesh *M){
    /*
     for (int i= 0;i< (Mesh_Size+1)*(Mesh_Size+1); i++) {
     Vector4f temp ;
     temp[0] = M[i].Points[0];
     temp[1] = M[i].Points[1];
     temp[2] = M[i].Points[2];
     temp[3] = 1.0;
     Vector4f res;
     res << projectionMatrix*(current_transMatrix*(temp));
     res[0] = res[0]/res[3];
     res[1] = res[1]/res[3];
     res[2] = res[2]/res[3];
     M[i].Points[0]  = res[0] ;
     M[i].Points[1]  = res[1] ;
     M[i].Points[2]  = res[2] ;
     
     //new
     
     temp[0] = M[i].Normal[0];
     temp[1] = M[i].Normal[1];
     temp[2] = M[i].Normal[2];
     temp[3] = 1.0;
     res << projectionMatrix*(current_transMatrix*(temp));
     res[0] = res[0]/res[3];
     res[1] = res[1]/res[3];
     res[2] = res[2]/res[3];
     M[i].Normal[0]  = res[0] ;
     M[i].Normal[1]  = res[1] ;
     M[i].Normal[2]  = res[2] ;
     
     }
     */
    
    for (int i= 0;i< (Mesh_Size+1)*(Mesh_Size+1); i++) {
        Vector4f temp ;
        temp[0] = M[i].Points[0];
        temp[1] = M[i].Points[1];
        temp[2] = M[i].Points[2];
        temp[3] = 1.0;
        Vector4f res;
        res << (current_transMatrix*(temp));
        M[i].Points[0]  = res[0] ;
        M[i].Points[1]  = res[1] ;
        M[i].Points[2]  = res[2] ;
        
        //new
        temp[0] = M[i].Points[0];
        temp[1] = M[i].Points[1];
        temp[2] = M[i].Points[2];
        temp[3] = 1.0;
        //std::cout<<"z" << res[2]<<std::endl;
        res << projectionMatrix*(temp);
        res[0] = res[0]/res[3]/2;
        res[1] = res[1]/res[3]/2;
        res[2] = res[2]/res[3]/2;
        //std::cout<<"z" << res[2]<<std::endl;
        M[i].Points[0]  = res[0] ;
        M[i].Points[1]  = res[1] ;
        M[i].Points[2]  = res[2] ;
    }
}

#endif /* Transformation_h */
