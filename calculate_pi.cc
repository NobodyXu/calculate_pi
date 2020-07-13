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

    for (T x = -1; x <= 1; x += gaps)
        circle_S += count_points_from_line_in_circle(x, gaps);

    return T(circle_S * 4) / square_S;
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
