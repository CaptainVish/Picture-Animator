//clouds.h
#include "utils.h"
#include "wave.h"
#include <string>
#ifndef _CLOUDS_H_
#define _CLOUDS_H_

class Clouds{
public:
    GLuint tex;
    Wave *wave;
    float current_pos=0.0f;
    unsigned int shaderProgram;
    Clouds(){};
    Clouds(std::string filename,Wave *wave_);
    void run(unsigned int VAO,int width,int height);


};


#endif
