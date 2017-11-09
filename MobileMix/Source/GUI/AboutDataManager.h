/*
  ==============================================================================

    AboutDataManager.h
    Created: 9 Nov 2017 1:49:31pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class AboutDataManager
{
public:
    AboutDataManager()
    {
        ensurePDFCreated();
    }

    ~AboutDataManager() {}

    class OpenDocumentCallback :
        public ModalComponentManager::Callback
    {
    public:
        ~OpenDocumentCallback() = default;

        void modalStateFinished(int returnValue) override
        {
            if (returnValue)
            {
                manager.ensurePDFCreated();
                manager.aboutPDF.startAsProcess();
            }
        }
    private:
        friend AboutDataManager;
        explicit OpenDocumentCallback(AboutDataManager& _manager) :
            manager(_manager) {}
        AboutDataManager& manager;
    };

    OpenDocumentCallback* getCallback()
    {
        return new OpenDocumentCallback(*this);
    }

private:
    void ensurePDFCreated()
    {
        if (!aboutPDF.exists())
        {
            aboutPDF = File::createTempFile(".pdf");
            std::unique_ptr<FileOutputStream> output(aboutPDF.createOutputStream());
            output->write(BinaryData::MobileMixAcknowledgements_pdf, BinaryData::MobileMixAcknowledgements_pdfSize);
        }
    }

    File aboutPDF;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AboutDataManager)
};
