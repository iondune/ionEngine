CXX=clang++
INCLUDE=-I ../ \
	-I ~/include/glm/
CXXFLAGS=$(INCLUDE) -g -std=c++11

SRCS=$(shell find . -name "*.cpp")
OBJS=$(subst .cpp,.o,$(SRCS))

all: $(OBJS)

UCT: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

libionAsset.a: $(OBJS)
	ar rc $@ $^

clean:
	rm -f $(OBJS) libionAsset.a

remake: clean all

depend:
	@echo Regenerating local dependencies.
	@makedepend -Y $(SRCS) $(HDRS) $(INCLUDE) -s "# Dependencies" > /dev/null 2>&1
	@rm Makefile.bak


# Dependencies

./CImageLoader.o: CImageLoader.h CImage.h ../ionCore.h ../ionCore/ionCore.h
./CImageLoader.o: ../ionConfig.h ../ionCore/ionClass.h
./CImageLoader.o: ../ionCore/ionComparison.h ../ionCore/ionTypes.h
./CImageLoader.o: ../ionCore/ionRand.h ../ionCore/ionSmartPtr.h
./CImageLoader.o: ../ionCore/ionThread.h ../ionCore/ionTreeNode.h
./CImageLoader.o: ../ionCore/ionUtils.h ../ionMath/SVector2.h
./CImageLoader.o: ../ionMath/SVector.h ../ionMath/Utilities.h
./CImageLoader.o: ../ionMath/Constants.h ../ionCore/ionTypes.h
./CImageLoader.o: ../ionMath/SColor.h ../ionGraphics/CTexture.h ../ionMath.h
./CImageLoader.o: ../ionMath/ionMath.h ../ionMath/SColor.h
./CImageLoader.o: ../ionMath/SVector2.h ../ionMath/SVector3.h
./CImageLoader.o: ../ionMath/SVector4.h ../ionMath/SMatrix4.h
./CImageLoader.o: ../ionMath/SBoundingBox3.h ../ionMath/SLine3.h
./CImageLoader.o: ../ionMath/SPlane3.h ../ionMath/SRect2.h
./CImageLoader.o: ../ionMath/STriangle2.h ../ionMath/STriangle3.h
./CImageLoader.o: ../ionMath/STransformation3.h ../ionAsset/CImage.h
./CImageLoader.o: ../ionGraphics/IRenderTarget.h
./CMeshLoader.o: CMeshLoader.h CMesh.h ../ionMath/SBoundingBox3.h
./CMeshLoader.o: ../ionMath/SVector3.h ../ionConfig.h ../ionMath/SVector.h
./CMeshLoader.o: ../ionCore.h ../ionCore/ionCore.h ../ionCore/ionClass.h
./CMeshLoader.o: ../ionCore/ionComparison.h ../ionCore/ionTypes.h
./CMeshLoader.o: ../ionCore/ionRand.h ../ionCore/ionSmartPtr.h
./CMeshLoader.o: ../ionCore/ionThread.h ../ionCore/ionTreeNode.h
./CMeshLoader.o: ../ionCore/ionUtils.h ../ionMath/SVector2.h
./CMeshLoader.o: ../ionMath/Utilities.h ../ionMath/Constants.h
./CMeshLoader.o: ../ionCore/ionTypes.h ../ionMath/SLine3.h ../ionGL/Buffer.h
./CMeshLoader.o: ../ionMath.h ../ionMath/ionMath.h ../ionMath/SColor.h
./CMeshLoader.o: ../ionMath/SVector4.h ../ionMath/SMatrix4.h
./CMeshLoader.o: ../ionMath/SBoundingBox3.h ../ionMath/SPlane3.h
./CMeshLoader.o: ../ionMath/SRect2.h ../ionMath/STriangle2.h
./CMeshLoader.o: ../ionMath/STriangle3.h ../ionMath/STransformation3.h
./CMeshLoader.o: ../ionGL/VertexArray.h ../ionGL/Buffer.h SVertex.h
./CMeshLoader.o: SMeshTriangle.h SMaterial.h ../ionGraphics/CTexture.h
./CMeshLoader.o: ../ionAsset/CImage.h ../ionMath/SVector2.h
./CMeshLoader.o: ../ionMath/SColor.h ../ionGraphics/IRenderTarget.h
./SMaterial.o: SMaterial.h ../ionMath.h ../ionMath/ionMath.h ../ionCore.h
./SMaterial.o: ../ionCore/ionCore.h ../ionConfig.h ../ionCore/ionClass.h
./SMaterial.o: ../ionCore/ionComparison.h ../ionCore/ionTypes.h
./SMaterial.o: ../ionCore/ionRand.h ../ionCore/ionSmartPtr.h
./SMaterial.o: ../ionCore/ionThread.h ../ionCore/ionTreeNode.h
./SMaterial.o: ../ionCore/ionUtils.h ../ionMath/SVector.h ../ionMath/SColor.h
./SMaterial.o: ../ionMath/SVector2.h ../ionMath/Utilities.h
./SMaterial.o: ../ionMath/Constants.h ../ionCore/ionTypes.h
./SMaterial.o: ../ionMath/SVector3.h ../ionMath/SVector4.h
./SMaterial.o: ../ionMath/SMatrix4.h ../ionMath/SBoundingBox3.h
./SMaterial.o: ../ionMath/SLine3.h ../ionMath/SPlane3.h ../ionMath/SRect2.h
./SMaterial.o: ../ionMath/STriangle2.h ../ionMath/STriangle3.h
./SMaterial.o: ../ionMath/STransformation3.h ../ionGraphics/CTexture.h
./SMaterial.o: ../ionAsset/CImage.h ../ionMath/SVector2.h ../ionMath/SColor.h
./SMaterial.o: ../ionGraphics/IRenderTarget.h
./SMeshBuffer.o: SMeshBuffer.h ../ionMath.h ../ionMath/ionMath.h ../ionCore.h
./SMeshBuffer.o: ../ionCore/ionCore.h ../ionConfig.h ../ionCore/ionClass.h
./SMeshBuffer.o: ../ionCore/ionComparison.h ../ionCore/ionTypes.h
./SMeshBuffer.o: ../ionCore/ionRand.h ../ionCore/ionSmartPtr.h
./SMeshBuffer.o: ../ionCore/ionThread.h ../ionCore/ionTreeNode.h
./SMeshBuffer.o: ../ionCore/ionUtils.h ../ionMath/SVector.h
./SMeshBuffer.o: ../ionMath/SColor.h ../ionMath/SVector2.h
./SMeshBuffer.o: ../ionMath/Utilities.h ../ionMath/Constants.h
./SMeshBuffer.o: ../ionCore/ionTypes.h ../ionMath/SVector3.h
./SMeshBuffer.o: ../ionMath/SVector4.h ../ionMath/SMatrix4.h
./SMeshBuffer.o: ../ionMath/SBoundingBox3.h ../ionMath/SLine3.h
./SMeshBuffer.o: ../ionMath/SPlane3.h ../ionMath/SRect2.h
./SMeshBuffer.o: ../ionMath/STriangle2.h ../ionMath/STriangle3.h
./SMeshBuffer.o: ../ionMath/STransformation3.h ../ionGL.h ../ionGL/ionGL.h
./SMeshBuffer.o: ../ionGL/Buffer.h ../ionGL/Program.h ../ionGL/Shader.h
./SMeshBuffer.o: ../ionGL/Texture.h ../ionGL/VertexArray.h ../ionGL/Uniform.h
./SMeshBuffer.o: ../ionGL/Context.h ../ionGL/DrawContext.h
./SVertex.o: SVertex.h ../ionMath.h ../ionMath/ionMath.h ../ionCore.h
./SVertex.o: ../ionCore/ionCore.h ../ionConfig.h ../ionCore/ionClass.h
./SVertex.o: ../ionCore/ionComparison.h ../ionCore/ionTypes.h
./SVertex.o: ../ionCore/ionRand.h ../ionCore/ionSmartPtr.h
./SVertex.o: ../ionCore/ionThread.h ../ionCore/ionTreeNode.h
./SVertex.o: ../ionCore/ionUtils.h ../ionMath/SVector.h ../ionMath/SColor.h
./SVertex.o: ../ionMath/SVector2.h ../ionMath/Utilities.h
./SVertex.o: ../ionMath/Constants.h ../ionCore/ionTypes.h
./SVertex.o: ../ionMath/SVector3.h ../ionMath/SVector4.h
./SVertex.o: ../ionMath/SMatrix4.h ../ionMath/SBoundingBox3.h
./SVertex.o: ../ionMath/SLine3.h ../ionMath/SPlane3.h ../ionMath/SRect2.h
./SVertex.o: ../ionMath/STriangle2.h ../ionMath/STriangle3.h
./SVertex.o: ../ionMath/STransformation3.h
./SMeshTriangle.o: SMeshTriangle.h ../ionMath.h ../ionMath/ionMath.h
./SMeshTriangle.o: ../ionCore.h ../ionCore/ionCore.h ../ionConfig.h
./SMeshTriangle.o: ../ionCore/ionClass.h ../ionCore/ionComparison.h
./SMeshTriangle.o: ../ionCore/ionTypes.h ../ionCore/ionRand.h
./SMeshTriangle.o: ../ionCore/ionSmartPtr.h ../ionCore/ionThread.h
./SMeshTriangle.o: ../ionCore/ionTreeNode.h ../ionCore/ionUtils.h
./SMeshTriangle.o: ../ionMath/SVector.h ../ionMath/SColor.h
./SMeshTriangle.o: ../ionMath/SVector2.h ../ionMath/Utilities.h
./SMeshTriangle.o: ../ionMath/Constants.h ../ionCore/ionTypes.h
./SMeshTriangle.o: ../ionMath/SVector3.h ../ionMath/SVector4.h
./SMeshTriangle.o: ../ionMath/SMatrix4.h ../ionMath/SBoundingBox3.h
./SMeshTriangle.o: ../ionMath/SLine3.h ../ionMath/SPlane3.h
./SMeshTriangle.o: ../ionMath/SRect2.h ../ionMath/STriangle2.h
./SMeshTriangle.o: ../ionMath/STriangle3.h ../ionMath/STransformation3.h
./CImage.o: CImage.h ../ionCore.h ../ionCore/ionCore.h ../ionConfig.h
./CImage.o: ../ionCore/ionClass.h ../ionCore/ionComparison.h
./CImage.o: ../ionCore/ionTypes.h ../ionCore/ionRand.h
./CImage.o: ../ionCore/ionSmartPtr.h ../ionCore/ionThread.h
./CImage.o: ../ionCore/ionTreeNode.h ../ionCore/ionUtils.h
./CImage.o: ../ionMath/SVector2.h ../ionMath/SVector.h ../ionMath/Utilities.h
./CImage.o: ../ionMath/Constants.h ../ionCore/ionTypes.h ../ionMath/SColor.h
./CGeometryCreator.o: CGeometryCreator.h SMeshBuffer.h ../ionMath.h
./CGeometryCreator.o: ../ionMath/ionMath.h ../ionCore.h ../ionCore/ionCore.h
./CGeometryCreator.o: ../ionConfig.h ../ionCore/ionClass.h
./CGeometryCreator.o: ../ionCore/ionComparison.h ../ionCore/ionTypes.h
./CGeometryCreator.o: ../ionCore/ionRand.h ../ionCore/ionSmartPtr.h
./CGeometryCreator.o: ../ionCore/ionThread.h ../ionCore/ionTreeNode.h
./CGeometryCreator.o: ../ionCore/ionUtils.h ../ionMath/SVector.h
./CGeometryCreator.o: ../ionMath/SColor.h ../ionMath/SVector2.h
./CGeometryCreator.o: ../ionMath/Utilities.h ../ionMath/Constants.h
./CGeometryCreator.o: ../ionCore/ionTypes.h ../ionMath/SVector3.h
./CGeometryCreator.o: ../ionMath/SVector4.h ../ionMath/SMatrix4.h
./CGeometryCreator.o: ../ionMath/SBoundingBox3.h ../ionMath/SLine3.h
./CGeometryCreator.o: ../ionMath/SPlane3.h ../ionMath/SRect2.h
./CGeometryCreator.o: ../ionMath/STriangle2.h ../ionMath/STriangle3.h
./CGeometryCreator.o: ../ionMath/STransformation3.h ../ionGL.h
./CGeometryCreator.o: ../ionGL/ionGL.h ../ionGL/Buffer.h ../ionGL/Program.h
./CGeometryCreator.o: ../ionGL/Shader.h ../ionGL/Texture.h
./CGeometryCreator.o: ../ionGL/VertexArray.h ../ionGL/Uniform.h
./CGeometryCreator.o: ../ionGL/Context.h ../ionGL/DrawContext.h
./CMesh.o: CMesh.h ../ionMath/SBoundingBox3.h ../ionMath/SVector3.h
./CMesh.o: ../ionConfig.h ../ionMath/SVector.h ../ionCore.h
./CMesh.o: ../ionCore/ionCore.h ../ionCore/ionClass.h
./CMesh.o: ../ionCore/ionComparison.h ../ionCore/ionTypes.h
./CMesh.o: ../ionCore/ionRand.h ../ionCore/ionSmartPtr.h
./CMesh.o: ../ionCore/ionThread.h ../ionCore/ionTreeNode.h
./CMesh.o: ../ionCore/ionUtils.h ../ionMath/SVector2.h ../ionMath/Utilities.h
./CMesh.o: ../ionMath/Constants.h ../ionCore/ionTypes.h ../ionMath/SLine3.h
./CMesh.o: ../ionGL/Buffer.h ../ionMath.h ../ionMath/ionMath.h
./CMesh.o: ../ionMath/SColor.h ../ionMath/SVector4.h ../ionMath/SMatrix4.h
./CMesh.o: ../ionMath/SBoundingBox3.h ../ionMath/SPlane3.h
./CMesh.o: ../ionMath/SRect2.h ../ionMath/STriangle2.h
./CMesh.o: ../ionMath/STriangle3.h ../ionMath/STransformation3.h
./CMesh.o: ../ionGL/VertexArray.h ../ionGL/Buffer.h SVertex.h SMeshTriangle.h
./CMesh.o: SMaterial.h ../ionGraphics/CTexture.h ../ionAsset/CImage.h
./CMesh.o: ../ionMath/SVector2.h ../ionMath/SColor.h
./CMesh.o: ../ionGraphics/IRenderTarget.h
./CMesh.Load.o: CMesh.h ../ionMath/SBoundingBox3.h ../ionMath/SVector3.h
./CMesh.Load.o: ../ionConfig.h ../ionMath/SVector.h ../ionCore.h
./CMesh.Load.o: ../ionCore/ionCore.h ../ionCore/ionClass.h
./CMesh.Load.o: ../ionCore/ionComparison.h ../ionCore/ionTypes.h
./CMesh.Load.o: ../ionCore/ionRand.h ../ionCore/ionSmartPtr.h
./CMesh.Load.o: ../ionCore/ionThread.h ../ionCore/ionTreeNode.h
./CMesh.Load.o: ../ionCore/ionUtils.h ../ionMath/SVector2.h
./CMesh.Load.o: ../ionMath/Utilities.h ../ionMath/Constants.h
./CMesh.Load.o: ../ionCore/ionTypes.h ../ionMath/SLine3.h ../ionGL/Buffer.h
./CMesh.Load.o: ../ionMath.h ../ionMath/ionMath.h ../ionMath/SColor.h
./CMesh.Load.o: ../ionMath/SVector4.h ../ionMath/SMatrix4.h
./CMesh.Load.o: ../ionMath/SBoundingBox3.h ../ionMath/SPlane3.h
./CMesh.Load.o: ../ionMath/SRect2.h ../ionMath/STriangle2.h
./CMesh.Load.o: ../ionMath/STriangle3.h ../ionMath/STransformation3.h
./CMesh.Load.o: ../ionGL/VertexArray.h ../ionGL/Buffer.h SVertex.h
./CMesh.Load.o: SMeshTriangle.h SMaterial.h ../ionGraphics/CTexture.h
./CMesh.Load.o: ../ionAsset/CImage.h ../ionMath/SVector2.h
./CMesh.Load.o: ../ionMath/SColor.h ../ionGraphics/IRenderTarget.h
