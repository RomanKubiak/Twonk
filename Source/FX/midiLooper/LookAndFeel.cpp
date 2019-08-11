  #include "LookAndFeel.h"

namespace LookAndFeelHelpers
{
    static void createRoundedPath (Path& p,
                                   const float x, const float y,
                                   const float w, const float h,
                                   const float cs,
                                   const bool curveTopLeft, const bool curveTopRight,
                                   const bool curveBottomLeft, const bool curveBottomRight) noexcept
    {
        const float cs2 = 2.0f * cs;

        if (curveTopLeft)
        {
            p.startNewSubPath (x, y + cs);
            p.addArc (x, y, cs2, cs2, float_Pi * 1.5f, float_Pi * 2.0f);
        }
        else
        {
            p.startNewSubPath (x, y);
        }

        if (curveTopRight)
        {
            p.lineTo (x + w - cs, y);
            p.addArc (x + w - cs2, y, cs2, cs2, 0.0f, float_Pi * 0.5f);
        }
        else
        {
            p.lineTo (x + w, y);
        }

        if (curveBottomRight)
        {
            p.lineTo (x + w, y + h - cs);
            p.addArc (x + w - cs2, y + h - cs2, cs2, cs2, float_Pi * 0.5f, float_Pi);
        }
        else
        {
            p.lineTo (x + w, y + h);
        }

        if (curveBottomLeft)
        {
            p.lineTo (x + cs, y + h);
            p.addArc (x, y + h - cs2, cs2, cs2, float_Pi, float_Pi * 1.5f);
        }
        else
        {
            p.lineTo (x, y + h);
        }

        p.closeSubPath();
    }

    static Colour createBaseColour (const Colour& buttonColour,
                                    const bool hasKeyboardFocus,
                                    const bool isMouseOverButton,
                                    const bool isButtonDown) noexcept
    {
        const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
        const Colour baseColour (buttonColour.withMultipliedSaturation (sat));

        if (isButtonDown)
            return baseColour.contrasting (0.2f);
        else if (isMouseOverButton)
            return baseColour.contrasting (0.1f);

        return baseColour;
    }

    static TextLayout layoutTooltipText (const String& text, const Colour& colour) noexcept
    {
        const float tooltipFontSize = 13.0f;
        const int maxToolTipWidth = 400;

        AttributedString s;
        s.setJustification (Justification::centred);
        s.append (text, Font (tooltipFontSize, Font::bold), colour);

        TextLayout tl;
        tl.createLayoutWithBalancedLineLengths (s, (float) maxToolTipWidth);
        return tl;
    }
}

static const Colour createBaseColour (const Colour& buttonColour,
                                      const bool hasKeyboardFocus,
                                      const bool isMouseOverButton,
                                      const bool isButtonDown) throw()
{
    const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
    const Colour baseColour (buttonColour.withMultipliedSaturation (sat));

    if (isButtonDown)
        return baseColour.contrasting (0.2f);
    else if (isMouseOverButton)
        return baseColour.contrasting (0.1f);

    return baseColour;
}



//==============================================================================
NonShinyLookAndFeel::NonShinyLookAndFeel()
{
    /* if this fails it means you're trying to create a LookAndFeel object before
       the static Colours have been initialised. That ain't gonna work. It probably
       means that you're using a static LookAndFeel object and that your compiler has
       decided to intialise it before the Colours class.
    */
    jassert (Colours::white == Colour (0xffffffff));

    // set up the standard set of colours..
    const int textButtonColour = 0xffb0b0b0;
    const int textHighlightColour = 0x401111ee;
    const int standardOutlineColour = 0x50808080;

	static const int32_t standardColours[] =
	{
		(int32_t)TextButton::buttonColourId,                 (int32_t)textButtonColour,
		(int32_t)TextButton::buttonOnColourId,               (int32_t)0xff4444ff,
		(int32_t)TextButton::textColourOnId,                 (int32_t)0xff000000,
		(int32_t)TextButton::textColourOffId,                (int32_t)0xff000000,

		(int32_t)ComboBox::buttonColourId,                   (int32_t)0xffb0b0b0,
		(int32_t)ComboBox::outlineColourId,                  (int32_t)standardOutlineColour,

		(int32_t)ToggleButton::textColourId,                 (int32_t)0xff000000,

		(int32_t)TextEditor::backgroundColourId,             (int32_t)0xffffffff,
		(int32_t)TextEditor::textColourId,                   (int32_t)0xff000000,
		(int32_t)TextEditor::highlightColourId,              (int32_t)textHighlightColour,
		(int32_t)TextEditor::highlightedTextColourId,        (int32_t)0xff000000,
		(int32_t)TextEditor::outlineColourId,                (int32_t)0x00000000,
		(int32_t)TextEditor::focusedOutlineColourId,         (int32_t)textButtonColour,
		(int32_t)TextEditor::shadowColourId,                 (int32_t)0x38000000,

		(int32_t)Label::backgroundColourId,                  (int32_t)0x00000000,
		(int32_t)Label::textColourId,                        (int32_t)0xff000000,
		(int32_t)Label::outlineColourId,                     (int32_t)0x00000000,

		(int32_t)ScrollBar::backgroundColourId,              (int32_t)0x00000000,
		(int32_t)ScrollBar::thumbColourId,                   (int32_t)0xffffffff,
		(int32_t)ScrollBar::trackColourId,                   (int32_t)0xffffffff,

		(int32_t)TreeView::linesColourId,                    (int32_t)0x4c000000,
		(int32_t)TreeView::backgroundColourId,               (int32_t)0x00000000,
		(int32_t)TreeView::dragAndDropIndicatorColourId,     (int32_t)0x80ff0000,

		(int32_t)PopupMenu::backgroundColourId,              (int32_t)0xffffffff,
		(int32_t)PopupMenu::textColourId,                    (int32_t)0xff000000,
		(int32_t)PopupMenu::headerTextColourId,              (int32_t)0xff000000,
		(int32_t)PopupMenu::highlightedTextColourId,         (int32_t)0xffffffff,
		(int32_t)PopupMenu::highlightedBackgroundColourId,   (int32_t)0x991111aa,

		(int32_t)ComboBox::textColourId,                     (int32_t)0xff000000,
		(int32_t)ComboBox::backgroundColourId,               (int32_t)0xffb0b0b0,
		(int32_t)ComboBox::arrowColourId,                    (int32_t)0x99000000,

		(int32_t)ListBox::backgroundColourId,                (int32_t)0xffffffff,
		(int32_t)ListBox::outlineColourId,                   (int32_t)standardOutlineColour,
		(int32_t)ListBox::textColourId,                      (int32_t)0xff000000,

		(int32_t)Slider::backgroundColourId,                 (int32_t)0x00000000,
		(int32_t)Slider::thumbColourId,                      (int32_t)textButtonColour,
		(int32_t)Slider::trackColourId,                      (int32_t)0x7fffffff,
		(int32_t)Slider::rotarySliderFillColourId,           (int32_t)0x7f0000ff,
		(int32_t)Slider::rotarySliderOutlineColourId,        (int32_t)0x66000000,
		(int32_t)Slider::textBoxTextColourId,                (int32_t)0xff000000,
		(int32_t)Slider::textBoxBackgroundColourId,          (int32_t)0xffffffff,
		(int32_t)Slider::textBoxHighlightColourId,           (int32_t)textHighlightColour,
		(int32_t)Slider::textBoxOutlineColourId,             (int32_t)standardOutlineColour,

		(int32_t)ResizableWindow::backgroundColourId,        (int32_t)0xff777777,
		//DocumentWindow::textColourId,               0xff000000, // (this is deliberately not set)

		(int32_t)AlertWindow::backgroundColourId,            (int32_t)0xffededed,
		(int32_t)AlertWindow::textColourId,                  (int32_t)0xff000000,
		(int32_t)AlertWindow::outlineColourId,               (int32_t)0xff666666,

		(int32_t)ProgressBar::backgroundColourId,            (int32_t)0xffeeeeee,
		(int32_t)ProgressBar::foregroundColourId,            (int32_t)0xffaaaaee,

		(int32_t)TooltipWindow::backgroundColourId,          (int32_t)0xffeeeebb,
		(int32_t)TooltipWindow::textColourId,                (int32_t)0xff000000,
		(int32_t)TooltipWindow::outlineColourId,             (int32_t)0x4c000000,

		(int32_t)TabbedComponent::backgroundColourId,        (int32_t)0x00000000,
		(int32_t)TabbedComponent::outlineColourId,           (int32_t)0xff777777,
		(int32_t)TabbedButtonBar::tabOutlineColourId,        (int32_t)0x80000000,
		(int32_t)TabbedButtonBar::frontOutlineColourId,      (int32_t)0x90000000,

		(int32_t)Toolbar::backgroundColourId,                (int32_t)0xfff6f8f9,
		(int32_t)Toolbar::separatorColourId,                 (int32_t)0x4c000000,
		(int32_t)Toolbar::buttonMouseOverBackgroundColourId, (int32_t)0x4c0000ff,
		(int32_t)Toolbar::buttonMouseDownBackgroundColourId, (int32_t)0x800000ff,
		(int32_t)Toolbar::labelTextColourId,                 (int32_t)0xff000000,
		(int32_t)Toolbar::editingModeOutlineColourId,        (int32_t)0xffff0000,

		(int32_t)HyperlinkButton::textColourId,              (int32_t)0xcc1111ee,

		(int32_t)GroupComponent::outlineColourId,            (int32_t)0x66000000,
		(int32_t)GroupComponent::textColourId,               (int32_t)0xff000000,

		(int32_t)DirectoryContentsDisplayComponent::highlightColourId,   (int32_t)textHighlightColour,
		(int32_t)DirectoryContentsDisplayComponent::textColourId,        (int32_t)0xff000000,

		(int32_t)0x1000440, /*LassoComponent::lassoFillColourId*/        (int32_t)0x66dddddd,
		(int32_t)0x1000441, /*LassoComponent::lassoOutlineColourId*/     (int32_t)0x99111111,

		(int32_t)MidiKeyboardComponent::whiteNoteColourId,               (int32_t)0xffffffff,
		(int32_t)MidiKeyboardComponent::blackNoteColourId,               (int32_t)0xff000000,
		(int32_t)MidiKeyboardComponent::keySeparatorLineColourId,        (int32_t)0x66000000,
		(int32_t)MidiKeyboardComponent::mouseOverKeyOverlayColourId,     (int32_t)0x80ffff00,
		(int32_t)MidiKeyboardComponent::keyDownOverlayColourId,          (int32_t)0xffb6b600,
		(int32_t)MidiKeyboardComponent::textLabelColourId,               (int32_t)0xff000000,
		(int32_t)MidiKeyboardComponent::upDownButtonBackgroundColourId,  (int32_t)0xffd3d3d3,
		(int32_t)MidiKeyboardComponent::upDownButtonArrowColourId,       (int32_t)0xff000000,

			(int32_t)CodeEditorComponent::backgroundColourId, (int32_t)0xffffffff,
			(int32_t)CodeEditorComponent::highlightColourId, (int32_t)textHighlightColour,
			(int32_t)CodeEditorComponent::defaultTextColourId, (int32_t)0xff000000,

			(int32_t)ColourSelector::backgroundColourId, (int32_t)0xffe5e5e5,
			(int32_t)ColourSelector::labelTextColourId, (int32_t)0xff000000,

			(int32_t)KeyMappingEditorComponent::backgroundColourId, (int32_t)0x00000000,
			(int32_t)KeyMappingEditorComponent::textColourId, (int32_t)0xff000000,

			(int32_t)FileSearchPathListComponent::backgroundColourId, (int32_t)0xffffffff,

			(int32_t)FileChooserDialogBox::titleTextColourId, (int32_t)0xff000000,
	};

    for (int i = 0; i < numElementsInArray (standardColours); i += 2)
        setColour (standardColours [i], Colour (standardColours [i + 1]));
}

int NonShinyLookAndFeel::getTooltipSize (const String& tipText, int& width, int& height)
{
    const TextLayout tl (LookAndFeelHelpers::layoutTooltipText (tipText, Colours::black));

    width = (int)tl.getWidth() + 18;
    height = (int)tl.getHeight() + 10;

	return 0;
}

void NonShinyLookAndFeel::drawTooltip (Graphics& g, const String& text, int width, int height)
{
    g.fillAll (findColour (TooltipWindow::backgroundColourId));

   #if ! JUCE_MAC // The mac windows already have a non-optional 1 pix outline, so don't double it here..
    g.setColour (findColour (TooltipWindow::outlineColourId));
    g.drawRect (0, 0, width, height, 1);
   #endif

    const TextLayout tl (LookAndFeelHelpers::layoutTooltipText (text, findColour (TooltipWindow::textColourId)));
    tl.draw (g, Rectangle<float> ((float) width, (float) height));
}


//==============================================================================
void NonShinyLookAndFeel::drawButtonBackground (Graphics& g,
                                        Button& button,
                                        const Colour& backgroundColour,
                                        bool isMouseOverButton,
                                        bool isButtonDown)
{
    const int width = button.getWidth();
    const int height = button.getHeight();

    const float outlineThickness = button.isEnabled() ? ((isButtonDown || isMouseOverButton) ? 1.2f : 0.7f) : 0.4f;
    const float halfThickness = outlineThickness * 0.5f;

    const float indentL = button.isConnectedOnLeft()   ? 0.1f : halfThickness;
    const float indentR = button.isConnectedOnRight()  ? 0.1f : halfThickness;
    const float indentT = button.isConnectedOnTop()    ? 0.1f : halfThickness;
	const float indentB = button.isConnectedOnBottom() ? (button.getToggleState() ? -1.f : 0.1f) : halfThickness;

    const Colour baseColour (createBaseColour (backgroundColour,
                                               button.hasKeyboardFocus (true),
                                               isMouseOverButton, isButtonDown)
                               .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    drawGlassLozenge (g,
                      indentL,
                      indentT,
                      width - indentL - indentR,
                      height - indentT - indentB,
                      baseColour, outlineThickness, -1.0f,
                      button.isConnectedOnLeft(),
                      button.isConnectedOnRight(),
                      button.isConnectedOnTop(),
                      button.isConnectedOnBottom());
}

void NonShinyLookAndFeel::drawTickBox (Graphics& g,
                               Component& component,
                               float x, float y, float w, float h,
                               const bool ticked,
                               const bool isEnabled,
                               const bool isMouseOverButton,
                               const bool isButtonDown)
{
    const float boxSize = w * 0.8f;

    drawGlassLozenge (g,x,y+(h-boxSize)*0.5f,boxSize,boxSize,
					  createBaseColour (component.findColour (TextButton::buttonColourId)
                                                 .withMultipliedAlpha (isEnabled ? 1.0f : 0.5f),
									    true,
                                        isMouseOverButton,
                                        isButtonDown),
					  isEnabled ? ((isButtonDown || isMouseOverButton) ? 1.2f : 0.7f) : 0.4f,
					  -1.0f,true,true,true,true);

    if (ticked)
    {
        Path tick;
        tick.startNewSubPath (2.0f, 3.0f);
        tick.lineTo (3.5f, 6.0f);
        tick.lineTo (6.5f, 0.0f);

        g.setColour (isEnabled ? Colours::black : Colours::grey);

        const AffineTransform trans (AffineTransform::scale (w / 9.0f, h / 9.0f)
                                         .translated (x, y));

        g.strokePath (tick, PathStrokeType (2.5f), trans);
    }
}

void NonShinyLookAndFeel::drawButtonText (Graphics& g, TextButton& button,
                                  bool /*isMouseOverButton*/, bool /*isButtonDown*/)
{
    Font font (getTextButtonFont(button, button.getHeight()));
	if (button.getToggleState())
		font.setBold(true);
	g.setFont (font);
    g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                                            : TextButton::textColourOffId)
                       .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
    const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;

    const int fontHeight = roundToInt (font.getHeight() * 0.6f);
    const int leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
    const int rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));

    g.drawFittedText (button.getButtonText(),
                      leftIndent,
                      yIndent,
                      button.getWidth() - leftIndent - rightIndent,
                      button.getHeight() - yIndent * 2,
                      Justification::centred, 2);
}

void NonShinyLookAndFeel::drawToggleButton (Graphics& g,
                                    ToggleButton& button,
                                    bool isMouseOverButton,
                                    bool isButtonDown)
{
    if (button.hasKeyboardFocus (true))
    {
        g.setColour (button.findColour (TextEditor::focusedOutlineColourId));
        g.drawRect (0, 0, button.getWidth(), button.getHeight());
    }

    float fontSize = jmin (15.0f, button.getHeight() * 0.75f);
    const float tickWidth = fontSize * 1.1f;

    drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                 tickWidth, tickWidth,
                 button.getToggleState(),
                 button.isEnabled(),
                 isMouseOverButton,
                 isButtonDown);

    g.setColour (button.findColour (ToggleButton::textColourId));
    g.setFont (fontSize);

    if (! button.isEnabled())
        g.setOpacity (0.5f);

    const int textX = (int) tickWidth + 5;

    g.drawFittedText (button.getButtonText(),
                      textX, 0,
                      button.getWidth() - textX - 2, button.getHeight(),
                      Justification::centredLeft, 10);
}

//==============================================================================
Font NonShinyLookAndFeel::getPopupMenuFont()
{
    return Font (13.0f);
}

void NonShinyLookAndFeel::drawPopupMenuBackground (Graphics& g, int width, int height)
{
    const Colour background (findColour (PopupMenu::backgroundColourId));

    g.fillAll (background);
    g.setColour (background.overlaidWith (Colour (0x2badd8e6)));

    for (int i = 0; i < height; i += 3)
        g.fillRect (0, i, width, 1);

#if ! JUCE_MAC
    g.setColour (findColour (PopupMenu::textColourId).withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
#endif
}

void NonShinyLookAndFeel::drawMenuBarBackground (Graphics& g, int width, int height,
                                         bool, MenuBarComponent& menuBar)
{
    const Colour baseColour (createBaseColour (menuBar.findColour (PopupMenu::backgroundColourId), false, false, false));

    if (menuBar.isEnabled())
    {
        drawShinyButtonShape (g,
                              -4.0f, 0.0f,
                              width + 8.0f, (float) height,
                              0.0f,
                              baseColour,
                              0.4f,
                              true, true, true, true);
    }
    else
    {
        g.fillAll (baseColour);
    }
}

void NonShinyLookAndFeel::drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& textEditor)
{
    if (textEditor.isEnabled())
    {
        if (textEditor.hasKeyboardFocus (true) && ! textEditor.isReadOnly())
        {
            const int border = 2;

            g.setColour (textEditor.findColour (TextEditor::focusedOutlineColourId));
            g.drawRect (0, 0, width, height, border);

            g.setOpacity (1.0f);
            const Colour shadowColour (textEditor.findColour (TextEditor::shadowColourId).withMultipliedAlpha (0.75f));
            drawBevel (g, 0, 0, width, height + 2, border + 2, shadowColour, shadowColour);
        }
        else
        {
            g.setColour (textEditor.findColour (TextEditor::outlineColourId));
            g.drawRect (0, 0, width, height);

            g.setOpacity (1.0f);
            const Colour shadowColour (textEditor.findColour (TextEditor::shadowColourId));
            drawBevel (g, 0, 0, width, height + 2, 3, shadowColour, shadowColour);
        }
    }
}

//==============================================================================
void NonShinyLookAndFeel::drawComboBox (Graphics& g, int width, int height,
                                const bool isButtonDown,
                                int buttonX, int buttonY,
                                int buttonW, int buttonH,
                                ComboBox& box)
{
    g.fillAll (box.findColour (ComboBox::backgroundColourId));

    if (box.isEnabled() && box.hasKeyboardFocus (false))
    {
        g.setColour (box.findColour (TextButton::buttonColourId));
        g.drawRect (0, 0, width, height, 2);
    }
    else
    {
        g.setColour (box.findColour (ComboBox::outlineColourId));
        g.drawRect (0, 0, width, height);
    }

    const float outlineThickness = box.isEnabled() ? (isButtonDown ? 1.2f : 0.7f) : 0.4f;

    const Colour baseColour (createBaseColour (box.findColour (ComboBox::buttonColourId),
                                               box.hasKeyboardFocus (true),
                                               false, isButtonDown)
                               .withMultipliedAlpha (box.isEnabled() ? 1.0f : 0.5f));

    drawGlassLozenge (g,
                      buttonX + outlineThickness, buttonY + outlineThickness,
                      buttonW - outlineThickness * 2.0f, buttonH - outlineThickness * 2.0f,
                      baseColour, outlineThickness, -1.0f,
                      true, true, true, true);

    if (box.isEnabled())
    {
        const float arrowX = 0.3f;
        const float arrowH = 0.2f;

        Path p;
        //p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.45f - arrowH),
        //               buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.45f,
        //               buttonX + buttonW * arrowX,          buttonY + buttonH * 0.45f);

        p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.55f + arrowH),
                       buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.55f,
                       buttonX + buttonW * arrowX,          buttonY + buttonH * 0.55f);

        g.setColour (box.findColour (ComboBox::arrowColourId));
        g.fillPath (p);
    }
}

Font NonShinyLookAndFeel::getComboBoxFont (ComboBox& box)
{
    return Font (jmin (15.0f, box.getHeight() * 0.85f));
}

void NonShinyLookAndFeel::drawLinearSlider (Graphics& g,
                                    int x, int y,
                                    int width, int height,
                                    float sliderPos,
                                    float minSliderPos,
                                    float maxSliderPos,
                                    const Slider::SliderStyle style,
                                    Slider& slider)
{
    g.fillAll (slider.findColour (Slider::backgroundColourId));

    if (style == Slider::LinearBar)
    {
        const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

        Colour baseColour (createBaseColour (slider.findColour (Slider::thumbColourId)
                                                   .withMultipliedSaturation (slider.isEnabled() ? 1.0f : 0.5f),
                                             false,
                                             isMouseOver,
                                             isMouseOver || slider.isMouseButtonDown()));

        drawShinyButtonShape (g,
                              (float) x, (float) y, sliderPos - (float) x, (float) height, 0.0f,
                              baseColour,
                              slider.isEnabled() ? 0.9f : 0.3f,
                              true, true, true, true);
    }
    else
    {
        drawLinearSliderBackground (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
        drawLinearSliderThumb (g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
    }
}

Button* NonShinyLookAndFeel::createSliderButton (Slider &,const bool isIncrement)
{
    return new TextButton (isIncrement ? "+" : "-", String());
}

class SliderLabelComp : public Label
{
public:
	SliderLabelComp() : Label (String(), String()) {}
	~SliderLabelComp()	{}

	virtual int mouseWheelMove (const MouseEvent&, float, float) { return 0; }
};

Label* NonShinyLookAndFeel::createSliderTextBox (Slider& slider)
{
	return LookAndFeel_V4::createSliderTextBox(slider);
}

//==============================================================================
void NonShinyLookAndFeel::drawCornerResizer (Graphics& g,
                                     int w, int h,
                                     bool /*isMouseOver*/,
                                     bool /*isMouseDragging*/)
{
    const float lineThickness = jmin (w, h) * 0.075f;

    for (float i = 0.0f; i < 1.0f; i += 0.3f)
    {
        g.setColour (Colours::lightgrey);

        g.drawLine (w * i,
                    h + 1.0f,
                    w + 1.0f,
                    h * i,
                    lineThickness);

        g.setColour (Colours::darkgrey);

        g.drawLine (w * i + lineThickness,
                    h + 1.0f,
                    w + 1.0f,
                    h * i + lineThickness,
                    lineThickness);
    }
}

//==============================================================================
static void createRoundedPath (Path& p,
                               const float x, const float y,
                               const float w, const float h,
                               const float cs,
                               const bool curveTopLeft, const bool curveTopRight,
                               const bool curveBottomLeft, const bool curveBottomRight) throw()
{
    const float cs2 = 2.0f * cs;

    if (curveTopLeft)
    {
        p.startNewSubPath (x, y + cs);
        p.addArc (x, y, cs2, cs2, float_Pi * 1.5f, float_Pi * 2.0f);
    }
    else
    {
        p.startNewSubPath (x, y);
    }

    if (curveTopRight)
    {
        p.lineTo (x + w - cs, y);
        p.addArc (x + w - cs2, y, cs2, cs2, 0.0f, float_Pi * 0.5f);
    }
    else
    {
        p.lineTo (x + w, y);
    }

    if (curveBottomRight)
    {
        p.lineTo (x + w, y + h - cs);
        p.addArc (x + w - cs2, y + h - cs2, cs2, cs2, float_Pi * 0.5f, float_Pi);
    }
    else
    {
        p.lineTo (x + w, y + h);
    }

    if (curveBottomLeft)
    {
        p.lineTo (x + cs, y + h);
        p.addArc (x, y + h - cs2, cs2, cs2, float_Pi, float_Pi * 1.5f);
    }
    else
    {
        p.lineTo (x, y + h);
    }

    p.closeSubPath();
}

//==============================================================================
void NonShinyLookAndFeel::drawShinyButtonShape (Graphics& g,
                                        float x, float y, float w, float h,
                                        float maxCornerSize,
                                        const Colour& baseColour,
                                        const float strokeWidth,
                                        const bool flatOnLeft,
                                        const bool flatOnRight,
                                        const bool flatOnTop,
                                        const bool flatOnBottom) throw()
{
    if (w <= strokeWidth * 1.1f || h <= strokeWidth * 1.1f)
        return;

    const float cs = jmin (maxCornerSize, w * 0.5f, h * 0.5f);

    Path outline;
    createRoundedPath (outline, x, y, w, h, cs,
                        ! (flatOnLeft || flatOnTop),
                        ! (flatOnRight || flatOnTop),
                        ! (flatOnLeft || flatOnBottom),
                        ! (flatOnRight || flatOnBottom));

    ColourGradient cg (baseColour, 0.0f, y,
                       baseColour.overlaidWith (Colour (0x070000ff)), 0.0f, y + h,
                       false);

    cg.addColour (0.5, baseColour.overlaidWith (Colour (0x25ffffff)));
    cg.addColour (0.51, baseColour.overlaidWith (Colour (0x110000ff)));

    //g.setGradientFill (cg);
	g.setColour(baseColour);
    g.fillPath (outline);

    g.setColour (Colour (0x80000000));
    g.strokePath (outline, PathStrokeType (strokeWidth));
}

//==============================================================================
void NonShinyLookAndFeel::drawGlassSphere (Graphics& g,
                                   const float x, const float y,
                                   const float diameter,
                                   const Colour& colour,
                                   const float outlineThickness) throw()
{
    if (diameter <= outlineThickness)
        return;

    Path p;
    p.addEllipse (x, y, diameter, diameter);

    {
        ColourGradient cg (Colours::white.overlaidWith (colour.withMultipliedAlpha (0.3f)), 0, y,
                           Colours::white.overlaidWith (colour.withMultipliedAlpha (0.3f)), 0, y + diameter, false);

        cg.addColour (0.4, Colours::white.overlaidWith (colour));

        g.setGradientFill (cg);
        g.fillPath (p);
    }

    g.setGradientFill (ColourGradient (Colours::white, 0, y + diameter * 0.06f,
                                       Colours::transparentWhite, 0, y + diameter * 0.3f, false));
    //g.fillEllipse (x + diameter * 0.2f, y + diameter * 0.05f, diameter * 0.6f, diameter * 0.4f);

    ColourGradient cg (Colours::transparentBlack,
                       x + diameter * 0.5f, y + diameter * 0.5f,
                       Colours::black.withAlpha (0.5f * outlineThickness * colour.getFloatAlpha()),
                       x, y + diameter * 0.5f, true);

    cg.addColour (0.7, Colours::transparentBlack);
    cg.addColour (0.8, Colours::black.withAlpha (0.1f * outlineThickness));

    g.setGradientFill (cg);
    g.fillPath (p);

    g.setColour (colour.darker(10.f).withAlpha (0.5f * colour.getFloatAlpha()));
    g.drawEllipse (x, y, diameter, diameter, outlineThickness);
}

//==============================================================================
void NonShinyLookAndFeel::drawGlassPointer (Graphics& g,
                                    const float x, const float y,
                                    const float diameter,
                                    const Colour& colour, const float outlineThickness,
                                    const int direction) throw()
{
    if (diameter <= outlineThickness)
        return;

    Path p;
    p.startNewSubPath (x + diameter * 0.5f, y);
    p.lineTo (x + diameter, y + diameter * 0.6f);
    p.lineTo (x + diameter, y + diameter);
    p.lineTo (x, y + diameter);
    p.lineTo (x, y + diameter * 0.6f);
    p.closeSubPath();

    p.applyTransform (AffineTransform::rotation (direction * (float_Pi * 0.5f), x + diameter * 0.5f, y + diameter * 0.5f));

    {
        ColourGradient cg (Colours::white.overlaidWith (colour.withMultipliedAlpha (0.3f)), 0, y,
                           Colours::white.overlaidWith (colour.withMultipliedAlpha (0.3f)), 0, y + diameter, false);

        cg.addColour (0.4, Colours::white.overlaidWith (colour));

        g.setGradientFill (cg);
        g.fillPath (p);
    }

    ColourGradient cg (Colours::transparentBlack,
                       x + diameter * 0.5f, y + diameter * 0.5f,
                       Colours::black.withAlpha (0.5f * outlineThickness * colour.getFloatAlpha()),
                       x - diameter * 0.2f, y + diameter * 0.5f, true);

    cg.addColour (0.5, Colours::transparentBlack);
    cg.addColour (0.7, Colours::black.withAlpha (0.07f * outlineThickness));

    g.setGradientFill (cg);
    g.fillPath (p);

    g.setColour (Colours::black.withAlpha (0.5f * colour.getFloatAlpha()));
    g.strokePath (p, PathStrokeType (outlineThickness));
}

//==============================================================================
void NonShinyLookAndFeel::drawGlassLozenge (Graphics& g,
                                    const float x, const float y,
                                    const float width, const float height,
                                    const Colour& colour,
                                    const float outlineThickness,
                                    const float cornerSize,
                                    const bool flatOnLeft,
                                    const bool flatOnRight,
                                    const bool flatOnTop,
                                    const bool flatOnBottom) throw()
{
    if (width <= outlineThickness || height <= outlineThickness)
        return;

    const int intX = (int) x;
    const int intY = (int) y;
    const int intW = (int) width;
    const int intH = (int) height;

    const float cs = cornerSize < 0 ? jmin (width * 0.5f, height * 0.5f) : cornerSize;
    const float edgeBlurRadius = height * 0.75f + (height - cs * 2.0f);
    const int intEdge = (int) edgeBlurRadius;

    Path outline;
    createRoundedPath (outline, x, y, width, height, cs,
                        ! (flatOnLeft || flatOnTop),
                        ! (flatOnRight || flatOnTop),
                        ! (flatOnLeft || flatOnBottom),
                        ! (flatOnRight || flatOnBottom));

    {
        ColourGradient cg (colour.darker (0.1f), 0, y,
                           colour.darker (0.1f), 0, y + height, false);

        cg.addColour (0.03, colour.withMultipliedAlpha (0.3f));
        cg.addColour (0.4, colour);
        cg.addColour (0.97, colour.withMultipliedAlpha (0.3f));

        //g.setGradientFill (cg);
		g.setColour(colour);
        g.fillPath (outline);
    }

    //ColourGradient cg (Colours::transparentBlack, x + edgeBlurRadius, y + height * 0.5f,
    //                   colour.darker (0.1f), x, y + height * 0.5f, true);

    //cg.addColour (jlimit (0.0, 1.0, 1.0 - (cs * 0.5f) / edgeBlurRadius), Colours::transparentBlack);
    //cg.addColour (jlimit (0.0, 1.0, 1.0 - (cs * 0.25f) / edgeBlurRadius), colour.darker (0.2f).withMultipliedAlpha (0.3f));

    if (! (flatOnLeft || flatOnTop || flatOnBottom))
    {
        g.saveState();
//        g.setGradientFill (cg);
		g.setColour(colour);
        g.reduceClipRegion (intX, intY, intEdge, intH);
        g.fillPath (outline);
        g.restoreState();
    }

    if (! (flatOnRight || flatOnTop || flatOnBottom))
    {
        //cg.point1.setX (x + width - edgeBlurRadius);
        //cg.point2.setX (x + width);

        g.saveState();
        //g.setGradientFill (cg);
		g.setColour(colour);
        g.reduceClipRegion (intX + intW - intEdge, intY, 2 + intEdge, intH);
        g.fillPath (outline);
        g.restoreState();
    }

    //{
    //    const float leftIndent = flatOnLeft ? 0.0f : cs * 0.4f;
    //    const float rightIndent = flatOnRight ? 0.0f : cs * 0.4f;

    //    Path highlight;
    //    createRoundedPath (highlight,
    //                       x + leftIndent,
    //                       y + cs * 0.1f,
    //                       width - (leftIndent + rightIndent),
    //                       height * 0.4f, cs * 0.4f,
    //                       ! (flatOnLeft || flatOnTop),
    //                       ! (flatOnRight || flatOnTop),
    //                       ! (flatOnLeft || flatOnBottom),
    //                       ! (flatOnRight || flatOnBottom));

    //    g.setGradientFill (ColourGradient (colour.brighter (10.0f), 0, y + height * 0.06f,
    //                                       Colours::transparentWhite, 0, y + height * 0.4f, false));
    //    g.fillPath (highlight);
    //}

	g.setColour (colour.darker(10.f).withMultipliedAlpha (1.5f));
    g.strokePath (outline, PathStrokeType (outlineThickness));
}

