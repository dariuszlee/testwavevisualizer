#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "FrequencyVisualizer.h"
#include <mutex>


const int kNumPresets = 1;

enum EParams
{
  kGain = 0,
  kMeter,
  kNumParams
};

using namespace iplug;
using namespace igraphics;

class TestWaveVisualizer final : public Plugin
{
public:
  TestWaveVisualizer(const InstanceInfo& info);

#if IPLUG_DSP // http://bit.ly/2S64BDd
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void OnIdle() override;
#endif

private:
  VisualizerData* pLastVal;
  std::mutex g_pages_mutex;
  int pSample;
  int pThreshold;
};
