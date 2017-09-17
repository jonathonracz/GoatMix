/*
  ==============================================================================

    DraggableTabBarButton.cpp
    Created: 16 Sep 2017 7:25:01pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#include "DraggableTabBarButton.h"

DraggableTabBarButton::DraggableTabBarButton(const String& name, TabbedButtonBar& ownerBar) :
    TabBarButton(name, ownerBar)
{
    ownerConstrain.setMinimumOnscreenAmounts(INT_MAX, INT_MAX, INT_MAX, INT_MAX);
}

DraggableTabBarButton::~DraggableTabBarButton()
{
}

int DraggableTabBarButton::getBestTabLength (int depth)
{
    return owner.getWidth() / owner.getNumTabs();
}

void DraggableTabBarButton::mouseDown(const MouseEvent& e)
{
    if (Desktop::getInstance().getAnimator().isAnimating(this))
        return;

    TabBarButton::mouseDown(e);
    owner.setCurrentTabIndex(getIndex()); // Tab changes on mouseUp by default.
    assert(&owner == getParentComponent());
    setMoveTriggersFromTab(getIndex());
    dragger.startDraggingComponent(this, e);
}

void DraggableTabBarButton::mouseDrag(const MouseEvent& e)
{
    TabBarButton::mouseDrag(e);
    dragger.dragComponent(this, e, &ownerConstrain);
    if (getBoundsInParent().getCentreX() > triggerTabUpX)
    {
        setMoveTriggersFromTab(getIndex() + 1);
        owner.moveTab(getIndex() + 1, getIndex(), true);
        // This (and the duplicated instance below) is a hack to prevent this
        // tab from moving (more like spazzing out) by attempting to animate
        // from the above moveTab call while we're still dragging it.
        Desktop::getInstance().getAnimator().cancelAnimation(this, false);
    }
    else if (getBoundsInParent().getCentreX() < triggerTabDownX)
    {
        setMoveTriggersFromTab(getIndex() - 1);
        owner.moveTab(getIndex() - 1, getIndex(), true);
        Desktop::getInstance().getAnimator().cancelAnimation(this, false);
    }
}

void DraggableTabBarButton::mouseUp(const MouseEvent& e)
{
    TabBarButton::mouseUp(e);
    Desktop::getInstance().getAnimator().animateComponent(this, getBoundsInParent().withX(triggerTabDownX), getAlpha(), 200, false, 3.0, 0.0);
}

void DraggableTabBarButton::setMoveTriggersFromTab(int index)
{
    TabBarButton* button = owner.getTabButton(index);
    triggerTabUpX = button->getBoundsInParent().getRight();
    triggerTabDownX = button->getBoundsInParent().getX();
}
