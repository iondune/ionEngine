
Installation
============

.. toctree::
   :maxdepth: 2


Windows
-------

First you need to get all of the "header only" dependencies, which are:

- stb - https://github.com/nothings/stb
- tinyformat - https://github.com/c42f/tinyformat
- glm - https://github.com/g-truc/glm
- imgui - https://github.com/ocornut/imgui
- Catch - https://github.com/philsquared/Catch
- glad - https://github.com/iondune/glad
- dirent - https://github.com/tronkko/dirent

The easiest way to do this is to navigate to the ``Dependencies/`` folder and run ``Clone.bat``.
Make sure that you have ``git`` in your path.

Next we need to get ``glfw``, the only binary dependency.
The easiest way to do this is using `vcpkg <https://github.com/Microsoft/vcpkg>`_.
Install that, then install the ``glfw:x64-windows`` triplet.



Linux
-----

These instructions are tailored for Ubuntu but the same principles should apply to most Linux distros (in terms of using your flavor of package manager to install binary deps, and using bash/cmake for the rest).

Thankfully all dependencies are available as packages or are header-only.

You will need ``g++`` and ``cmake`` for compilation.

.. highlight:: bash

::

   > sudo apt-get -y install g++ cmake


You'll also need to install GLFW3 and X.Org development packages.
On older distros a sufficiently recent version of GLFW is not available as a native package, so this is where instructions diverge depending on version.


Ubuntu 16.04
^^^^^^^^^^^^

Simply install the packages ``xorg-dev`` and ``libglfw3-dev``.

::

   > sudo apt-get -y install xorg-dev libglfw3-dev



Ubuntu 14.04
^^^^^^^^^^^^

The Ubuntu GLFW package is prohibitively out of date so we need to install a ppa to provide an up-to-date version.

::

   > sudo add-apt-repository ppa:keithw/glfw3 -y
   > sudo apt-get update

With that done we can now install all of our package-based dependencies::

::

   > sudo apt-get -y install xorg-dev libglfw3-dev

Next, install the header-only dependencies by running ``Clone.bash`` in the ``Dependencies/`` folder.

::

   > ./Clone.bash

With that we are ready to build ionEngine.
Make a directory called ``build`` and ``cd`` to it.
From that directory, run ``cmake``.

::

   > mkdir build
   > cd build
   > cmake ..
   > make



OS X
----

These instructions are for OS X 10.9.5 but should hopefully apply pretty universally.

First, make sure that you have both `Xcode <https://developer.apple.com/xcode/download/>`_ and `Homebrew <http://brew.sh/>`_ installed.

Next, install ``CMake`` and ``GLFW3`` through homebrew.

::

   > brew install cmake glew glfw3

Next, install the header-only dependencies by running ``Clone.bash`` in the ``Dependencies/`` folder.

::

   > ./Clone.bash

With that we are ready to build ionEngine.
Make a directory called ``build`` and ``cd`` to it.
From that directory, run ``cmake``.

::

   > mkdir build
   > cd build
   > cmake ..
   > make
