#ifndef DEC_HEX_WARNINGS_H
#define DEC_HEX_WARNINGS_H

// pragma macro
#ifdef __GNUC__
    #define PRAGMA(x) _Pragma(#x)
#else
    #define PRAGMA(x)
#endif

// macros
#ifdef __GNUC__
    #define SAVE_WARNING_STATE() PRAGMA(GCC diagnostic push)
    #define RESTORE_WARNING_STATE() PRAGMA(GCC diagnostic pop)
    #define DISABLE_WARNING(x) PRAGMA(GCC diagnostic ignored #x)
    #define SUPPRESS_WARNING(x) SAVE_WARNING_STATE() DISABLE_WARNING(x)

    // warnings
    #define DISABLE_WARNING_SIGN_COMPARE() DISABLE_WARNING(-Wsign-compare)
    #define SUPPRESS_WARNING_SIGN_COMPARE() SUPPRESS_WARNING(-Wsign-compare)
#else
    #define SAVE_WARNINGS()
    #define RESTORE_WARNINGS()
    #define DISABLE_WARNING(x)
    #define SUPPRESS_WARNING(x)

    #define DISABLE_WARNING_SIGN_COMPARE()
    #define SUPPRESS_WARNING_SIGN_COMPARE()
#endif

#endif