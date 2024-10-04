# include <iostream>
# include <vector>

class Line {
public:
    Line();
    Line(size_t n);
    Line(Line const & );
    size_t size() const;
    float const & x(size_t it) const;
    float       & x(size_t it)      ;
    float const & y(size_t it) const;
    float       & y(size_t it)      ;

private:
    std::vector<float> m_x;
    std::vector<float> m_y;
};

Line::Line() {
    m_x.resize(0);
    m_y.resize(0);
}

Line::Line(size_t n) {
    m_x.resize(n);
    m_y.resize(n);
}

Line::Line(Line const & line) {
    m_x = line.m_x;
    m_y = line.m_y;
}

size_t Line::size() const {
    if (m_x.size() != m_y.size()) throw std::runtime_error("x and y have different sizes");
    return m_x.size();
}

float const & Line::x(size_t it) const {
    return m_x[it];
}

float & Line::x(size_t it) {
    return m_x[it];
}

float const & Line::y(size_t it) const {
    return m_y[it];
}

float & Line::y(size_t it) {
    return m_y[it];
}


int main(int, char **) {
    Line line(3);
    line.x(0) = 0; line.y(0) = 1;
    line.x(1) = 1; line.y(1) = 3;
    line.x(2) = 2; line.y(2) = 5;

    Line line2(line);
    line2.x(0) = 9;

    std::cout << "line: number of points = " << line.size() << std::endl;
    for (size_t it=0; it<line.size(); ++it) {
        std::cout << "point " << it << ":"
                  << " x = " << line.x(it)
                  << " y = " << line.y(it) << std::endl;
    }

    std::cout << "line2: number of points = " << line.size() << std::endl;
    for (size_t it=0; it<line.size(); ++it) {
        std::cout << "point " << it << ":"
                  << " x = " << line2.x(it)
                  << " y = " << line2.y(it) << std::endl;
    }

    return 0;
}