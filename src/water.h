//water.h
#include "utils.h"
#include "wave.h"
#include <string>
#ifndef _WATER_H_
#define _WATER_H_

class Water{
public:
    GLuint tex;
    unsigned int shaderProgram;


    Wave *wave;
    std::chrono::high_resolution_clock::time_point t1;

    Water(){};
    Water(std::string filename,Wave *wave);
    void run(unsigned int VAO,int width,int height);

};


#endif
