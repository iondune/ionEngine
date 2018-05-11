![Logo](http://i.imgur.com/AMFY7t6.png)

ionEngine
=========

| Branch | Status |
|--------|--------------|
| [![release](https://img.shields.io/badge/branch-release-38C7B6.svg)](https://github.com/iondune/ionEngine/releases) | [![Build Status](https://travis-ci.org/iondune/ionEngine.svg?branch=release)](https://travis-ci.org/iondune/ionEngine) [![Build status](https://ci.appveyor.com/api/projects/status/p8wakf96tk3qrm2x/branch/release?svg=true)](https://ci.appveyor.com/project/iondune/ionengine/branch/release) [![GitHub release](https://img.shields.io/github/release/iondune/ionEngine.svg)](https://github.com/iondune/ionEngine/releases) |
| [![master](https://img.shields.io/badge/branch-master-B2A0EB.svg)](https://github.com/iondune/ionEngine) | [![Build Status](https://travis-ci.org/iondune/ionEngine.svg?branch=master)](https://travis-ci.org/iondune/ionEngine) [![Build status](https://ci.appveyor.com/api/projects/status/p8wakf96tk3qrm2x?svg=true)](https://ci.appveyor.com/project/iondune/ionengine) [![GitHub](https://img.shields.io/badge/pre--release-v0.4.5-blue.svg)](https://github.com/iondune/ionEngine/commits/master) |

Overview
--------

ionEngine is a C++ application framework designed to aid in the creation of high-performance rendering applications.
It is modular and generic, designed for use in both game engines and scientific data visualization.
The primary goal of ionEngine is to improve the DX (Developer Experience) of writing graphics programs, from small educational examples to full production game engines.

ionEngine includes many modular components, including:

* **ionCore**: basic typedefs and boilerplate, some string and file helpers, standard library helpers
* **ionMath**: vector classes for 2, 3, and 4 dimensions. A custom “color” class that encapsulates a vec3 or vec4 with implicit conversions between float and byte colors.
  Other geometric primitives including rays, lines, boxes, triangles, etc.
* **ionWindow**: generic interface and helpers for operating system utilities, in particular window/context creation
* **ionGraphics**: generic and modular interface for any rendering API, in particular for OpenGL
* **ionScene**: scene interface that provides basic mesh loading, encapsulated renderable objects, and extensibility to add multipass rendering and other advanced functionality
* **ionScience**: algorithm implementations useful for various scientific applications, including long/lat classes, marching cubes, ear clipping, volumetric data rendering


:pencil: Features
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


:package: Distribution
------------

Source code distributions are available at [Bitbucket](https://bitbucket.org/iondune/ionengine) and [GitHub](https://github.com/iondune/ionEngine)

Further information can be found at [ionengine.io](http://ionengine.io/).

Documentation can be found at [docs.ionengine.io](http://docs.ionengine.io/).


:hammer: License
-------

The ionEngine is licensed under the [MIT license](http://opensource.org/licenses/MIT)
