#include <iostream>
#include <iomanip>
#include <array>
#include <math.h>

inline double sqr(double x) {
    return x*x;
}

class Point {
public:
    Point(){}
    Point(double x, double y) : x(x), y(y) {}

    double x;
    double y;
};

class Vector {
public:
    Vector(){}
    Vector(double x, double y) : x(x), y(y) {}

    double x;
    double y;
};

std::ostream& operator<<(std::ostream &ostr, const Point &p) {
    return ostr << "(" << p.x << ", " << p.y << ")"; 
}

double distance(const Point &p1, const Point &p2) {
    return sqrt(sqr(p1.x-p2.x) + sqr(p1.y-p2.y));
}

Vector unitVector(const Point &p1, const Point &p2) {

    const double len = distance(p1, p2);

    return Vector((p2.x - p1.x)/len, (p2.y - p1.y)/len);
}

double angle(const Point &p1, const Point &p2, const Point &p3) {
    const auto v1 = unitVector(p1,p2);
    const auto v2 = unitVector(p2,p3);

    const auto dotProduct = v1.x*v2.x + v1.y*v2.y;

    const auto radians = acos(dotProduct);
    const auto degrees = (radians / M_PI) * 180.0;

    return degrees;
}

//corners
const Point lowXlowY(0,0);
const Point highXlowY(1,0);
const Point lowXhighY(3,1);
const Point highXhighY(4,1);

// search range
constexpr double minX = 0;
constexpr double maxX = 4;
constexpr double minY = 0;
constexpr double maxY = 1;


double pathDistance(const Point &p1, const Point &p2) {
    const double mainDiagonal = 
        distance(lowXlowY, p1) +
        distance(p1, p2) + 
        distance(p2, highXhighY);

    const double offDiagonals = 
        distance(highXlowY, p1) +
        distance(lowXhighY, p2);

    return mainDiagonal + offDiagonals;
}

template<size_t nSteps> std::array<double, nSteps> steps(double low, double high) {
    const double step = (high - low)/nSteps;
    std::array<double, nSteps> steps;
    for(size_t index = 0; index < nSteps; ++index) {
        steps[index] = low + index * step;
    }

    return steps;
}

void full() {

    constexpr std::size_t nStepsX = 101;
    constexpr std::size_t nStepsY = 101;

    auto xSteps = steps<nStepsX>(minX, maxX);
    auto ySteps = steps<nStepsY>(minY, maxY);

    double bestDistance = HUGE_VAL;
    Point bestP1;
    Point bestP2;

    for (const auto &x1 : xSteps)
    {
        for (const auto &y1 : ySteps)
        {
            for (const auto &x2 : xSteps)
            {
                for (const auto &y2 : ySteps)
                {
                    const Point p1(x1, y1);
                    const Point p2(x2, y2);
                    const double distance = pathDistance(p1, p2);
                    if (distance < bestDistance)
                    {
                        bestDistance = distance;
                        bestP1 = p1;
                        bestP2 = p2;
                    }
                }
            }
        }
    }

    std::cout << bestP1 << " " << bestP2 << ": " << bestDistance << std::endl;

    std::cout << "angle(lowXlowY, p1, highXlowY)=" << angle(lowXlowY, bestP1, highXlowY) << std::endl;
    std::cout << "angle(lowXlowY, p1, p2)=" << angle(lowXlowY, bestP1, bestP2) << std::endl;
    std::cout << "angle(highXlowY, p1, p2)=" << angle(highXlowY, bestP1, bestP2) << std::endl;
}

void hack() {

    constexpr std::size_t nStepsX = 10001;
    constexpr std::size_t nStepsY = 10001;

    auto xSteps = steps<nStepsX>(0.9, 1);
    auto ySteps = steps<nStepsY>(0, 0.1);

    double bestDistance = HUGE_VAL;
    Point bestP1;
    Point bestP2;

    for (const auto &x1 : xSteps)
    {
        for (const auto &y1 : ySteps)
        {
            //for (const auto &x2 : xSteps)
            const auto x2 = (minX + maxX) - x1;
            {
                const auto y2 = (minY + maxY) - y1;
                //for (const auto &y2 : ySteps)
                {
                    const Point p1(x1, y1);
                    const Point p2(x2, y2);
                    const double distance = pathDistance(p1, p2);
                    if (distance < bestDistance)
                    {
                        bestDistance = distance;
                        bestP1 = p1;
                        bestP2 = p2;
                    }
                }
            }
        }
    }

    std::cout << bestP1 << " " << bestP2 << ": " << bestDistance << std::endl;

    std::cout << "angle(lowXlowY, p1, highXlowY)=" << angle(lowXlowY, bestP1, highXlowY) << std::endl;
    std::cout << "angle(lowXlowY, p1, p2)=" << angle(lowXlowY, bestP1, bestP2) << std::endl;
    std::cout << "angle(highXlowY, p1, p2)=" << angle(highXlowY, bestP1, bestP2) << std::endl;
}

main() {
    hack();
}