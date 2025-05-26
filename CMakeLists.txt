cmake_minimum_required(VERSION 3.22)

project(JUCE_GUI_STYLESHEET VERSION 0.0.1)

include(FetchContent)

FetchContent_Declare(
        JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 8.0.7
)
FetchContent_MakeAvailable(JUCE)

FetchContent_Declare(
        choc
        GIT_REPOSITORY https://github.com/Tracktion/choc
        GIT_TAG aa027d0
)
FetchContent_MakeAvailable(choc)

juce_add_gui_app(JUCE_GUI_STYLESHEET)

target_sources(JUCE_GUI_STYLESHEET
        PRIVATE
        Main.cpp
        MainComponent.cpp)

target_compile_definitions(JUCE_GUI_STYLESHEET
        PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:JUCE_GUI_STYLESHEET,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:JUCE_GUI_STYLESHEET,JUCE_VERSION>")

juce_add_binary_data(BinaryData SOURCES StyleSheet.xml)

target_link_libraries(JUCE_GUI_STYLESHEET
        PRIVATE
        BinaryData
        juce::juce_gui_extra
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

target_include_directories(JUCE_GUI_STYLESHEET
        PRIVATE
        ${choc_SOURCE_DIR})
