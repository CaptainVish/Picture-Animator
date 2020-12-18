//boat.h
#include "utils.h"
#include "wave.h"
#include <string>
#ifndef _BOAT_H_
#define _BOAT_H_

class Boat{
public:
    GLuint tex;
    unsigned int shaderProgram;
    // float translation=0.0004f;
    // float rotation=0.02f;
    // glm::vec2 pos=glm::vec2(-0.34,0.56);
    glm::vec2 pos=glm::vec2(0.0,0.0);
    // float current_pos=0.0f;
    // float current_angle=0.0f;
    // float count=0;//max count 60
    // float maxcount=60;
    // bool mid=true;

    Wave *wave;
    std::chrono::high_resolution_clock::time_point t1;

    Boat(){};
    Boat(std::string filename,Wave *wave,bool from_layer=false);
    void run(unsigned int VAO,int width,int height);
    bool setPos(float x,float y);

};


#endif
