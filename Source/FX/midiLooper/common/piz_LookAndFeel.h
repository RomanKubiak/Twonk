#ifndef __PIZLOOKANDFEEL__
#define __PIZLOOKANDFEEL__

#include "JuceHeader.h"

//==============================================================================
class PizLookAndFeel    : public LookAndFeel_V4
{
public:
    //==============================================================================
    /** Creates the default JUCE look and feel. */
    PizLookAndFeel();

    /** Destructor. */
    virtual ~PizLookAndFeel();

    //==============================================================================
    /** Draws the lozenge-shaped background for a standard button. */
    void drawButtonBackground (Graphics& g,
                                       Button& button,
                                       const Colour& backgroundColour,
                                       bool isMouseOverButton,
                                       bool isButtonDown);


    /** Draws the contents of a standard ToggleButton. */
    void drawToggleButton (Graphics& g,
                                   ToggleButton& button,
                                   bool isMouseOverButton,
                                   bool isButtonDown);

    void drawTickBox (Graphics& g,
                              Component& component,
                              int x, int y, int w, int h,
                              const bool ticked,
                              const bool isEnabled,
                              const bool isMouseOverButton,
                              const bool isButtonDown);

    //==============================================================================
    void drawTextEditorOutline (Graphics& g,
                                        int width, int height,
                                        TextEditor& textEditor);

    //==============================================================================
    /** Fills the background of a popup menu component. */
    void drawPopupMenuBackground (Graphics& g, int width, int height);
    Font getPopupMenuFont();

    void drawMenuBarBackground (Graphics& g, int width, int height,
                                        bool isMouseOverBar,
                                        MenuBarComponent& menuBar);

    //==============================================================================
    void drawComboBox (Graphics& g, int width, int height,
                               bool isButtonDown,
                               int buttonX, int buttonY,
                               int buttonW, int buttonH,
                               ComboBox& box);

	Font getComboBoxFont (ComboBox& box);

    //==============================================================================
    void drawLinearSlider (Graphics& g,
                                   int x, int y,
                                   int width, int height,
                                   float sliderPos,
                                   float minSliderPos,
                                   float maxSliderPos,
                                   const Slider::SliderStyle style,
                                   Slider& slider);

    int getSliderThumbRadius (Slider& slider);

    void drawRotarySlider (Graphics& g,
                                   int x, int y,
                                   int width, int height,
                                   float sliderPosProportional,
                                   float rotaryStartAngle,
                                   float rotaryEndAngle,
                                   Slider& slider);

    Button* createSliderButton (Button &, bool isIncrement);

    //==============================================================================
    virtual void drawCornerResizer (Graphics& g,
                                    int w, int h,
                                    bool isMouseOver,
                                    bool isMouseDragging);

    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    PizLookAndFeel (const PizLookAndFeel&);
    const PizLookAndFeel& operator= (const PizLookAndFeel&);
};


#endif   // __JUCE_PIZLOOKANDFEEL_JUCEHEADER__
