#include <app/Graph.h>

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

void Graph::plot(
    std::function<double(double)> f,
    double xMin,
    double xMax
)
{
    const int width = 80;
    const int height = 25;

    if (!f || !std::isfinite(xMin) || !std::isfinite(xMax) || xMin >= xMax)
    {
        std::cout << "A finite increasing x interval is required."
                  << std::endl;
        return;
    }

    std::vector<std::string> grid(
        height,
        std::string(width, ' ')
    );

    double dx =
        (xMax - xMin) / (width - 1);

    std::vector<double> yValues;

    double yMin =
        std::numeric_limits<double>::max();

    double yMax =
        std::numeric_limits<double>::lowest();

    for (int col = 0; col < width; col++)
    {
        double x =
            xMin + col * dx;

        double y =
            f(x);

        if (!std::isfinite(y))
        {
            std::cout << "Cannot graph a function that is undefined or infinite "
                      << "on the selected interval."
                      << std::endl;
            return;
        }

        yValues.push_back(y);

        if (y < yMin)
        {
            yMin = y;
        }

        if (y > yMax)
        {
            yMax = y;
        }
    }

    if (std::abs(yMax - yMin) < 0.000001)
    {
        yMax += 1;
        yMin -= 1;
    }

    int xAxis =
        static_cast<int>(
            (yMax / (yMax - yMin))
            * (height - 1)
        );

    int yAxis =
        static_cast<int>(
            (-xMin / (xMax - xMin))
            * width
        );

    for (int row = 0; row < height; row++)
    {
        if (yAxis >= 0 && yAxis < width)
        {
            grid[row][yAxis] = '|';
        }
    }

    for (int col = 0; col < width; col++)
    {
        if (xAxis >= 0 && xAxis < height)
        {
            grid[xAxis][col] = '-';
        }
    }

    if (xAxis >= 0 &&
        xAxis < height &&
        yAxis >= 0 &&
        yAxis < width)
    {
        grid[xAxis][yAxis] = '+';
    }

    for (int col = 0; col < width; col++)
    {
        double y =
            yValues[col];

        int row =
            static_cast<int>(
                (yMax - y)
                / (yMax - yMin)
                * (height - 1)
            );

        if (row >= 0 && row < height)
        {
            grid[row][col] = '*';
        }
    }

    for (const auto& line : grid)
    {
        std::cout << line
                  << std::endl;
    }

    std::cout << std::endl;

    std::cout << "yMin = "
              << yMin
              << std::endl;

    std::cout << "yMax = "
              << yMax
              << std::endl;
}
