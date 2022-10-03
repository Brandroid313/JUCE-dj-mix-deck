/*
  ==============================================================================

    DeckGUI.cpp
    Created: 9 Mar 2021 1:16:38pm
    Author:  Brandon Godbold

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
// Constructor takes player as an input, and usues assignment syntax to achive this; _player is the variable; then assigned to player object; also takes audioformat manager for waveform use; uses initialzation list to use private waveform display after player
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager & formatManagerToUse,
                 AudioThumbnailCache & cacheToUse
                 ) : player(_player),
                     waveformDisplay(formatManagerToUse,  cacheToUse)
{
    
    //===PlayButton=========
    addAndMakeVisible(playButton);
    playButton.addListener(this);
    playButton.setColour (juce::TextButton::buttonColourId, juce::Colours::seagreen);
    
    //=====Stop Buttons====
    addAndMakeVisible(stopButton);
    stopButton.addListener(this);
    stopButton.setColour (juce::TextButton::buttonColourId, juce::Colours::red);
    
    //=====Load Buttons======
    addAndMakeVisible(loadButton);
    loadButton.addListener(this);
    loadButton.setColour (juce::TextButton::buttonColourId, juce::Colours::black);
    
    //=====FastForward Button======
    addAndMakeVisible(skipPosByTen);
    skipPosByTen.addListener(this);
    skipPosByTen.setColour (juce::TextButton::buttonColourId, juce::Colours::darkblue);
    
    
    //=====Rewind Button=====
    addAndMakeVisible(rewPosByTen);
    rewPosByTen.addListener(this);
    rewPosByTen.setColour (juce::TextButton::buttonColourId, juce::Colours::darkblue);
    
    //====VolumeSlider=====
    addAndMakeVisible(volSlider);
    volSlider.addListener(this);
    volSlider.setRange(0.0, 1.0); // Sets the min and max values for volume slider
    addAndMakeVisible(volumeLabel);
    volSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.attachToComponent(&volSlider, true);
    
    //======Speed Slider======
    addAndMakeVisible(speedSlider);
    speedSlider.addListener(this);
    speedSlider.setRange(0.1, 2.00); // Don't let the speed go above twice the natural Speed
    addAndMakeVisible(speedLabel);
    speedSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    speedLabel.setText("Speed", juce::dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, true);
    
    //=====posSlider=====
    addAndMakeVisible(posSlider);
    posSlider.addListener(this);
    posSlider.setRange(0.0, 1.0); // Sets the range for position; will be multiplied by length of track to get a relative spot
    posSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(positionLabel);
    positionLabel.setText("Position", juce::dontSendNotification);
    positionLabel.attachToComponent(&posSlider, true);
    
    
    
    
    //====Make waveformDisplay visible====
    addAndMakeVisible(waveformDisplay);
    
    
    //====Set a timer to update peridocllay; used for drawing waveforms=====
    startTimer(500); // Takes an argument in miliseconds
    
}

DeckGUI::~DeckGUI() //Destructor 
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::cyan);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (30.0f);
    
    g.drawText("Mix Deck", getWidth() * 0.3, 10, 150, 100, juce::Justification::centred, true);
}

//====Sets the size and location of buttons and sliders====
void DeckGUI::resized()
{
    // Number of rows
    double rowH = getHeight() / 9;
    double columnW = getWidth() / 4;
    //===Position of buttons, sliders and waveform displays====
    
        //Top - Play and Stop Buttons
    playButton.setBounds(0, 1, getWidth() / 4, rowH);
    stopButton.setBounds(0, rowH * 1.5, getWidth() / 4, rowH);
    skipPosByTen.setBounds(columnW * 3 , 1, getWidth() / 4, rowH);
    rewPosByTen.setBounds(columnW * 3, rowH * 1.5, getWidth() / 4, rowH);
    
        // Middle Volume, speed and position sliders
    volSlider.setBounds(getWidth() * 0.15, rowH * 5, getWidth() * 0.85 , rowH);
    speedSlider.setBounds(getWidth() * 0.15, rowH * 6, getWidth() * 0.85, rowH);
    posSlider.setBounds(getWidth() * 0.15, rowH * 7, getWidth() * 0.85, rowH);
    
        // Bottom waveformDisplay and load Button
    waveformDisplay.setBounds(0, rowH * 2.5, getWidth(), rowH * 2);
    loadButton.setBounds(0, rowH * 8, getWidth(), rowH);
}
//=====Button Listener Logic=====
void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        player->start(); // Starts playing; pointer to player
    }

     if (button == &stopButton)
    {
        player->stop(); // Stops playing; pointer to player
    }

    if (button == &loadButton) // Use FileChooser to open a file
    {
        FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen()) // if they select a file return true, if they select cancel return false
        {
            player->loadURL(URL{chooser.getResult()}); // Load the selected file; from pointer
            
            waveformDisplay.loadURL(URL{chooser.getResult()}); // load the waveform display data; not a pointer
        }
    }
    
    if (button == &skipPosByTen)
    {
        player->skipPosByTen(); // Skips ahead 10 seconds; implemented in DJAudioPlayer
    }
    
    if (button == &rewPosByTen)
    {
        player->rewPosByTen(); // Rewinds back 10 seconds; implemented in DJAudioPlayer
    }
}
//=== Slider Listener Logic =======
void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue()); // Change volume; pointer to player
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue()); // Change speed of track; pointer to player
    }

    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue()); // Change position of track; pointer to player
    }

}

//Returns true or false if file drag in area detected
bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
//    std::cout << " DeckGUI::isInterestedInFileDrag " << std::endl;
    return true;
}

// Callback; indicates if files have been dropped
void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
//    std::cout << " DeckGUI::filesDropped " << std::endl;
    if (files.size() == 1)
    {
        player->loadURL(URL{File{files[0]}});
        waveformDisplay.loadURL(URL{File{files[0]}}); // load the waveform display data; not a pointer
    }
}

//Callback to timer to wet the waveform position
void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}

void DeckGUI::loadWaveFormFromList(URL audioURL)
{    
    waveformDisplay.loadURL(audioURL);
}

