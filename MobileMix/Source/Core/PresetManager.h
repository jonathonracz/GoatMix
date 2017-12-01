/*
  ==============================================================================

    PresetManager.h
    Created: 30 Nov 2017 12:49:34pm
    Author:  Jonathon Racz

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class PresetManager
{
public:
    static File getDefaultPresetsDirectory() noexcept
    {
        File baseDirectory = File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory);
    #if JUCE_MAC || JUCE_IOS
        File appSupportDir = baseDirectory.getChildFile("Application Support");
        jassert(appSupportDir.exists() && !appSupportDir.existsAsFile()); // Uh...
        baseDirectory = appSupportDir;
    #endif
        return baseDirectory.getChildFile(JucePlugin_Manufacturer + File::getSeparatorString() + JucePlugin_Name);
    }

    struct DumpBlock
    {
        StringRef name;
        const char*& block;
        const int& blockSize;
    };

    PresetManager(
        int _numPresets,
        const std::vector<DumpBlock>& _factoryPresets = {},
        File _presetsDirectory = getDefaultPresetsDirectory(),
        StringRef _emptyPresetName = "Empty",
        StringRef _indexDelimiter = " ") :
        numPresets(_numPresets),
        factoryPresets(_factoryPresets),
        presetsDirectory(_presetsDirectory),
        emptyPresetName(_emptyPresetName),
        indexDelimiter(_indexDelimiter)
    {
        initializePresets();
    }

    File getPresetsDirectory() const noexcept
    {
        return presetsDirectory;
    }

    int getNumPresets() const noexcept
    {
        return numPresets;
    }

    void setPresetName(int index, String newName)
    {
        File file = enumeratePresetFiles()[index];
        if (file.getFullPathName().isEmpty())
        {
            file = getPresetsDirectory().getChildFile(addIndexToPresetName(newName, index));
            file.create();
        }
        else
        {
            file.moveFileTo(file.getParentDirectory().getChildFile(addIndexToPresetName(newName, index)));
        }
    }

    StringArray enumeratePresetNames() noexcept
    {
        StringArray ret;
        for (int i = 0; i < numPresets; ++i)
            ret.add(emptyPresetName);

        std::vector<File> presetFiles = enumeratePresetFiles();
        for (size_t i = 0; i < presetFiles.size(); ++i)
        {
            if (presetFiles[i].getFullPathName().length() > 0)
                ret.set(static_cast<int>(i), stripIndexFromPresetName(presetFiles[i].getFileName()));
        }

        return ret;
    }

    std::vector<File> enumeratePresetFiles() const noexcept
    {
        std::vector<File> ret(static_cast<size_t>(numPresets));

        if (!getPresetsDirectory().exists())
            return ret;

        DirectoryIterator presetDirectoryFiles(getPresetsDirectory(), false);
        bool falseOption = false;

        while (presetDirectoryFiles.next(&falseOption,
                                         &falseOption,
                                         nullptr,
                                         nullptr,
                                         nullptr,
                                         &falseOption))
        {
            File currFile = presetDirectoryFiles.getFile();
            int index = getIndexFromPresetName(currFile.getFileName());
            if (index > numPresets || index < 0)
                continue;

            ret[index] = currFile;
        }

        return ret;
    }

    void getStateForPreset(int index, MemoryBlock& dataDest) const noexcept
    {
        File presetFile = enumeratePresetFiles()[index];
        if (presetFile.existsAsFile())
        {
            FileInputStream inputStream(presetFile);
            inputStream.readIntoMemoryBlock(dataDest);
        }
    }

    void setStateForPreset(int index, const void* data, int sizeInBytes) noexcept
    {
        File preset = enumeratePresetFiles()[index];
        jassert(preset.existsAsFile()); // If the preset is uninitialized, you must first set a name for it with setPresetName!
        FileOutputStream outputStream(preset);
        outputStream.write(data, sizeInBytes);
    }

private:
    Result createPresetsDirectoryIfNeeded() const noexcept
    {
        return getPresetsDirectory().createDirectory();
    }

    int getIndexFromPresetName(String name) const noexcept
    {
        int indexOfSeparator = name.indexOf(indexDelimiter);
        String indexStr = name.substring(0, indexOfSeparator);
        if (!indexStr.containsOnly("1234567890"))
            return -1;

        return indexStr.getIntValue();
    }

    String stripIndexFromPresetName(String name) const noexcept
    {
        int indexOfSeparator = name.indexOf(indexDelimiter);
        return name.substring(indexOfSeparator + 1);
    }

    String addIndexToPresetName(String name, int index) const noexcept
    {
        jassert(index >= 0);
        return String(index) + indexDelimiter + name;
    }

    Result dumpPresetBlocksToDisk() const noexcept
    {
        {
            Result createResult = createPresetsDirectoryIfNeeded();
            if (!createResult)
                return createResult;
        }

        for (int i = 0; i < factoryPresets.size(); ++i)
        {
            String presetName = String(i) + indexDelimiter + factoryPresets[i].name;
            File presetFile = getPresetsDirectory().getChildFile(presetName);
            FileOutputStream presetWriter(presetFile);

            {
                Result openResult = presetWriter.getStatus();
                if (!openResult)
                    return openResult;
            }

            if (!presetWriter.write(factoryPresets[i].block, factoryPresets[i].blockSize))
                return Result::fail("Failed to write preset: " + presetFile.getFullPathName());
        }

        return Result::ok();
    }

    Result initializePresets() const noexcept
    {
        if (getPresetsDirectory().existsAsFile())
        {
            bool result = getPresetsDirectory().deleteFile();
            if (!result)
                return Result::fail("Failed to delete the file " + getPresetsDirectory().getFullPathName() + ", which is blocking preset folder creation.");
        }

        if (!getPresetsDirectory().exists())
            return dumpPresetBlocksToDisk();

        return Result::fail("Failed to dump presets to disk.");
    }

    int numPresets;
    std::vector<DumpBlock> factoryPresets;
    File presetsDirectory;
    StringRef emptyPresetName;
    StringRef indexDelimiter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetManager)
};
