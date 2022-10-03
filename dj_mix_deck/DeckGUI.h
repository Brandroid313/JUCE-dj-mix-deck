/*
  ==============================================================================

    DeckGUI.h
    Created: 9 Mar 2021 1:16:38pm
    Author:  Brandon Godbold

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
// Inherits from the three classes below
class DeckGUI  : public juce::Component,
                 public Button::Listener,
                 public Slider::Listener,
                 public FileDragAndDropTarget,
                 public Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            AudioFormatManager & formatManagerToUse,
            AudioThumbnailCache & cacheToUse); // Consturcter received a pointer to DJAudioPlayer player ( player defined below in private )
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    //====== Listeners for buttons and sliders================
    void buttonClicked (Button *) override;
    void sliderValueChanged (Slider *slider) override;
    
    //===== Listeners for dragging and dropping files======
        //Returns true or false if file drag in area detected
    bool isInterestedInFileDrag (const StringArray &files) override;
        // Callback; indicates if files have been dropped
    void filesDropped (const StringArray &files, int x, int y) override;
    
    void timerCallback() override;
    
    //Loads the URL Waveform from the playlist component drag and drop; final call is in Playlist.cpp line 149
    void loadWaveFormFromList(URL audioURL);

private:
    
    //=====Audio Control Buttons =========
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    TextButton skipPosByTen{"FastFoward"}; // Fastfowards 10 seconds
    TextButton rewPosByTen{"Rewind"}; // Rewinds 10 seconds
  
    //====Sliders======
    Slider volSlider; // Volume
    Slider speedSlider; // Track playback speed
    Slider posSlider; // Track position
    
    //==== Labels for Sliders===
    Label volumeLabel;
    Label speedLabel;
    Label positionLabel;
    
    //====Instance of DJAudioPlayer class; from pointer *====
    DJAudioPlayer* player;
    
    //===Instance of WaveformDisplay====
    WaveformDisplay waveformDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)

};
