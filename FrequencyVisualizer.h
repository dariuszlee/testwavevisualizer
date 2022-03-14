#pragma once

#include "IControl.h"
#include <complex.h>
#include <math.h>
#include <sstream>

using namespace iplug;
using namespace igraphics;
typedef std::complex<double> Complex;

struct VisualizerData {
  unsigned int samples;
  double sampleRate;
  Complex ** sampleDbs;
  unsigned int nChans;

  VisualizerData() : samples(0), nChans(0), sampleRate(0.0) {}

  VisualizerData(unsigned int samples, double sampleRate, unsigned int nChans, Complex ** sampleDbs) : samples(samples), nChans(nChans), sampleRate(sampleRate), sampleDbs(sampleDbs) {}

  VisualizerData(const VisualizerData & other) : samples(other.samples), nChans(other.nChans), sampleRate(other.sampleRate) {
    sampleDbs = new Complex*[other.nChans];
    for(int c = 0; c < nChans; c++){
      sampleDbs[c] = new Complex[other.samples];
      for ( int j = 0; j < other.samples ; j++){
        sampleDbs[c][j] = Complex(other.sampleDbs[c][j]);
      }
    }
  }

  ~VisualizerData() {
      if (nChans != 0) {
		for(int c = 0; c < nChans; c++){
		  delete[] sampleDbs[c];
		}
		delete [] sampleDbs;

    }
  }
};

class FrequencyVisualizer final : public IBitmapControl
{
public:
  FrequencyVisualizer(const IRECT& bounds, const IBitmap& bitmap)
  : IBitmapControl(bounds, bitmap), data()
  {
  }
  
  void Draw(IGraphics& g) override
  {
    g.FillRect(COLOR_WHITE, mRECT);
    IRECT r = mRECT;
    
    g.StartLayer(this, r);
    /* double maxRange = 8388607; */
    double maxRange = 1;
    double maxDbfs = 144;

    double lineMax = -200000;
    double nSamples = data.samples / 2;
    double width = r.W() / (double) nSamples;
    for (int c = 0; c < data.nChans - 1; c++) {
      for (int k = 0; k < nSamples; k++) {

        double line = 20 * log10(abs(data.sampleDbs[c][k + (int) nSamples].real()) / maxRange);
        double lineRation = (maxDbfs + line) / maxDbfs;
        if(line > lineMax){
          lineMax = line;
        }
        g.DrawLine(COLOR_INDIGO, k * width, r.B, k * width, r.B - (lineRation * r.H()), 0, width);
      }
    }

    std::stringstream ss("");
    ss << lineMax;
    g.DrawText(IText(20), ss.str().c_str(), mRECT.GetCentredInside(20));

    mLayer = g.EndLayer();
    g.DrawLayer(mLayer);
  }

  void OnMsgFromDelegate(int msgTag, int dataSize, const void* pData) {
    data = *((VisualizerData*) pData);
    delete pData;
    SetDirty(true);
  }


private:
  ILayerPtr mLayer;
  VisualizerData data;
};