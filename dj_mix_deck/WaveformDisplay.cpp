/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 9 Mar 2021 5:42:34pm
    Author:  Brandon Godbold

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & formatManagerToUse,
                                 AudioThumbnailCache & cacheToUse) : audioThumb(1000,     formatManagerToUse, cacheToUse),
                                 fileLoaded(false),
                                 position(0)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    audioThumb.addChangeListener(this);

}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.
     
        Grahpics& g is akin to Canvas in p5.js; an area to draw to the screen

       You should replace everything in this method with your own
       drawing code..
    */

    
    g.fillAll (juce::Colours::black); // Set background to black

    g.setColour (juce::Colours::cyan); //set surrounding color of rect
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::lawngreen);
    
    // If the file is loaded draw the thmbnail
    if(fileLoaded)
    {
        audioThumb.drawChannel(g, // The canvas we are drawing to
                               getLocalBounds(), // allows to draw on the whole of g
                               0, // start time we want to start drawing from
                               audioThumb.getTotalLength(), //length of the file in seconds
                               0, // the channel
                               1.0f // zoom, can boost up size of the wave form
        );
        
        g.setColour(Colours::lightgreen);
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else // Else display, file not loaded
    {
        g.setFont (20.0f);
        g.drawText ("File not loaded...", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }
    
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(URL audioURL)
{
    
    
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
    if(fileLoaded)
    {
        std::cout << "waveform: loaded!!" << std::endl;
    }
    else{
        std::cout << "waveform: NOT loaded!!" << std::endl;
    }
}

void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if(pos != position && pos == pos) // If pos doesnt equal the updated position
    {
        position = pos; // Update pos
        repaint(); // repaint the graphics
    }
    
}
