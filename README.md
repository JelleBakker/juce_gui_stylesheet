# juce_gui_stylesheet

This project demonstrates how to use an XML file as a hot-reloadable stylesheet for a JUCE GUI, enabling faster iteration during development without recompilation.

## Motivation
Developing a GUI with JUCE can be slow due to long compilation times, especially when making frequent visual tweaks. This project shows how to use an XML-based stylesheet to define visual properties like colours, fonts or dimensions. The concept is straightforward, you define properties in the stylesheet and use them as follows:

```
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (styleSheet.getProperties().backgroundColour);
}
```

Then, during runtime, when editing the XML file, the GUI automatically reloads. This hot-reloading feature is intended for development. In release builds, the XML is embedded as binary data.

## Build Instructions

Run the following commands

```
cd /path/to/juce_gui_stylesheet
cmake . -B build
cmake --build build
```
