#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include <valarray>
#include <complex>

const double PI = 3.141592653589793238460;
 
typedef std::complex<double> Complex;

using namespace iplug;
using namespace igraphics;

Complex** fft(sample** x, int nFrames, int nChans);
