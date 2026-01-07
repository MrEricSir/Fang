# TidyLib static library
add_library(TidyLib STATIC
    # Source files
    access.c
    alloc.c
    attrask.c
    attrdict.c
    attrget.c
    attrs.c
    buffio.c
    charsets.c
    clean.c
    config.c
    entities.c
    fileio.c
    iconvtc.c
    istack.c
    lexer.c
    localize.c
    parser.c
    pprint.c
    streamio.c
    tagask.c
    tags.c
    tidylib.c
    tmbstr.c
    utf8.c
    win32tc.c

    # Header files
    access.h
    attrdict.h
    attrs.h
    charsets.h
    clean.h
    config.h
    entities.h
    forward.h
    iconvtc.h
    lexer.h
    message.h
    parser.h
    pprint.h
    streamio.h
    tags.h
    tidy-int.h
    tmbstr.h
    utf8.h
    version.h
    win32tc.h
    include/buffio.h
    include/fileio.h
    include/platform.h
    include/tidy.h
    include/tidyenum.h
)

# Include directories (PUBLIC so they're inherited by linking targets)
target_include_directories(TidyLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# C standard
set_target_properties(TidyLib PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
)

# Platform-specific compiler flags
if(WIN32)
    target_compile_definitions(TidyLib PRIVATE
        _CRT_SECURE_NO_WARNINGS
        _CRT_NONSTDC_NO_DEPRECATE
    )
endif()

if(APPLE)
    target_compile_options(TidyLib PRIVATE
        -Wno-missing-field-initializers
    )
endif()
