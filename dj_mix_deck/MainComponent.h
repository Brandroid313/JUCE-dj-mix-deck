/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==================Audio Source Implementation=================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //=========================Component Implementaion================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; // Holds up to 100 waveforms 

    //=== DeckGUI with address tp players passed to them======
    DJAudioPlayer player1{formatManager};
    DeckGUI deckGUI1{&player1, formatManager, thumbCache};
    
    DJAudioPlayer player2{formatManager};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache};
    
    MixerAudioSource mixerSource; // allows more than one track to be played at a time
    
    //==== One Playlist per Deck========
    PlaylistComponent playlistComponent1{&player1, &deckGUI1, formatManager, thumbCache};
    PlaylistComponent playlistComponent2{&player2, &deckGUI2, formatManager, thumbCache};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
