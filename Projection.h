//
//  Projection.h
//  CS285_Assignment_2.2
//
//  Created by 喀相明 on 2019/5/3.
//  Copyright © 2019 喀相明. All rights reserved.
//

#ifndef Projection_h
#define Projection_h

RtVoid RiProjection(RtToken name, ...){
    projectionMatrix.setIdentity();
    float fov = 180;
    
    RtFloat A = 1/(RtFloat)tan((fov/2)/180*Pi);
    RtFloat B = 1/(RtFloat)tan((fov/2/aspectRatio)/180*Pi);
    RtFloat C = yon/(yon-hither);
    RtFloat D = (-yon*hither)/(yon-hither);
    
    
    Matrix4f persp;
    persp<< A, 0, 0, 0,
    0, B, 0, 0,
    0, 0, C, D,
    0, 0, 1, 0;
    //std::cout <<"persp"<< C<<","<<D <<std::endl;
    projectionMatrix<< persp;
}

#endif /* Projection_h */
