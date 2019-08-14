#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"

class TwonkToolBarButton : public Button
{
	public:
		TwonkToolBarButton ();
		~TwonkToolBarButton();
		void paintButton(Graphics &g, bool, bool);
		void setIcon(Image _icon) { icon = _icon;  }
		void setBaseColour(Colour _baseColour) { baseColour = _baseColour;  }
		void resized() override;
	private:
		Colour baseColour;
		Path roundingHexagon;
		Image icon;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TwonkToolBarButton)
};

