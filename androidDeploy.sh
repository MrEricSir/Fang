#!/bin/bash

# Print a nice little hello message.

echo "+----------------------------+"
echo "| Fang packager for Android  |"
echo "| Copyright Eric Gregory     |"
echo "+----------------------------+"
echo ""
echo "Last updated for Qt 5.5 (beta) in May 2015"
echo ""

# The qmake script runs this automatically

# Create our new HTML
sed s,qrc:///,file:///android_asset/,g ../html/index.html &> ../html/index_android.html
