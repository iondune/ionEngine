![Logo](http://i.imgur.com/AMFY7t6.png)

ionEngine
=========

ionEngine is a C++ rendering engine that I wrote while a student at Cal Poly.
It was used for my [master's thesis](http://relicengine.com/) as well as some scientific visualization work.
Development of ionEngine has been discontinued.
I'm working on a Direct3D 11 port that is closed-source for the time being.

Overview
--------

ionEngine is made up of several libraries:

* **ionCore**: basic typedefs and boilerplate, some string and file helpers, standard library helpers
* **ionMath**: vector classes for 2, 3, and 4 dimensions. A custom “color” class that encapsulates a vec3 or vec4 with implicit conversions between float and byte colors.
  Other geometric primitives including rays, lines, boxes, triangles, etc.
* **ionWindow**: generic interface and helpers for operating system utilities, in particular window/context creation
* **ionGraphics**: generic and modular interface for any rendering API, in particular for OpenGL
* **ionScene**: scene interface that provides basic mesh loading, encapsulated renderable objects, and extensibility to add multipass rendering and other advanced functionality
* **ionScience**: algorithm implementations useful for various scientific applications, including long/lat classes, marching cubes, ear clipping, volumetric data rendering


Features
--------

ionEngine provides features through a large number of optional modules so
that only the necessary components need to be included in a project.

Features included in ionEngine or additional modules are:

* Component-entity based scene graph which is renderer-agnostic to maximize extendability
* Forward and deferred lighting systems implemented using OpenGL
* Bloom, SSAO, depth-of-field, and other post-processing effects
* Volumetric utilities such as a shader-based raycast volume renderer and marching cubes implementation
* GUI elements provided through [dear imgui](https://github.com/ocornut/imgui)
* Windowing and input provided through [GLFW](http://www.glfw.org/)


Distribution
------------

Source code is available on [GitHub](https://github.com/iondune/ionEngine)

Further information can be found at [ionengine.io](http://ionengine.io/).

Documentation (generated with [Doxygen](http://www.doxygen.nl/)) can be found at [docs.ionengine.io](http://docs.ionengine.io/).


License
-------

ionEngine is licensed under the [MIT license](http://opensource.org/licenses/MIT)
