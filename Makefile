# CXX=x86_64-w64-mingw32-g++ -std=c++17
# CXX=x86_64-w64-mingw32-g++ -std=c++17


LINUX_MINGW :=/usr
WIN_MINGW :=/mnt/c/msys64/mingw64/
# MINGW := $(LINUX_MINGW)
MINGW := $(WIN_MINGW)

# export PATH := $(MINGW)/bin:$(MINGW)/lib/gcc/x86_64-w64-mingw32/11.2.0

CXX=$(LINUX_MINGW)/bin/x86_64-w64-mingw32-g++ -std=c++17
WINDRES := $(LINUX_MINGW)/bin/x86_64-w64-mingw32-windres


IGRAPHICS_DEPENDENCIS := ../iPlug2/Dependencies/IGraphics

# INCLUDE := -I../iPlug2/Dependencies/IPlug/RTAudio -I../iPlug2/Dependencies/IPlug/RTMidi -I../iPlug2/IGraphics/Controls -I../iPlug2/IGraphics/Drawing -I../iPlug2/IGraphics/Platforms  -I../iPlug2/IPlug/APP -I../iPlug2/IPlug 
INCLUDE := -I../iPlug2/Dependencies/IPlug/RTMidi -I../iPlug2/IGraphics -I../iPlug2/IGraphics/Controls -I../iPlug2/IGraphics/Drawing -I../iPlug2/IGraphics/Platforms  -I../iPlug2/IPlug/APP -I../iPlug2/IPlug -I../iPlug2/WDL/ -I$(IGRAPHICS_DEPENDENCIS)/NanoVG/src -I../iPlug2/Dependencies/IGraphics/NanoSVG/src -I../iPlug2/IPlug/Extras -I$(IGRAPHICS_DEPENDENCIS)/STB -I$(IGRAPHICS_DEPENDENCIS)/glad_GL2/include -I$(IGRAPHICS_DEPENDENCIS)/glad_GL2/src/ -I./ -I../iPlug2/Dependencies/IPlug/RTAudio -I./resources -I../iPlug2/Dependencies/IPlug/RTAudio/include
# SRCS = ../iPlug2/Dependencies/IPlug/RTAudio/include/asio.cpp ../iPlug2/Dependencies/IPlug/RTAudio/include/asiodrivers.cpp ../iPlug2/Dependencies/IPlug/RTAudio/include/asiolist.cpp ../iPlug2/Dependencies/IPlug/RTAudio/include/iasiothiscallresolver.cpp ../iPlug2/Dependencies/IPlug/RTAudio/RtAudio.cpp ../iPlug2/Dependencies/IPlug/RTMidi/RtMidi.cpp ../iPlug2/IGraphics/Controls/IControls.cpp ../iPlug2/IGraphics/Controls/IPopupMenuControl.cpp ../iPlug2/IGraphics/Controls/ITextEntryControl.cpp ../iPlug2/IGraphics/Drawing/IGraphicsNanoVG.cpp ../iPlug2/IGraphics/IControl.cpp ../iPlug2/IGraphics/IGraphics.cpp ../iPlug2/IGraphics/IGraphicsEditorDelegate.cpp ../iPlug2/IGraphics/Platforms/IGraphicsWin.cpp ../iPlug2/IPlug/APP/IPlugAPP.cpp ../iPlug2/IPlug/APP/IPlugAPP_dialog.cpp ../iPlug2/IPlug/APP/IPlugAPP_host.cpp ../iPlug2/IPlug/APP/IPlugAPP_main.cpp ../iPlug2/IPlug/IPlugAPIBase.cpp ../iPlug2/IPlug/IPlugParameter.cpp ../iPlug2/IPlug/IPlugPaths.cpp ../iPlug2/IPlug/IPlugPluginBase.cpp ../iPlug2/IPlug/IPlugProcessor.cpp ../iPlug2/IPlug/IPlugTimer.cpp ./fft.cpp ./FrequencyVisualizer.cpp ./TestWaveVisualizer.cpp
SRCS = ../iPlug2/Dependencies/IPlug/RTAudio/include/asio.cpp ../iPlug2/Dependencies/IPlug/RTAudio/include/asiodrivers.cpp ../iPlug2/Dependencies/IPlug/RTAudio/include/asiolist.cpp ../iPlug2/Dependencies/IPlug/RTAudio/include/iasiothiscallresolver.cpp ../iPlug2/Dependencies/IPlug/RTAudio/RtAudio.cpp ../iPlug2/Dependencies/IPlug/RTMidi/RtMidi.cpp ../iPlug2/IGraphics/Controls/IControls.cpp ../iPlug2/IGraphics/Controls/IPopupMenuControl.cpp ../iPlug2/IGraphics/Controls/ITextEntryControl.cpp ../iPlug2/IGraphics/IControl.cpp ../iPlug2/IGraphics/IGraphics.cpp ../iPlug2/IGraphics/IGraphicsEditorDelegate.cpp ../iPlug2/IGraphics/Platforms/IGraphicsWin.cpp ../iPlug2/IPlug/APP/IPlugAPP.cpp ../iPlug2/IPlug/APP/IPlugAPP_dialog.cpp ../iPlug2/IPlug/APP/IPlugAPP_host.cpp ../iPlug2/IPlug/APP/IPlugAPP_main.cpp ../iPlug2/IPlug/IPlugAPIBase.cpp ../iPlug2/IPlug/IPlugParameter.cpp ../iPlug2/IPlug/IPlugPaths.cpp ../iPlug2/IPlug/IPlugPluginBase.cpp ../iPlug2/IPlug/IPlugProcessor.cpp ../iPlug2/IPlug/IPlugTimer.cpp ./fft.cpp ./FrequencyVisualizer.cpp ./TestWaveVisualizer.cpp

LINK := 
# LINK := -lgdi32

# MINGW_LIB := /usr/x86_64-w64-mingw32/lib/
MINGW_LIB := $(MINGW)/lib
# STATIC_LINK :=
STATIC_LINK := $(MINGW_LIB)/libdsound.a $(MINGW_LIB)/libwininet.a $(MINGW_LIB)/libcomctl32.a $(MINGW_LIB)/libshlwapi.a $(MINGW_LIB)/libwinmm.a $(MINGW_LIB)/libgdi32.a $(MINGW_LIB)/libgdiplus.a $(MINGW_LIB)/libole32.a $(MINGW_LIB)/libopengl32.a $(MINGW_LIB)/libcomdlg32.a

# CXX Flags
DEBUG_DEFS := -D _DEBUG
APP_DEFS := -D APP_API -D __WINDOWS_DS__ -D __WINDOWS_MM__ -D __WINDOWS_ASIO__ -D IPLUG_EDITOR=1 -D IPLUG_DSP=1 
WIN_DEFS := -D WIN32 -D _CRT_SECURE_NO_DEPRECATE -D _CRT_NONSTDC_NO_DEPRECATE -D NOMINMAX 
MINGW_DEFS := -D MINGW

PREPROCESSORS := -D IGRAPHICS_NANOVG -D IGRAPHICS_GL2 -D OS_WIN -D _USE_MATH_DEFINES $(APP_DEFS) $(DEBUG_DEFS) $(WIN_DEFS) $(MINGW_DEFS)

CXXFLAGS += $(PREPROCESSORS)
CXXFLAGS += -fpermissive -static-libgcc -static-libstdc++

OUTPUT = ./output

SOURCE_DIRS += $(dir $(SRCS))

VPATH = $(sort $(SOURCE_DIRS))

CPP_FILES := $(notdir $(SRCS))
OBJ_FILES := $(patsubst %.cpp, $(OUTPUT)/%.o, $(CPP_FILES) )
OBJ_FILES += $(OUTPUT)/resources.o


all: $(OUTPUT)/program.exe

$(OUTPUT)/program.exe: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -g -o $@ $(LINK) $^ $(STATIC_LINK)

$(OUTPUT)/%.o : %.cpp
	$(CXX) $(CXXFLAGS) -g $(INCLUDE) -c $< -o $@

$(OUTPUT)/resources.o : resources/main.rc
	$(WINDRES) $(PREPROCESSORS) $< -o $@

clean:
	$(shell rm $(OUTPUT)/*)
