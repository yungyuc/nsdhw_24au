#ifndef __POINT_H__
#define __POINT_H__

class Point
{
public:
    Point(float x, float y);
    Point();
    ~Point();

    float const & x() const;
    float & x();
    float const & y() const;
    float & y();

private:
    float x_;
    float y_;
};

#endif /* __POINT_H__ */
