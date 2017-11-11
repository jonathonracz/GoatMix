# MobileMix

Welcome to the MobileMix repository! Please keep in mind that audio plugins are extremely fickle and complex things when it comes to building, due to the massive number of dependencies, SDKs, and build gymnastics needed to compile them and make them run. That said, this document will attempt to explain as clearly and concisely as possible how to get started. To course instructors reading this, I am more than happy to meet during office hours and assist in setting it up.

## Step 1: Have the correct build tools.
MobileMix is tested to build using Xcode 9.1 under macOS High Sierra (10.13). Tested plugin hosts/targets are:

* Garageband as an AUv3 plugin (iOS)
* Logic Pro X (10.3.2) as an AUv2 plugin (macOS)
* Ableton Live 9.7.5 as a VST2 plugin (macOS)

## Step 2: Clone the repository recursively.

If you do a simple `git clone`, the code **_will not work!_** You must clone recursively to also pull in the many dependencies. Note that downloading a `.zip` of `master` from the repository will not download any of the submodules. To clone recursively, use `git clone --recursive https://github.com/jonathonracz/MobileMix.git`

It will take a while to clone everything. Once complete, own `MobileMix.xcworkspace`.

## Step 3: Build.

This is where things will either go without a hitch or crash and burn, mostly due to paths to SDKs (which are included as submodules) are not referenced correctly for whatever reason. Again, contact me (jdracz at umich dot edu) if you run into these issues, but in the case of simply building and side-loading the app onto a device, there shouldn't be any issues.

##### Building for iOS (AUv3)

This will build MobileMix in iOS' native plugin format, Audio Unit version 3 (AUv3) for use with any iOS plugin host - this is the meat and potatoes build target for this course. To build, pick the "AUv3 AppExtension" build target. Make sure it's the iOS deployment version, as there are two! You can tell by looking at the popup menu to see if the target refers to "My Mac" or an iOS device.

To load the built plugin into Garageband, follow [Apple's Instructions](https://support.apple.com/kb/PH24861?viewlocale=en_US&locale=en_US) under "Add an Audio Units Effect".

Note that depending on the age or style of your device (iPhone vs. iPad, etc.), GUI performance under Garageband may be dismal - which is why most mobile plugins are simply an array of labeled sliders rather than an slew of animation like MobileMix. Audio processing will almost definitely be handled without issue, however.

##### Building for iOS (Standalone)

This will build MobileMix in a standalone "dummy" mode which is mostly useful for smoke testing or checking out GUI behaviors, as no audio can be routed through it since there is no host to provide audio. This target is the "Standalone Plugin" iOS deployment option in the build targets menu.

##### Building for macOS (Any target)

I've lumped the macOS build instructions into one category because they're almost completely analagous to the iOS instructions - just choose the target which deploys to "My Mac" rather than to an iOS device. Note that no host on macOS currently works with AUv3, so stick to AUv2 (supported by any first party host on macOS, such as Logic or Garageband) or VST (supported by any third party host, such as Ableton Live, Reaper, Cubase, etc.).
