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
    float translation;
    float rotation;

    Wave(){};
    Wave(float frequency,float wave_length,float amplitude,float translation,float rotation);


    float get_position(float x,float t);
    std::chrono::high_resolution_clock::time_point get_time();
    long double get_time_diff(std::chrono::high_resolution_clock::time_point);
    void update_parameters(float windspeed);
    void update_frequency(float _frequency);
    void update_wavelength(float _wavelength);
    void update_amplitude(float _amplitude);

};


#endif
