#ifndef Piz_VSTSlider_h
#define Piz_VSTSlider_h

#include "../JuceLibraryCode/JuceHeader.h"

class VSTSlider : public Slider
{
public:
    VSTSlider(String name);
    ~VSTSlider();
    String getTextFromValue (double value);
    void setOwner(AudioProcessor*, int);
    float mapToVSTRange();
    void setVSTSlider(float x);
	void setIndex(int index);
private:
    AudioProcessor* ownerPlugin;
    int vstIndex;
};
#endif
