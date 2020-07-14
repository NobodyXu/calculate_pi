#include <cstdio>

#include <cstdlib>
#include <err.h>
#include <cerrno>

#include "utility.hpp"

template <class T>
T calculate_pi(T gaps) noexcept
{
    // can be interpretted as Surface area or Sum of the circle with R = 1
    T circle_S = 0;
    T square_S = 4 / (gaps * gaps);

    T y = 0;
    for (T x = -1; x < 0; x += gaps)
        circle_S += count_points_from_line_in_circle2(x, y, gaps);

    // S_circle / S_square = pi * ((1) ** 2) / (2 * 2)
    //                     = pi / 4
    //
    // So pi = S_circle / S_square * 4
    //
    // number of points in circle that has x \in (-1, 0) is
    // the same as points has x \in (0, 1) due to symmtry of the
    // circle
    return circle_S / square_S * 8 + 
           // x == 0 is special: It should only be counted once.
           // Since it is probably too large, adding it to circle_S
           // might make it overflow
           //
           //   (2 / gaps) / (4 / (gaps * gaps)) * 4
           // = 8 / gaps / 4 * (gaps * gaps)
           // = 2 / gaps * (gaps * gaps)
           // = 2 * gaps
           (gaps * 2);
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
