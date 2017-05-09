
Installation
============

Windows
-------

First you need to get all of the "header only" dependencies, which are:

- stb - `https://github.com/nothings/stb`
- tinyformat - `https://github.com/c42f/tinyformat`
- glm - `https://github.com/g-truc/glm`
- imgui - `https://github.com/ocornut/imgui`
- Catch - `https://github.com/philsquared/Catch`
- glad - `https://github.com/iondune/glad`
- dirent - `https://github.com/tronkko/dirent`

The easiest way to do this is to navigate to the `Dependencies/` folder and run `Clone.bat`. Make sure that you have `git` in your path.

Next we need to get ``glfw``, the only binary dependency.
The engine currently uses version `3.1.2`.
You can download pre-built binaries at [this link](https://github.com/glfw/glfw/releases/download/3.1.2/glfw-3.1.2.bin.WIN64.zip) or by finding the link on [http://www.glfw.org/download.html](http://www.glfw.org/download.html).
Extract the `glfw-3.1.2.bin.WIN64` folder to the `Dependencies/` folder alongside the other dependencies.



Linux
-----

These instructions are tailored for Ubuntu 14.04 but the same principles should apply to most Linux distros and in particular to any similar version of Ubuntu.

Thankfully all dependencies are available as packages or are header-only.

You will need `g++` and 'cmake' for compilation.

You'll also need to install both GLEW and GLFW3. Unfortunately, at time of this writing the Ubuntu GLFW package is prohibitively out of date so we need to install a ppa to provide an up-to-date version::

   sudo add-apt-repository ppa:keithw/glfw3 -y
   sudo apt-get -qq update

With that done we can now install all of our package-based dependencies::

   sudo apt-get -qq install g++ cmake libglew-dev xorg-dev libglfw3-dev -y

Finally, install the header-only dependencies by running this script from the ionEngine project root directory::

   ./UpdateDependencies.bash

With that we are ready to build ionEngine. From that same directory, run cmake::

   cmake .
   make



OS X
----

These instructions are for OS X 10.9.5 but should hopefully apply pretty universally.

First, make sure that you have both [Xcode](https://developer.apple.com/xcode/download/) and [Homebrew](http://brew.sh/) installed.

Next, install CMake, GLEW, and GLFW3 through homebrew::

   brew install cmake glew glfw3

Finally, install the header-only dependencies by running this script from the ionEngine project root directory::

   ./UpdateDependencies.bash

With that we are ready to build ionEngine. From that same directory, run cmake::

   cmake .
   make
