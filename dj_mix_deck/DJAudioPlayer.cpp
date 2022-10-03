/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 8 Mar 2021 7:45:46pm
    Author:  Brandon Godbold

  ==============================================================================
*/

#include "DJAudioPlayer.h"
// Constructor
DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
: formatManager(_formatManager)
{
    
}
DJAudioPlayer::~DJAudioPlayer() // Destructor
{
    
}

// ===== Basic Audio LifeCycle funtions ====////
    // Birth of Audio
void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
    // Life of Audio
void DJAudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);
}
    // Death of the Audio file
void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

//==== Functions we made to control audio data==///
void DJAudioPlayer::loadURL(URL audioURL) // load the music file
{
    /* Taking the audio url and converts into input stream and passes it to AudioFormat Manager, then creates a reader*/
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file, can be read!
    {
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource (reader,
true)); // creates audio format reader source, a local variabe
        transportSource.setSource (newSource.get(), 0, nullptr, reader->sampleRate); // above passed here
        readerSource.reset (newSource.release());
    }
}

void DJAudioPlayer::setGain(double gain)  // set the volume
{
    // Makes the volume slider robust, not allowing crazy numbers that might crash the program
    if (gain < 0 || gain > 1.0)
    {
        std::cout << " DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else{
        transportSource.setGain(gain);
    }
   
}

void DJAudioPlayer::setSpeed(double ratio) // set the speed of the playback
{
    // Makes the speed slider robust, not allowing crazy numbers that might crash the program
    if (ratio < 0 || ratio > 1.10)
    {
        std::cout << " DJAudioPlayer::setSpeed ratio should be between 0 and 1.10" << std::endl;
    }
    else{
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs) // set the position of the music
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
    // Makes the speed slider robust, not allowing crazy numbers that might crash the program
    if (pos < 0 || pos > 1.0)
    {
        std::cout << " DJAudioPlayer::setPositionRelative position should be between 0 and 1" << std::endl;
    }
    else{
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start() // play
{
    transportSource.start(); // Starts playing
}

void DJAudioPlayer::stop() // stop
{
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

void DJAudioPlayer::skipPosByTen() // set the position of the music
{
    double skipCurrentPos = transportSource.getCurrentPosition() + 10;
    transportSource.setPosition(skipCurrentPos);
}

void DJAudioPlayer::rewPosByTen()
{
    double rewindCurrentPos = transportSource.getCurrentPosition() - 10;
    transportSource.setPosition(rewindCurrentPos);
}

