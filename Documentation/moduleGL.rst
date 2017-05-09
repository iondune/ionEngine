
ionGL
=====

Overview
--------

ionGL is an object oriented C++ interface to OpenGL that offers a few benefits over the
traditional state-machine C interface:

- Removal of as much global state and dynamic scope as possible.
- Clean, readable syntax.
- Minimal interface that promotes best-practice, modern OpenGL programs.
- Prevent global namespace pollution by GL.h inclusion.


Documentation
-------------

The ionGL Module is contained in the ion::GL namespace. An example of basic usage can be found in TestGL/Main.cpp
and an example of more advanced usage can be found in TestAsset/Main.cpp.

Example
^^^^^^^

Consider the below example which shows the initialization of a VAO with a position VBO and an index buffer::

   // Initiale a vertex buffer object
   ion::GL::VertexBuffer * vbo = new ion::GL::VertexBuffer();
   vbo->Data(Vertices, 2);

   // Initial an index buffer object
   ion::GL::IndexBuffer * ibo = new ion::GL::IndexBuffer();
   ibo->Data(Indices);

   // Bind the vertex buffer and index buffer onto a new vertex array object
   ion::GL::VertexArray * vao = new ion::GL::VertexArray();
   vao->SetIndexBuffer(ibo);
   vao->BindAttribute(0, vbo);

The next example shows how to initialize a shader program with Vertex and Fragment stages::

   // Create a vertex shader and compile from source
   ion::GL::VertexShader * vert = new ion::GL::VertexShader();
   vert->Source(VertexShaderSource);

   if (! vert->Compile())
       std::cerr << "Failed to compile vertex shader!" << std::endl << vert->InfoLog() << std::endl;

   // Create a fragment shader and compile from source
   ion::GL::FragmentShader * frag = new ion::GL::FragmentShader();
   frag->Source(FragmentShaderSource);

   if (! frag->Compile())
       std::cerr << "Failed to compile vertex shader!" << std::endl << frag->InfoLog() << std::endl;

   // Link the vertex and fragment shader stages into a new shader program object
   ion::GL::Program * shader = new ion::GL::Program();
   shader->AttachShader(vert);
   shader->AttachShader(frag);
   shader->Link();
   shader->BindAttributeLocation(0, "position");

Finally, the below example shows how to implement a simple draw loop::

   // Clear the color and depth buffers
   ion::GL::Context::Clear({ EBuffer::Color, EBuffer::Depth });

   // Use the shader we compiled
   shader->Use();

   // Draw the vertex array we created
   vao->Draw();

   // End the draw stage
   ion::GL::Program::End();
