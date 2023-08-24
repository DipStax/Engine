#pragma once

#if !defined(PROJECT_STATIC)
    #if defined(_WIN32)
        // Windows compilers need specific (and different) keywords for export and import
        #define PROJECT_API_EXPORT __declspec(dllexport)
        #define PROJECT_API_IMPORT __declspec(dllimport)
        // For Visual C++ compilers, we also need to turn off this annoying C4251 warning
        #ifdef _MSC_VER
            #pragma warning(disable : 4251)
        #endif
    #else // Linux, FreeBSD, macOS
        #define PROJECT_API_EXPORT __attribute__((__visibility__("default")))
        #define PROJECT_API_IMPORT __attribute__((__visibility__("default")))
    #endif
#endif

#if defined(PROJECT_EXPORTS)

    #define PROJECT_API PROJECT_API_EXPORT
#else
    #define PROJECT_API PROJECT_API_IMPORT
#endif