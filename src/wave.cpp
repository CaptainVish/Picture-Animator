//wave.cpp
#include "wave.h"
#include <string>
// constructor
Wave::Wave(float frequency_,float wave_length_,float amplitude_,float _translation,float _rotation){
    frequency=frequency_;
    wave_length=wave_length_;
    amplitude=amplitude_;
    translation=_translation;
    rotation=_rotation;
    k=(2*M_PI)/wave_length;
    w=2*M_PI*frequency;
}

float Wave::get_position(float x, float t){
    float argument=k*x-w*t;
    return amplitude*sin(argument);
}

void Wave::update_parameters(float windspeed){
    frequency=windspeed/10000;
    wave_length=windspeed/100;
    amplitude=windspeed/10000;
    translation=windspeed/10000;
    rotation=windspeed/10000;
    // std::cout<<"updated frequency"<<frequency<<std::endl;
    k=(2*M_PI)/wave_length;
    w=2*M_PI*frequency;
}

void Wave::update_frequency(float _frequency){
    frequency=_frequency/100000;
    w=2*M_PI*frequency;

}
void Wave::update_wavelength(float _wavelength){
    wave_length=_wavelength;
    k=(2*M_PI)/wave_length;

}
void Wave::update_amplitude(float _amplitude){
    amplitude=_amplitude;
}

std::chrono::high_resolution_clock::time_point Wave::get_time(){
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    return t1;
}
long double Wave::get_time_diff(std::chrono::high_resolution_clock::time_point t1){
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = t2 - t1;
    return time_span.count();
}
