<p align="center">
  <img src="https://github.com/MrEricSir/Fang/blob/master/qml/images/fang_logo_color.svg" alt="Fang logo">
</p>

# Fang

[![Build and Test](https://github.com/MrEricSir/Fang/workflows/Build%20and%20Test/badge.svg)](https://github.com/MrEricSir/Fang/actions)
[![Coverage Report](https://img.shields.io/badge/coverage-report-blue.svg)](https://mrericsir.github.io/Fang/coverage/)

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

### Command Line

**Note:** All commands below should be run from the Fang project root directory.

1. First time setup: Configure...
    - ...with the version of Qt on your PATH:
      ```bash
      cmake -B build
      ```
    - ...OR with a specific version of Qt 6:
      ```bash
      cmake -B build -DCMAKE_PREFIX_PATH=/path/to/Qt6
      ```
1. Build in the build subfolder:
   ```bash
   cmake --build build
   ```
1. Run Fang...
    - ...on macOS:
      ```bash
      ./build/Fang.app/Contents/MacOS/Fang
      ```
    - ...on Windows:
      ```
      TODO
      ```
1. Optionally, install locally...
    - ...on macOS (TODO: verify)
      ```bash
      cmake --install build --prefix /desired/install/path
      ```
    - ...on Windows:
      ```
      TODO
      ```

## Debugging Tips

To debug the Javascript and HTML, you'll need to set a debugging port and set it as an environment variable. For example, we'll use `9999` as our port.

* Set the `QTWEBENGINE_REMOTE_DEBUGGING` variable to `9999`. In Qt Creator this can be found in Projects, Build & Run, Run, Environment. Click Add and enter:
   -  `QTWEBENGINE_REMOTE_DEBUGGING=9999`
* Open up Chrome (or any Chromium-based browser) to localhost at your chosen port, for example http://localhost:9999/ and click the link under "Inspectable Pages." Every time you restart Fang you will have to open that URL again to debug the page.

## Unit Tests and Code Coverage

Install `lcov` and build Fang in Debug mode. Coverage will be automatically enabled!

Installing `lcov`:
- macOS: `brew install lcov`
- Ubuntu: `sudo apt-get install lcov`

### Qt Creator

1. Make sure you have a Debug build selected in the Projects pane (coverage is automatically enabled)
1. Run the tests: View → Output Panes → Test Results → Click "Run All Tests"
1. Generate coverage report using the Terminal pane:
   - View → Output Panes → Terminal
   - Run: `./coverage.sh`
1. The coverage report will **open automatically in your browser**!

### Command Line

**Note:** Coverage requires a Debug build. Configure with:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

1. Run all tests:
   ```bash
   ctest --test-dir build
   ```

1. Generate coverage report:
   ```bash
   ./coverage.sh
   ```
   The coverage report will **open automatically in your browser**!

**Alternative:** Generate coverage from the build directory:
```bash
cd build
make coverage-html
```

## Troubleshooting

* If a kit isn't found it's likely one needs to be installed, for example Xcode or Visual C++. Once installed, you may need to add it manually by clicking "Projects" in the sidebar and then "Manage Kits."
* If `cmake` can't find a package, it's possible it needs to be installed via Qt's maintenence tool. Note that all required Qt packages are open source.

## Building a Release

To build version `1.2.3`, follow these steps:

Edit `CMakeLists.txt` to reflect the new version and commit the change.
```
project(Fang VERSION 1.2.3 LANGUAGES CXX C)
```

Push that change and create and push a tag with the same name:

```bash
git tag -a v1.2.3 -m "Version 1.2.3"
git push origin v1.2.3
```

GitHub Actions should create and publish the build automatically.
