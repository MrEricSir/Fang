#!/bin/bash

# Print a nice little hello message.

echo "+----------------------------+"
echo "| Fang packager for Mac OS X |"
echo "| Copyright Eric Gregory     |"
echo "+----------------------------+"
echo ""
echo "Last updated for Qt 5.3.1 in September 2014"
echo ""

# Make sure the folder exists!

if [ ! -d "Fang.app" ]
  then
    echo "----- Oops! -----"
    echo ""
	echo "You must run this from the release build directory, but I don't"
	echo "see a Fang.app folder here."
	echo ""
	echo "Make sure you've build one and try again."
	echo ""
	
	exit 280
fi


# QtWebkit 2 workaround
# See: https://bugreports.qt-project.org/browse/QTBUG-35211

cp -R ~/Qt/5.3/clang_64/libexec Fang.app/Contents

cat >> Fang.app/Contents/libexec/qt.conf <<EOD
[Paths]
Plugins = ../PlugIns
Imports = ../Resources/qml
Qml2Imports = ../Resources/qml
EOD


# Run the Mac deploy tool.
#
# About the arguments:
#   Fang.app:     The .app file must already exist (as checked above.)
#   -verbose=2:   Print at a "normal" level of verbosity
#   -qmldir="...  Scan QML files for dependencies (does NOT include Fang's QML!!!!!!)

~/Qt/5.3/clang_64/bin/macdeployqt Fang.app -verbose=2 -qmldir="../Fang/qml" -executable="Fang.app/Contents/libexec/QtWebProcess"


# Sign the app bundle.

# TODO


# Package into a DMG image

#todo
