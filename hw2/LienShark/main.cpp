//
//  main.cpp
//  Hw2_try
//
//  Created by 許承晏 on 2024/9/24.
//
#include <vector>
#include <iostream>
using namespace std;

class Line {
public:
    // 預設建構函數
    Line() = default;

    // 初始化指定大小的建構函數
    Line(size_t size) : x_coords(size), y_coords(size) {}

    // 複製建構函數
    Line(const Line& other) : x_coords(other.x_coords), y_coords(other.y_coords) {}

    // 移動建構函數
    Line(Line&& other) noexcept : x_coords(std::move(other.x_coords)), y_coords(std::move(other.y_coords)) {}

    // 複製指派運算子
    Line& operator=(const Line& other) {
        if (this != &other) {
            x_coords = other.x_coords;
            y_coords = other.y_coords;
        }
        return *this;
    }

    // 移動指派運算子
    Line& operator=(Line&& other) noexcept {
        if (this != &other) {
            x_coords = std::move(other.x_coords);
            y_coords = std::move(other.y_coords);
        }
        return *this;
    }

    // 解構函數
    ~Line() = default;

    // 回傳點的數量
    size_t size() const {
        return x_coords.size();
    }

    // 存取 x 座標
    float& x(size_t it) {
        return x_coords[it];
    }

    const float& x(size_t it) const {
        return x_coords[it];
    }

    // 存取 y 座標
    float& y(size_t it) {
        return y_coords[it];
    }

    const float& y(size_t it) const {
        return y_coords[it];
    }

private:
    std::vector<float> x_coords; // 存儲 x 座標的 STL 容器
    std::vector<float> y_coords; // 存儲 y 座標的 STL 容器
};


int main(int, char **)
{
    Line line(3);
    line.x(0) = 0; line.y(0) = 1;
    line.x(1) = 1; line.y(1) = 3;
    line.x(2) = 2; line.y(2) = 5;

    Line line2(line);
    line2.x(0) = 9;

    std::cout << "line: number of points = " << line.size() << std::endl;
    for (size_t it=0; it<line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                  << " x = " << line.x(it)
                  << " y = " << line.y(it) << std::endl;
    }

    std::cout << "line2: number of points = " << line.size() << std::endl;
    for (size_t it=0; it<line.size(); ++it)
    {
        std::cout << "point " << it << ":"
                  << " x = " << line2.x(it)
                  << " y = " << line2.y(it) << std::endl;
    }

    return 0;
}
