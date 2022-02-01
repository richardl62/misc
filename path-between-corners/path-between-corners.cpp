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

std::ostream& operator<<(std::ostream &ostr, const Point &p) {
    return ostr << "(" << p.x << ", " << p.y << ")"; 
}

double distance(const Point &p1, const Point &p2) {
    return sqrt(sqr(p1.x-p2.x) + sqr(p1.y-p2.y));
}

double pathDistance(const Point &p1, const Point &p2) {
    const double mainDiagonal = 
        distance(Point(0,0), p1) +
        distance(p1, p2) + 
        distance(p2, Point(1,1));

    const double offDiagonals = 
        distance(Point(0,1), p1) +
        distance(Point(1,0), p2);

    return mainDiagonal + offDiagonals;
}

void full() {
    constexpr std::size_t nSteps = 101;
    std::array<double, nSteps> steps;

    for(size_t index = 0; index < nSteps; ++index) {
        steps[index] = index * 1.0/(nSteps - 1);
    }

    double bestDistance = HUGE_VAL;
    Point bestP1;
    Point bestP2;

    for (const auto &x1 : steps)
    {
        for (const auto &y1 : steps)
        {
            for (const auto &x2 : steps)
            {
                for (const auto &y2 : steps)
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
}

void hack() {
    constexpr std::size_t nSteps = 10000001;
    // std::array<double, nSteps> steps;

    // for(size_t index = 0; index < nSteps; ++index) {
    //     steps[index] = index * 1.0/(nSteps - 1);
    // }

    double bestDistance = HUGE_VAL;
    Point bestP1;
    Point bestP2;

    for(size_t index = 0; index < nSteps; ++index)
    {
        const double x1 = index * 1.0/(nSteps - 1);

        //for (const auto &y1 : steps)
        const double y1 = 0.5;
        {
            const double x2 = 1 - x1;
            //for (const auto &x2 : steps)
            {
                //for (const auto &y2 : steps)
                const double y2 = 0.5;
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

    std::cout <<std::setprecision(12) << bestP1 << " " << bestP2 << ": " << bestDistance << std::endl;
}


main() {
    hack();
}