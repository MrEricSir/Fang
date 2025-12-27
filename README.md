<p align="center">
  <img src="https://github.com/MrEricSir/Fang/blob/master/qml/images/fang_logo_color.svg" alt="Fang logo">
</p>

# Fang

[![Unit Tests](https://github.com/MrEricSir/Fang/workflows/Unit%20Tests/badge.svg)](https://github.com/MrEricSir/Fang/actions)

Feed on news

Fang is a newsreader for any website that supports RSS or Atom feeds. Except when otherwise noted and not includig test data, Fang is available under a [GPL 3 license.](https://github.com/MrEricSir/Fang/blob/master/LICENSE)

For community documentation see [the wiki on GitHub.](https://github.com/MrEricSir/Fang/wiki)

Bugs and small feature requests can be filed [on the Github issues page.](https://github.com/MrEricSir/Fang/issues)

## Prerequisites

* Supported platform. Currently the primary targets are Windows and MacOS, but Linux, Android, and iOS builds have been built in the past.
* Qt 6.10
* WebEngine (or WebView, depending on platform)

## Build, Run, and Debug

It is recommended to build, run, and debug from Qt Creator for development purposes. It can also be automated via the command line.

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

The steps for running/debugging the unit tests are essentially the same as above but use the `CMakeLists.txt` in the `test` subfolder.

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
    - on Windows:
     `TODO`

## Debugging Tips

To debug the Javascript and HTML, you'll need to set a debugging port and set it as an environment variable. For example, we'll use `9999` as our port.

* Set the `QTWEBENGINE_REMOTE_DEBUGGING` variable to `9999`. In Qt Creator this can be found in Projects, Build & Run, Run, Environment. Click Add and enter `QTWEBENGINE_REMOTE_DEBUGGING=9999`
* Open up Chrome (or any Chromium-based browser) to localhost at your port, for example `http://127.0.0.1` and click the link under "Inspectable Pages."

### Troubleshooting

* If a kit isn't found it's likely one needs to be installed, for example Xcode or Visual C++. Once installed, you may need to add it manually by clicking "Projects" in the sidebar and then "Manage Kits."
* If `cmake` can't find a package, it's possible it needs to be installed via Qt's maintenence tool. Note that all required Qt packages are open source.


    make check
