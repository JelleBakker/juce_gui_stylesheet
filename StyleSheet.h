#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "platform/choc_FileWatcher.h"

class StyleSheet
{
public:
    StyleSheet(const juce::File& xmlFile, std::function<void()> onReload) : properties(xmlFile)
    {
        fileWatcher = std::make_unique<choc::file::Watcher>(xmlFile.getFullPathName().toStdString(),
                                                            [&, xmlFile, onReload](const auto&)
                                                            {
                                                                const juce::WeakReference<StyleSheet> safeOwner (this);

                                                                juce::MessageManager::callAsync(
                                                                    [&, xmlFile, onReload, safeOwner]
                                                                    {
                                                                        if (safeOwner)
                                                                        {
                                                                            properties = Properties{xmlFile};
                                                                            juce::NullCheckedInvocation::invoke(
                                                                                onReload);
                                                                        }
                                                                    });
                                                            });
    }

    explicit StyleSheet(const juce::String& xmlText) : properties(xmlText)
    {
    }

    struct Properties
    {
        explicit Properties(const juce::File& xmlFile) : tree(juce::ValueTree::fromXml(xmlFile.loadFileAsString()))
        {
        }

        explicit Properties(const juce::String& xmlText) : tree(juce::ValueTree::fromXml(xmlText))
        {
        }

        juce::ValueTree tree;

        int uiWidth = tree["uiWidth"];
        int uiHeight = tree["uiHeight"];
        juce::Colour backgroundColour = juce::Colour::fromString(tree["backgroundColour"].toString());
        juce::String buttonText = tree["buttonText"];
        int buttonWidth = tree["buttonWidth"];
        int buttonHeight = tree["buttonHeight"];
    };

    const Properties& getProperties() const
    {
        return properties;
    }

private:
    Properties properties;
    std::unique_ptr<const choc::file::Watcher> fileWatcher;

    JUCE_DECLARE_WEAK_REFERENCEABLE(StyleSheet)
};
