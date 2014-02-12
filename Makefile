CXX=g++
INCLUDE=-I ~/484/ionEngine \
	-I ~/484/ionEngine/ionCore \
	-I ~/484/ionEngine/ionMath \
	-I ~/484/deps/glm/include \
	-I ~/484/deps/glew/include \
	-I ~/484/deps/glfw/include \
	-I ~/484/deps/stb_image/include \
	-I ~/484/deps/freetype/include/freetype
CXXFLAGS=$(INCLUDE) -g -std=gnu++0x
LDFLAGS=-lGL -lGLU -lXrandr \
	-L ~/484/deps/lib \
	-lfreetype -lGLEW -lglfw3

SRCS=$(shell find . -name "*.cpp")
OBJS=$(subst .cpp,.o,$(SRCS))

all: UCT libionEngine.a

UCT: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

libionEngine.a: $(filter-out UtilityCompileTest/Main.o,$(OBJS))
	ar rc $@ $^

clean:
	rm -f $(OBJS) libionEngine.a

remake: clean all

depend:
	@echo Regenerating local dependencies.
	@makedepend -Y $(SRCS) $(HDRS) $(INCLUDE) -s "# Dependencies" > /dev/null 2>&1
	@rm Makefile.bak


# Dependencies

./ionGL/Texture.o: ./ionGL/Texture.h /home/idunn01/484/ionEngine/ionCore.h
./ionGL/Texture.o: ionCore/ionCore.h ionConfig.h ionCore/ionComparison.h
./ionGL/Texture.o: ionCore/ionTypes.h ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionGL/Texture.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionGL/Texture.o: ionCore/ionUtils.h /home/idunn01/484/ionEngine/ionMath.h
./ionGL/Texture.o: ionMath/ionMath.h ionMath/SVector.h ionMath/SColor.h
./ionGL/Texture.o: ionMath/SVector2.h ionMath/Utilities.h ionMath/Constants.h
./ionGL/Texture.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionGL/Texture.o: ionMath/SVector3.h
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionGL/Texture.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionGL/Texture.o: ionMath/SBoundingBox3.h ionMath/SLine3.h ionMath/SPlane3.h
./ionGL/Texture.o: ionMath/SRect2.h ionMath/STriangle2.h ionMath/STriangle3.h
./ionGL/Texture.o: ionMath/STransformation3.h
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionGL/Texture.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionGL/Utilities.o: ionMath/Utilities.h
./ionGL/Utilities.o: /home/idunn01/484/ionEngine/ionCore.h ionCore/ionCore.h
./ionGL/Utilities.o: ionConfig.h ionCore/ionComparison.h ionCore/ionTypes.h
./ionGL/Utilities.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionGL/Utilities.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionGL/Utilities.o: ionCore/ionUtils.h ionMath/Constants.h
./ionGL/Utilities.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionGL/Utilities.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionGL/Buffer.o: ./ionGL/Buffer.h /home/idunn01/484/ionEngine/ionCore.h
./ionGL/Buffer.o: ionCore/ionCore.h ionConfig.h ionCore/ionComparison.h
./ionGL/Buffer.o: ionCore/ionTypes.h ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionGL/Buffer.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionGL/Buffer.o: ionCore/ionUtils.h /home/idunn01/484/ionEngine/ionMath.h
./ionGL/Buffer.o: ionMath/ionMath.h ionMath/SVector.h ionMath/SColor.h
./ionGL/Buffer.o: ionMath/SVector2.h ionMath/Utilities.h ionMath/Constants.h
./ionGL/Buffer.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionGL/Buffer.o: ionMath/SVector3.h
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionGL/Buffer.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionGL/Buffer.o: ionMath/SBoundingBox3.h ionMath/SLine3.h ionMath/SPlane3.h
./ionGL/Buffer.o: ionMath/SRect2.h ionMath/STriangle2.h ionMath/STriangle3.h
./ionGL/Buffer.o: ionMath/STransformation3.h
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionGL/Buffer.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionGL/VertexArray.o: ./ionGL/VertexArray.h
./ionGL/VertexArray.o: /home/idunn01/484/ionEngine/ionCore.h
./ionGL/VertexArray.o: ionCore/ionCore.h ionConfig.h ionCore/ionComparison.h
./ionGL/VertexArray.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionGL/VertexArray.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionGL/VertexArray.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionGL/VertexArray.o: /home/idunn01/484/ionEngine/ionMath.h
./ionGL/VertexArray.o: ionMath/ionMath.h ionMath/SVector.h ionMath/SColor.h
./ionGL/VertexArray.o: ionMath/SVector2.h ionMath/Utilities.h
./ionGL/VertexArray.o: ionMath/Constants.h
./ionGL/VertexArray.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionGL/VertexArray.o: ionMath/SVector3.h
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionGL/VertexArray.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionGL/VertexArray.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionGL/VertexArray.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionGL/VertexArray.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionGL/VertexArray.o: ionMath/STransformation3.h
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionGL/VertexArray.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionGL/VertexArray.o: ./ionGL/Buffer.h
./ionGL/VertexArray.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionGL/Shader.o: ./ionGL/Shader.h /home/idunn01/484/ionEngine/ionCore.h
./ionGL/Shader.o: ionCore/ionCore.h ionConfig.h ionCore/ionComparison.h
./ionGL/Shader.o: ionCore/ionTypes.h ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionGL/Shader.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionGL/Shader.o: ionCore/ionUtils.h /home/idunn01/484/ionEngine/ionMath.h
./ionGL/Shader.o: ionMath/ionMath.h ionMath/SVector.h ionMath/SColor.h
./ionGL/Shader.o: ionMath/SVector2.h ionMath/Utilities.h ionMath/Constants.h
./ionGL/Shader.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionGL/Shader.o: ionMath/SVector3.h
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionGL/Shader.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionGL/Shader.o: ionMath/SBoundingBox3.h ionMath/SLine3.h ionMath/SPlane3.h
./ionGL/Shader.o: ionMath/SRect2.h ionMath/STriangle2.h ionMath/STriangle3.h
./ionGL/Shader.o: ionMath/STransformation3.h
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionGL/Shader.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionGL/Program.o: ./ionGL/Program.h /home/idunn01/484/ionEngine/ionCore.h
./ionGL/Program.o: ionCore/ionCore.h ionConfig.h ionCore/ionComparison.h
./ionGL/Program.o: ionCore/ionTypes.h ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionGL/Program.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionGL/Program.o: ionCore/ionUtils.h /home/idunn01/484/ionEngine/ionMath.h
./ionGL/Program.o: ionMath/ionMath.h ionMath/SVector.h ionMath/SColor.h
./ionGL/Program.o: ionMath/SVector2.h ionMath/Utilities.h ionMath/Constants.h
./ionGL/Program.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionGL/Program.o: ionMath/SVector3.h
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionGL/Program.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionGL/Program.o: ionMath/SBoundingBox3.h ionMath/SLine3.h ionMath/SPlane3.h
./ionGL/Program.o: ionMath/SRect2.h ionMath/STriangle2.h ionMath/STriangle3.h
./ionGL/Program.o: ionMath/STransformation3.h
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionGL/Program.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionGL/Program.o: ./ionGL/Buffer.h ./ionGL/Shader.h
./ionGL/Program.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionEngine.h
./UtilityCompileTest/Build.o: ionConfig.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionCore.h
./UtilityCompileTest/Build.o: ionCore/ionCore.h ionCore/ionComparison.h
./UtilityCompileTest/Build.o: ionCore/ionTypes.h ionCore/ionRand.h
./UtilityCompileTest/Build.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./UtilityCompileTest/Build.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./UtilityCompileTest/Build.o: ionAnimation.h ionAnimation/ionAnimation.h
./UtilityCompileTest/Build.o: ionAnimation/IPath.h
./UtilityCompileTest/Build.o: ionAnimation/IInterpolator.h
./UtilityCompileTest/Build.o: ionAnimation/Interpolators.h
./UtilityCompileTest/Build.o: ionAnimation/SPathNode.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionMath.h
./UtilityCompileTest/Build.o: ionMath/ionMath.h ionMath/SVector.h
./UtilityCompileTest/Build.o: ionMath/SColor.h ionMath/SVector2.h
./UtilityCompileTest/Build.o: ionMath/Utilities.h ionMath/Constants.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./UtilityCompileTest/Build.o: ionMath/SVector3.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./UtilityCompileTest/Build.o: ionMath/SVector4.h ionMath/SMatrix4.h
./UtilityCompileTest/Build.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./UtilityCompileTest/Build.o: ionMath/SPlane3.h ionMath/SRect2.h
./UtilityCompileTest/Build.o: ionMath/STriangle2.h ionMath/STriangle3.h
./UtilityCompileTest/Build.o: ionMath/STransformation3.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./UtilityCompileTest/Build.o: ionAnimation/CPath.h ionFramework.h
./UtilityCompileTest/Build.o: ionFramework/ionFramework.h
./UtilityCompileTest/Build.o: ionFramework/SEvent.h ionFramework/SEventData.h
./UtilityCompileTest/Build.o: ionFramework/IEventListener.h
./UtilityCompileTest/Build.o: ionFramework/CApplicationContextObject.h
./UtilityCompileTest/Build.o: ionFramework/CApplication.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionScene.h
./UtilityCompileTest/Build.o: ionScene/ionScene.h ionScene/CMesh.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./UtilityCompileTest/Build.o: ionScene/SVertex.h ionScene/CBufferObject.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionGL.h
./UtilityCompileTest/Build.o: ionGL/ionGL.h ./ionGL/Buffer.h
./UtilityCompileTest/Build.o: ./ionGL/Program.h ./ionGL/Shader.h
./UtilityCompileTest/Build.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./UtilityCompileTest/Build.o: ionScene/CRenderable.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./UtilityCompileTest/Build.o: ionScene/ISceneObject.Enumerations.h
./UtilityCompileTest/Build.o: ionScene/IRenderPass.h ionScene/SUniform.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./UtilityCompileTest/Build.o: ionScene/CShaderContext.h ionScene/CShader.h
./UtilityCompileTest/Build.o: ionScene/CTexture.h ionScene/CImage.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./UtilityCompileTest/Build.o: ionScene/IRenderTarget.h ionScene/SAttribute.h
./UtilityCompileTest/Build.o: ionScene/CMeshLoader.h
./UtilityCompileTest/Build.o: ionScene/CMeshSceneObject.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./UtilityCompileTest/Build.o: ionScene/CSceneObject.h ionScene/ISceneObject.h
./UtilityCompileTest/Build.o: ionScene/CInstanceSceneObject.h
./UtilityCompileTest/Build.o: ionScene/CShaderLoader.h
./UtilityCompileTest/Build.o: ionScene/CImageLoader.h
./UtilityCompileTest/Build.o: ionScene/CSceneManager.h
./UtilityCompileTest/Build.o: ionScene/CFrameBufferObject.h
./UtilityCompileTest/Build.o: ionScene/CRenderBufferObject.h
./UtilityCompileTest/Build.o: ionScene/CSceneEffectManager.h
./UtilityCompileTest/Build.o: ionScene/CPerspectiveCameraSceneObject.h
./UtilityCompileTest/Build.o: ionScene/CCameraSceneObject.h
./UtilityCompileTest/Build.o: ionScene/ICameraSceneObject.h ionScene/CScene.h
./UtilityCompileTest/Build.o: ionScene/IScene.h ionScene/CLightSceneObject.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionMath/SLine3.h
./UtilityCompileTest/Build.o: ionScene/CDefaultColorRenderPass.h
./UtilityCompileTest/Build.o: ionScene/CMultiOutRenderPass.h
./UtilityCompileTest/Build.o: ionScene/CDeferredShadingManager.h
./UtilityCompileTest/Build.o: ionScene/CPointLightSceneObject.h
./UtilityCompileTest/Build.o: ionScene/CDirectionalLightSceneObject.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionWindow.h
./UtilityCompileTest/Build.o: ionWindow/ionWindow.h ionWindow/EKey.h
./UtilityCompileTest/Build.o: ionWindow/SKeyboardEvent.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionFramework/SEvent.h
./UtilityCompileTest/Build.o: ionWindow/SMouseEvent.h
./UtilityCompileTest/Build.o: ionWindow/SWindowResizedEvent.h
./UtilityCompileTest/Build.o: ionWindow/CWindow.h ionWindow/CWindowManager.h
./UtilityCompileTest/Build.o: ionWindow/CGamePad.h ionWindow/EGamePadButton.h
./UtilityCompileTest/Build.o: ionFramework/CStateManager.h
./UtilityCompileTest/Build.o: ionFramework/IState.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionScene/CSceneManager.h
./UtilityCompileTest/Build.o: ionFramework/CContextObject.h
./UtilityCompileTest/Build.o: ionFramework/CContextState.h
./UtilityCompileTest/Build.o: ionFramework/CCameraControl.h
./UtilityCompileTest/Build.o: ionFramework/CFadeOutState.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionScene/CFrameBufferObject.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionScene/CTexture.h
./UtilityCompileTest/Build.o: ionGUI.h ionGUI/ionGUI.h ionGUI/FreeType.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/ft2build.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/config/ftheader.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/freetype.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/config/ftconfig.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/config/ftoption.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/config/ftstdlib.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/fttypes.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/config/ftconfig.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/ftsystem.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/ftimage.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/fterrors.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/ftmoderr.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/fterrdef.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/ftglyph.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/freetype.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/ftoutln.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/freetype/include/freetype/fttrigon.h
./UtilityCompileTest/Build.o: ionScience.h ionScience/ionScience.h
./UtilityCompileTest/Build.o: ionScience/CColorTable.h
./UtilityCompileTest/Build.o: ionScience/IColorMapper.h
./UtilityCompileTest/Build.o: ionScience/IDataRecord.h ionScience/IDatabase.h
./UtilityCompileTest/Build.o: ionScience/SRange.h ionScience/STable.h
./UtilityCompileTest/Build.o: ionScience/SVolumeDatabase.h
./UtilityCompileTest/Build.o: ionScience/SVolume.h ionScience/Interpolation.h
./UtilityCompileTest/Build.o: ionScience/CKDTree.h ionScience/MarchingCubes.h
./UtilityCompileTest/Build.o: /home/idunn01/484/ionEngine/ionScene/CMesh.h
./UtilityCompileTest/Build.o: ionScience/CPrintProgressBar.h
./UtilityCompileTest/Build.o: ionScience/IProgressBar.h
./UtilityCompileTest/Build.o: ionScience/SLongitudeLatitude.h
./UtilityCompileTest/Build.o: /home/idunn01/484/deps/glfw/include/GLFW/glfw3.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionFramework/CApplication.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionCore.h ionCore/ionCore.h
./ionGUI/FreeType.o: ionConfig.h ionCore/ionComparison.h ionCore/ionTypes.h
./ionGUI/FreeType.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionGUI/FreeType.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionGUI/FreeType.o: ionCore/ionUtils.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionScene.h
./ionGUI/FreeType.o: ionScene/ionScene.h ionScene/CMesh.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionGUI/FreeType.o: ionMath/SVector3.h ionMath/SVector.h ionMath/SVector2.h
./ionGUI/FreeType.o: ionMath/Utilities.h ionMath/Constants.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionGUI/FreeType.o: ionMath/SLine3.h ionScene/SVertex.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionMath.h ionMath/ionMath.h
./ionGUI/FreeType.o: ionMath/SColor.h ionMath/SVector4.h ionMath/SMatrix4.h
./ionGUI/FreeType.o: ionMath/SBoundingBox3.h ionMath/SPlane3.h
./ionGUI/FreeType.o: ionMath/SRect2.h ionMath/STriangle2.h
./ionGUI/FreeType.o: ionMath/STriangle3.h ionMath/STransformation3.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionGUI/FreeType.o: ionScene/CBufferObject.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionGUI/FreeType.o: ./ionGL/Buffer.h ./ionGL/Program.h ./ionGL/Shader.h
./ionGUI/FreeType.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionGUI/FreeType.o: ionScene/CRenderable.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionGUI/FreeType.o: ionScene/ISceneObject.Enumerations.h
./ionGUI/FreeType.o: ionScene/IRenderPass.h ionScene/SUniform.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionGUI/FreeType.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionGUI/FreeType.o: ionScene/CShaderContext.h ionScene/CShader.h
./ionGUI/FreeType.o: ionScene/CTexture.h ionScene/CImage.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionGUI/FreeType.o: ionScene/IRenderTarget.h ionScene/SAttribute.h
./ionGUI/FreeType.o: ionScene/CMeshLoader.h ionScene/CMeshSceneObject.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./ionGUI/FreeType.o: ionScene/CSceneObject.h ionScene/ISceneObject.h
./ionGUI/FreeType.o: ionScene/CInstanceSceneObject.h ionScene/CShaderLoader.h
./ionGUI/FreeType.o: ionScene/CImageLoader.h ionScene/CSceneManager.h
./ionGUI/FreeType.o: ionScene/CFrameBufferObject.h
./ionGUI/FreeType.o: ionScene/CRenderBufferObject.h
./ionGUI/FreeType.o: ionScene/CSceneEffectManager.h
./ionGUI/FreeType.o: ionScene/CPerspectiveCameraSceneObject.h
./ionGUI/FreeType.o: ionScene/CCameraSceneObject.h
./ionGUI/FreeType.o: ionScene/ICameraSceneObject.h ionScene/CScene.h
./ionGUI/FreeType.o: ionScene/IScene.h ionScene/CLightSceneObject.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionMath/SLine3.h
./ionGUI/FreeType.o: ionScene/CDefaultColorRenderPass.h
./ionGUI/FreeType.o: ionScene/CMultiOutRenderPass.h
./ionGUI/FreeType.o: ionScene/CDeferredShadingManager.h
./ionGUI/FreeType.o: ionScene/CPointLightSceneObject.h
./ionGUI/FreeType.o: ionScene/CDirectionalLightSceneObject.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionWindow.h
./ionGUI/FreeType.o: ionWindow/ionWindow.h ionWindow/EKey.h
./ionGUI/FreeType.o: ionWindow/SKeyboardEvent.h
./ionGUI/FreeType.o: /home/idunn01/484/ionEngine/ionFramework/SEvent.h
./ionGUI/FreeType.o: ionFramework/SEventData.h ionFramework/IEventListener.h
./ionGUI/FreeType.o: ionWindow/SMouseEvent.h ionWindow/SWindowResizedEvent.h
./ionGUI/FreeType.o: ionWindow/CWindow.h ionWindow/CWindowManager.h
./ionGUI/FreeType.o: ionWindow/CGamePad.h ionWindow/EGamePadButton.h
./ionGUI/FreeType.o: ionFramework/CStateManager.h ionFramework/IState.h
./ionGUI/FreeType.o: ionGUI/FreeType.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/ft2build.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/config/ftheader.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/freetype.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/config/ftconfig.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/config/ftoption.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/config/ftstdlib.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/fttypes.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/config/ftconfig.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/ftsystem.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/ftimage.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/fterrors.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/ftmoderr.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/fterrdef.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/ftglyph.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/freetype.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/ftoutln.h
./ionGUI/FreeType.o: /home/idunn01/484/deps/freetype/include/freetype/fttrigon.h
./ionScene/CImageLoader.o: ionScene/CImageLoader.h ionScene/CImage.h
./ionScene/CImageLoader.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CImageLoader.o: ionMath/SVector.h
./ionScene/CImageLoader.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CImageLoader.o: ionCore/ionCore.h ionConfig.h
./ionScene/CImageLoader.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CImageLoader.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CImageLoader.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CImageLoader.o: ionCore/ionUtils.h ionMath/Utilities.h
./ionScene/CImageLoader.o: ionMath/Constants.h
./ionScene/CImageLoader.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CImageLoader.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CImageLoader.o: ionScene/CTexture.h
./ionScene/CImageLoader.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CImageLoader.o: ionMath/ionMath.h ionMath/SColor.h
./ionScene/CImageLoader.o: ionMath/SVector2.h ionMath/SVector3.h
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CImageLoader.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CImageLoader.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CImageLoader.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CImageLoader.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CImageLoader.o: ionMath/STransformation3.h
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CImageLoader.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CImageLoader.o: ionScene/IRenderTarget.h
./ionScene/CCameraSceneObject.o: ionScene/CCameraSceneObject.h ionConfig.h
./ionScene/CCameraSceneObject.o: ionScene/ICameraSceneObject.h
./ionScene/CCameraSceneObject.o: ionScene/ISceneObject.h
./ionScene/CCameraSceneObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CCameraSceneObject.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CCameraSceneObject.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CCameraSceneObject.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CCameraSceneObject.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CCameraSceneObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CCameraSceneObject.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CCameraSceneObject.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CCameraSceneObject.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CCameraSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CCameraSceneObject.o: ionMath/SVector3.h
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CCameraSceneObject.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CCameraSceneObject.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CCameraSceneObject.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CCameraSceneObject.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CCameraSceneObject.o: ionMath/STransformation3.h
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CCameraSceneObject.o: ionScene/CBufferObject.h
./ionScene/CCameraSceneObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CCameraSceneObject.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CCameraSceneObject.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CCameraSceneObject.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CCameraSceneObject.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CCameraSceneObject.o: ionScene/CShader.h ionScene/CTexture.h
./ionScene/CCameraSceneObject.o: ionScene/CImage.h
./ionScene/CCameraSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CCameraSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CCameraSceneObject.o: ionScene/IRenderTarget.h
./ionScene/CCameraSceneObject.o: ionScene/CShaderContext.h
./ionScene/CCameraSceneObject.o: ionScene/IRenderPass.h
./ionScene/CCameraSceneObject.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.ShaderVariables.o: ionScene/CScene.h ionConfig.h
./ionScene/CScene.ShaderVariables.o: ionScene/IScene.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CScene.ShaderVariables.o: ionScene/ICameraSceneObject.h
./ionScene/CScene.ShaderVariables.o: ionScene/ISceneObject.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CScene.ShaderVariables.o: ionCore/ionCore.h
./ionScene/CScene.ShaderVariables.o: ionCore/ionComparison.h
./ionScene/CScene.ShaderVariables.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CScene.ShaderVariables.o: ionCore/ionSmartPtr.h
./ionScene/CScene.ShaderVariables.o: ionCore/ionThread.h
./ionScene/CScene.ShaderVariables.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CScene.ShaderVariables.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CScene.ShaderVariables.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CScene.ShaderVariables.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CScene.ShaderVariables.o: ionMath/SVector3.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CScene.ShaderVariables.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CScene.ShaderVariables.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CScene.ShaderVariables.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CScene.ShaderVariables.o: ionMath/STriangle2.h
./ionScene/CScene.ShaderVariables.o: ionMath/STriangle3.h
./ionScene/CScene.ShaderVariables.o: ionMath/STransformation3.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CScene.ShaderVariables.o: ionScene/CBufferObject.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CScene.ShaderVariables.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CScene.ShaderVariables.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CScene.ShaderVariables.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CScene.ShaderVariables.o: ionScene/CShader.h ionScene/CTexture.h
./ionScene/CScene.ShaderVariables.o: ionScene/CImage.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CScene.ShaderVariables.o: ionScene/IRenderTarget.h
./ionScene/CScene.ShaderVariables.o: ionScene/CShaderContext.h
./ionScene/CScene.ShaderVariables.o: ionScene/IRenderPass.h
./ionScene/CScene.ShaderVariables.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.ShaderVariables.o: ionScene/CLightSceneObject.h
./ionScene/CScene.ShaderVariables.o: ionScene/SUniform.h
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CScene.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CScene.ShaderVariables.o: ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.ShaderVariables.o: ionScene/CCameraSceneObject.h
./ionScene/CScene.ShaderVariables.o: ionScene/SAttribute.h
./ionScene/ISceneObject.o: ionScene/ISceneObject.h
./ionScene/ISceneObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/ISceneObject.o: ionCore/ionCore.h ionConfig.h
./ionScene/ISceneObject.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/ISceneObject.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/ISceneObject.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/ISceneObject.o: ionCore/ionUtils.h
./ionScene/ISceneObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/ISceneObject.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/ISceneObject.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/ISceneObject.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/ISceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/ISceneObject.o: ionMath/SVector3.h
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/ISceneObject.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/ISceneObject.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/ISceneObject.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/ISceneObject.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/ISceneObject.o: ionMath/STransformation3.h
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/ISceneObject.o: ionScene/CBufferObject.h
./ionScene/ISceneObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/ISceneObject.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/ISceneObject.o: ./ionGL/Buffer.h ./ionGL/Program.h
./ionScene/ISceneObject.o: ./ionGL/Shader.h ./ionGL/Texture.h
./ionScene/ISceneObject.o: ./ionGL/VertexArray.h ionScene/CShader.h
./ionScene/ISceneObject.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/ISceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/ISceneObject.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/ISceneObject.o: ionScene/IRenderTarget.h ionScene/CShaderContext.h
./ionScene/ISceneObject.o: ionScene/IRenderPass.h
./ionScene/ISceneObject.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneManager.o: ionScene/CSceneManager.h ionScene/CSceneObject.h
./ionScene/CSceneManager.o: ionScene/ISceneObject.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CSceneManager.o: ionCore/ionCore.h ionConfig.h
./ionScene/CSceneManager.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CSceneManager.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CSceneManager.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CSceneManager.o: ionCore/ionUtils.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CSceneManager.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CSceneManager.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CSceneManager.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CSceneManager.o: ionMath/SVector3.h
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CSceneManager.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CSceneManager.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CSceneManager.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CSceneManager.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CSceneManager.o: ionMath/STransformation3.h
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CSceneManager.o: ionScene/CBufferObject.h
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/CSceneManager.o: ./ionGL/Buffer.h ./ionGL/Program.h
./ionScene/CSceneManager.o: ./ionGL/Shader.h ./ionGL/Texture.h
./ionScene/CSceneManager.o: ./ionGL/VertexArray.h ionScene/CShader.h
./ionScene/CSceneManager.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CSceneManager.o: ionScene/IRenderTarget.h
./ionScene/CSceneManager.o: ionScene/CShaderContext.h ionScene/IRenderPass.h
./ionScene/CSceneManager.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneManager.o: ionScene/CRenderable.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CSceneManager.o: ionScene/SUniform.h
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CSceneManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CSceneManager.o: ionScene/SAttribute.h ionScene/CMeshSceneObject.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./ionScene/CSceneManager.o: ionScene/CMesh.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionScene/CSceneManager.o: ionScene/SVertex.h ionScene/CFrameBufferObject.h
./ionScene/CSceneManager.o: ionScene/CRenderBufferObject.h
./ionScene/CSceneManager.o: ionScene/CSceneEffectManager.h
./ionScene/CSceneManager.o: ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CSceneManager.o: ionScene/CCameraSceneObject.h
./ionScene/CSceneManager.o: ionScene/ICameraSceneObject.h ionScene/CScene.h
./ionScene/CSceneManager.o: ionScene/IScene.h ionScene/CLightSceneObject.h
./ionScene/CSceneManager.o: /home/idunn01/484/ionEngine/ionMath/SLine3.h
./ionScene/CSceneManager.o: ionScene/CDefaultColorRenderPass.h
./ionScene/CSceneManager.o: ionScene/CMultiOutRenderPass.h
./ionScene/CSceneManager.o: ionScene/CShaderLoader.h ionScene/CMeshLoader.h
./ionScene/CSceneManager.o: ionScene/CImageLoader.h
./ionScene/CSceneManager.o: ionScene/CDeferredShadingManager.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/CSceneObject.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/ISceneObject.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CSceneObject.ShaderManagement.o: ionCore/ionCore.h ionConfig.h
./ionScene/CSceneObject.ShaderManagement.o: ionCore/ionComparison.h
./ionScene/CSceneObject.ShaderManagement.o: ionCore/ionTypes.h
./ionScene/CSceneObject.ShaderManagement.o: ionCore/ionRand.h
./ionScene/CSceneObject.ShaderManagement.o: ionCore/ionSmartPtr.h
./ionScene/CSceneObject.ShaderManagement.o: ionCore/ionThread.h
./ionScene/CSceneObject.ShaderManagement.o: ionCore/ionTreeNode.h
./ionScene/CSceneObject.ShaderManagement.o: ionCore/ionUtils.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/ionMath.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/SVector.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/SColor.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/SVector2.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/Utilities.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/Constants.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/SVector3.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CSceneObject.ShaderManagement.o: ionMath/SVector4.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/SMatrix4.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/SBoundingBox3.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/SLine3.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/SPlane3.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/SRect2.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/STriangle2.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/STriangle3.h
./ionScene/CSceneObject.ShaderManagement.o: ionMath/STransformation3.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CSceneObject.ShaderManagement.o: ionScene/CBufferObject.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CSceneObject.ShaderManagement.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionGL/Program.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionGL/Shader.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionGL/Texture.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionGL/VertexArray.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/CShader.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/CTexture.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/CImage.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/IRenderTarget.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/CShaderContext.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/IRenderPass.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/CRenderable.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/SUniform.h
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CSceneObject.ShaderManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CSceneObject.ShaderManagement.o: ionScene/SAttribute.h
./ionScene/CSceneObject.ShaderManagement.o: ionScene/CShaderLoader.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/CSceneObject.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/ISceneObject.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CSceneObject.ContextManagement.o: ionCore/ionCore.h ionConfig.h
./ionScene/CSceneObject.ContextManagement.o: ionCore/ionComparison.h
./ionScene/CSceneObject.ContextManagement.o: ionCore/ionTypes.h
./ionScene/CSceneObject.ContextManagement.o: ionCore/ionRand.h
./ionScene/CSceneObject.ContextManagement.o: ionCore/ionSmartPtr.h
./ionScene/CSceneObject.ContextManagement.o: ionCore/ionThread.h
./ionScene/CSceneObject.ContextManagement.o: ionCore/ionTreeNode.h
./ionScene/CSceneObject.ContextManagement.o: ionCore/ionUtils.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/ionMath.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/SVector.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/SColor.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/SVector2.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/Utilities.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/Constants.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/SVector3.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CSceneObject.ContextManagement.o: ionMath/SVector4.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/SMatrix4.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/SBoundingBox3.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/SLine3.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/SPlane3.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/SRect2.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/STriangle2.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/STriangle3.h
./ionScene/CSceneObject.ContextManagement.o: ionMath/STransformation3.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CSceneObject.ContextManagement.o: ionScene/CBufferObject.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CSceneObject.ContextManagement.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CSceneObject.ContextManagement.o: ./ionGL/Program.h
./ionScene/CSceneObject.ContextManagement.o: ./ionGL/Shader.h
./ionScene/CSceneObject.ContextManagement.o: ./ionGL/Texture.h
./ionScene/CSceneObject.ContextManagement.o: ./ionGL/VertexArray.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/CShader.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/CTexture.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/CImage.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/IRenderTarget.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/CShaderContext.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/IRenderPass.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/CRenderable.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/SUniform.h
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CSceneObject.ContextManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CSceneObject.ContextManagement.o: ionScene/SAttribute.h
./ionScene/CSceneObject.ContextManagement.o: ionScene/CImageLoader.h
./ionScene/CTexture.o: ionScene/CTexture.h
./ionScene/CTexture.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CTexture.o: ionCore/ionCore.h ionConfig.h ionCore/ionComparison.h
./ionScene/CTexture.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CTexture.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CTexture.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CTexture.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CTexture.o: ionMath/ionMath.h ionMath/SVector.h ionMath/SColor.h
./ionScene/CTexture.o: ionMath/SVector2.h ionMath/Utilities.h
./ionScene/CTexture.o: ionMath/Constants.h
./ionScene/CTexture.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CTexture.o: ionMath/SVector3.h
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CTexture.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CTexture.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CTexture.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CTexture.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CTexture.o: ionMath/STransformation3.h
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CTexture.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CTexture.o: ionScene/CImage.h
./ionScene/CTexture.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CTexture.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CTexture.o: ionScene/IRenderTarget.h
./ionScene/CTexture.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CTexture.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/CTexture.o: ./ionGL/Buffer.h ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CTexture.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/ISceneObject.StatisticMethods.o: ionScene/ISceneObject.h
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/ISceneObject.StatisticMethods.o: ionCore/ionCore.h ionConfig.h
./ionScene/ISceneObject.StatisticMethods.o: ionCore/ionComparison.h
./ionScene/ISceneObject.StatisticMethods.o: ionCore/ionTypes.h
./ionScene/ISceneObject.StatisticMethods.o: ionCore/ionRand.h
./ionScene/ISceneObject.StatisticMethods.o: ionCore/ionSmartPtr.h
./ionScene/ISceneObject.StatisticMethods.o: ionCore/ionThread.h
./ionScene/ISceneObject.StatisticMethods.o: ionCore/ionTreeNode.h
./ionScene/ISceneObject.StatisticMethods.o: ionCore/ionUtils.h
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/ionMath.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/SVector.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/SColor.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/SVector2.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/Utilities.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/Constants.h
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/SVector3.h
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/ISceneObject.StatisticMethods.o: ionMath/SVector4.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/SMatrix4.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/SBoundingBox3.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/SLine3.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/SPlane3.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/SRect2.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/STriangle2.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/STriangle3.h
./ionScene/ISceneObject.StatisticMethods.o: ionMath/STransformation3.h
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/ISceneObject.StatisticMethods.o: ionScene/CBufferObject.h
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/ISceneObject.StatisticMethods.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionGL/Program.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionGL/Shader.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionGL/Texture.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionGL/VertexArray.h
./ionScene/ISceneObject.StatisticMethods.o: ionScene/CShader.h
./ionScene/ISceneObject.StatisticMethods.o: ionScene/CTexture.h
./ionScene/ISceneObject.StatisticMethods.o: ionScene/CImage.h
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/ISceneObject.StatisticMethods.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/ISceneObject.StatisticMethods.o: ionScene/IRenderTarget.h
./ionScene/ISceneObject.StatisticMethods.o: ionScene/CShaderContext.h
./ionScene/ISceneObject.StatisticMethods.o: ionScene/IRenderPass.h
./ionScene/ISceneObject.StatisticMethods.o: ionScene/ISceneObject.Enumerations.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionScene/ISceneObject.h
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionCore/ionCore.h ionConfig.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionCore/ionComparison.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionCore/ionTypes.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionCore/ionRand.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionCore/ionSmartPtr.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionCore/ionThread.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionCore/ionTreeNode.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionCore/ionUtils.h
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/ionMath.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/SVector.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/SColor.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/SVector2.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/Utilities.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/Constants.h
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/SVector3.h
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/SVector4.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/SMatrix4.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/SBoundingBox3.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/SLine3.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/SPlane3.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/SRect2.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/STriangle2.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/STriangle3.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionMath/STransformation3.h
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/ISceneObject.SceneGraphMethods.o: ionScene/CBufferObject.h
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionGL/Program.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionGL/Shader.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionGL/Texture.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionGL/VertexArray.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionScene/CShader.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionScene/CTexture.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionScene/CImage.h
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/ISceneObject.SceneGraphMethods.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionScene/IRenderTarget.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionScene/CShaderContext.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionScene/IRenderPass.h
./ionScene/ISceneObject.SceneGraphMethods.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CMesh.o: ionScene/CMesh.h
./ionScene/CMesh.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionScene/CMesh.o: ionMath/SVector3.h ionConfig.h ionMath/SVector.h
./ionScene/CMesh.o: /home/idunn01/484/ionEngine/ionCore.h ionCore/ionCore.h
./ionScene/CMesh.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CMesh.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CMesh.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CMesh.o: ionCore/ionUtils.h ionMath/SVector2.h ionMath/Utilities.h
./ionScene/CMesh.o: ionMath/Constants.h
./ionScene/CMesh.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CMesh.o: ionMath/SLine3.h ionScene/SVertex.h
./ionScene/CMesh.o: /home/idunn01/484/ionEngine/ionMath.h ionMath/ionMath.h
./ionScene/CMesh.o: ionMath/SColor.h ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CMesh.o: ionMath/SBoundingBox3.h ionMath/SPlane3.h
./ionScene/CMesh.o: ionMath/SRect2.h ionMath/STriangle2.h
./ionScene/CMesh.o: ionMath/STriangle3.h ionMath/STransformation3.h
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CMesh.o: ionScene/CBufferObject.h
./ionScene/CMesh.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CMesh.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/CMesh.o: ./ionGL/Buffer.h ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CMesh.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CMesh.o: ionScene/CRenderable.h
./ionScene/CMesh.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CMesh.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CMesh.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CMesh.o: ionScene/IRenderPass.h ionScene/SUniform.h
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CMesh.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CMesh.o: ionScene/CShaderContext.h ionScene/CShader.h
./ionScene/CMesh.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CMesh.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CMesh.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CMesh.o: ionScene/IRenderTarget.h ionScene/SAttribute.h
./ionScene/CShaderLoader.o: ionScene/CShaderLoader.h ionScene/CShader.h
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CShaderLoader.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/CShaderLoader.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CShaderLoader.o: ionCore/ionCore.h ionConfig.h
./ionScene/CShaderLoader.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CShaderLoader.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CShaderLoader.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CShaderLoader.o: ionCore/ionUtils.h
./ionScene/CShaderLoader.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CShaderLoader.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CShaderLoader.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CShaderLoader.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CShaderLoader.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CShaderLoader.o: ionMath/SVector3.h
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CShaderLoader.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CShaderLoader.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CShaderLoader.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CShaderLoader.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CShaderLoader.o: ionMath/STransformation3.h
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CShaderLoader.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CShaderLoader.o: ./ionGL/Buffer.h ./ionGL/Program.h
./ionScene/CShaderLoader.o: ./ionGL/Shader.h ./ionGL/Texture.h
./ionScene/CShaderLoader.o: ./ionGL/VertexArray.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/CSceneObject.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/ISceneObject.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CSceneObject.RenderableManagement.o: ionCore/ionCore.h ionConfig.h
./ionScene/CSceneObject.RenderableManagement.o: ionCore/ionComparison.h
./ionScene/CSceneObject.RenderableManagement.o: ionCore/ionTypes.h
./ionScene/CSceneObject.RenderableManagement.o: ionCore/ionRand.h
./ionScene/CSceneObject.RenderableManagement.o: ionCore/ionSmartPtr.h
./ionScene/CSceneObject.RenderableManagement.o: ionCore/ionThread.h
./ionScene/CSceneObject.RenderableManagement.o: ionCore/ionTreeNode.h
./ionScene/CSceneObject.RenderableManagement.o: ionCore/ionUtils.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/ionMath.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/SVector.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/SColor.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/SVector2.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/Utilities.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/Constants.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/SVector3.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CSceneObject.RenderableManagement.o: ionMath/SVector4.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/SMatrix4.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/SBoundingBox3.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/SLine3.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/SPlane3.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/SRect2.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/STriangle2.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/STriangle3.h
./ionScene/CSceneObject.RenderableManagement.o: ionMath/STransformation3.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CSceneObject.RenderableManagement.o: ionScene/CBufferObject.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CSceneObject.RenderableManagement.o: ionGL/ionGL.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionGL/Buffer.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionGL/Program.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionGL/Shader.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionGL/Texture.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionGL/VertexArray.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/CShader.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/CTexture.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/CImage.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/IRenderTarget.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/CShaderContext.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/IRenderPass.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/CRenderable.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CSceneObject.RenderableManagement.o: ionScene/SUniform.h
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CSceneObject.RenderableManagement.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CSceneObject.RenderableManagement.o: ionScene/SAttribute.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/CRenderable.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CRenderable.UpdateMethods.o: ionConfig.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CRenderable.UpdateMethods.o: ionMath/SVector3.h ionMath/SVector.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CRenderable.UpdateMethods.o: ionCore/ionCore.h
./ionScene/CRenderable.UpdateMethods.o: ionCore/ionComparison.h
./ionScene/CRenderable.UpdateMethods.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CRenderable.UpdateMethods.o: ionCore/ionSmartPtr.h
./ionScene/CRenderable.UpdateMethods.o: ionCore/ionThread.h
./ionScene/CRenderable.UpdateMethods.o: ionCore/ionTreeNode.h
./ionScene/CRenderable.UpdateMethods.o: ionCore/ionUtils.h ionMath/SVector2.h
./ionScene/CRenderable.UpdateMethods.o: ionMath/Utilities.h
./ionScene/CRenderable.UpdateMethods.o: ionMath/Constants.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/IRenderPass.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/SUniform.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CRenderable.UpdateMethods.o: ionScene/CShaderContext.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CRenderable.UpdateMethods.o: ionMath/ionMath.h ionMath/SColor.h
./ionScene/CRenderable.UpdateMethods.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CRenderable.UpdateMethods.o: ionMath/SBoundingBox3.h
./ionScene/CRenderable.UpdateMethods.o: ionMath/SLine3.h ionMath/SPlane3.h
./ionScene/CRenderable.UpdateMethods.o: ionMath/SRect2.h ionMath/STriangle2.h
./ionScene/CRenderable.UpdateMethods.o: ionMath/STriangle3.h
./ionScene/CRenderable.UpdateMethods.o: ionMath/STransformation3.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/CShader.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/IRenderTarget.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/SAttribute.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/CBufferObject.h
./ionScene/CRenderable.UpdateMethods.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CRenderable.UpdateMethods.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CRenderable.UpdateMethods.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CRenderable.UpdateMethods.o: ./ionGL/Texture.h
./ionScene/CRenderable.UpdateMethods.o: ./ionGL/VertexArray.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/CSceneObject.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/ISceneObject.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/IScene.h
./ionScene/CRenderable.UpdateMethods.o: ionScene/ICameraSceneObject.h
./ionScene/CMeshSceneObject.o: ionScene/CMeshSceneObject.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./ionScene/CMeshSceneObject.o: ionConfig.h ionMath/SVector.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CMeshSceneObject.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CMeshSceneObject.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CMeshSceneObject.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CMeshSceneObject.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CMeshSceneObject.o: ionMath/SVector2.h ionMath/Utilities.h
./ionScene/CMeshSceneObject.o: ionMath/Constants.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CMeshSceneObject.o: ionScene/CShader.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CMeshSceneObject.o: ionScene/CMesh.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionScene/CMeshSceneObject.o: ionMath/SVector3.h ionMath/SLine3.h
./ionScene/CMeshSceneObject.o: ionScene/SVertex.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CMeshSceneObject.o: ionMath/ionMath.h ionMath/SColor.h
./ionScene/CMeshSceneObject.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CMeshSceneObject.o: ionMath/SBoundingBox3.h ionMath/SPlane3.h
./ionScene/CMeshSceneObject.o: ionMath/SRect2.h ionMath/STriangle2.h
./ionScene/CMeshSceneObject.o: ionMath/STriangle3.h
./ionScene/CMeshSceneObject.o: ionMath/STransformation3.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CMeshSceneObject.o: ionScene/CBufferObject.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CMeshSceneObject.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CMeshSceneObject.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CMeshSceneObject.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CMeshSceneObject.o: ionScene/CRenderable.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CMeshSceneObject.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CMeshSceneObject.o: ionScene/IRenderPass.h ionScene/SUniform.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CMeshSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CMeshSceneObject.o: ionScene/CShaderContext.h ionScene/CTexture.h
./ionScene/CMeshSceneObject.o: ionScene/CImage.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CMeshSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CMeshSceneObject.o: ionScene/IRenderTarget.h ionScene/SAttribute.h
./ionScene/CMeshSceneObject.o: ionScene/CSceneObject.h
./ionScene/CMeshSceneObject.o: ionScene/ISceneObject.h
./ionScene/CMeshSceneObject.o: ionScene/CShaderLoader.h
./ionScene/CScene.Details.o: ionScene/CScene.h ionConfig.h ionScene/IScene.h
./ionScene/CScene.Details.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CScene.Details.o: ionScene/ICameraSceneObject.h
./ionScene/CScene.Details.o: ionScene/ISceneObject.h
./ionScene/CScene.Details.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CScene.Details.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CScene.Details.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CScene.Details.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CScene.Details.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CScene.Details.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CScene.Details.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CScene.Details.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CScene.Details.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CScene.Details.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CScene.Details.o: ionMath/SVector3.h
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CScene.Details.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CScene.Details.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CScene.Details.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CScene.Details.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CScene.Details.o: ionMath/STransformation3.h
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CScene.Details.o: ionScene/CBufferObject.h
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CScene.Details.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CScene.Details.o: ionGL/ionGL.h ./ionGL/Buffer.h ./ionGL/Program.h
./ionScene/CScene.Details.o: ./ionGL/Shader.h ./ionGL/Texture.h
./ionScene/CScene.Details.o: ./ionGL/VertexArray.h ionScene/CShader.h
./ionScene/CScene.Details.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CScene.Details.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CScene.Details.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CScene.Details.o: ionScene/IRenderTarget.h
./ionScene/CScene.Details.o: ionScene/CShaderContext.h ionScene/IRenderPass.h
./ionScene/CScene.Details.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.Details.o: ionScene/CLightSceneObject.h ionScene/SUniform.h
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CScene.Details.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CScene.Details.o: ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.Details.o: ionScene/CCameraSceneObject.h
./ionScene/CScene.o: ionScene/CScene.h ionConfig.h ionScene/IScene.h
./ionScene/CScene.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CScene.o: ionScene/ICameraSceneObject.h ionScene/ISceneObject.h
./ionScene/CScene.o: /home/idunn01/484/ionEngine/ionCore.h ionCore/ionCore.h
./ionScene/CScene.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CScene.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CScene.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CScene.o: ionCore/ionUtils.h /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CScene.o: ionMath/ionMath.h ionMath/SVector.h ionMath/SColor.h
./ionScene/CScene.o: ionMath/SVector2.h ionMath/Utilities.h
./ionScene/CScene.o: ionMath/Constants.h
./ionScene/CScene.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CScene.o: ionMath/SVector3.h
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CScene.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CScene.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CScene.o: ionMath/SPlane3.h ionMath/SRect2.h ionMath/STriangle2.h
./ionScene/CScene.o: ionMath/STriangle3.h ionMath/STransformation3.h
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CScene.o: ionScene/CBufferObject.h
./ionScene/CScene.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CScene.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/CScene.o: ./ionGL/Buffer.h ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CScene.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CScene.o: ionScene/CShader.h ionScene/CTexture.h ionScene/CImage.h
./ionScene/CScene.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CScene.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CScene.o: ionScene/IRenderTarget.h ionScene/CShaderContext.h
./ionScene/CScene.o: ionScene/IRenderPass.h
./ionScene/CScene.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.o: ionScene/CLightSceneObject.h ionScene/SUniform.h
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CScene.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CScene.o: ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.o: ionScene/CCameraSceneObject.h ionScene/SAttribute.h
./ionScene/CScene.Update.o: ionScene/CScene.h ionConfig.h ionScene/IScene.h
./ionScene/CScene.Update.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CScene.Update.o: ionScene/ICameraSceneObject.h
./ionScene/CScene.Update.o: ionScene/ISceneObject.h
./ionScene/CScene.Update.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CScene.Update.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CScene.Update.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CScene.Update.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CScene.Update.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CScene.Update.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CScene.Update.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CScene.Update.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CScene.Update.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CScene.Update.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CScene.Update.o: ionMath/SVector3.h
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CScene.Update.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CScene.Update.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CScene.Update.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CScene.Update.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CScene.Update.o: ionMath/STransformation3.h
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CScene.Update.o: ionScene/CBufferObject.h
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CScene.Update.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/CScene.Update.o: ./ionGL/Buffer.h ./ionGL/Program.h
./ionScene/CScene.Update.o: ./ionGL/Shader.h ./ionGL/Texture.h
./ionScene/CScene.Update.o: ./ionGL/VertexArray.h ionScene/CShader.h
./ionScene/CScene.Update.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CScene.Update.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CScene.Update.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CScene.Update.o: ionScene/IRenderTarget.h
./ionScene/CScene.Update.o: ionScene/CShaderContext.h ionScene/IRenderPass.h
./ionScene/CScene.Update.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.Update.o: ionScene/CLightSceneObject.h ionScene/SUniform.h
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CScene.Update.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CScene.Update.o: ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.Update.o: ionScene/CCameraSceneObject.h
./ionScene/CSceneEffectManager.o: ionScene/CSceneEffectManager.h
./ionScene/CSceneEffectManager.o: ionScene/CFrameBufferObject.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CSceneEffectManager.o: ionConfig.h ionScene/CRenderBufferObject.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CSceneEffectManager.o: ionMath/ionMath.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CSceneEffectManager.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CSceneEffectManager.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CSceneEffectManager.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CSceneEffectManager.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CSceneEffectManager.o: ionMath/SVector.h ionMath/SColor.h
./ionScene/CSceneEffectManager.o: ionMath/SVector2.h ionMath/Utilities.h
./ionScene/CSceneEffectManager.o: ionMath/Constants.h ionMath/SVector3.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CSceneEffectManager.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CSceneEffectManager.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CSceneEffectManager.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CSceneEffectManager.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CSceneEffectManager.o: ionMath/STransformation3.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CSceneEffectManager.o: ionScene/IRenderTarget.h
./ionScene/CSceneEffectManager.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CSceneEffectManager.o: ionScene/ISceneObject.h
./ionScene/CSceneEffectManager.o: ionScene/CBufferObject.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CSceneEffectManager.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CSceneEffectManager.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CSceneEffectManager.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CSceneEffectManager.o: ionScene/CShader.h
./ionScene/CSceneEffectManager.o: ionScene/CShaderContext.h
./ionScene/CSceneEffectManager.o: ionScene/IRenderPass.h
./ionScene/CSceneEffectManager.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneEffectManager.o: ionScene/SUniform.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CSceneEffectManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CSceneEffectManager.o: ionScene/CSceneManager.h
./ionScene/CSceneEffectManager.o: ionScene/CSceneObject.h
./ionScene/CSceneEffectManager.o: ionScene/CRenderable.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CSceneEffectManager.o: ionScene/SAttribute.h
./ionScene/CSceneEffectManager.o: ionScene/CMeshSceneObject.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./ionScene/CSceneEffectManager.o: ionScene/CMesh.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionScene/CSceneEffectManager.o: ionScene/SVertex.h
./ionScene/CSceneEffectManager.o: ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CSceneEffectManager.o: ionScene/CCameraSceneObject.h
./ionScene/CSceneEffectManager.o: ionScene/ICameraSceneObject.h
./ionScene/CSceneEffectManager.o: ionScene/CScene.h ionScene/IScene.h
./ionScene/CSceneEffectManager.o: ionScene/CLightSceneObject.h
./ionScene/CSceneEffectManager.o: /home/idunn01/484/ionEngine/ionMath/SLine3.h
./ionScene/CSceneEffectManager.o: ionScene/CDefaultColorRenderPass.h
./ionScene/CSceneEffectManager.o: ionScene/CMultiOutRenderPass.h
./ionScene/CSceneEffectManager.o: ionScene/CImageLoader.h
./ionScene/CSceneEffectManager.o: ionScene/CShaderLoader.h
./ionScene/CShader.o: ionScene/CShader.h
./ionScene/CShader.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CShader.o: /home/idunn01/484/ionEngine/ionCore.h ionCore/ionCore.h
./ionScene/CShader.o: ionConfig.h ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CShader.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CShader.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CShader.o: ionCore/ionUtils.h
./ionScene/CFrameBufferObject.o: ionScene/CFrameBufferObject.h
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CFrameBufferObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CFrameBufferObject.o: ionConfig.h ionScene/CRenderBufferObject.h
./ionScene/CFrameBufferObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CFrameBufferObject.o: ionMath/ionMath.h
./ionScene/CFrameBufferObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CFrameBufferObject.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CFrameBufferObject.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CFrameBufferObject.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CFrameBufferObject.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CFrameBufferObject.o: ionMath/SVector.h ionMath/SColor.h
./ionScene/CFrameBufferObject.o: ionMath/SVector2.h ionMath/Utilities.h
./ionScene/CFrameBufferObject.o: ionMath/Constants.h ionMath/SVector3.h
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CFrameBufferObject.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CFrameBufferObject.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CFrameBufferObject.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CFrameBufferObject.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CFrameBufferObject.o: ionMath/STransformation3.h
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CFrameBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CFrameBufferObject.o: ionScene/IRenderTarget.h ionScene/CTexture.h
./ionScene/CFrameBufferObject.o: ionScene/CImage.h
./ionScene/CFrameBufferObject.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CFrameBufferObject.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CFrameBufferObject.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CFrameBufferObject.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CFrameBufferObject.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CFrameBufferObject.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/ISceneObject.UpdateMethods.o: ionScene/ISceneObject.h
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/ISceneObject.UpdateMethods.o: ionCore/ionCore.h ionConfig.h
./ionScene/ISceneObject.UpdateMethods.o: ionCore/ionComparison.h
./ionScene/ISceneObject.UpdateMethods.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/ISceneObject.UpdateMethods.o: ionCore/ionSmartPtr.h
./ionScene/ISceneObject.UpdateMethods.o: ionCore/ionThread.h
./ionScene/ISceneObject.UpdateMethods.o: ionCore/ionTreeNode.h
./ionScene/ISceneObject.UpdateMethods.o: ionCore/ionUtils.h
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/Utilities.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/Constants.h
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/SVector3.h
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/ISceneObject.UpdateMethods.o: ionMath/SVector4.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/SMatrix4.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/SBoundingBox3.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/SLine3.h ionMath/SPlane3.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/SRect2.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/STriangle2.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/STriangle3.h
./ionScene/ISceneObject.UpdateMethods.o: ionMath/STransformation3.h
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/ISceneObject.UpdateMethods.o: ionScene/CBufferObject.h
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/ISceneObject.UpdateMethods.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionGL/Texture.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionGL/VertexArray.h
./ionScene/ISceneObject.UpdateMethods.o: ionScene/CShader.h
./ionScene/ISceneObject.UpdateMethods.o: ionScene/CTexture.h
./ionScene/ISceneObject.UpdateMethods.o: ionScene/CImage.h
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/ISceneObject.UpdateMethods.o: ionScene/IRenderTarget.h
./ionScene/ISceneObject.UpdateMethods.o: ionScene/CShaderContext.h
./ionScene/ISceneObject.UpdateMethods.o: ionScene/IRenderPass.h
./ionScene/ISceneObject.UpdateMethods.o: ionScene/ISceneObject.Enumerations.h
./ionScene/ISceneObject.UpdateMethods.o: ionScene/IScene.h
./ionScene/ISceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/ISceneObject.UpdateMethods.o: ionScene/ICameraSceneObject.h
./ionScene/CMeshLoader.o: ionScene/CMeshLoader.h ionScene/CMesh.h
./ionScene/CMeshLoader.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionScene/CMeshLoader.o: ionMath/SVector3.h ionConfig.h ionMath/SVector.h
./ionScene/CMeshLoader.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CMeshLoader.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CMeshLoader.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CMeshLoader.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CMeshLoader.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CMeshLoader.o: ionMath/SVector2.h ionMath/Utilities.h
./ionScene/CMeshLoader.o: ionMath/Constants.h
./ionScene/CMeshLoader.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CMeshLoader.o: ionMath/SLine3.h ionScene/SVertex.h
./ionScene/CMeshLoader.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CMeshLoader.o: ionMath/ionMath.h ionMath/SColor.h
./ionScene/CMeshLoader.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CMeshLoader.o: ionMath/SBoundingBox3.h ionMath/SPlane3.h
./ionScene/CMeshLoader.o: ionMath/SRect2.h ionMath/STriangle2.h
./ionScene/CMeshLoader.o: ionMath/STriangle3.h ionMath/STransformation3.h
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CMeshLoader.o: ionScene/CBufferObject.h
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CMeshLoader.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/CMeshLoader.o: ./ionGL/Buffer.h ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CMeshLoader.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CMeshLoader.o: ionScene/CRenderable.h
./ionScene/CMeshLoader.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CMeshLoader.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CMeshLoader.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CMeshLoader.o: ionScene/IRenderPass.h ionScene/SUniform.h
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CMeshLoader.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CMeshLoader.o: ionScene/CShaderContext.h ionScene/CShader.h
./ionScene/CMeshLoader.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CMeshLoader.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CMeshLoader.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CMeshLoader.o: ionScene/IRenderTarget.h ionScene/SAttribute.h
./ionScene/ISceneObject.CullingMethods.o: ionScene/ISceneObject.h
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/ISceneObject.CullingMethods.o: ionCore/ionCore.h ionConfig.h
./ionScene/ISceneObject.CullingMethods.o: ionCore/ionComparison.h
./ionScene/ISceneObject.CullingMethods.o: ionCore/ionTypes.h
./ionScene/ISceneObject.CullingMethods.o: ionCore/ionRand.h
./ionScene/ISceneObject.CullingMethods.o: ionCore/ionSmartPtr.h
./ionScene/ISceneObject.CullingMethods.o: ionCore/ionThread.h
./ionScene/ISceneObject.CullingMethods.o: ionCore/ionTreeNode.h
./ionScene/ISceneObject.CullingMethods.o: ionCore/ionUtils.h
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/Utilities.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/Constants.h
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/SVector3.h
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/ISceneObject.CullingMethods.o: ionMath/SVector4.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/SMatrix4.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/SBoundingBox3.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/SLine3.h ionMath/SPlane3.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/SRect2.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/STriangle2.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/STriangle3.h
./ionScene/ISceneObject.CullingMethods.o: ionMath/STransformation3.h
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/ISceneObject.CullingMethods.o: ionScene/CBufferObject.h
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/ISceneObject.CullingMethods.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/ISceneObject.CullingMethods.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/ISceneObject.CullingMethods.o: ./ionGL/Texture.h
./ionScene/ISceneObject.CullingMethods.o: ./ionGL/VertexArray.h
./ionScene/ISceneObject.CullingMethods.o: ionScene/CShader.h
./ionScene/ISceneObject.CullingMethods.o: ionScene/CTexture.h
./ionScene/ISceneObject.CullingMethods.o: ionScene/CImage.h
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/ISceneObject.CullingMethods.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/ISceneObject.CullingMethods.o: ionScene/IRenderTarget.h
./ionScene/ISceneObject.CullingMethods.o: ionScene/CShaderContext.h
./ionScene/ISceneObject.CullingMethods.o: ionScene/IRenderPass.h
./ionScene/ISceneObject.CullingMethods.o: ionScene/ISceneObject.Enumerations.h
./ionScene/ISceneObject.CullingMethods.o: ionScene/ICameraSceneObject.h
./ionScene/CSceneObject.o: ionScene/CSceneObject.h ionScene/ISceneObject.h
./ionScene/CSceneObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CSceneObject.o: ionCore/ionCore.h ionConfig.h
./ionScene/CSceneObject.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CSceneObject.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CSceneObject.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CSceneObject.o: ionCore/ionUtils.h
./ionScene/CSceneObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CSceneObject.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CSceneObject.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CSceneObject.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CSceneObject.o: ionMath/SVector3.h
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CSceneObject.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CSceneObject.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CSceneObject.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CSceneObject.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CSceneObject.o: ionMath/STransformation3.h
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CSceneObject.o: ionScene/CBufferObject.h
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CSceneObject.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/CSceneObject.o: ./ionGL/Buffer.h ./ionGL/Program.h
./ionScene/CSceneObject.o: ./ionGL/Shader.h ./ionGL/Texture.h
./ionScene/CSceneObject.o: ./ionGL/VertexArray.h ionScene/CShader.h
./ionScene/CSceneObject.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CSceneObject.o: ionScene/IRenderTarget.h ionScene/CShaderContext.h
./ionScene/CSceneObject.o: ionScene/IRenderPass.h
./ionScene/CSceneObject.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneObject.o: ionScene/CRenderable.h
./ionScene/CSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CSceneObject.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CSceneObject.o: ionScene/SUniform.h
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CSceneObject.o: ionScene/SAttribute.h
./ionScene/CLightSceneObject.o: ionScene/CLightSceneObject.h
./ionScene/CLightSceneObject.o: ionScene/ISceneObject.h
./ionScene/CLightSceneObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CLightSceneObject.o: ionCore/ionCore.h ionConfig.h
./ionScene/CLightSceneObject.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CLightSceneObject.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CLightSceneObject.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CLightSceneObject.o: ionCore/ionUtils.h
./ionScene/CLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CLightSceneObject.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CLightSceneObject.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CLightSceneObject.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CLightSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CLightSceneObject.o: ionMath/SVector3.h
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CLightSceneObject.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CLightSceneObject.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CLightSceneObject.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CLightSceneObject.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CLightSceneObject.o: ionMath/STransformation3.h
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CLightSceneObject.o: ionScene/CBufferObject.h
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CLightSceneObject.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CLightSceneObject.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CLightSceneObject.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CLightSceneObject.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CLightSceneObject.o: ionScene/CShader.h ionScene/CTexture.h
./ionScene/CLightSceneObject.o: ionScene/CImage.h
./ionScene/CLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CLightSceneObject.o: ionScene/IRenderTarget.h
./ionScene/CLightSceneObject.o: ionScene/CShaderContext.h
./ionScene/CLightSceneObject.o: ionScene/IRenderPass.h
./ionScene/CLightSceneObject.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CLightSceneObject.o: ionScene/SUniform.h
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CPointLightSceneObject.o: ionScene/CPointLightSceneObject.h
./ionScene/CPointLightSceneObject.o: ionScene/ISceneObject.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CPointLightSceneObject.o: ionCore/ionCore.h ionConfig.h
./ionScene/CPointLightSceneObject.o: ionCore/ionComparison.h
./ionScene/CPointLightSceneObject.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CPointLightSceneObject.o: ionCore/ionSmartPtr.h
./ionScene/CPointLightSceneObject.o: ionCore/ionThread.h
./ionScene/CPointLightSceneObject.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CPointLightSceneObject.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CPointLightSceneObject.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CPointLightSceneObject.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CPointLightSceneObject.o: ionMath/SVector3.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CPointLightSceneObject.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CPointLightSceneObject.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CPointLightSceneObject.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CPointLightSceneObject.o: ionMath/STriangle2.h
./ionScene/CPointLightSceneObject.o: ionMath/STriangle3.h
./ionScene/CPointLightSceneObject.o: ionMath/STransformation3.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CPointLightSceneObject.o: ionScene/CBufferObject.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CPointLightSceneObject.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CPointLightSceneObject.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CPointLightSceneObject.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CPointLightSceneObject.o: ionScene/CShader.h ionScene/CTexture.h
./ionScene/CPointLightSceneObject.o: ionScene/CImage.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CPointLightSceneObject.o: ionScene/IRenderTarget.h
./ionScene/CPointLightSceneObject.o: ionScene/CShaderContext.h
./ionScene/CPointLightSceneObject.o: ionScene/IRenderPass.h
./ionScene/CPointLightSceneObject.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CPointLightSceneObject.o: ionScene/CMeshLoader.h ionScene/CMesh.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionScene/CPointLightSceneObject.o: ionScene/SVertex.h
./ionScene/CPointLightSceneObject.o: ionScene/CRenderable.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CPointLightSceneObject.o: ionScene/SUniform.h
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CPointLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CPointLightSceneObject.o: ionScene/SAttribute.h
./ionScene/CPointLightSceneObject.o: ionScene/CShaderLoader.h
./ionScene/CPointLightSceneObject.o: ionScene/IScene.h
./ionScene/CPointLightSceneObject.o: ionScene/ICameraSceneObject.h
./ionScene/CImage.o: ionScene/CImage.h
./ionScene/CImage.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CImage.o: ionMath/SVector.h /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CImage.o: ionCore/ionCore.h ionConfig.h ionCore/ionComparison.h
./ionScene/CImage.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CImage.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CImage.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CImage.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CImage.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CImage.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CImage.o: /home/idunn01/484/deps/stb_image/include/stb_image.c
./ionScene/CImage.o: ./ionScene/BitmapWriter.h
./ionScene/CRenderable.SShaderSetup.o: ionScene/CRenderable.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CRenderable.SShaderSetup.o: ionConfig.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CRenderable.SShaderSetup.o: ionMath/SVector3.h ionMath/SVector.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CRenderable.SShaderSetup.o: ionCore/ionCore.h
./ionScene/CRenderable.SShaderSetup.o: ionCore/ionComparison.h
./ionScene/CRenderable.SShaderSetup.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CRenderable.SShaderSetup.o: ionCore/ionSmartPtr.h
./ionScene/CRenderable.SShaderSetup.o: ionCore/ionThread.h
./ionScene/CRenderable.SShaderSetup.o: ionCore/ionTreeNode.h
./ionScene/CRenderable.SShaderSetup.o: ionCore/ionUtils.h ionMath/SVector2.h
./ionScene/CRenderable.SShaderSetup.o: ionMath/Utilities.h
./ionScene/CRenderable.SShaderSetup.o: ionMath/Constants.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CRenderable.SShaderSetup.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.SShaderSetup.o: ionScene/IRenderPass.h
./ionScene/CRenderable.SShaderSetup.o: ionScene/SUniform.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CRenderable.SShaderSetup.o: ionScene/CShaderContext.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CRenderable.SShaderSetup.o: ionMath/ionMath.h ionMath/SColor.h
./ionScene/CRenderable.SShaderSetup.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CRenderable.SShaderSetup.o: ionMath/SBoundingBox3.h
./ionScene/CRenderable.SShaderSetup.o: ionMath/SLine3.h ionMath/SPlane3.h
./ionScene/CRenderable.SShaderSetup.o: ionMath/SRect2.h ionMath/STriangle2.h
./ionScene/CRenderable.SShaderSetup.o: ionMath/STriangle3.h
./ionScene/CRenderable.SShaderSetup.o: ionMath/STransformation3.h
./ionScene/CRenderable.SShaderSetup.o: ionScene/CShader.h ionScene/CTexture.h
./ionScene/CRenderable.SShaderSetup.o: ionScene/CImage.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CRenderable.SShaderSetup.o: ionScene/IRenderTarget.h
./ionScene/CRenderable.SShaderSetup.o: ionScene/SAttribute.h
./ionScene/CRenderable.SShaderSetup.o: ionScene/CBufferObject.h
./ionScene/CRenderable.SShaderSetup.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CRenderable.SShaderSetup.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CRenderable.SShaderSetup.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CRenderable.SShaderSetup.o: ./ionGL/Texture.h
./ionScene/CRenderable.SShaderSetup.o: ./ionGL/VertexArray.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CDirectionalLightSceneObject.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/ISceneObject.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CDirectionalLightSceneObject.o: ionCore/ionCore.h ionConfig.h
./ionScene/CDirectionalLightSceneObject.o: ionCore/ionComparison.h
./ionScene/CDirectionalLightSceneObject.o: ionCore/ionTypes.h
./ionScene/CDirectionalLightSceneObject.o: ionCore/ionRand.h
./ionScene/CDirectionalLightSceneObject.o: ionCore/ionSmartPtr.h
./ionScene/CDirectionalLightSceneObject.o: ionCore/ionThread.h
./ionScene/CDirectionalLightSceneObject.o: ionCore/ionTreeNode.h
./ionScene/CDirectionalLightSceneObject.o: ionCore/ionUtils.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/ionMath.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/SVector.h ionMath/SColor.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/SVector2.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/Utilities.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/Constants.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/SVector3.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CDirectionalLightSceneObject.o: ionMath/SVector4.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/SMatrix4.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/SBoundingBox3.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/SLine3.h ionMath/SPlane3.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/SRect2.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/STriangle2.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/STriangle3.h
./ionScene/CDirectionalLightSceneObject.o: ionMath/STransformation3.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CDirectionalLightSceneObject.o: ionScene/CBufferObject.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CDirectionalLightSceneObject.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CDirectionalLightSceneObject.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CDirectionalLightSceneObject.o: ./ionGL/Texture.h
./ionScene/CDirectionalLightSceneObject.o: ./ionGL/VertexArray.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CShader.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CTexture.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CImage.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/IRenderTarget.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CShaderContext.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/IRenderPass.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CMeshLoader.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CMesh.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/SVertex.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CRenderable.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/SUniform.h
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CDirectionalLightSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CDirectionalLightSceneObject.o: ionScene/SAttribute.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CShaderLoader.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CSceneEffectManager.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CFrameBufferObject.h
./ionScene/CDirectionalLightSceneObject.o: ionScene/CRenderBufferObject.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/CCameraSceneObject.h
./ionScene/CPerspectiveCameraSceneObject.o: ionConfig.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/ICameraSceneObject.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/ISceneObject.h
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CPerspectiveCameraSceneObject.o: ionCore/ionCore.h
./ionScene/CPerspectiveCameraSceneObject.o: ionCore/ionComparison.h
./ionScene/CPerspectiveCameraSceneObject.o: ionCore/ionTypes.h
./ionScene/CPerspectiveCameraSceneObject.o: ionCore/ionRand.h
./ionScene/CPerspectiveCameraSceneObject.o: ionCore/ionSmartPtr.h
./ionScene/CPerspectiveCameraSceneObject.o: ionCore/ionThread.h
./ionScene/CPerspectiveCameraSceneObject.o: ionCore/ionTreeNode.h
./ionScene/CPerspectiveCameraSceneObject.o: ionCore/ionUtils.h
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/ionMath.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/SVector.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/SColor.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/SVector2.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/Utilities.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/Constants.h
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/SVector3.h
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/SVector4.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/SMatrix4.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/SBoundingBox3.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/SLine3.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/SPlane3.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/SRect2.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/STriangle2.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/STriangle3.h
./ionScene/CPerspectiveCameraSceneObject.o: ionMath/STransformation3.h
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/CBufferObject.h
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CPerspectiveCameraSceneObject.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionGL/Program.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionGL/Shader.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionGL/Texture.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionGL/VertexArray.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/CShader.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/CTexture.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/CImage.h
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CPerspectiveCameraSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/IRenderTarget.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/CShaderContext.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/IRenderPass.h
./ionScene/CPerspectiveCameraSceneObject.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.ShaderVariables.o: ionScene/CRenderable.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CRenderable.ShaderVariables.o: ionConfig.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CRenderable.ShaderVariables.o: ionMath/SVector3.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/SVector.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CRenderable.ShaderVariables.o: ionCore/ionCore.h
./ionScene/CRenderable.ShaderVariables.o: ionCore/ionComparison.h
./ionScene/CRenderable.ShaderVariables.o: ionCore/ionTypes.h
./ionScene/CRenderable.ShaderVariables.o: ionCore/ionRand.h
./ionScene/CRenderable.ShaderVariables.o: ionCore/ionSmartPtr.h
./ionScene/CRenderable.ShaderVariables.o: ionCore/ionThread.h
./ionScene/CRenderable.ShaderVariables.o: ionCore/ionTreeNode.h
./ionScene/CRenderable.ShaderVariables.o: ionCore/ionUtils.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/SVector2.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/Utilities.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/Constants.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CRenderable.ShaderVariables.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.ShaderVariables.o: ionScene/IRenderPass.h
./ionScene/CRenderable.ShaderVariables.o: ionScene/SUniform.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CRenderable.ShaderVariables.o: ionScene/CShaderContext.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/ionMath.h ionMath/SColor.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/SVector4.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/SMatrix4.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/SBoundingBox3.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/SLine3.h ionMath/SPlane3.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/SRect2.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/STriangle2.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/STriangle3.h
./ionScene/CRenderable.ShaderVariables.o: ionMath/STransformation3.h
./ionScene/CRenderable.ShaderVariables.o: ionScene/CShader.h
./ionScene/CRenderable.ShaderVariables.o: ionScene/CTexture.h
./ionScene/CRenderable.ShaderVariables.o: ionScene/CImage.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CRenderable.ShaderVariables.o: ionScene/IRenderTarget.h
./ionScene/CRenderable.ShaderVariables.o: ionScene/SAttribute.h
./ionScene/CRenderable.ShaderVariables.o: ionScene/CBufferObject.h
./ionScene/CRenderable.ShaderVariables.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CRenderable.ShaderVariables.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CRenderable.ShaderVariables.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CRenderable.ShaderVariables.o: ./ionGL/Texture.h
./ionScene/CRenderable.ShaderVariables.o: ./ionGL/VertexArray.h
./ionScene/CRenderable.o: ionScene/CRenderable.h
./ionScene/CRenderable.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CRenderable.o: ionConfig.h
./ionScene/CRenderable.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CRenderable.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CRenderable.o: ionMath/SVector3.h ionMath/SVector.h
./ionScene/CRenderable.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CRenderable.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CRenderable.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CRenderable.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CRenderable.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CRenderable.o: ionMath/SVector2.h ionMath/Utilities.h
./ionScene/CRenderable.o: ionMath/Constants.h
./ionScene/CRenderable.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CRenderable.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.o: ionScene/IRenderPass.h ionScene/SUniform.h
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CRenderable.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CRenderable.o: ionScene/CShaderContext.h
./ionScene/CRenderable.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CRenderable.o: ionMath/ionMath.h ionMath/SColor.h
./ionScene/CRenderable.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CRenderable.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CRenderable.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CRenderable.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CRenderable.o: ionMath/STransformation3.h ionScene/CShader.h
./ionScene/CRenderable.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CRenderable.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CRenderable.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CRenderable.o: ionScene/IRenderTarget.h ionScene/SAttribute.h
./ionScene/CRenderable.o: ionScene/CBufferObject.h
./ionScene/CRenderable.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/CRenderable.o: ./ionGL/Buffer.h ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CRenderable.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CInstanceSceneObject.o: ionScene/CInstanceSceneObject.h
./ionScene/CInstanceSceneObject.o: ionScene/CSceneObject.h
./ionScene/CInstanceSceneObject.o: ionScene/ISceneObject.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CInstanceSceneObject.o: ionCore/ionCore.h ionConfig.h
./ionScene/CInstanceSceneObject.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CInstanceSceneObject.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CInstanceSceneObject.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CInstanceSceneObject.o: ionCore/ionUtils.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CInstanceSceneObject.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CInstanceSceneObject.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CInstanceSceneObject.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CInstanceSceneObject.o: ionMath/SVector3.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CInstanceSceneObject.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CInstanceSceneObject.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CInstanceSceneObject.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CInstanceSceneObject.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CInstanceSceneObject.o: ionMath/STransformation3.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CInstanceSceneObject.o: ionScene/CBufferObject.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CInstanceSceneObject.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CInstanceSceneObject.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CInstanceSceneObject.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CInstanceSceneObject.o: ionScene/CShader.h ionScene/CTexture.h
./ionScene/CInstanceSceneObject.o: ionScene/CImage.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CInstanceSceneObject.o: ionScene/IRenderTarget.h
./ionScene/CInstanceSceneObject.o: ionScene/CShaderContext.h
./ionScene/CInstanceSceneObject.o: ionScene/IRenderPass.h
./ionScene/CInstanceSceneObject.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CInstanceSceneObject.o: ionScene/CRenderable.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CInstanceSceneObject.o: ionScene/SUniform.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CInstanceSceneObject.o: ionScene/SAttribute.h
./ionScene/CInstanceSceneObject.o: ionScene/CMeshSceneObject.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./ionScene/CInstanceSceneObject.o: ionScene/CMesh.h
./ionScene/CInstanceSceneObject.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionScene/CInstanceSceneObject.o: ionScene/SVertex.h ionScene/IScene.h
./ionScene/CInstanceSceneObject.o: ionScene/ICameraSceneObject.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionScene/ISceneObject.h
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionCore/ionCore.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionConfig.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionCore/ionComparison.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionCore/ionTypes.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionCore/ionRand.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionCore/ionSmartPtr.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionCore/ionThread.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionCore/ionTreeNode.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionCore/ionUtils.h
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/ionMath.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/SVector.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/SColor.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/SVector2.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/Utilities.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/Constants.h
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/SVector3.h
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/SVector4.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/SMatrix4.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/SBoundingBox3.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/SLine3.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/SPlane3.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/SRect2.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/STriangle2.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/STriangle3.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionMath/STransformation3.h
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/ISceneObject.ModelTransformMethods.o: ionScene/CBufferObject.h
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionGL/ionGL.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionGL/Buffer.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionGL/Program.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionGL/Shader.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionGL/Texture.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionGL/VertexArray.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionScene/CShader.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionScene/CTexture.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionScene/CImage.h
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/ISceneObject.ModelTransformMethods.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionScene/IRenderTarget.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionScene/CShaderContext.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionScene/IRenderPass.h
./ionScene/ISceneObject.ModelTransformMethods.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CShaderContext.o: ionScene/CShaderContext.h
./ionScene/CShaderContext.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CShaderContext.o: ionCore/ionCore.h ionConfig.h
./ionScene/CShaderContext.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CShaderContext.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CShaderContext.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CShaderContext.o: ionCore/ionUtils.h
./ionScene/CShaderContext.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CShaderContext.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CShaderContext.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CShaderContext.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CShaderContext.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CShaderContext.o: ionMath/SVector3.h
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CShaderContext.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CShaderContext.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CShaderContext.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CShaderContext.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CShaderContext.o: ionMath/STransformation3.h
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CShaderContext.o: ionScene/CShader.h
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CShaderContext.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CShaderContext.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CShaderContext.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CShaderContext.o: ionScene/IRenderTarget.h
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CShaderContext.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CShaderContext.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CShaderContext.o: ionGL/ionGL.h ./ionGL/Buffer.h ./ionGL/Program.h
./ionScene/CShaderContext.o: ./ionGL/Shader.h ./ionGL/Texture.h
./ionScene/CShaderContext.o: ./ionGL/VertexArray.h
./ionScene/CRenderBufferObject.o: ionScene/CRenderBufferObject.h
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CRenderBufferObject.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CRenderBufferObject.o: ionMath/ionMath.h
./ionScene/CRenderBufferObject.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CRenderBufferObject.o: ionCore/ionCore.h ionConfig.h
./ionScene/CRenderBufferObject.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScene/CRenderBufferObject.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScene/CRenderBufferObject.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScene/CRenderBufferObject.o: ionCore/ionUtils.h ionMath/SVector.h
./ionScene/CRenderBufferObject.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CRenderBufferObject.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CRenderBufferObject.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CRenderBufferObject.o: ionMath/SVector3.h
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CRenderBufferObject.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CRenderBufferObject.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CRenderBufferObject.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CRenderBufferObject.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CRenderBufferObject.o: ionMath/STransformation3.h
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CRenderBufferObject.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CRenderBufferObject.o: ionScene/IRenderTarget.h
./ionScene/CRenderBufferObject.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CRenderBufferObject.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CRenderBufferObject.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CRenderBufferObject.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/CSceneObject.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/ISceneObject.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CSceneObject.UpdateMethods.o: ionCore/ionCore.h ionConfig.h
./ionScene/CSceneObject.UpdateMethods.o: ionCore/ionComparison.h
./ionScene/CSceneObject.UpdateMethods.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CSceneObject.UpdateMethods.o: ionCore/ionSmartPtr.h
./ionScene/CSceneObject.UpdateMethods.o: ionCore/ionThread.h
./ionScene/CSceneObject.UpdateMethods.o: ionCore/ionTreeNode.h
./ionScene/CSceneObject.UpdateMethods.o: ionCore/ionUtils.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/Utilities.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/Constants.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/SVector3.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CSceneObject.UpdateMethods.o: ionMath/SVector4.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/SMatrix4.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/SBoundingBox3.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/SLine3.h ionMath/SPlane3.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/SRect2.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/STriangle2.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/STriangle3.h
./ionScene/CSceneObject.UpdateMethods.o: ionMath/STransformation3.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CSceneObject.UpdateMethods.o: ionScene/CBufferObject.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CSceneObject.UpdateMethods.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionGL/Texture.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionGL/VertexArray.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/CShader.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/CTexture.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/CImage.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/IRenderTarget.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/CShaderContext.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/IRenderPass.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/CRenderable.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CSceneObject.UpdateMethods.o: ionScene/SUniform.h
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CSceneObject.UpdateMethods.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CSceneObject.UpdateMethods.o: ionScene/SAttribute.h
./ionScene/CScene.Camera.o: ionScene/CScene.h ionConfig.h ionScene/IScene.h
./ionScene/CScene.Camera.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CScene.Camera.o: ionScene/ICameraSceneObject.h
./ionScene/CScene.Camera.o: ionScene/ISceneObject.h
./ionScene/CScene.Camera.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CScene.Camera.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CScene.Camera.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CScene.Camera.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CScene.Camera.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CScene.Camera.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CScene.Camera.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CScene.Camera.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CScene.Camera.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CScene.Camera.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CScene.Camera.o: ionMath/SVector3.h
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CScene.Camera.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CScene.Camera.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CScene.Camera.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CScene.Camera.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CScene.Camera.o: ionMath/STransformation3.h
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CScene.Camera.o: ionScene/CBufferObject.h
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CScene.Camera.o: /home/idunn01/484/ionEngine/ionGL.h ionGL/ionGL.h
./ionScene/CScene.Camera.o: ./ionGL/Buffer.h ./ionGL/Program.h
./ionScene/CScene.Camera.o: ./ionGL/Shader.h ./ionGL/Texture.h
./ionScene/CScene.Camera.o: ./ionGL/VertexArray.h ionScene/CShader.h
./ionScene/CScene.Camera.o: ionScene/CTexture.h ionScene/CImage.h
./ionScene/CScene.Camera.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CScene.Camera.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CScene.Camera.o: ionScene/IRenderTarget.h
./ionScene/CScene.Camera.o: ionScene/CShaderContext.h ionScene/IRenderPass.h
./ionScene/CScene.Camera.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.Camera.o: ionScene/CLightSceneObject.h ionScene/SUniform.h
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CScene.Camera.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CScene.Camera.o: ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.Camera.o: ionScene/CCameraSceneObject.h
./ionScene/CScene.SLightBinding.o: ionScene/CScene.h ionConfig.h
./ionScene/CScene.SLightBinding.o: ionScene/IScene.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CScene.SLightBinding.o: ionScene/ICameraSceneObject.h
./ionScene/CScene.SLightBinding.o: ionScene/ISceneObject.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CScene.SLightBinding.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CScene.SLightBinding.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CScene.SLightBinding.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CScene.SLightBinding.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CScene.SLightBinding.o: ionMath/ionMath.h ionMath/SVector.h
./ionScene/CScene.SLightBinding.o: ionMath/SColor.h ionMath/SVector2.h
./ionScene/CScene.SLightBinding.o: ionMath/Utilities.h ionMath/Constants.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CScene.SLightBinding.o: ionMath/SVector3.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CScene.SLightBinding.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CScene.SLightBinding.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CScene.SLightBinding.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CScene.SLightBinding.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CScene.SLightBinding.o: ionMath/STransformation3.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CScene.SLightBinding.o: ionScene/CBufferObject.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CScene.SLightBinding.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CScene.SLightBinding.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CScene.SLightBinding.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScene/CScene.SLightBinding.o: ionScene/CShader.h ionScene/CTexture.h
./ionScene/CScene.SLightBinding.o: ionScene/CImage.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CScene.SLightBinding.o: ionScene/IRenderTarget.h
./ionScene/CScene.SLightBinding.o: ionScene/CShaderContext.h
./ionScene/CScene.SLightBinding.o: ionScene/IRenderPass.h
./ionScene/CScene.SLightBinding.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.SLightBinding.o: ionScene/CLightSceneObject.h
./ionScene/CScene.SLightBinding.o: ionScene/SUniform.h
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CScene.SLightBinding.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CScene.SLightBinding.o: ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.SLightBinding.o: ionScene/CCameraSceneObject.h
./ionScene/CRenderable.SMaterial.o: ionScene/CRenderable.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScene/CRenderable.SMaterial.o: ionConfig.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScene/CRenderable.SMaterial.o: ionMath/SVector3.h ionMath/SVector.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScene/CRenderable.SMaterial.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScene/CRenderable.SMaterial.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScene/CRenderable.SMaterial.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScene/CRenderable.SMaterial.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScene/CRenderable.SMaterial.o: ionMath/SVector2.h ionMath/Utilities.h
./ionScene/CRenderable.SMaterial.o: ionMath/Constants.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScene/CRenderable.SMaterial.o: ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.SMaterial.o: ionScene/IRenderPass.h
./ionScene/CRenderable.SMaterial.o: ionScene/SUniform.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScene/CRenderable.SMaterial.o: ionScene/CShaderContext.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScene/CRenderable.SMaterial.o: ionMath/ionMath.h ionMath/SColor.h
./ionScene/CRenderable.SMaterial.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScene/CRenderable.SMaterial.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScene/CRenderable.SMaterial.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScene/CRenderable.SMaterial.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScene/CRenderable.SMaterial.o: ionMath/STransformation3.h
./ionScene/CRenderable.SMaterial.o: ionScene/CShader.h ionScene/CTexture.h
./ionScene/CRenderable.SMaterial.o: ionScene/CImage.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScene/CRenderable.SMaterial.o: ionScene/IRenderTarget.h
./ionScene/CRenderable.SMaterial.o: ionScene/SAttribute.h
./ionScene/CRenderable.SMaterial.o: ionScene/CBufferObject.h
./ionScene/CRenderable.SMaterial.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScene/CRenderable.SMaterial.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScene/CRenderable.SMaterial.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScene/CRenderable.SMaterial.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionWindow/CGamePad.o: ionWindow/CGamePad.h
./ionWindow/CGamePad.o: /home/idunn01/484/ionEngine/ionMath.h
./ionWindow/CGamePad.o: ionMath/ionMath.h
./ionWindow/CGamePad.o: /home/idunn01/484/ionEngine/ionCore.h
./ionWindow/CGamePad.o: ionCore/ionCore.h ionConfig.h ionCore/ionComparison.h
./ionWindow/CGamePad.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionWindow/CGamePad.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionWindow/CGamePad.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionWindow/CGamePad.o: ionMath/SVector.h ionMath/SColor.h ionMath/SVector2.h
./ionWindow/CGamePad.o: ionMath/Utilities.h ionMath/Constants.h
./ionWindow/CGamePad.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionWindow/CGamePad.o: ionMath/SVector3.h
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionWindow/CGamePad.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionWindow/CGamePad.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionWindow/CGamePad.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionWindow/CGamePad.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionWindow/CGamePad.o: ionMath/STransformation3.h
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionWindow/CGamePad.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionWindow/CGamePad.o: ionWindow/EGamePadButton.h
./ionWindow/CWindow.o: ionWindow/CWindow.h
./ionWindow/CWindow.o: /home/idunn01/484/ionEngine/ionFramework/SEvent.h
./ionWindow/CWindow.o: /home/idunn01/484/ionEngine/ionCore.h
./ionWindow/CWindow.o: ionCore/ionCore.h ionConfig.h ionCore/ionComparison.h
./ionWindow/CWindow.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionWindow/CWindow.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionWindow/CWindow.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionWindow/CWindow.o: ionFramework/SEventData.h
./ionWindow/CWindow.o: ionFramework/IEventListener.h
./ionWindow/CWindow.o: ionWindow/SKeyboardEvent.h ionWindow/EKey.h
./ionWindow/CWindow.o: ionWindow/SMouseEvent.h
./ionWindow/CWindow.o: /home/idunn01/484/ionEngine/ionMath.h
./ionWindow/CWindow.o: ionMath/ionMath.h ionMath/SVector.h ionMath/SColor.h
./ionWindow/CWindow.o: ionMath/SVector2.h ionMath/Utilities.h
./ionWindow/CWindow.o: ionMath/Constants.h
./ionWindow/CWindow.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionWindow/CWindow.o: ionMath/SVector3.h
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionWindow/CWindow.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionWindow/CWindow.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionWindow/CWindow.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionWindow/CWindow.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionWindow/CWindow.o: ionMath/STransformation3.h
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionWindow/CWindow.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionWindow/CWindow.o: ionWindow/SWindowResizedEvent.h
./ionWindow/CWindow.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionWindow/CWindow.o: /home/idunn01/484/deps/glfw/include/GLFW/glfw3.h
./ionWindow/CWindowManager.o: ionWindow/CWindowManager.h
./ionWindow/CWindowManager.o: /home/idunn01/484/ionEngine/ionMath.h
./ionWindow/CWindowManager.o: ionMath/ionMath.h
./ionWindow/CWindowManager.o: /home/idunn01/484/ionEngine/ionCore.h
./ionWindow/CWindowManager.o: ionCore/ionCore.h ionConfig.h
./ionWindow/CWindowManager.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionWindow/CWindowManager.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionWindow/CWindowManager.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionWindow/CWindowManager.o: ionCore/ionUtils.h ionMath/SVector.h
./ionWindow/CWindowManager.o: ionMath/SColor.h ionMath/SVector2.h
./ionWindow/CWindowManager.o: ionMath/Utilities.h ionMath/Constants.h
./ionWindow/CWindowManager.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionWindow/CWindowManager.o: ionMath/SVector3.h
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionWindow/CWindowManager.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionWindow/CWindowManager.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionWindow/CWindowManager.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionWindow/CWindowManager.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionWindow/CWindowManager.o: ionMath/STransformation3.h
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionWindow/CWindowManager.o: ionWindow/CWindow.h
./ionWindow/CWindowManager.o: /home/idunn01/484/ionEngine/ionFramework/SEvent.h
./ionWindow/CWindowManager.o: ionFramework/SEventData.h
./ionWindow/CWindowManager.o: ionFramework/IEventListener.h
./ionWindow/CWindowManager.o: ionWindow/SKeyboardEvent.h ionWindow/EKey.h
./ionWindow/CWindowManager.o: ionWindow/SMouseEvent.h
./ionWindow/CWindowManager.o: ionWindow/SWindowResizedEvent.h
./ionWindow/CWindowManager.o: ionWindow/CGamePad.h ionWindow/EGamePadButton.h
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionWindow/CWindowManager.o: /home/idunn01/484/deps/glfw/include/GLFW/glfw3.h
./ionScience/STable.o: ionScience/STable.h
./ionScience/STable.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScience/STable.o: ionCore/ionCore.h ionConfig.h ionCore/ionComparison.h
./ionScience/STable.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScience/STable.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScience/STable.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScience/STable.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScience/STable.o: ionMath/ionMath.h ionMath/SVector.h ionMath/SColor.h
./ionScience/STable.o: ionMath/SVector2.h ionMath/Utilities.h
./ionScience/STable.o: ionMath/Constants.h
./ionScience/STable.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScience/STable.o: ionMath/SVector3.h
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScience/STable.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScience/STable.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScience/STable.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScience/STable.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScience/STable.o: ionMath/STransformation3.h
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScience/STable.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScience/STable.o: ionScience/SRange.h ionScience/IDataRecord.h
./ionScience/STable.o: ionScience/IDatabase.h
./ionScience/STable.Row.o: ionScience/STable.h
./ionScience/STable.Row.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScience/STable.Row.o: ionCore/ionCore.h ionConfig.h
./ionScience/STable.Row.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScience/STable.Row.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScience/STable.Row.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScience/STable.Row.o: ionCore/ionUtils.h
./ionScience/STable.Row.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScience/STable.Row.o: ionMath/ionMath.h ionMath/SVector.h
./ionScience/STable.Row.o: ionMath/SColor.h ionMath/SVector2.h
./ionScience/STable.Row.o: ionMath/Utilities.h ionMath/Constants.h
./ionScience/STable.Row.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScience/STable.Row.o: ionMath/SVector3.h
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScience/STable.Row.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScience/STable.Row.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScience/STable.Row.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScience/STable.Row.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScience/STable.Row.o: ionMath/STransformation3.h
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScience/STable.Row.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScience/STable.Row.o: ionScience/SRange.h ionScience/IDataRecord.h
./ionScience/STable.Row.o: ionScience/IDatabase.h
./ionScience/MarchingCubes.o: ionScience/MarchingCubes.h
./ionScience/MarchingCubes.o: /home/idunn01/484/ionEngine/ionScene/CMesh.h
./ionScience/MarchingCubes.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionScience/MarchingCubes.o: ionMath/SVector3.h ionConfig.h
./ionScience/MarchingCubes.o: ionMath/SVector.h
./ionScience/MarchingCubes.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScience/MarchingCubes.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionScience/MarchingCubes.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScience/MarchingCubes.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionScience/MarchingCubes.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScience/MarchingCubes.o: ionMath/SVector2.h ionMath/Utilities.h
./ionScience/MarchingCubes.o: ionMath/Constants.h
./ionScience/MarchingCubes.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScience/MarchingCubes.o: ionMath/SLine3.h ionScene/SVertex.h
./ionScience/MarchingCubes.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScience/MarchingCubes.o: ionMath/ionMath.h ionMath/SColor.h
./ionScience/MarchingCubes.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScience/MarchingCubes.o: ionMath/SBoundingBox3.h ionMath/SPlane3.h
./ionScience/MarchingCubes.o: ionMath/SRect2.h ionMath/STriangle2.h
./ionScience/MarchingCubes.o: ionMath/STriangle3.h ionMath/STransformation3.h
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScience/MarchingCubes.o: ionScene/CBufferObject.h
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionScience/MarchingCubes.o: /home/idunn01/484/ionEngine/ionGL.h
./ionScience/MarchingCubes.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionScience/MarchingCubes.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionScience/MarchingCubes.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionScience/MarchingCubes.o: ionScene/CRenderable.h
./ionScience/MarchingCubes.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionScience/MarchingCubes.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionScience/MarchingCubes.o: ionScene/ISceneObject.Enumerations.h
./ionScience/MarchingCubes.o: ionScene/IRenderPass.h ionScene/SUniform.h
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionScience/MarchingCubes.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionScience/MarchingCubes.o: ionScene/CShaderContext.h ionScene/CShader.h
./ionScience/MarchingCubes.o: ionScene/CTexture.h ionScene/CImage.h
./ionScience/MarchingCubes.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionScience/MarchingCubes.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionScience/MarchingCubes.o: ionScene/IRenderTarget.h ionScene/SAttribute.h
./ionScience/MarchingCubes.o: ionScience/SVolume.h ionScience/Interpolation.h
./ionScience/MarchingCubes.o: ./ionScience/MarchingCubesLookupTables.h
./ionScience/MarchingCubes.o: ionScience/CColorTable.h
./ionScience/CColorTable.o: ionScience/CColorTable.h
./ionScience/CColorTable.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScience/CColorTable.o: ionMath/ionMath.h
./ionScience/CColorTable.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScience/CColorTable.o: ionCore/ionCore.h ionConfig.h
./ionScience/CColorTable.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScience/CColorTable.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScience/CColorTable.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScience/CColorTable.o: ionCore/ionUtils.h ionMath/SVector.h
./ionScience/CColorTable.o: ionMath/SColor.h ionMath/SVector2.h
./ionScience/CColorTable.o: ionMath/Utilities.h ionMath/Constants.h
./ionScience/CColorTable.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScience/CColorTable.o: ionMath/SVector3.h
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScience/CColorTable.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScience/CColorTable.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScience/CColorTable.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScience/CColorTable.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionScience/CColorTable.o: ionMath/STransformation3.h
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScience/CColorTable.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScience/CColorTable.o: ./ionScience/DefaultColorTable.h
./ionScience/IProgressBar.o: ionScience/IProgressBar.h
./ionScience/IProgressBar.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScience/IProgressBar.o: ionCore/ionCore.h ionConfig.h
./ionScience/IProgressBar.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionScience/IProgressBar.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionScience/IProgressBar.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionScience/IProgressBar.o: ionCore/ionUtils.h
./ionScience/STable.FieldIterator.o: ionScience/STable.h
./ionScience/STable.FieldIterator.o: /home/idunn01/484/ionEngine/ionCore.h
./ionScience/STable.FieldIterator.o: ionCore/ionCore.h ionConfig.h
./ionScience/STable.FieldIterator.o: ionCore/ionComparison.h
./ionScience/STable.FieldIterator.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionScience/STable.FieldIterator.o: ionCore/ionSmartPtr.h
./ionScience/STable.FieldIterator.o: ionCore/ionThread.h
./ionScience/STable.FieldIterator.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionScience/STable.FieldIterator.o: /home/idunn01/484/ionEngine/ionMath.h
./ionScience/STable.FieldIterator.o: ionMath/ionMath.h ionMath/SVector.h
./ionScience/STable.FieldIterator.o: ionMath/SColor.h ionMath/SVector2.h
./ionScience/STable.FieldIterator.o: ionMath/Utilities.h ionMath/Constants.h
./ionScience/STable.FieldIterator.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionScience/STable.FieldIterator.o: ionMath/SVector3.h
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionScience/STable.FieldIterator.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionScience/STable.FieldIterator.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionScience/STable.FieldIterator.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionScience/STable.FieldIterator.o: ionMath/STriangle2.h
./ionScience/STable.FieldIterator.o: ionMath/STriangle3.h
./ionScience/STable.FieldIterator.o: ionMath/STransformation3.h
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionScience/STable.FieldIterator.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionScience/STable.FieldIterator.o: ionScience/SRange.h
./ionScience/STable.FieldIterator.o: ionScience/IDataRecord.h
./ionScience/STable.FieldIterator.o: ionScience/IDatabase.h
./ionFramework/CCameraControl.o: ionFramework/CCameraControl.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./ionFramework/CCameraControl.o: ionConfig.h ionMath/SVector.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionCore.h
./ionFramework/CCameraControl.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionFramework/CCameraControl.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionFramework/CCameraControl.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionFramework/CCameraControl.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionFramework/CCameraControl.o: ionMath/SVector2.h ionMath/Utilities.h
./ionFramework/CCameraControl.o: ionMath/Constants.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionScene.h
./ionFramework/CCameraControl.o: ionScene/ionScene.h ionScene/CMesh.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionFramework/CCameraControl.o: ionMath/SVector3.h ionMath/SLine3.h
./ionFramework/CCameraControl.o: ionScene/SVertex.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionMath.h
./ionFramework/CCameraControl.o: ionMath/ionMath.h ionMath/SColor.h
./ionFramework/CCameraControl.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionFramework/CCameraControl.o: ionMath/SBoundingBox3.h ionMath/SPlane3.h
./ionFramework/CCameraControl.o: ionMath/SRect2.h ionMath/STriangle2.h
./ionFramework/CCameraControl.o: ionMath/STriangle3.h
./ionFramework/CCameraControl.o: ionMath/STransformation3.h
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionFramework/CCameraControl.o: ionScene/CBufferObject.h
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionGL.h
./ionFramework/CCameraControl.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionFramework/CCameraControl.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionFramework/CCameraControl.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionFramework/CCameraControl.o: ionScene/CRenderable.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionFramework/CCameraControl.o: ionScene/ISceneObject.Enumerations.h
./ionFramework/CCameraControl.o: ionScene/IRenderPass.h ionScene/SUniform.h
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionFramework/CCameraControl.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionFramework/CCameraControl.o: ionScene/CShaderContext.h ionScene/CShader.h
./ionFramework/CCameraControl.o: ionScene/CTexture.h ionScene/CImage.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionFramework/CCameraControl.o: ionScene/IRenderTarget.h
./ionFramework/CCameraControl.o: ionScene/SAttribute.h ionScene/CMeshLoader.h
./ionFramework/CCameraControl.o: ionScene/CMeshSceneObject.h
./ionFramework/CCameraControl.o: ionScene/CSceneObject.h
./ionFramework/CCameraControl.o: ionScene/ISceneObject.h
./ionFramework/CCameraControl.o: ionScene/CInstanceSceneObject.h
./ionFramework/CCameraControl.o: ionScene/CShaderLoader.h
./ionFramework/CCameraControl.o: ionScene/CImageLoader.h
./ionFramework/CCameraControl.o: ionScene/CSceneManager.h
./ionFramework/CCameraControl.o: ionScene/CFrameBufferObject.h
./ionFramework/CCameraControl.o: ionScene/CRenderBufferObject.h
./ionFramework/CCameraControl.o: ionScene/CSceneEffectManager.h
./ionFramework/CCameraControl.o: ionScene/CPerspectiveCameraSceneObject.h
./ionFramework/CCameraControl.o: ionScene/CCameraSceneObject.h
./ionFramework/CCameraControl.o: ionScene/ICameraSceneObject.h
./ionFramework/CCameraControl.o: ionScene/CScene.h ionScene/IScene.h
./ionFramework/CCameraControl.o: ionScene/CLightSceneObject.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionMath/SLine3.h
./ionFramework/CCameraControl.o: ionScene/CDefaultColorRenderPass.h
./ionFramework/CCameraControl.o: ionScene/CMultiOutRenderPass.h
./ionFramework/CCameraControl.o: ionScene/CDeferredShadingManager.h
./ionFramework/CCameraControl.o: ionScene/CPointLightSceneObject.h
./ionFramework/CCameraControl.o: ionScene/CDirectionalLightSceneObject.h
./ionFramework/CCameraControl.o: ionFramework/CApplication.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionWindow.h
./ionFramework/CCameraControl.o: ionWindow/ionWindow.h ionWindow/EKey.h
./ionFramework/CCameraControl.o: ionWindow/SKeyboardEvent.h
./ionFramework/CCameraControl.o: /home/idunn01/484/ionEngine/ionFramework/SEvent.h
./ionFramework/CCameraControl.o: ionFramework/SEventData.h
./ionFramework/CCameraControl.o: ionFramework/IEventListener.h
./ionFramework/CCameraControl.o: ionWindow/SMouseEvent.h
./ionFramework/CCameraControl.o: ionWindow/SWindowResizedEvent.h
./ionFramework/CCameraControl.o: ionWindow/CWindow.h
./ionFramework/CCameraControl.o: ionWindow/CWindowManager.h
./ionFramework/CCameraControl.o: ionWindow/CGamePad.h
./ionFramework/CCameraControl.o: ionWindow/EGamePadButton.h
./ionFramework/CCameraControl.o: ionFramework/CStateManager.h
./ionFramework/CCameraControl.o: ionFramework/IState.h
./ionFramework/CApplication.o: ionFramework/CApplication.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionCore.h
./ionFramework/CApplication.o: ionCore/ionCore.h ionConfig.h
./ionFramework/CApplication.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionFramework/CApplication.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionFramework/CApplication.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionFramework/CApplication.o: ionCore/ionUtils.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionScene.h
./ionFramework/CApplication.o: ionScene/ionScene.h ionScene/CMesh.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionFramework/CApplication.o: ionMath/SVector3.h ionMath/SVector.h
./ionFramework/CApplication.o: ionMath/SVector2.h ionMath/Utilities.h
./ionFramework/CApplication.o: ionMath/Constants.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionFramework/CApplication.o: ionMath/SLine3.h ionScene/SVertex.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionMath.h
./ionFramework/CApplication.o: ionMath/ionMath.h ionMath/SColor.h
./ionFramework/CApplication.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionFramework/CApplication.o: ionMath/SBoundingBox3.h ionMath/SPlane3.h
./ionFramework/CApplication.o: ionMath/SRect2.h ionMath/STriangle2.h
./ionFramework/CApplication.o: ionMath/STriangle3.h
./ionFramework/CApplication.o: ionMath/STransformation3.h
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionFramework/CApplication.o: ionScene/CBufferObject.h
./ionFramework/CApplication.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionGL.h
./ionFramework/CApplication.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionFramework/CApplication.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionFramework/CApplication.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionFramework/CApplication.o: ionScene/CRenderable.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionFramework/CApplication.o: ionScene/ISceneObject.Enumerations.h
./ionFramework/CApplication.o: ionScene/IRenderPass.h ionScene/SUniform.h
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionFramework/CApplication.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionFramework/CApplication.o: ionScene/CShaderContext.h ionScene/CShader.h
./ionFramework/CApplication.o: ionScene/CTexture.h ionScene/CImage.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionFramework/CApplication.o: ionScene/IRenderTarget.h ionScene/SAttribute.h
./ionFramework/CApplication.o: ionScene/CMeshLoader.h
./ionFramework/CApplication.o: ionScene/CMeshSceneObject.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./ionFramework/CApplication.o: ionScene/CSceneObject.h
./ionFramework/CApplication.o: ionScene/ISceneObject.h
./ionFramework/CApplication.o: ionScene/CInstanceSceneObject.h
./ionFramework/CApplication.o: ionScene/CShaderLoader.h
./ionFramework/CApplication.o: ionScene/CImageLoader.h
./ionFramework/CApplication.o: ionScene/CSceneManager.h
./ionFramework/CApplication.o: ionScene/CFrameBufferObject.h
./ionFramework/CApplication.o: ionScene/CRenderBufferObject.h
./ionFramework/CApplication.o: ionScene/CSceneEffectManager.h
./ionFramework/CApplication.o: ionScene/CPerspectiveCameraSceneObject.h
./ionFramework/CApplication.o: ionScene/CCameraSceneObject.h
./ionFramework/CApplication.o: ionScene/ICameraSceneObject.h
./ionFramework/CApplication.o: ionScene/CScene.h ionScene/IScene.h
./ionFramework/CApplication.o: ionScene/CLightSceneObject.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionMath/SLine3.h
./ionFramework/CApplication.o: ionScene/CDefaultColorRenderPass.h
./ionFramework/CApplication.o: ionScene/CMultiOutRenderPass.h
./ionFramework/CApplication.o: ionScene/CDeferredShadingManager.h
./ionFramework/CApplication.o: ionScene/CPointLightSceneObject.h
./ionFramework/CApplication.o: ionScene/CDirectionalLightSceneObject.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionWindow.h
./ionFramework/CApplication.o: ionWindow/ionWindow.h ionWindow/EKey.h
./ionFramework/CApplication.o: ionWindow/SKeyboardEvent.h
./ionFramework/CApplication.o: /home/idunn01/484/ionEngine/ionFramework/SEvent.h
./ionFramework/CApplication.o: ionFramework/SEventData.h
./ionFramework/CApplication.o: ionFramework/IEventListener.h
./ionFramework/CApplication.o: ionWindow/SMouseEvent.h
./ionFramework/CApplication.o: ionWindow/SWindowResizedEvent.h
./ionFramework/CApplication.o: ionWindow/CWindow.h ionWindow/CWindowManager.h
./ionFramework/CApplication.o: ionWindow/CGamePad.h
./ionFramework/CApplication.o: ionWindow/EGamePadButton.h
./ionFramework/CApplication.o: ionFramework/CStateManager.h
./ionFramework/CApplication.o: ionFramework/IState.h
./ionFramework/CApplication.o: /home/idunn01/484/deps/glfw/include/GLFW/glfw3.h
./ionFramework/COrthoCamera.o: ./ionFramework/COrthoCamera.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./ionFramework/COrthoCamera.o: ionConfig.h ionMath/SVector.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionCore.h
./ionFramework/COrthoCamera.o: ionCore/ionCore.h ionCore/ionComparison.h
./ionFramework/COrthoCamera.o: ionCore/ionTypes.h ionCore/ionRand.h
./ionFramework/COrthoCamera.o: ionCore/ionSmartPtr.h ionCore/ionThread.h
./ionFramework/COrthoCamera.o: ionCore/ionTreeNode.h ionCore/ionUtils.h
./ionFramework/COrthoCamera.o: ionMath/SVector2.h ionMath/Utilities.h
./ionFramework/COrthoCamera.o: ionMath/Constants.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionScene/CCameraSceneObject.h
./ionFramework/COrthoCamera.o: ionScene/ICameraSceneObject.h
./ionFramework/COrthoCamera.o: ionScene/ISceneObject.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionMath.h
./ionFramework/COrthoCamera.o: ionMath/ionMath.h ionMath/SColor.h
./ionFramework/COrthoCamera.o: ionMath/SVector3.h ionMath/SVector4.h
./ionFramework/COrthoCamera.o: ionMath/SMatrix4.h ionMath/SBoundingBox3.h
./ionFramework/COrthoCamera.o: ionMath/SLine3.h ionMath/SPlane3.h
./ionFramework/COrthoCamera.o: ionMath/SRect2.h ionMath/STriangle2.h
./ionFramework/COrthoCamera.o: ionMath/STriangle3.h
./ionFramework/COrthoCamera.o: ionMath/STransformation3.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionFramework/COrthoCamera.o: ionScene/CBufferObject.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionGL.h
./ionFramework/COrthoCamera.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionFramework/COrthoCamera.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionFramework/COrthoCamera.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionFramework/COrthoCamera.o: ionScene/CShader.h ionScene/CTexture.h
./ionFramework/COrthoCamera.o: ionScene/CImage.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionFramework/COrthoCamera.o: ionScene/IRenderTarget.h
./ionFramework/COrthoCamera.o: ionScene/CShaderContext.h
./ionFramework/COrthoCamera.o: ionScene/IRenderPass.h
./ionFramework/COrthoCamera.o: ionScene/ISceneObject.Enumerations.h
./ionFramework/COrthoCamera.o: ionFramework/CApplication.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionScene.h
./ionFramework/COrthoCamera.o: ionScene/ionScene.h ionScene/CMesh.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionFramework/COrthoCamera.o: ionScene/SVertex.h ionScene/CRenderable.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionFramework/COrthoCamera.o: ionScene/SUniform.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionFramework/COrthoCamera.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionFramework/COrthoCamera.o: ionScene/SAttribute.h ionScene/CMeshLoader.h
./ionFramework/COrthoCamera.o: ionScene/CMeshSceneObject.h
./ionFramework/COrthoCamera.o: ionScene/CSceneObject.h
./ionFramework/COrthoCamera.o: ionScene/CInstanceSceneObject.h
./ionFramework/COrthoCamera.o: ionScene/CShaderLoader.h
./ionFramework/COrthoCamera.o: ionScene/CImageLoader.h
./ionFramework/COrthoCamera.o: ionScene/CSceneManager.h
./ionFramework/COrthoCamera.o: ionScene/CFrameBufferObject.h
./ionFramework/COrthoCamera.o: ionScene/CRenderBufferObject.h
./ionFramework/COrthoCamera.o: ionScene/CSceneEffectManager.h
./ionFramework/COrthoCamera.o: ionScene/CPerspectiveCameraSceneObject.h
./ionFramework/COrthoCamera.o: ionScene/CCameraSceneObject.h
./ionFramework/COrthoCamera.o: ionScene/CScene.h ionScene/IScene.h
./ionFramework/COrthoCamera.o: ionScene/CLightSceneObject.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionMath/SLine3.h
./ionFramework/COrthoCamera.o: ionScene/CDefaultColorRenderPass.h
./ionFramework/COrthoCamera.o: ionScene/CMultiOutRenderPass.h
./ionFramework/COrthoCamera.o: ionScene/CDeferredShadingManager.h
./ionFramework/COrthoCamera.o: ionScene/CPointLightSceneObject.h
./ionFramework/COrthoCamera.o: ionScene/CDirectionalLightSceneObject.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionWindow.h
./ionFramework/COrthoCamera.o: ionWindow/ionWindow.h ionWindow/EKey.h
./ionFramework/COrthoCamera.o: ionWindow/SKeyboardEvent.h
./ionFramework/COrthoCamera.o: /home/idunn01/484/ionEngine/ionFramework/SEvent.h
./ionFramework/COrthoCamera.o: ionFramework/SEventData.h
./ionFramework/COrthoCamera.o: ionFramework/IEventListener.h
./ionFramework/COrthoCamera.o: ionWindow/SMouseEvent.h
./ionFramework/COrthoCamera.o: ionWindow/SWindowResizedEvent.h
./ionFramework/COrthoCamera.o: ionWindow/CWindow.h ionWindow/CWindowManager.h
./ionFramework/COrthoCamera.o: ionWindow/CGamePad.h
./ionFramework/COrthoCamera.o: ionWindow/EGamePadButton.h
./ionFramework/COrthoCamera.o: ionFramework/CStateManager.h
./ionFramework/COrthoCamera.o: ionFramework/IState.h
./ionFramework/CStateManager.o: ionFramework/CStateManager.h
./ionFramework/CStateManager.o: ionFramework/IState.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionCore.h
./ionFramework/CStateManager.o: ionCore/ionCore.h ionConfig.h
./ionFramework/CStateManager.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionFramework/CStateManager.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionFramework/CStateManager.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionFramework/CStateManager.o: ionCore/ionUtils.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionWindow.h
./ionFramework/CStateManager.o: ionWindow/ionWindow.h ionWindow/EKey.h
./ionFramework/CStateManager.o: ionWindow/SKeyboardEvent.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionFramework/SEvent.h
./ionFramework/CStateManager.o: ionFramework/SEventData.h
./ionFramework/CStateManager.o: ionFramework/IEventListener.h
./ionFramework/CStateManager.o: ionWindow/SMouseEvent.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionMath.h
./ionFramework/CStateManager.o: ionMath/ionMath.h ionMath/SVector.h
./ionFramework/CStateManager.o: ionMath/SColor.h ionMath/SVector2.h
./ionFramework/CStateManager.o: ionMath/Utilities.h ionMath/Constants.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionFramework/CStateManager.o: ionMath/SVector3.h
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionFramework/CStateManager.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionFramework/CStateManager.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionFramework/CStateManager.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionFramework/CStateManager.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionFramework/CStateManager.o: ionMath/STransformation3.h
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionFramework/CStateManager.o: ionWindow/SWindowResizedEvent.h
./ionFramework/CStateManager.o: ionWindow/CWindow.h
./ionFramework/CStateManager.o: ionWindow/CWindowManager.h
./ionFramework/CStateManager.o: ionWindow/CGamePad.h
./ionFramework/CStateManager.o: ionWindow/EGamePadButton.h
./ionFramework/CStateManager.o: ionFramework/CApplication.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionScene.h
./ionFramework/CStateManager.o: ionScene/ionScene.h ionScene/CMesh.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionFramework/CStateManager.o: ionScene/SVertex.h ionScene/CBufferObject.h
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionGL.h
./ionFramework/CStateManager.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionFramework/CStateManager.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionFramework/CStateManager.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionFramework/CStateManager.o: ionScene/CRenderable.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionFramework/CStateManager.o: ionScene/ISceneObject.Enumerations.h
./ionFramework/CStateManager.o: ionScene/IRenderPass.h ionScene/SUniform.h
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionFramework/CStateManager.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionFramework/CStateManager.o: ionScene/CShaderContext.h ionScene/CShader.h
./ionFramework/CStateManager.o: ionScene/CTexture.h ionScene/CImage.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionFramework/CStateManager.o: ionScene/IRenderTarget.h
./ionFramework/CStateManager.o: ionScene/SAttribute.h ionScene/CMeshLoader.h
./ionFramework/CStateManager.o: ionScene/CMeshSceneObject.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./ionFramework/CStateManager.o: ionScene/CSceneObject.h
./ionFramework/CStateManager.o: ionScene/ISceneObject.h
./ionFramework/CStateManager.o: ionScene/CInstanceSceneObject.h
./ionFramework/CStateManager.o: ionScene/CShaderLoader.h
./ionFramework/CStateManager.o: ionScene/CImageLoader.h
./ionFramework/CStateManager.o: ionScene/CSceneManager.h
./ionFramework/CStateManager.o: ionScene/CFrameBufferObject.h
./ionFramework/CStateManager.o: ionScene/CRenderBufferObject.h
./ionFramework/CStateManager.o: ionScene/CSceneEffectManager.h
./ionFramework/CStateManager.o: ionScene/CPerspectiveCameraSceneObject.h
./ionFramework/CStateManager.o: ionScene/CCameraSceneObject.h
./ionFramework/CStateManager.o: ionScene/ICameraSceneObject.h
./ionFramework/CStateManager.o: ionScene/CScene.h ionScene/IScene.h
./ionFramework/CStateManager.o: ionScene/CLightSceneObject.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionMath/SLine3.h
./ionFramework/CStateManager.o: ionScene/CDefaultColorRenderPass.h
./ionFramework/CStateManager.o: ionScene/CMultiOutRenderPass.h
./ionFramework/CStateManager.o: ionScene/CDeferredShadingManager.h
./ionFramework/CStateManager.o: ionScene/CPointLightSceneObject.h
./ionFramework/CStateManager.o: ionScene/CDirectionalLightSceneObject.h
./ionFramework/CStateManager.o: /home/idunn01/484/ionEngine/ionWindow/CWindow.h
./ionFramework/CFadeOutState.o: ionFramework/CFadeOutState.h
./ionFramework/CFadeOutState.o: ionFramework/CStateManager.h
./ionFramework/CFadeOutState.o: ionFramework/IState.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionCore.h
./ionFramework/CFadeOutState.o: ionCore/ionCore.h ionConfig.h
./ionFramework/CFadeOutState.o: ionCore/ionComparison.h ionCore/ionTypes.h
./ionFramework/CFadeOutState.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionFramework/CFadeOutState.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionFramework/CFadeOutState.o: ionCore/ionUtils.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionWindow.h
./ionFramework/CFadeOutState.o: ionWindow/ionWindow.h ionWindow/EKey.h
./ionFramework/CFadeOutState.o: ionWindow/SKeyboardEvent.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionFramework/SEvent.h
./ionFramework/CFadeOutState.o: ionFramework/SEventData.h
./ionFramework/CFadeOutState.o: ionFramework/IEventListener.h
./ionFramework/CFadeOutState.o: ionWindow/SMouseEvent.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionMath.h
./ionFramework/CFadeOutState.o: ionMath/ionMath.h ionMath/SVector.h
./ionFramework/CFadeOutState.o: ionMath/SColor.h ionMath/SVector2.h
./ionFramework/CFadeOutState.o: ionMath/Utilities.h ionMath/Constants.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionCore/ionTypes.h
./ionFramework/CFadeOutState.o: ionMath/SVector3.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/core/_fixes.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/core/setup.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/setup.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/_vectorize.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_half.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/_detail.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_float.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_int.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_gentype.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_size.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle_func.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec1.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec2.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec3.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_vec4.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x2.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x3.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat2x4.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x2.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x3.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat3x4.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x2.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x3.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/type_mat4x4.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_trigonometric.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_exponential.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/_fixes.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_common.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_packing.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_geometric.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_matrix.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_vector_relational.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_integer.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/func_noise.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/./core/_swizzle.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/glm.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtc/matrix_transform.inl
./ionFramework/CFadeOutState.o: ionMath/SVector4.h ionMath/SMatrix4.h
./ionFramework/CFadeOutState.o: ionMath/SBoundingBox3.h ionMath/SLine3.h
./ionFramework/CFadeOutState.o: ionMath/SPlane3.h ionMath/SRect2.h
./ionFramework/CFadeOutState.o: ionMath/STriangle2.h ionMath/STriangle3.h
./ionFramework/CFadeOutState.o: ionMath/STransformation3.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtc/half_float.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtx/euler_angles.inl
./ionFramework/CFadeOutState.o: ionWindow/SWindowResizedEvent.h
./ionFramework/CFadeOutState.o: ionWindow/CWindow.h
./ionFramework/CFadeOutState.o: ionWindow/CWindowManager.h
./ionFramework/CFadeOutState.o: ionWindow/CGamePad.h
./ionFramework/CFadeOutState.o: ionWindow/EGamePadButton.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionScene/CFrameBufferObject.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glew/include/GL/glew.h
./ionFramework/CFadeOutState.o: ionScene/CRenderBufferObject.h
./ionFramework/CFadeOutState.o: ionScene/IRenderTarget.h ionScene/CTexture.h
./ionFramework/CFadeOutState.o: ionScene/CImage.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionMath/SVector2.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionMath/SColor.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionScene/CTexture.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionScene/CSceneManager.h
./ionFramework/CFadeOutState.o: ionScene/CSceneObject.h
./ionFramework/CFadeOutState.o: ionScene/ISceneObject.h
./ionFramework/CFadeOutState.o: ionScene/CBufferObject.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionGL.h
./ionFramework/CFadeOutState.o: ionGL/ionGL.h ./ionGL/Buffer.h
./ionFramework/CFadeOutState.o: ./ionGL/Program.h ./ionGL/Shader.h
./ionFramework/CFadeOutState.o: ./ionGL/Texture.h ./ionGL/VertexArray.h
./ionFramework/CFadeOutState.o: ionScene/CShader.h ionScene/CShaderContext.h
./ionFramework/CFadeOutState.o: ionScene/IRenderPass.h
./ionFramework/CFadeOutState.o: ionScene/ISceneObject.Enumerations.h
./ionFramework/CFadeOutState.o: ionScene/CRenderable.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionCore/ionSmartPtr.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionMath/STransformation3.h
./ionFramework/CFadeOutState.o: ionScene/SUniform.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.hpp
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtc/constants.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtc/quaternion.inl
./ionFramework/CFadeOutState.o: /home/idunn01/484/deps/glm/include/glm/gtc/type_ptr.inl
./ionFramework/CFadeOutState.o: ionScene/SAttribute.h
./ionFramework/CFadeOutState.o: ionScene/CMeshSceneObject.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionMath/SVector3.h
./ionFramework/CFadeOutState.o: ionScene/CMesh.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionMath/SBoundingBox3.h
./ionFramework/CFadeOutState.o: ionScene/SVertex.h
./ionFramework/CFadeOutState.o: ionScene/CFrameBufferObject.h
./ionFramework/CFadeOutState.o: ionScene/CSceneEffectManager.h
./ionFramework/CFadeOutState.o: ionScene/CPerspectiveCameraSceneObject.h
./ionFramework/CFadeOutState.o: ionScene/CCameraSceneObject.h
./ionFramework/CFadeOutState.o: ionScene/ICameraSceneObject.h
./ionFramework/CFadeOutState.o: ionScene/CScene.h ionScene/IScene.h
./ionFramework/CFadeOutState.o: ionScene/CLightSceneObject.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionMath/SLine3.h
./ionFramework/CFadeOutState.o: ionScene/CDefaultColorRenderPass.h
./ionFramework/CFadeOutState.o: ionScene/CMultiOutRenderPass.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionScene/CImageLoader.h
./ionFramework/CFadeOutState.o: ionFramework/CApplication.h
./ionFramework/CFadeOutState.o: /home/idunn01/484/ionEngine/ionScene.h
./ionFramework/CFadeOutState.o: ionScene/ionScene.h ionScene/CMeshLoader.h
./ionFramework/CFadeOutState.o: ionScene/CInstanceSceneObject.h
./ionFramework/CFadeOutState.o: ionScene/CShaderLoader.h
./ionFramework/CFadeOutState.o: ionScene/CImageLoader.h
./ionFramework/CFadeOutState.o: ionScene/CSceneManager.h
./ionFramework/CFadeOutState.o: ionScene/CDeferredShadingManager.h
./ionFramework/CFadeOutState.o: ionScene/CPointLightSceneObject.h
./ionFramework/CFadeOutState.o: ionScene/CDirectionalLightSceneObject.h
./ionMath/SColor.o: ionMath/SColor.h ionMath/SVector.h
./ionMath/SColor.o: /home/idunn01/484/ionEngine/ionCore.h ionCore/ionCore.h
./ionMath/SColor.o: ionConfig.h ionCore/ionComparison.h ionCore/ionTypes.h
./ionMath/SColor.o: ionCore/ionRand.h ionCore/ionSmartPtr.h
./ionMath/SColor.o: ionCore/ionThread.h ionCore/ionTreeNode.h
./ionMath/SColor.o: ionCore/ionUtils.h
