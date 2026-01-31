<html>
<head>
    <meta charset="UTF-8" />
    <title>Fang</title>
    <meta name="viewport" content="width=device-width, minimum-scale=1.0, maximum-scale=1.0" />
    <link rel="shortcut icon" type="image/x-icon" href="favicon.ico" />
    <link rel="stylesheet" href="assets/style.css" />
    <link rel="alternate" type="application/rss+xml" title="Fang Releases" href="/feed.xml" />
</head>
<body>

<div id="container">
<br />
<img src="assets/fang.png" width="425" height="178" alt="Logo" /><br clear="all" />

<h1>Feed on news</h1>

<p>Fang helps you stay up to date with your favorite news websites and blogs.</p>

<p>Currently Fang is in an <span class="highlight">early beta test.</span> Download a package for your platform if you'd like to help test it.</p>

<p>Browse the source code and contribute <a href="https://github.com/MrEricSir/Fang/">on GitHub.</a></p>

<h1>Versions &amp; Downloads</h1>


<details open>
    <summary>Fang 0.2.10-beta</summary>

    <div class="version-info">
        <h2>Changelog</h2>
        <ul>
            
            <li>Option to select which feed(s) to add for web pages that publish more than one</li>
            
            <li>Reduce web view tearing</li>
            
            <li>Spinning arrow UI during slow web view requests</li>
            
            <li>Assign TCP ports dynamically</li>
            
            <li>Database optimizations</li>
            
            <li>Stability improvements</li>
            
            <li>[Internal] Split out <a href="https://github.com/MrEricSir/QSingleInstanceCheck/">QSingleInstanceCheck</a> and <a href="https://github.com/MrEricSir/QSimpleStateMachine">QSimpleStateMachine</a> into reusable libraries</li>
            
            <li>[Windows] Install to correct Program Files folder</li>
            
        </ul>

        <h2>Downloads</h2>
        <ul>
            <li><a href="https://github.com/MrEricSir/Fang/releases/download/v0.2.10-beta.1/Fang.msi">Windows</a></li>
            <li><a href="https://github.com/MrEricSir/Fang/releases/download/v0.2.10-beta.1/Fang.dmg">macOS</a></li>
            <li><a href="https://github.com/MrEricSir/Fang/releases/download/v0.2.10-beta.1/Fang.AppImage">Linux (AppImage)</a></li>
            <li><a href="https://github.com/MrEricSir/Fang/archive/refs/tags/v0.2.10-beta.1.zip">Source code</a></li>
        </ul>
    </div>
</details>

<details>
    <summary>Fang 0.2.9-beta</summary>

    <div class="version-info">
        <h2>Changelog</h2>
        <ul>
            
            <li>Refreshed UI</li>
            
            <li>Feeds can be organized into folders</li>
            
            <li>Option to follow the system's light or dark mode</li>
            
            <li>System tray icon support on Windows</li>
            
            <li>Context menus for feeds</li>
            
            <li>More reliable web UI</li>
            
            <li>Support for automatically re-discovering feed URL if it changed on the server</li>
            
            <li>Ported to Qt 6</li>
            
            <li>New build system with packages for Windows, macOS, and Linux</li>
            
            <li>Fixed single instance check</li>
            
            <li>Numerous bugs and crashes fixed</li>
            
            <li>Unit tests and code coverage report added</li>
            
        </ul>

        <h2>Downloads</h2>
        <ul>
            <li><a href="https://github.com/MrEricSir/Fang/releases/download/v0.2.9-beta.1/Fang.msi">Windows</a></li>
            <li><a href="https://github.com/MrEricSir/Fang/releases/download/v0.2.9-beta.1/Fang.dmg">macOS</a></li>
            <li><a href="https://github.com/MrEricSir/Fang/releases/download/v0.2.9-beta.1/Fang.AppImage">Linux (AppImage)</a></li>
            <li><a href="https://github.com/MrEricSir/Fang/archive/refs/tags/v0.2.9-beta.1.zip">Source code</a></li>
        </ul>
    </div>
</details>


<h1>Bugs</h1>

<p>Found a bug? File a ticket on <a href="https://github.com/MrEricSir/Fang/issues">the issue tracker.</a></p>

<br /><br />

<p id="copyright">Copyright 2026 Eric Gregory. All rights reserved. No warranty is expressed or implied.</p>

<br />
</div>


</body>
</html>
