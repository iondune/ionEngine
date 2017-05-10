
Modules
=======

.. graphviz::
   :align: center

   digraph deps {
      bgcolor=transparent;
      node [shape=box];
      ionCore [URL="moduleCore.html"];

      ionCore -> ionMath            [dir="back"];
      ionMath -> ionFramework       [dir="back"];
      ionFramework -> ionGraphics   [dir="back"];
      ionGraphics -> ionWindow      [dir="back"];
      ionWindow -> ionGraphicsGL    [dir="back"];
      ionWindow -> ionGUI           [dir="back"];
   }


Overview
--------

`ionCore <moduleCore.html>`_ is the basis for all other modules, a set of boilerplate functions, classes, and templates.

ionFramework provides basic application structures including event listeners.

ionWindow wraps GLFW and hooks up to ionFramework interfaces.

ionGraphics provides a interface to the graphics hardware that can be fulfilled by either DirectX or OpenGL.

`ionGraphicsGL <moduleGL.html>`_ implements the ionGraphics interfaces for OpenGL.


Further Reading
---------------

.. toctree::
   :maxdepth: 1


   moduleCore
   moduleGL
