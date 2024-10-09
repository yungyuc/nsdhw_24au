

#include <cmath>
class Vector {
private:
    double x = 0, y = 0;
public:
    Vector() = default;
    Vector(double x, double y);
    double GetX();
    double GetY();
    double GetDistance();
    double GetAngle(Vector other);
};