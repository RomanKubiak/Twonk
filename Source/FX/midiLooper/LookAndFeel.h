#ifndef __MIDILOOPER_LOOKANDFEEL_HEADER__
#define __MIDILOOPER_LOOKANDFEEL_HEADER__

#include "../JuceLibraryCode/JuceHeader.h"

class NonShinyLookAndFeel : public LookAndFeel_V4
{
public:
    //==============================================================================
    NonShinyLookAndFeel();

	int getTooltipSize (const String& tipText, int& width, int& height);
	void drawTooltip (Graphics& g, const String& text, int width, int height);

    //==============================================================================
    void drawButtonBackground (Graphics& g,
                                       Button& button,
                                       const Colour& backgroundColour,
                                       bool isMouseOverButton,
                                       bool isButtonDown);


	void drawButtonText (Graphics& g, TextButton& button,
                                  bool /*isMouseOverButton*/, bool /*isButtonDown*/);

	void drawToggleButton (Graphics& g,
                                   ToggleButton& button,
                                   bool isMouseOverButton,
                                   bool isButtonDown);

    void drawTickBox (Graphics& g,
                              Component& component,
                              float x, float y, float w, float h,
                              bool ticked,
                              bool isEnabled,
                              bool isMouseOverButton,
                              bool isButtonDown);

    //==============================================================================
    void drawTextEditorOutline (Graphics& g,
                                        int width, int height,
                                        TextEditor& textEditor);

    //==============================================================================
    /** Fills the background of a popup menu component. */
    void drawPopupMenuBackground (Graphics& g, int width, int height);

    void drawMenuBarBackground (Graphics& g, int width, int height,
                                        bool isMouseOverBar,
                                        MenuBarComponent& menuBar);
	Font getPopupMenuFont();
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

	Button* createSliderButton (Slider&, bool isIncrement);
    Label* createSliderTextBox (Slider& slider);

    
    void drawCornerResizer (Graphics& g,
                                    int w, int h,
                                    bool isMouseOver,
                                    bool isMouseDragging);

	//==============================================================================
    /** Utility function to draw a shiny, glassy circle (for round LED-type buttons). */
    static void drawGlassSphere (Graphics& g,
                                 float x, float y,
                                 float diameter,
                                 const Colour& colour,
                                 float outlineThickness) throw();

    static void drawGlassPointer (Graphics& g,
                                  float x, float y,
                                  float diameter,
                                  const Colour& colour, float outlineThickness,
                                  int direction) throw();

    /** Utility function to draw a shiny, glassy oblong (for text buttons). */
    static void drawGlassLozenge (Graphics& g,
                                  float x, float y,
                                  float width, float height,
                                  const Colour& colour,
                                  float outlineThickness,
                                  float cornerSize,
                                  bool flatOnLeft, bool flatOnRight,
                                  bool flatOnTop, bool flatOnBottom) throw();

private:

    void drawShinyButtonShape (Graphics& g,
                               float x, float y, float w, float h, float maxCornerSize,
                               const Colour& baseColour,
                               float strokeWidth,
                               bool flatOnLeft,
                               bool flatOnRight,
                               bool flatOnTop,
                               bool flatOnBottom) throw();
};


#endif
