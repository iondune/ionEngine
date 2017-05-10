
Dependencies
============

.. toctree::
   :maxdepth: 2


ionEngine depends on the following external libraries:

- **Header Only**

  - `stb <https://github.com/nothings/stb>`_
    - Image loading/writing, integer divide methods
  - `tinyformat <https://github.com/c42f/tinyformat>`_
    - Typesafe C++11 printf-style string formatting
  - `GLM <https://github.com/g-truc/glm>`_
    - Vector and matrix math
  - `imgui <https://github.com/ocornut/imgui>`_
    - GUI components
  - `Catch <https://github.com/philsquared/Catch>`_
    - Unit testing (only necessary to build/run unit tests)
  - `GLAD <https://github.com/iondune/glad>`_
    - OpenGL extension loading
  - `dirent <https://github.com/tronkko/dirent>`_
    - Directory navigation
    - Only on windows (UNIX-variants have it by default)

- **Binary**

  - `GLFW <http://www.glfw.org/>`_
    - Windowing and other OS functions

For instructions on how to build and install, see the `installation page <installation.html>`_.
