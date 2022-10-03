/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 8 Mar 2021 7:45:46pm
    Author:  Brandon Godbold

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h" // remember to include the juce headers


class DJAudioPlayer : public AudioSource // inherits from audioSource
{
    public:
    
        DJAudioPlayer(AudioFormatManager& _formatManager); // Constructor
        ~DJAudioPlayer(); // Destructor
        
        // ===== Basic Audio LifeCycle ====////
        void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;
        
        //==== Functions we made to handle audio data==///
        void loadURL(URL audioURL); // load the music file
        void setGain(double gain); // set the volume
        void setSpeed(double ratio); // set the speed of the playback
        void setPosition(double posInSecs); // set the position of the music
        void setPositionRelative(double pos); // Set the relative position to the slider;
        void skipPosByTen(); // Skip ahead 10 seconds
        void rewPosByTen(); // Rewind 10 seconds
        
        void start(); // play
        void stop(); // stop
    
        //==get the relative of the play head===
        double getPositionRelative();
    
    
    private:
    
        /* First layer */ /* Must instancete on the fly becuase it id going to read a file and we don't know which file will be read; so we must use a pointer or a smart pointer */
        AudioFormatManager& formatManager; // Handles the format, used on loadURL
        std::unique_ptr<AudioFormatReaderSource> readerSource; // audio format reader source needs to be a unique pointer used on loadURL, the file we are loading
        AudioTransportSource transportSource; //used on loadURL
        ResamplingAudioSource resampleSource{&transportSource, false, 2}; // source of audio, bool and number of channels
    
    
};
