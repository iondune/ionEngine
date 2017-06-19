
Modules                        {#modules_overview}
=======

Hierarchy
---------

The following graph shows the dependency hierarchy for ionEngine's default modules.

@dot
digraph deps {
   bgcolor=transparent;
   node [shape=box];
   ionCore [URL="moduleCore.html"];
   ionGraphicsGL [URL="moduleGL.html"];

   ionCore -> ionMath            [dir="back"];
   ionMath -> ionFramework       [dir="back"];
   ionFramework -> ionGraphics   [dir="back"];
   ionGraphics -> ionWindow      [dir="back"];
   ionWindow -> ionGraphicsGL    [dir="back"];
   ionWindow -> ionGUI           [dir="back"];
}
@enddot


Overview
--------

[ionCore](@ref ionCore) is the basis for all other modules, a set of boilerplate functions, classes, and templates.

ionFramework provides basic application structures including event listeners.

ionWindow wraps GLFW and hooks up to ionFramework interfaces.

ionGraphics provides a interface to the graphics hardware that can be fulfilled by either DirectX or OpenGL.

[ionGraphicsGL](@ref ionGraphicsGL) implements the ionGraphics interfaces for OpenGL.
