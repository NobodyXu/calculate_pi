#include <cstdio>
#include <thread>

#include "utility.hpp"

template <class T>
class Thread {
    // Part of the circle_S
    T circle_S = 0;

    std::thread thread;

public:
    Thread(T gaps, T start_x, T end_x):
        thread{[](T &circle_S, T gaps, T start_x, T end_x) noexcept {
            for (T x = start_x; x < end_x; x += gaps) {
                for (T y = -1; y <= 1; y += gaps) {
                    if (x * x + y * y <= 1)
                        circle_S += 1;
                }
            }
        }, circle_S, gaps, start_x, end_x}
    {}
};

template <class T>
T calculate_pi(T gaps) noexcept
{
    // can be interpretted as Surface area or Sum of the circle with R = 1
    T circle_S = 0;
    T square_S = 4 / (gaps * gaps);

    for (T x = -1; x <= 1; x += gaps) {
        for (T y = -1; y <= 1; y += gaps) {
            if (x * x + y * y <= 1)
                circle_S += 1;
        }
    }

    return circle_S * 4 / square_S;
}

int main(int argc, char* argv[])
{
    std::printf("pi = %Lf\n", calculate_pi(0.00001L));
}
