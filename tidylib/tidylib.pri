######################################################################
# TidyLib
# Thanklessly copied from this project: 
# https://github.com/pehohlva/qt-gmail-access
######################################################################

VPATH += tidylib tidylib/include
INCLUDEPATH += tidylib tidylib/include

# Disable deprecation warnings.
win32:DEFINES += "_CRT_SECURE_NO_WARNINGS" "_CRT_NONSTDC_NO_DEPRECATE"

# TidyLib doesn't initialize all fields. :(
macx:QMAKE_CXXFLAGS_WARN_OFF += "-Wmissing-field-initializers"


# Input
HEADERS += access.h \
           attrdict.h \
           attrs.h \
           charsets.h \
           clean.h \
           config.h \
           entities.h \
           forward.h \
           iconvtc.h \
           lexer.h \
           message.h \
           parser.h \
           pprint.h \
           streamio.h \
           tags.h \
           tidy-int.h \
           tmbstr.h \
           utf8.h \
           version.h \
           win32tc.h \
           include/buffio.h \
           include/fileio.h \
           include/platform.h \
           include/tidy.h \
           include/tidyenum.h \

SOURCES += access.c \
           alloc.c \
           attrask.c \
           attrdict.c \
           attrget.c \
           attrs.c \
           buffio.c \
           charsets.c \
           clean.c \
           config.c \
           entities.c \
           fileio.c \
           iconvtc.c \
           istack.c \
           lexer.c \
           localize.c \
           parser.c \
           pprint.c \
           streamio.c \
           tagask.c \
           tags.c \
           tidylib.c \
           tmbstr.c \
           utf8.c \
           win32tc.c \
