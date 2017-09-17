/*
  ==============================================================================

    ProcessingChainComponent.cpp
    Created: 16 Sep 2017 6:58:30pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "ProcessingChainComponent.h"
#include "DraggableTab.h"

ProcessingChainComponent::ProcessingChainComponent() :
    TabbedComponent(TabbedButtonBar::Orientation::TabsAtBottom)
{
    addTab("1", juce::Colours::white, new TextEditor, true);
    addTab("2", juce::Colours::green, new TextEditor, true);
    addTab("3", juce::Colours::green, new TextEditor, true);
    addTab("4", juce::Colours::green, new TextEditor, true);
}

ProcessingChainComponent::~ProcessingChainComponent()
{

}

TabBarButton* ProcessingChainComponent::createTabButton(const String& tabName, int tabIndex)
{
    return new DraggableTab(tabName, getTabbedButtonBar());
}
