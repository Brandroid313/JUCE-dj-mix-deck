/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 10 Mar 2021 2:01:57pm
    Author:  Brandon Godbold

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _player1,                                        DeckGUI* _GUI,
                                     AudioFormatManager & formatManagerToUse,
                                     AudioThumbnailCache & cacheToUse
                                     ) : player(_player1), GUI(_GUI)

{
    //====== Headers of columns in playlist======
    tableComponent.getHeader().addColumn("Track Title", 1, 200);
    tableComponent.getHeader().addColumn("Load Deck", 2, 200);
    
    //Changes the tablelistboxmodel that is being used for this table
    tableComponent.setModel(this);
    
    //Add and make the table component visable
    addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent()
{
}

//====Style the component======
void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

//=====Position the component as a whole=====
void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    // Table list location, starting from upper left
    tableComponent.setBounds(0, 0, getWidth(), getHeight());

}

//=====Get the number of rows=====
int PlaylistComponent::getNumRows ()
{
    return trackTitles.size();
}

//=====Draw background of row======
void PlaylistComponent::paintRowBackground (Graphics& g,
                         int rowNumber,
                         int width,
                         int height,
                         bool
                         rowIsSelected)
{
    if(rowIsSelected)
    {
        g.fillAll(Colours::orange); // If selected, highlight orange
    }
    else{
        g.fillAll(Colours::darkgrey); // Else, grey
    }
}

//=====Draws individual cells========
void PlaylistComponent::paintCell (Graphics& g,
                int rowNumber,
                int columnId,
                int width,
                int height,
                bool rowIsSelected)
{
    //====Draw the titles of the tracks==========
    if(columnId == 1){
        g.drawText(trackTitles[rowNumber], // From Vector trackTitles
                   2,
                   0,
                   width - 4,
                   height,
                   Justification::centredLeft,
                   true);
    }
    
}

//=====Make the Load Buttons for each cell=========
Component* PlaylistComponent::refreshComponentForCell (int rowNumber,
                                    int columnId,
                                    bool isRowSelected,
                                    Component *existingComponentToUpdate)
{
    if(columnId == 2)// Load to deck column
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn =  new TextButton{"Load to Deck "}; // Make new buttons for every cell
            btn->addListener(this); // add the btn to the listener here
            String id{std::to_string(rowNumber)}; // store variable id, as a string parsed from the rowNumber passed into the function
            btn->setComponentID(id); // set the componentID as that string; Note that setComponentID can only take strings
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

//=======Button Listener========
void PlaylistComponent::buttonClicked(Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString()); // Convert back from string to an interger; Assigns unique id to each song
    //convert url path to a file
    File file = urlTitles[id]; // Use the id to connectd titles with URL's
    player->loadURL(URL(file)); // Load the selected file; from pointer
    GUI->loadWaveFormFromList(URL(file)); // Pointer to the GUI to loadwaveform
}

//======Returns true or false if file drag in area detected========
bool PlaylistComponent::isInterestedInFileDrag (const StringArray &files)
{
    return true;
}

//=====Adds tracks to the Playlist from files be dragges/dropped======
void PlaylistComponent::filesDropped (const StringArray &files, int x, int y)
{
    
    if (files.size() == 1)
    {
        // Get full path name from the full local file
        juce::String urlPath = URL{File{files[0]}}.getLocalFile().getFullPathName();
        //Push full path to vector
        urlTitles.push_back(urlPath);
        
        // Seperate vector for the titles to be displayed, from juce to std string
        std::string title = URL{File{files[0]}}.getFileName().toStdString();
 
        // push the titles to the string vector
        trackTitles.push_back(title);
        
        // Update the rows
        tableComponent.updateContent();
    }
}
