//clouds.h
#include "utils.h"
#include <string>
#ifndef _CLOUDS_H_
#define _CLOUDS_H_

class Clouds{
public:
    GLuint tex;
    float translation=0.001f;
    float current_pos=0.0f;
    unsigned int shaderProgram;
    Clouds(){};
    Clouds(std::string filename);
    void run(unsigned int VAO,int width,int height);

};


#endif
