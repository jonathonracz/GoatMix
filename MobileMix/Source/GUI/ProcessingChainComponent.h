/*
  ==============================================================================

    ProcessingChainComponent.h
    Created: 16 Sep 2017 6:58:30pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ProcessingChainComponent :
    public TabbedComponent
{
public:
    ProcessingChainComponent();
    ~ProcessingChainComponent();

    TabBarButton* createTabButton(const String& tabName, int tabIndex) override;
};
