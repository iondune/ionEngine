
Modules
=======

.. graphviz::

   digraph deps {
      node [shape=box];
      ionCore [URL="moduleCore.html"];

      ionCore -> ionMath            [dir="back"];
      ionMath -> ionFramework       [dir="back"];
      ionFramework -> ionGraphics   [dir="back"];
      ionGraphics -> ionWindow      [dir="back"];
      ionWindow -> ionGraphicsGL    [dir="back"];
      ionWindow -> ionGUI           [dir="back"];
   }



ionCore
-------

`ionCore <moduleCore.html>`_ is the basis for all other modules, a set of boilerplate functions and templates. See
module documentation here: \ref moduleCore



ionFramework
------------

ionFramework provides basic application structures including event listeners.



ionWindow
---------

ionWindow wraps GLFW and hooks up to ionFramework interfaces.



ionGraphics
-----------
ionGraphics provides a interface to the graphics hardware that can be fulfilled by either DirectX or OpenGL.



ionGraphicsGL
-------------
`ionGraphicsGL <moduleGL.html>`_ implements the ionGraphics interfaces for OpenGL.
