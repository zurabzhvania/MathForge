#ifndef GRAPH_H
#define GRAPH_H

#include <functional>

class Graph
{
public:
    static void plot(
        std::function<double(double)> f,
        double xMin,
        double xMax
    );
};

#endif
