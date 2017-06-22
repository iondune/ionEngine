
Modules Overview               {#modules_overview}
================

Hierarchy
---------

The following graph shows the dependency hierarchy for ionEngine's default modules.

@dot
digraph deps {
   bgcolor=transparent;
   node [shape=box];
   ionCore [URL="\ref ionCore"];
   ionMath [URL="\ref ionMath"];
   ionGraphics [URL="\ref ionGraphics"];
   ionGraphicsGL [URL="\ref ionGraphicsGL"];

   ionCore -> ionMath            [dir="back"];
   ionMath -> ionFramework       [dir="back"];
   ionFramework -> ionGraphics   [dir="back"];
   ionGraphics -> ionWindow      [dir="back"];
   ionWindow -> ionGraphicsGL    [dir="back"];
   ionWindow -> ionGUI           [dir="back"];
   ionGraphicsGL -> ionScene     [dir="back"];
}
@enddot


Overview
--------

[ionCore](@ref ionCore) is the basis for all other modules, a set of boilerplate functions, classes, and templates.

[ionMath](@ref ionCore) is another basis for most modules, vector classes and geometric primitives.

ionFramework provides basic application structures including event listeners.

ionWindow wraps GLFW and hooks up to ionFramework interfaces.

[ionGraphics](@ref ionGraphics) provides a interface to the graphics hardware that can be fulfilled by either DirectX or OpenGL.

[ionGraphicsGL](@ref ionGraphicsGL) implements the ionGraphics interfaces for OpenGL.
