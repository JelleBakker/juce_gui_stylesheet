#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "platform/choc_FileWatcher.h"

class StyleSheet
{
public:
    StyleSheet(const juce::File& xmlFile, std::function<void()> onReload) : properties(
        std::make_unique<Properties>(xmlFile))
    {
        fileWatcher = std::make_unique<choc::file::Watcher>(xmlFile.getFullPathName().toStdString(),
                                                            [&, xmlFile, onReload](const auto&)
                                                            {
                                                                const juce::WeakReference<StyleSheet> safeOwner(this);

                                                                juce::MessageManager::callAsync(
                                                                    [&, xmlFile, onReload, safeOwner]
                                                                    {
                                                                        if (safeOwner)
                                                                        {
                                                                            properties = std::make_unique<Properties>(
                                                                                xmlFile);
                                                                            juce::NullCheckedInvocation::invoke(
                                                                                onReload);
                                                                        }
                                                                    });
                                                            });
    }

    explicit StyleSheet(const juce::String& xmlText) : properties(std::make_unique<Properties>(xmlText))
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

        const juce::CachedValue<int> uiWidth{tree, "uiWidth", {}};
        const juce::CachedValue<int> uiHeight{tree, "uiHeight", {}};
        const juce::CachedValue<juce::Colour> backgroundColour{tree, "backgroundColour", {}};
        const juce::CachedValue<juce::String> buttonText{tree, "buttonText", {}};
        const juce::CachedValue<int> buttonWidth{tree, "buttonWidth", {}};
        const juce::CachedValue<int> buttonHeight{tree, "buttonHeight", {}};
    };

    const Properties& getProperties() const
    {
        return *properties;
    }

private:
    std::unique_ptr<Properties> properties;
    std::unique_ptr<const choc::file::Watcher> fileWatcher;

    JUCE_DECLARE_WEAK_REFERENCEABLE(StyleSheet)
};

namespace juce
{
    template <>
    struct VariantConverter<Colour>
    {
        static Colour fromVar(const var& var)
        {
            return Colour::fromString(var.toString());
        }

        static var toVar(Colour colour)
        {
            return colour.toString();
        }
    };
}
