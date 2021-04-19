#include "Oulu.h"

NAMESPACE_OULU_BEGIN

double Interpolate( double val, double y0, double x0, double y1, double x1 ) {
    return (val-x0)*(y1-y0)/(x1-x0) + y0;
}

double JetPaletteBase( double val ) {
    if ( val <= -0.75 ) return 0;
    else if ( val <= -0.25 ) return Interpolate( val, 0.0, -0.75, 1.0, -0.25 );
    else if ( val <= 0.25 ) return 1.0;
    else if ( val <= 0.75 ) return Interpolate( val, 1.0, 0.25, 0.0, 0.75 );
    else return 0.0;
}

double JetPaletteRed( double gray ) {
    return JetPaletteBase( gray - 0.5 );
}
double JetPaletteGreen( double gray ) {
    return JetPaletteBase( gray );
}
double JetPaletteBlue( double gray ) {
    return JetPaletteBase( gray + 0.5 );
}

NAMESPACE_OULU_END
