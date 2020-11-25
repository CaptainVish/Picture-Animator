//boat.h
#include "utils.h"
#include <string>
#ifndef _BOAT_H_
#define _BOAT_H_

class Boat{
public:
    GLuint tex;
    unsigned int shaderProgram;
    float translation=0.002f;
    float rotation=0.02f;
    glm::vec2 pos;
    float current_pos=0.0f;
    float current_angle=0.0f;
    float count=0;//max count 60
    float maxcount=60;
    bool mid=true;
    Boat(){};
    Boat(std::string filename);
    void run(unsigned int VAO,int width,int height);

};


#endif
