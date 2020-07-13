#include <cstdio>
#include "utility.hpp"

template <class T>
T calculate_pi(T gaps) noexcept
{
    // can be interpretted as Surface area or Sum of the circle with R = 1
    T circle_S = 0;
    T square_S = 4 / (gaps * gaps);

    for (T x = -1; x <= 1; x += gaps)
        circle_S += count_points_from_line_in_circle(x, gaps);

    return T(circle_S * 4) / square_S;
}

int main(int argc, char* argv[])
{
    std::printf("pi = %Lf\n", calculate_pi(0.00001L));
}
