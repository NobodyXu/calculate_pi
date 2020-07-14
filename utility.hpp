#ifndef  __calculate_pi_utility_HPP__
# define __calculate_pi_utility_HPP__

# include <cstdint>

/**
 * @param gaps < 1
 * count number of points from a line that is in the circle R = 1.
 */
template <class T>
auto count_points_from_line_in_circle(T x, T gaps) -> T
{
    if (x == 1 || x == -1)
        return 1;
    else if (x == 0)
        // Any point which has x == 0 is in the circle of R = 1.
        return 2 / gaps;

    // Calculate downwards is faster than upwards by roughly 3 times.
    //
    // It is due to the fact that the circle took > 50% of the surface
    // area of the square, thus calculating downwards is faster.
    T y = 1;
    for (; y > 0 && x * x + y * y > 1; y -= gaps)
        ;

    // Now y is the first that is in the circle
    // The rest of points that is in the circle and
    // has y > 0 can be calculated.
    //
    // Since a circle is symmtric, the points with
    // y < 0 is the same as the ones with y > 0.
    //
    // y == 0 is a special case where it is always
    // in the circle, given any x.
    return (y / gaps) * 2 + 1;
}

/**
 * @param gaps < 1
 * @param y either is 0, or the one pass to previous call to 
 *          count_points_from_line_in_circle2(x1, y, gaps),
 *          where -1 <= x1 < x <= 0.
 * count number of points from a line that is in the circle R = 1.
 */
template <class T>
auto count_points_from_line_in_circle2(T x, T &y, T gaps) -> T
{
    if (x == 1 || x == -1)
        return 1;
    else if (x == 0)
        // Any point which has x == 0 is in the circle of R = 1.
        return 2 / gaps;

    // Calculate downwards is faster than upwards by roughly 3 times.
    //
    // It is due to the fact that the circle took > 50% of the surface
    // area of the square, thus calculating downwards is faster.
    //
    // However, now that y is cached and x is guaranteed to be growing,
    // calculating upwards is faster.
    for (; y <= 1 && x * x + y * y <= 1; y += gaps)
        ;
    y -= gaps;

    // Now y is the first that is in the circle
    // The rest of points that is in the circle and
    // has y > 0 can be calculated.
    //
    // Since a circle is symmtric, the points with
    // y < 0 is the same as the ones with y > 0.
    //
    // y == 0 is a special case where it is always
    // in the circle, given any x.
    return (y / gaps) * 2 + 1;
}

#endif
