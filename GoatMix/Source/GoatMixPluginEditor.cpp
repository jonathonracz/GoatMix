/*
  ==============================================================================

    GoatMixPluginEditor.cpp
    Created: 11 Sep 2017 2:45:04pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "GoatMixPluginProcessor.h"
#include "GoatMixPluginEditor.h"
#include "GUI/ScreenResolutionConstants.h"

GoatMixAudioProcessorEditor::GoatMixAudioProcessorEditor(GoatMixAudioProcessor& p) :
    AudioProcessorEditor(&p),
    processor(p),
    topBar(p),
    tabs(TabbedButtonBar::Orientation::TabsAtBottom),
    aboutMessage(NEEDS_TRANS("The about and acknowledgements PDF can be found in GoatMix's iTunes file sharing.")),
    tooltipDisplay(*this)
{
#if JUCE_DEBUG
    setResizable(true, true);
#endif
    setSize(ScreenResolutionConstants::iPhone7LogicalY,
        ScreenResolutionConstants::iPhone7LogicalX);
    processor.params.state.addListener(this);
    processor.chainTree.addListener(this);
    for (int i = 0; i < processor.chain.getNumNodes(); ++i)
    {
        jassert(processor.chainTree.getChild(i).getType() == Identifier(processor.chain.getNode(i)->getProcessor()->getName()));
        GMPluginInstance* currentProcessor = static_cast<GMPluginInstance*>(processor.chain.getNode(i)->getProcessor());
        tabs.addTabForPlugin(currentProcessor);
    }

    topBar.addListener(this);
    addAndMakeVisible(topBar);
    tabs.addListener(this);
    addAndMakeVisible(tabs);
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    setBufferedToImage(true);
    addChildComponent(aboutMessage);
    processor.undoManager.clearUndoHistory();
}

GoatMixAudioProcessorEditor::~GoatMixAudioProcessorEditor()
{
    setLookAndFeel(nullptr); // Prevent assertion on quit
    processor.params.state.removeListener(this);
    processor.chainTree.removeListener(this);
}

void GoatMixAudioProcessorEditor::paint(Graphics& g)
{
    g.fillAll(static_cast<GMLookAndFeel&>(getLookAndFeel()).findColour(GMLookAndFeel::ColourIds::background));
    ColourGradient gradient(ColourGradient(Colour(0x00000000), 0, 0, Colour(0x18000000), 0, getHeight(), false));
    g.setGradientFill(gradient);
    g.fillAll();
}

void GoatMixAudioProcessorEditor::resized()
{
    FlexBox layout;
    layout.flexDirection = FlexBox::Direction::column;

    layout.items.add(FlexItem(topBar).withFlex(0.10f));
    layout.items.add(FlexItem(tabs).withFlex(1.0f));

    layout.performLayout(getLocalBounds());

    aboutMessage.setBounds(getLocalBounds());

    // Manual hack since we aren't laying out the tabbedButtonBar directly...
    tabs.setTabBarDepth(topBar.getHeight());
}

int GoatMixAudioProcessorEditor::getIndexOfTabWithName(String name)
{
    TabbedButtonBar& bar = tabs.getTabbedButtonBar();
    for (int i = 0; i < bar.getNumTabs(); ++i)
        if (bar.getTabButton(i)->getName() == name)
            return i;

    jassert(false);
    return -1;
}

void GoatMixAudioProcessorEditor::tabDragStarted(int atIndex)
{
    processor.undoManager.beginNewTransaction("Tab move");
}

void GoatMixAudioProcessorEditor::tabMovedViaDrag(int fromIndex, int toIndex)
{
    // Attempting to move tabs representing processor indices which don't exist...
    jassert(fromIndex < processor.chain.getNumNodes() && toIndex < processor.chain.getNumNodes());
    jassert(fromIndex < processor.chainTree.getNumChildren() && toIndex < processor.chainTree.getNumChildren());
    processor.chainTree.moveChild(fromIndex, toIndex, &processor.undoManager);
}

void GoatMixAudioProcessorEditor::valueTreeChildOrderChanged(ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex)
{
    if (parentTreeWhoseChildrenHaveMoved == processor.chainTree)
    {
        // Check if the tab actually needs to be moved before attempting to move
        // it (otherwise we get the same tab moving twice).
        if (Identifier(tabs.getTabbedButtonBar().getTabButton(newIndex)->getName()) != processor.chainTree.getChild(newIndex).getType())
        {
            tabs.moveTab(oldIndex, newIndex, true);
        }
    }
}

void GoatMixAudioProcessorEditor::valueTreeRedirected(ValueTree &treeWhichHasBeenChanged)
{
    if (treeWhichHasBeenChanged == processor.chainTree)
    {
        // We need to rebuild our tabs.
        for (int i = 0; i < processor.chainTree.getNumChildren(); ++i)
        {
            int currentTabIndex = getIndexOfTabWithName(processor.chainTree.getChild(i).getType().toString());
            if (currentTabIndex > -1 && currentTabIndex != i)
            {
                tabs.moveTab(currentTabIndex, i, true);
            }
        }
    }
}

void GoatMixAudioProcessorEditor::infoClicked(GMTopBar* bar)
{
#if !JUCE_IOS
    AlertWindow::showOkCancelBox(
        AlertWindow::AlertIconType::WarningIcon,
        NEEDS_TRANS("Open Acknowledgements?"),
        NEEDS_TRANS("Opening the acknowledgements document may cause audio to stop. Continue?"),
        "",
        "",
        this,
        aboutData.getCallback());
#else
    aboutMessage.show();
#endif
}
