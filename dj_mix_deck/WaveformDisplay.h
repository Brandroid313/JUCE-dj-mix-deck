/*
  ==============================================================================

    WaveformDisplay.h
    Created: 9 Mar 2021 5:42:34pm
    Author:  Brandon Godbold

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager & formatManagerToUse,
                    AudioThumbnailCache & cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallback (ChangeBroadcaster *source) override;
    
    void loadURL(URL audioURL);
    /** set the relative position of the playhead */
    void setPositionRelative(double pos);

private:
    AudioThumbnail audioThumb; // Instance of audio thumbnail
    bool fileLoaded; // true or false if the file is loaded
    double position; //stores the position locally for the waveform needle
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
