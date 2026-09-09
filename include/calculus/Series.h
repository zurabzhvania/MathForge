#ifndef SERIES_H
#define SERIES_H

namespace Series
{
    double exponentialMaclaurin(
        double x,
        int terms
    );

    double sineMaclaurin(
        double x,
        int terms
    );

    double exponentialTaylor(
        double x,
        double a,
        int terms
    );

    double sineTaylor(
        double x,
        double a,
        int terms
    );
}

#endif
