//wave.h
#include "utils.h"
#include <string>
#ifndef _WAVE_H_
#define _WAVE_H_

class Wave{
public:

    float frequency;
    float wave_length;
    float amplitude;
    float k;
    float w;

    Wave(){};
    Wave(float frequency,float wave_length,float amplitude);


    float get_position(float x,float t);
    std::chrono::high_resolution_clock::time_point get_time();
    long double get_time_diff(std::chrono::high_resolution_clock::time_point);


};


#endif
