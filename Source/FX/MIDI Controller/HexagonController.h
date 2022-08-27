/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.4

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
class TwonkToolBarButton;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class HexagonController  : public Component
{
public:
    //==============================================================================
    HexagonController ();
    ~HexagonController();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	class Polygon : public Component
	{
	public:
		void paint(Graphics &g)
		{
			g.setColour(Colours::red);
			g.strokePath(hex, PathStrokeType(1.0f));
			if (isMouseButtonDown())
			{
				g.setColour(Colours::red.brighter());
				g.fillPath(hex);
			}
		}

		void resized()
		{
			hex.clear();
			hex.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth() * 0.5f, 0.0f);
		}

		void mouseDown(const MouseEvent &e) override
		{
			repaint();
		}

		void mouseUp(const MouseEvent &e) override
		{
			repaint();
		}

		bool hitTest(int x, int y) override
		{
			return hex.contains((float)x, (float)y);
		}
		Path hex;
	};
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void mouseMove (const MouseEvent& e) override;
    void mouseDown (const MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HexagonController)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

