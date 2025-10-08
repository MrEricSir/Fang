<p align="center">
  <img src="https://github.com/MrEricSir/Fang/blob/master/qml/images/fang_logo_color.svg" alt="Fang logo">
</p>

# Fang

Feed on news

Fang is a newsreader for any website that supports RSS or Atom feeds. Except when otherwise noted and not includig test data, Fang is available under a [GPL 3 license.](https://github.com/MrEricSir/Fang/blob/master/LICENSE)

For community documentation see [the wiki on GitHub.](https://github.com/MrEricSir/Fang/wiki)

Bugs and small feature requests can be filed [on the Github issues page.](https://github.com/MrEricSir/Fang/issues)

## Prerequisites

* Supported platform. Currently the primary targets are Windows and MacOS, but Linux, Android, and iOS builds have been built in the past.
* Qt 6.10
* WebEngine (or WebView, depending on platform)

## Build and run

It is recommended to build, run, and debug from Qt Creator. 

In Qt Creator run `qmake` on `Fang.pro`. Assuming the output has no errors, it should be possible to build and run.

### Troubleshooting

* If a kit isn't found it's likely one needs to be installed, for example Xcode or Visual C++. Once installed, you may need to add it manually by clicking "Projects" in the sidebar and then "Manage Kits."
* If `qmake` can't find a package, it's possible it needs to be installed via Qt's maintenence tool. Note that all required Qt packages are open source.

## Testing

Fang includes a suite of unit tests in the `test` subdirectory.

### Build, run, and debug individual tests

1. Open the `tests\AllUnitTests.pro` file in Qt Creator.
1. From there, open the test subfolder. Right click on the individual `.pro` file to run or debug that suite.
1. Individual tests in each suite are specified in the corresponding `.cpp` files. Thees can be temporarily commented out to focus on a single test. 

### Build and run all unit tests

    cd test/build
    qmake ..
    make
    make check
