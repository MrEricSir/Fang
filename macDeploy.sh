#!/bin/bash

# Print a nice little hello message.

echo "+----------------------------+"
echo "| Fang packager for Mac OS X |"
echo "| Copyright Eric Gregory     |"
echo "+----------------------------+"
echo ""
echo "Last updated for Qt 5.5 beta in May 2015"
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

#cat >> Fang.app/Contents/libexec/qt.conf <<EOD
#[Paths]
#Plugins = ../PlugIns
#Imports = ../Resources/qml
#Qml2Imports = ../Resources/qml
#EOD
#cat >> Fang.app/Contents/libexec/qt.conf


export QML2_IMPORT_PATH="../qml"


# Run the Mac deploy tool.
#
# About the arguments:
#   Fang.app:     The .app file must already exist (as checked above.)
#   -verbose=2:   Print at a "normal" level of verbosity
#   -qmldir="...  Scan QML files for dependencies

macdeployqt Fang.app -verbose=3 -qmldir="../qml"


# Need to copy SQLite driver.
# (Seems to be a bug in Qt 5.5 beta?)
SQLDRIVERS=Fang.app/Contents/PlugIns/sqldrivers
mkdir -p $SQLDRIVERS
cp $QTDIR/plugins/sqldrivers/libqsqlite.dylib $SQLDRIVERS

# Fixup load paths for the SQLite driver (macdeployqt does this for all other modules)
install_name_tool -change $QTDIR/lib/QtSql.framework/Versions/5/QtSql @executable_path/../Frameworks/QtSql.framework/Versions/5/QtSql $SQLDRIVERS/libqsqlite.dylib 
install_name_tool -change $QTDIR/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore $SQLDRIVERS/libqsqlite.dylib 


# Sign the app bundle.

# TODO


# Package into a DMG image

#todo
