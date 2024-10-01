#include<cmath>
#include<pybind11/pybind11.h>

float calc_angle(float x1, float y1, float x2, float y2)
{
    float len1 = sqrt(x1*x1 + y1*y1);
    float len2 = sqrt(x2*x2 + y2*y2);
    float dot_product = x1*x2 + y1*y2;
    return acos( dot_product / (len1*len2) );
}

PYBIND11_MODULE(_vector, m)
{
    m.def("calc_angle", &calc_angle, "Calculate the angle between two vectors.");
} 
