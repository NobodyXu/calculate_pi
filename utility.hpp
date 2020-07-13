#ifndef  __calculate_pi_utility_HPP__
# define __calculate_pi_utility_HPP__

# include <cstdint>

/**
 * @param gaps < 1
 * count number of points from a line that is in the circle R = 1.
 */
template <class T>
auto count_points_from_line_in_circle(T x, T gaps) -> std::uint64_t
{
    if (x == 1 || x == -1)
        return 1;
    else if (x == 0)
        // Any point which has x == 0 is in the circle of R = 1.
        return 2 / gaps;

    T y = gaps;
    std::uint64_t cnt = 0;
    for (; x * x + y * y <= 1; y += gaps)
        ++cnt;

    // Now y is the first that is in the circle
    // The rest of points that is in the circle and
    // has y > 0 can be calculated.
    //
    // Since a circle is symmtric, the points with
    // y < 0 is the same as the ones with y > 0.
    //
    // y == 0 is a special case where it is always
    // in the circle, given any x.
    return cnt * 2 + 1;
}

#endif
