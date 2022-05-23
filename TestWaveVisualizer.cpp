#include "TestWaveVisualizer.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "fft.h"

TestWaveVisualizer::TestWaveVisualizer(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets)), pLastVal(new VisualizerData()), pSample(0), pThreshold(50)
{
  GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");

#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  
  mLayoutFunc = [&](IGraphics* pGraphics) {
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(COLOR_GRAY);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
    const IRECT b = pGraphics->GetBounds();
    pGraphics->AttachControl(new ITextControl(b.GetFromBottom(50), "Hello iPlug 2!", IText(50)));
    pGraphics->AttachControl(new IVKnobControl(b.GetCentredInside(100).GetHShifted(-250).GetVShifted(250), kGain));

    FrequencyVisualizer* freqVis = new FrequencyVisualizer(b.GetFromTop(500), pGraphics->LoadBitmap("C:\\Users\\dariu\\OneDrive\\Pictures\\DSC_4688.jpg"));
    pGraphics->AttachControl(freqVis, 
        kMeter);
  };
#endif
}

#if IPLUG_DSP
void TestWaveVisualizer::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const double gain = GetParam(kGain)->Value() / 100.;
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
    for (int c = 0; c < nChans; c++) {
      outputs[c][s] = inputs[c][s] * gain;
    }
  }

  if (pSample == pThreshold) {
    std::lock_guard<std::mutex> guard(g_pages_mutex);
    delete pLastVal;
    pLastVal = new VisualizerData(nFrames, GetSampleRate(), nChans, fft(inputs, nFrames, nChans));
    pSample = 0;
  }
  pSample += 1;
}

void TestWaveVisualizer::OnIdle() {
  std::lock_guard<std::mutex> guard(g_pages_mutex);
  VisualizerData* toSend = new VisualizerData(*pLastVal);
  SendControlMsgFromDelegate(kMeter, 0, sizeof(VisualizerData), toSend);
}

#endif