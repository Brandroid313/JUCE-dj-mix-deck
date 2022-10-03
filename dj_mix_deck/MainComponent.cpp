/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() // Constructor
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }  
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    
    // Make the decks visable
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    
    addAndMakeVisible(playlistComponent1);
    addAndMakeVisible(playlistComponent2);
    
    formatManager.registerBasicFormats();
    
}


MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//=====================Main Life Cycle of Audio==============
    // First Step in life cycle; Prepare the files
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // Sets up the files for the two players
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    // Allows multiple files to be played at once
    // Works without for some reason....
   // mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    // takes address of player; bool is for if i want it to delete the source when finished;
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
}

    // Second Step; pass this to the Dj component to deal with
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Gets the buffer blocks to fill
    mixerSource.getNextAudioBlock(bufferToFill);
}

    // Final Step; Free up memory and resources
void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    
    // Release rousrces for players and mixer
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}
//==============End of Audio Life Cycle====================


void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    deckGUI1.setBounds(0, 0, getWidth() / 2, getHeight() / 2);
    deckGUI2.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 2);
    
    playlistComponent1.setBounds(0, getHeight() / 2, getWidth() / 2, getHeight() / 2);
    
    playlistComponent2.setBounds(getWidth() / 2, getHeight() / 2, getWidth() / 2, getHeight() / 2);
}
