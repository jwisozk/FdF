#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void    draw_bresenham_line(int x1, int y1, int x2, int y2, int color)
{
    int dx;
    int dy;
    int    step;
    float    slope;
    float     error;
    int    x;
    int    y;

    ////
    color = 0;
    ////

    dx = x2 - x1;
    dy = y2 - y1;
    slope = abs(dx) > abs(dy) ? abs(dy) / abs(dx) : abs(dx) / abs(dy);
    step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    error = 0;
    x = x1;
    y = y1;
    while (step > 0)
    {
        printf("x = %d, y = %d, error = %f\n", x, y, error);
        error = error + slope;
        x = abs(dx) > abs(dy) ? x++ : (int)round((float)x + error);
        y = abs(dy) > abs(dx) ? y++ : (int)round((float)y + error);
        step--;
    }
}

int   main(void)
{
    draw_bresenham_line(1, 1, 8, 4, 255);
    return (0);
}