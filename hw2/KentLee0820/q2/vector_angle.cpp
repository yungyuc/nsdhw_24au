#include <cmath>
#include <limits>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>

double calculate_angle(double x1, double y1, double x2, double y2)
{
	double l1_len = sqrt(x1*x1 + y1*y1);
	double l2_len = sqrt(x2*x2 + y2*y2);

	return acos((x1 * x2 + y1 * y2) / (l1_len * l2_len));
}


PYBIND11_MODULE(_vector, m)
{
	m.doc() = "pybind11 module example";
	m.def("calculate_angle", &calculate_angle, "A function which calculate angle between two vectors");
}
