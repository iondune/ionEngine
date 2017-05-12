
Dependencies
============

.. toctree::
   :maxdepth: 2


ionEngine depends on the following external libraries:

- **Header Only**

  - `stb <https://github.com/nothings/stb>`_

    - Image loading/writing, integer divide methods
    - Latest commit as of 5/11/2017: `c711058 <https://github.com/nothings/stb/commit/c7110588a4d24c4bb5155c184fbb77dd90b3116e>`_

  - `tinyformat <https://github.com/c42f/tinyformat>`_

    - Typesafe C++11 printf-style string formatting
    - `v2.1.0 <https://github.com/c42f/tinyformat/releases/tag/v2.1.0>`_

  - `GLM <https://github.com/g-truc/glm>`_

    - Vector and matrix math
    - `v0.9.8.4 <https://github.com/g-truc/glm/releases/tag/0.9.8.4>`_

  - `imgui <https://github.com/ocornut/imgui>`_

    - GUI components
    - Latest commit as of 5/11/2017: `df52f46 <https://github.com/ocornut/imgui/commit/df52f46b13891acf6298a6a783d7f024ccd9ab21>`_

  - `Catch <https://github.com/philsquared/Catch>`_

    - Unit testing (only necessary to build/run unit tests)
    - `v1.9.3 <https://github.com/philsquared/Catch/releases/tag/v1.9.3>`_

  - `GLAD <https://github.com/iondune/glad>`_

    - OpenGL extension loading

  - `tinyobjloader <https://github.com/syoyo/tinyobjloader>`_

    - Import ``.obj`` meshes
    - `v0.9.25 <https://github.com/syoyo/tinyobjloader/releases/tag/v0.9.25>`_

  - `simpleini <https://github.com/brofield/simpleini>`_

    - Read config from ``.ini`` files
    - Latest commit as of 5/11/2017: `03e27b2 <https://github.com/brofield/simpleini/commit/03e27b27901c8e12fef6daeddc18a9a3e217dea4>`_

  - `dirent <https://github.com/tronkko/dirent>`_

    - Directory navigation
    - (Windows Only)
    - Latest commit as of 5/11/2017: `8b1db50 <https://github.com/tronkko/dirent/commit/8b1db5092479a73d47eafd3de739b27e876e6bf3>`_

- **Binary**

  - `GLFW <http://www.glfw.org/>`_
    - Windowing and other OS functions
    - v3.2.1

For instructions on how to build and install, see the `installation page <installation.html>`_.
