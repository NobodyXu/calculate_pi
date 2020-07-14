#include <cstdio>
#include <cinttypes>

#include <cstdlib>
#include <err.h>
#include <cerrno>

#include "utility.hpp"

template <class T>
T calculate_pi(T gaps) noexcept
{
    // S_square = 4 / (gaps * gaps);
    // 
    // S_circle / S_square = pi * ((1) ** 2) / (2 * 2)
    //                     = pi / 4
    //
    // So pi = S_circle / S_square * 4
    //       = 4 * S_circle / (4 / (gaps * gaps))
    //       = S_circle * gaps * gaps

    // y == 0 is a special case where it is always
    // in the circle, given any x.
    long double pi = (1 - gaps) * gaps;

    T y = 0;
    // Calculate 1 / 4 part of circle
    for (T x = -1 + gaps; x < -0.0L; x += gaps) {
        // Calculate downwards is faster than upwards by roughly 3 times.
        //
        // It is due to the fact that the circle took > 50% of the surface
        // area of the square, thus calculating downwards is faster.
        //
        // However, now that y is cached and x is guaranteed to be growing,
        // calculating upwards is faster.
        for (y += gaps; x * x + y * y <= 1; y += gaps)
            ;
        y -= gaps;

        pi += y * gaps;
    }

    return pi * 4;
}

auto Strtold(const char *str) -> long double
{
    char *str_end;

    errno = 0;
    auto ret = std::strtold(str, &str_end);
    if (str_end == str || *str_end != '\0' || errno != 0)
        err(1, "std::strtold(%s, &str_end) failed", str);

    return ret;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        errx(1, "Usage %s: gaps\n    gaps should in range (0, 1)", argv[0]);

    auto gap = Strtold(argv[1]);
    if (gap <= 0)
        errx(1, "argv[1] too small! Should be greater than 0.");
    else if (gap >= 1)
        errx(1, "argv[1] too big! Should be less than 1.");

    std::printf("pi = %Lf\n", calculate_pi(gap));
}
