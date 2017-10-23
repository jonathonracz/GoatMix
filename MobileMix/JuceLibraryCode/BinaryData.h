/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   redo_svg;
    const int            redo_svgSize = 873;

    extern const char*   undo_svg;
    const int            undo_svgSize = 886;

    extern const char*   filter_svg;
    const int            filter_svgSize = 638;

    extern const char*   goataudio_svg;
    const int            goataudio_svgSize = 8256;

    extern const char*   mutebuttonbackground_svg;
    const int            mutebuttonbackground_svgSize = 868;

    extern const char*   power_svg;
    const int            power_svgSize = 996;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 6;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
