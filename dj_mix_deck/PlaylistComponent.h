/*
  ==============================================================================

    PlaylistComponent.h
    Created: 10 Mar 2021 2:01:57pm
    Author:  Brandon Godbold

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/

//=====Class takes similar components to DJAudio Player and GUI to use them as pointers;===
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public Button::Listener,
                           public FileDragAndDropTarget
{
    
public:
    
    PlaylistComponent(DJAudioPlayer* player, DeckGUI* GUI,
                      AudioFormatManager & formatManagerToUse,
                      AudioThumbnailCache & cacheToUse);
    ~PlaylistComponent() override;
    
    //===Paint and position functions=======
    void paint (juce::Graphics&) override;
    void resized() override;
    
    //====returns the number of rows in the table=====
    int  getNumRows () override;
    
    //======provides graphical code which draws the background of a row in the table=====
    void paintRowBackground (Graphics &,
                             int rowNumber,
                             int width,
                             int height,
                             bool
                             rowIsSelected) override;
    
    //====contains graphical code which draws the contents of individual cells======
    void paintCell (Graphics &,
                    int rowNumber,
                    int columnId,
                    int width,
                    int height,
                    bool rowIsSelected) override;
    
    
    Component* refreshComponentForCell (int rowNumber,
                                        int columnId,
                                        bool isRowSelected,
                                        Component *existingComponentToUpdate) override;
    
    //===== Listeners for dragging and dropping files======
    bool isInterestedInFileDrag (const StringArray &files) override; //Bool file drag in area detected
    void filesDropped (const StringArray &files, int x, int y) override; // Callback; indicates if files have been dropped
    
    //====Listener for if Button Clicked====
    void buttonClicked(Button* button) override;

private:
    
    TableListBox tableComponent;
    //====Storage of tracks and titles========
    std::vector<std::string> trackTitles; // Titles as strings
    std::vector<juce::String> urlTitles; // Full URL in juce string
    
    //====Instance of DJAudioPlayer class; from pointer *====
    DJAudioPlayer* player;
    
    //====Instance of DeckGUI class; from pointer *=====
    DeckGUI* GUI;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
