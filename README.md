<p align="center">
  <img src="https://github.com/MrEricSir/Fang/blob/master/qml/images/fang_logo_color.svg" alt="Fang logo">
</p>

# Fang

[![Build and Test](https://github.com/MrEricSir/Fang/workflows/Build%20and%20Test/badge.svg)](https://github.com/MrEricSir/Fang/actions)

Feed on news

Fang is a newsreader for any website that supports RSS or Atom feeds. Except when otherwise noted and not includig test data, Fang is available under a [GPL 3 license.](https://github.com/MrEricSir/Fang/blob/master/LICENSE)

For community documentation see [the wiki on GitHub.](https://github.com/MrEricSir/Fang/wiki)

Bugs and small feature requests can be filed [on the Github issues page.](https://github.com/MrEricSir/Fang/issues)

## Quick Install Guide

Because Fang is a free, open source application the binaries are not signed. If you don't trust the binaries provided, you are welcome to build from source.

The binaries are provided as a convenience only but require extra steps to run on Mac and Windows. Follow this guide to install Fang.

### macOS

1. Download `Fang-macOS-DMG` from the [Releases page](https://github.com/MrEricSir/Fang/releases)
2. Double-click the DMG file
3. Drag Fang.app to the Applications folder
4. In the Applications folder, control-click Fang.app. Select Open from the menu, then Open from the warning dialog.

### Windows

1. Download `Fang-Windows-MSI` from the [Releases page](https://github.com/MrEricSir/Fang/releases)
2. Double-click the MSI file to run the installer
3. A dialog will open with the message "Windows protected your PC." Click "More Info," then "Run Anyway" and continue with the installation.

### Linux

1. Download `Fang-Linux-AppImage` from the [Releases page](https://github.com/MrEricSir/Fang/releases)
2. Mark it as executable:
   ```bash
   chmod +x Fang.AppImage
   ```
3. Run it:
   ```bash
   ./Fang.AppImage
   ```

## Build, Run, and Debug

It is recommended to build, run, and debug from Qt Creator for development purposes. It can also be automated via the command line.

### Prerequisites

* Supported platform. Currently the primary targets are Windows and MacOS, but Linux, Android, and iOS builds have been built in the past.
* Qt 6.10
* WebEngine (or WebView, depending on platform)

### Qt Creator

1. Open Qt Creator
1. File -> Open File or Project
1. Select `CMakeLists.txt` in the main project folder
1. First time setup
    1. Pick the project kit you want to build (must be Qt 6) and click "Configure Project"
    1. Build -> Run CMake
1. Run or debug
    - To run without debugging, select Build -> Run or click the Run button in the Application output pane
    - To run with debugging, select Debug -> Start Debugging -> Start Debugging of Startup Project or click the Start Debugging of Startup Project button in the Debugger pane

To run the tests, go to View -> Output Panes -> Test Results and click Run All Tests.

### Command Line

1. First time setup: Configure...
    - ...with the version of Qt on your PATH:
      `cmake -B build`
    - ...OR with a specific version of Qt 6:
      `cmake -B build -DCMAKE_PREFIX_PATH=/path/to/Qt6`
1. Build in the build subfolder:
  `cmake --build build`
1. Run unit tests
  `ctest --test-dir build --output-on-failure`
1. Run Fang...
    - ...on macOS:
     `./build/Fang.app/Contents/MacOS/Fang`
    - ...on Windows:
     `TODO`
1. Optionally, install locally...
    - ...on macOS (TODO: verify)
      `cmake --install build --prefix /desired/install/path`
    - ...on Windows:
     `TODO`

## Debugging Tips

To debug the Javascript and HTML, you'll need to set a debugging port and set it as an environment variable. For example, we'll use `9999` as our port.

* Set the `QTWEBENGINE_REMOTE_DEBUGGING` variable to `9999`. In Qt Creator this can be found in Projects, Build & Run, Run, Environment. Click Add and enter:
   -  `QTWEBENGINE_REMOTE_DEBUGGING=9999`
* Open up Chrome (or any Chromium-based browser) to localhost at your chosen port, for example http://localhost:9999/ and click the link under "Inspectable Pages." Every time you restart Fang you will have to open that URL again to debug the page.

### Troubleshooting

* If a kit isn't found it's likely one needs to be installed, for example Xcode or Visual C++. Once installed, you may need to add it manually by clicking "Projects" in the sidebar and then "Manage Kits."
* If `cmake` can't find a package, it's possible it needs to be installed via Qt's maintenence tool. Note that all required Qt packages are open source.
