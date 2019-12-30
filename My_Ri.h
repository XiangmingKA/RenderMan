//
//  My_Ri.h
//  CS285_Assignment_2.2
//
//  Created by 喀相明 on 2019/5/3.
//  Copyright © 2019 喀相明. All rights reserved.
//

#ifndef My_Ri_h
#define My_Ri_h

#include <eigen3/Eigen/Eigen>

using namespace Eigen;

#define Mesh_Size 10
#define numOfx  400
#define numOfy  300


#define numOfM 2
#define numOfN 2

#define Pi 3.1415926

extern RtFloat aspectRatio;


extern Matrix4f projectionMatrix;
extern Matrix4f current_transMatrix;
extern Vector3f current_Color;
extern Vector3f current_Opacity;
extern Matrix4f worldMatrix;

extern RtFloat yon;
extern RtFloat hither;
extern RtInt w;
extern RtInt h;

extern int numOfMicoPolygons;

extern std::vector<Eigen::Vector3f> myTexture;

struct OpcityLink{
    int ind;
    Vector3f Color;
    Vector3f Opcity;
    float depth;
    OpcityLink *next;
};


extern class newFrameBuffer{
    
public:
    int width,height;
    std::vector<Eigen::Vector3f> frame_buf;
    std::vector<float> depth_buf;
    std::vector<Eigen::Vector3f> opicity_buf;
    OpcityLink opcLink[400*300];
    
    
    newFrameBuffer(int w, int h):width(w), height(h)
    {
        frame_buf.resize(w * h);
        depth_buf.resize(w * h);
        opicity_buf.resize(w*h);
        //opicity_buf2.resize(w*h);
        for (int i =0; i<w*h; i++) {
            this->depth_buf[i]=100;
            this->opicity_buf[i][0] =1;
            this->opicity_buf[i][1] =1;
            this->opicity_buf[i][2] =1;
            
            opcLink[i].Opcity[0] = 1;
            opcLink[i].Opcity[1] = 1;
            opcLink[i].Opcity[2] = 1;
            
            opcLink[i].ind = 0;
            
            opcLink[i].depth = 0;
            opcLink[i].next = NULL;
        }
    }
    
    void set_pixel(const Vector3f& point, const Vector3f& color, float depth)
    {
        //old index: auto ind = point.y() + point.x() * width;
        //auto ind = (height-point.y()-1)*width + point.x();
        auto ind = (height*(1-point.y()))/2*width + (point.x()+1)/2*width;
        if(ind >= width*height || ind<0){
            std::cout<<"Set Pixel out of range: "<< point.x()<<", "<<point.y()<<"\n";
        }
        else if(depth_buf[ind] >depth+0.001)
        {
            frame_buf[ind] = color;
            depth_buf[ind] = depth;
           
        }
    }
    
    
    void set_pixel(int x ,int y, const Vector3f& color, float depth)
    {
        //old index: auto ind = point.y() + point.x() * width;
        //auto ind = (height-point.y()-1)*width + point.x();
        
        int ind = x + y*this->width;
        if(ind >= width*height || ind<0){
            std::cout<<"Set Pixel out of range: "<< x <<", "<<y<<"\n";
        }
        else if(depth_buf[ind] >depth+0.001){
            frame_buf[ind] = color;
            depth_buf[ind] = depth;
            
        }
        
        
    }
    
    void set_opicity(const Vector3f& point, const Vector3f& opicity,Vector3f& Color, float depth){
        int ind = (height*(1-point.y()))/2*width + (point.x()+1)/2*width;
        if(ind >= width*height || ind<0){
            std::cout<<"Set Opicity out of range: ";
        }
        else {
            int ind =0;
            OpcityLink temp = opcLink[ind];
            static OpcityLink res;
            res.Opcity[0] = opicity[0];
            res.Opcity[1] = opicity[1];
            res.Opcity[2] = opicity[2];
            res.Color[0] = Color[0];
            res.Color[1] = Color[1];
            res.Color[2] = Color[2];
            res.depth = depth;
            res.next = NULL;
            while(temp.next != NULL){
                temp = *temp.next;
                ind++;
            }
            res.ind = ind;
            temp.next = &res;
        }
    }
    
    OpcityLink *Insert(OpcityLink *head,const Vector3f& point, const Vector3f& opicity,Vector3f& Color, float depth){
        int ind = (height*(1-point.y()))/2*width + (point.x()+1)/2*width;
        OpcityLink* temp;
        temp = &this->opcLink[ind];
        OpcityLink *res;
        res = new OpcityLink;
        res->Opcity[0] = opicity[0];
        res->Opcity[1] = opicity[1];
        res->Opcity[2] = opicity[2];
        res->Color[0] = Color[0];
        res->Color[1] = Color[1];
        res->Color[2] = Color[2];
        res->depth = depth;
        res->ind = 1;
        res->next = nullptr;
        while(temp->next != nullptr){
            res->ind++;
            temp = temp->next;
        }
        temp->next = res;
        return head;
    }
    
    
    void set_opicity2(const Vector3f& point, const Vector3f& opicity,Vector3f& Color, float depth){
        int ind = (height*(1-point.y()))/2*width + (point.x()+1)/2*width;
        OpcityLink* reserve;
        reserve = &this->opcLink[ind];
        if(ind >= width*height || ind<0){
            std::cout<<"Set Opicity out of range: ";
        }
        else {
            OpcityLink* temp;
            temp = &this->opcLink[ind];
            OpcityLink *res;
            res = new OpcityLink;
            res->Opcity[0] = opicity[0];
            res->Opcity[1] = opicity[1];
            res->Opcity[2] = opicity[2];
            res->Color[0] = Color[0];
            res->Color[1] = Color[1];
            res->Color[2] = Color[2];
            res->depth = depth;
            res->ind = 1;
            res->next = nullptr;
            while(temp->next != nullptr){
                res->ind++;
                temp = temp->next;
            }
            temp->next = res;
            this->opcLink[ind] = *reserve;
        }
        
    }
    
    Vector3f get_pixel(const Vector3f& point)
    {
        int ind = (height-point.y())*width + point.x();
        if(ind >= width*height || ind<0){
            std::cout<<"Get Pixel out of range\n";
            return this->frame_buf[0];
        }
        else
        {
            if(opicity_buf[ind].isZero())
                return this->frame_buf[ind];
            else
            {
                Vector3f temp;
                temp[0] = frame_buf[ind][0]*opicity_buf[ind][0];
                temp[1] = frame_buf[ind][1]*opicity_buf[ind][1];
                temp[2] = frame_buf[ind][2]*opicity_buf[ind][2];
                return temp;
            }
        }
    }
    
    void get_pixel2(const Vector3f& point)
    {
        int ind = (height*(1-point.y()))/2*width + (point.x()+1)/2*width;
        
        
        Vector3f res ;
        float tempDepth=100;
        if(ind >= width*height || ind<0){
            std::cout<<"Get Pixel out of range\n";
        }
        else{
            OpcityLink *temp;
            temp = &this->opcLink[ind];
            OpcityLink *reserve;
            reserve = &this->opcLink[ind];
            temp = &this->opcLink[ind];
            Vector3f resColor;
            Vector3f tempOpc;
            Vector3f tempColor;
            int leastInd = 0;
            float leastDepth = 0;
            for(int i =0 ; i<6; i++){
                temp = reserve;
                do{
                    float test =depth_buf[ind];
                    if(temp->depth > leastDepth && temp->depth< this->depth_buf[ind]-0.001){
                        leastInd = temp->ind;
                        leastDepth = temp->depth;
                        tempOpc = temp->Opcity;
                        tempColor = temp->Color;
            
                    }
                    temp = temp->next;
                }while(temp != nullptr);
                //float A = this->frame_buf[ind][0];
                //float B = tempOpc[0];
                //float C = tempColor[0];
                float r = this->frame_buf[ind][0]*tempOpc[0] + tempColor[0]*(1-tempOpc[0]);
                float g = this->frame_buf[ind][1]*tempOpc[1] + tempColor[1]*(1-tempOpc[1]);
                float b = this->frame_buf[ind][2]*tempOpc[2] + tempColor[2]*(1-tempOpc[2]);
                this->frame_buf[ind][0] = r;
                this->frame_buf[ind][1] = g;
                this->frame_buf[ind][2] = b;
                this->depth_buf[ind] = leastDepth;
                //tempDepth = 0;
                
                //std::cout<<r<<std::endl;
                leastDepth = 0;
                tempOpc[0] = 1;
                tempOpc[1] = 1;
                tempOpc[2] = 1;
                tempColor[0] = 0;
                tempColor[1] = 0;
                tempColor[2] = 0;
                
                //opcLink[ind] = *reserve;
            }
        }
    }
    
    
    Vector3f get_pixel(int x, int y)
    {
        int ind = y*width + x;
        if(ind >= width*height || ind<0){
            std::cout<<"Get Pixel out of range\n";
            return this->frame_buf[0];
        }
        else
        {
            Vector3f temp;
            temp[0] = frame_buf[ind][0]*opicity_buf[ind][0];
            temp[1] = frame_buf[ind][1]*opicity_buf[ind][1];
            temp[2] = frame_buf[ind][2]*opicity_buf[ind][2];
            return temp;
        }
    }
    
    std::vector<Eigen::Vector3f>& frame_buffer() { return frame_buf; }
    
    
};

extern newFrameBuffer myBuffer;
extern newFrameBuffer mySampleBuffer;

class newMesh{
public:
    Vector3f Points;
    Vector3f Color;
    Vector3f Normal;
    Vector3f Opcity;
    
    newMesh(){}
    newMesh(Vector3f Pos,Vector3f Col, Vector3f Nor){
        Points = Pos;
        Color = Col;
        Normal = Nor;
        //Opcity = {,0,0};
    }
    
    
};

class newMicoPolygon{
    
public:
    newMesh Meshs[4];
    newMicoPolygon(){}
    newMicoPolygon(newMesh* a,newMesh* b, newMesh* c,newMesh* d){
        this->Meshs[0] = *a;
        this->Meshs[1] = *b;
        this->Meshs[2] = *c;
        this->Meshs[3] = *d;
    }
    
    void castMicoPolygon(newMesh* a,newMesh* b, newMesh* c,newMesh* d){
        this->Meshs[0] = *a;
        this->Meshs[1] = *b;
        this->Meshs[2] = *c;
        this->Meshs[3] = *d;
    }
    
    Vector3f getNormal(float a, float b){
        Vector3f Positions[4];
        Positions[0] << this->Meshs[0].Points[0],this->Meshs[0].Points[1],this->Meshs[0].Points[2];
        Positions[1] << this->Meshs[1].Points[0],this->Meshs[1].Points[1],this->Meshs[1].Points[2];
        Positions[2] << this->Meshs[2].Points[0],this->Meshs[2].Points[1],this->Meshs[2].Points[2];
        Positions[3] << this->Meshs[3].Points[0],this->Meshs[3].Points[1],this->Meshs[3].Points[2];
        
        Vector3f Lines[4];
        Lines[0] = (Positions[1]-Positions[0]).cross(Positions[2]-Positions[0]);
        Lines[1] = (Positions[3]-Positions[1]).cross(Positions[0]-Positions[1]);
        Lines[2] = (Positions[0]-Positions[2]).cross(Positions[3]-Positions[2]);
        Lines[3] = (Positions[2]-Positions[3]).cross(Positions[1]-Positions[3]);
        Lines[0].normalize();
        
        return Lines[0];
    }
    
    Vector3f getBumNormal(float a, float b)
    {
        srand(time(0));
        float strengh = 0.01;
        
        Vector3f Positions[4];
        Positions[0] << this->Meshs[0].Points[0],this->Meshs[0].Points[1],this->Meshs[0].Points[2];
        Positions[1] << this->Meshs[1].Points[0],this->Meshs[1].Points[1],this->Meshs[1].Points[2];
        Positions[2] << this->Meshs[2].Points[0],this->Meshs[2].Points[1],this->Meshs[2].Points[2];
        Positions[3] << this->Meshs[3].Points[0],this->Meshs[3].Points[1],this->Meshs[3].Points[2];
        
        Vector3f Lines[4];
        Lines[0] = (Positions[1]-Positions[0]).cross(Positions[2]-Positions[0]);
        Lines[1] = (Positions[3]-Positions[1]).cross(Positions[0]-Positions[1]);
        Lines[2] = (Positions[0]-Positions[2]).cross(Positions[3]-Positions[2]);
        Lines[3] = (Positions[2]-Positions[3]).cross(Positions[1]-Positions[3]);
        
        Lines[0].x() += strengh * (float)(rand()%11)/10;
        Lines[0].y() += strengh * (float)(rand()%11)/10;
        Lines[0].z() += strengh * (float)(rand()%11)/10;
        Lines[0].normalize();
        
        return Lines[0];
    }
    
    std::vector<Eigen::Vector3f> frame_buf;
    
};

extern newMesh myMesh[Mesh_Size*Mesh_Size];
extern newMicoPolygon myMicoPolygon[100000];

class Light{
public:
    Vector3f Position;
    Vector3f Color;
    float lightStrength;
    float ambientStrength;
    float specularStrength;
    
    Light(){
        Position<<0,0,0;
        Color<<0,0,0;
        lightStrength = 0;
        ambientStrength= 0.0;
        specularStrength =0;
    }
    
    void setLight( Vector3f Pos, Vector3f Col,float lightStg, float ambi, float specularStg){
        this->Position = Pos;
        this->Color = Col;
        this->lightStrength = lightStg;
        this->ambientStrength= ambi;
        this->specularStrength = specularStg;
    }
    
    Vector3f ambientLighting(Vector3f objectCol){
        return objectCol * this->ambientStrength;
    }
    
    Vector3f diffuseLighting(Vector3f objectPos,Vector3f objectNor,Vector3f objectCol){
        Vector3f lightDir = objectPos - this->Position;
        lightDir.normalize();
        float diffuse = objectNor.dot(-lightDir);
        diffuse = diffuse > 0? diffuse : 0;
        
        return diffuse*objectCol*lightStrength;
    }
    
    Vector3f specularLighting(Vector3f objectPos,Vector3f objectNor,Vector3f objectCol){
        Vector3f lightDir = objectPos - this->Position;
        lightDir.normalize();
        Vector3f viewDir = (-objectPos).normalized();
        Vector3f reflectDir = lightDir - 2*objectNor*(objectNor.dot(lightDir));
        //Vector3f reflectDir = lightDir-2*objectNor.dot(objectNor);
        float spec = pow(fmax(viewDir.dot(-reflectDir), 0.0), 32);
        Vector3f specular = specularStrength * spec * Color;
        return specular;
    }
    
    Vector3f normalLighting(Vector3f objectPos,Vector3f objectNor,Vector3f objectCol){
        Vector3f lightDir = (objectPos - this->Position).normalized();
        Vector3f viewDir = (-objectPos).normalized();
        Vector3f reflectDir = (lightDir - 2*objectNor*(objectNor.dot(lightDir))).normalized();
        
        float diffuse = objectNor.dot(lightDir);
        diffuse = diffuse > 0? diffuse : 0;
        
        float spec = pow(fmax(viewDir.dot(reflectDir), 0.0), 32);
        
        return objectCol*this->ambientStrength + diffuse*lightStrength*objectCol + specularStrength * spec * Color;
    }
};

extern Light myLight;


extern void formatMicopolygon(int u, int v, newMesh *m);
//extern void castToProjection(newMesh *myMesh);

extern int micoPolygonContainPoint(struct microPolygon M, RtPoint P);

extern void printMico(int i);
extern void testMatrix(RtMatrix a);
extern void printMesh(struct Mesh mesh);
extern void MyDisplay();
extern bool insideTriangle(float x, float y, const Vector3f* _v);
extern bool insideMicoPolygon(float x, float y, newMicoPolygon MP);
extern Vector3f castToTexture(int u, int v, int numofX, int numofY);
extern void castToProjection(newMesh *M);

extern float BUMP_AMPLITUDE;
extern float BUMP_MIN_FREQ_EXP;
extern float BUMP_MAX_FREQ_EXP;

extern RtToken BUMPY;
extern RtToken RI_PERSPECTIVE;

extern bool Bumpy ;
extern bool UsingTexture ;
extern bool UsingCheckBoard;
extern bool UsingOpicity;

extern void texture(int a);

extern int CHECK_SIZE_X ;
extern int CHECK_SIZE_Y ;
extern void (*CHECKERBOARD)(void);
#endif /* My_Ri_h */
