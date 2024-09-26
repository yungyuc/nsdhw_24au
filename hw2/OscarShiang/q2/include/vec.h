#ifndef __VEC_H__
#define __VEC_H__

class Vec {
public:
    Vec(float x, float y);
    float angle(Vec const &v);

    float len() const;

    float const & x() const;
    float const & y() const;

private:
    float x_;
    float y_;
};

#endif /* __VEC_H__ */
