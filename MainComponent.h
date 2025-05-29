#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include "StyleSheet.h"
#include <BinaryData.h>

class MainComponent final : public juce::Component
{
public:
    MainComponent();

    void paint(juce::Graphics&) override;

private:
#if JUCE_DEBUG
    const StyleSheet styleSheet { juce::File(__FILE__).getSiblingFile("StyleSheet.xml"), std::bind(&MainComponent::reload, this) };
#else
    const StyleSheet styleSheet{BinaryData::StyleSheet_xml};
#endif

    juce::TextButton button;

    void reload();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
