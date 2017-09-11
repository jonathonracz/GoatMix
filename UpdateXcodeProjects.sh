#!/bin/bash

ROOT_DIR_PATH_PREFIX="."
if [ -n $PROJECT_DIR ]; then
    ROOT_DIR_PATH_PREFIX="../../../"
fi

PROJUCER_EXEC_PATH="${ROOT_DIR_PATH_PREFIX}/external/JUCE/extras/Projucer/Builds/MacOSX/build/Release/Projucer.app/Contents/MacOS/Projucer"
if [ ! -x "$PROJUCER_EXEC_PATH" ]; then
    echo "warning: Local Projucer build not found in ./externals/JUCE. Build Projucer in Release mode to enable build-time Xcode project regeneration."

else
    echo "Updating Xcode projects..."
    "${PROJUCER_EXEC_PATH}" --resave "${ROOT_DIR_PATH_PREFIX}/MobileMix/MobileMix.jucer"
fi


