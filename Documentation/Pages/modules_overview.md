
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
   ionMath -> ionGraphics        [dir="back"];
   ionMath -> ionAnimation       [dir="back"];
   ionGraphics -> ionWindow      [dir="back"];
   ionWindow -> ionGraphicsGL    [dir="back"];
   ionWindow -> ionGUI           [dir="back"];
   ionGraphicsGL -> ionScene     [dir="back"];
   ionScene -> ionApplication    [dir="back"];
   ionGUI -> ionApplication      [dir="back"];
   ionApplication -> ionScience  [dir="back"];
}
@enddot


Overview
--------

[ionCore](@ref ionCore) is the basis for all other modules, a set of boilerplate functions, classes, and templates.

[ionMath](@ref ionCore) provides geometric primitives.

ionAnimation provides animation utilities such as spline classes.

ionWindow wraps GLFW and hooks up to ionFramework interfaces.

[ionGraphics](@ref ionGraphics) provides a interface to the graphics hardware that can be fulfilled by either DirectX or OpenGL.

[ionGraphicsGL](@ref ionGraphicsGL) implements the ionGraphics interfaces for OpenGL.

ionApplation provides a general framework for creating applications that manage assets and settings.

ionScience provides implementations of some common algorithms related to data visualization and other spatial queries.
