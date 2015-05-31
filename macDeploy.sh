#!/bin/bash

# Print a nice little hello message.

echo "+----------------------------+"
echo "| Fang packager for Mac OS X |"
echo "| Copyright Eric Gregory     |"
echo "+----------------------------+"
echo ""
echo "Last updated for Qt 5.5 beta in May 2015"
echo ""

echo "QTDIR is set to: $QTDIR"
echo ""

FANGAPP=Fang.app

# Make sure the folder exists!

if [ ! -d "$FANGAPP" ]
  then
    echo "----- Oops! -----"
    echo ""
	echo "You must run this from the Fang build directory, but I don't"
	echo "see the Fang.app folder here."
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


export QML2_IMPORT_PATH="qml"

FANGAPPFULL=$PWD/$FANGAPP
QMLDIRFULL=$(dirname $PWD)/qml

# Run the Mac deploy tool.
#
# About the arguments:
#   Fang.app:     The .app file must already exist (as checked above.)
#   -verbose=2:   Print at a "normal" level of verbosity
#   -qmldir="...  Scan QML files for dependencies

# Need the "executable" because of a WebEngine bug: https://bugreports.qt.io/browse/QTBUG-41611
# Need to push/pop the dir because of this bug: https://bugreports.qt.io/browse/QTBUG-46404
pushd $QTDIR/bin
echo "Changed directory to: $PWD"
./macdeployqt $FANGAPPFULL -verbose=3 -qmldir=$QMLDIRFULL -executable="$FANGAPPFULL/Contents/MacOS/Fang"
popd

# Web Engine exe is now at
# $FANGAPPFULL/Contents/Frameworks/QtWebEngineCore.framework/Versions/5/Helpers/QtWebEngineProcess



# Need to copy SQLite driver.
# (Seems to be a bug in Qt 5.5 beta?)
SQLDRIVERS=$FANGAPP/Contents/PlugIns/sqldrivers
mkdir -p $SQLDRIVERS
cp $QTDIR/plugins/sqldrivers/libqsqlite.dylib $SQLDRIVERS

# Fixup load paths for the SQLite driver (macdeployqt does this for all other modules)
install_name_tool -change $QTDIR/lib/QtSql.framework/Versions/5/QtSql @executable_path/../Frameworks/QtSql.framework/Versions/5/QtSql $SQLDRIVERS/libqsqlite.dylib 
install_name_tool -change $QTDIR/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore $SQLDRIVERS/libqsqlite.dylib 

# Install and fixup SVG module
IMAGEFORMATS=$FANGAPP/Contents/PlugIns/imageformats
cp $QTDIR/plugins/imageformats/libqsvg.dylib $IMAGEFORMATS
install_name_tool -change $QTDIR/lib/QtSvg.framework/Versions/5/QtSvg @executable_path/../Frameworks/QtSvg.framework/Versions/5/QtSvg $IMAGEFORMATS/libqsvg.dylib
install_name_tool -change $QTDIR/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets $IMAGEFORMATS/libqsvg.dylib
install_name_tool -change $QTDIR/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui $IMAGEFORMATS/libqsvg.dylib
install_name_tool -change $QTDIR/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore $IMAGEFORMATS/libqsvg.dylib

# Sign the app bundle.

# TODO


# Package into a DMG image

#todo
