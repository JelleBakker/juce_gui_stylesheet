#include "MainComponent.h"

MainComponent::MainComponent ()
{
    addAndMakeVisible (button);

    reload();
}

void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (styleSheet.getProperties().backgroundColour);
}

void MainComponent::reload ()
{
    const auto& props = styleSheet.getProperties();

    button.setButtonText (props.buttonText);
    button.setSize (props.buttonWidth, props.buttonHeight);

    repaint();
    setSize (props.uiWidth, props.uiHeight);
}