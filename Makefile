CXX=g++
CPPFLAGS= -g -std=gnu++0x \
	-I ~/484/ionEngine \
	-I ~/484/ionEngine/ionCore \
	-I ~/484/ionEngine/ionMath \
	-I ~/484/deps/glm/include \
	-I ~/484/deps/glew/include \
	-I ~/484/deps/glfw/include \
	-I ~/484/deps/stb_image/include \
	-I ~/484/deps/freetype/include/freetype
LDFLAGS=-lGL -lGLU -lXrandr \
	-L ~/484/deps/lib \
	-lfreetype -lGLEW -lglfw3

SRCS=$(shell find . -name "*.cpp")
OBJS=$(subst .cpp,.o,$(SRCS))

all: UCT ionEngine.a

UCT: $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

ionEngine.a: $(filter-out UtilityCompileTest/Main.o,$(OBJS))
	ar rc $@ $^

clean:
	rm -f $(OBJS)

remake: clean all

depend:
	@echo Regenerating local dependencies.
	@makedepend -Y $(SRCS) $(HDRS) -s "# Dependencies" > /dev/null 2>&1
	@rm Makefile.bak


# Dependencies

./ionGL/Texture.o: ./ionGL/Texture.h ./ionGL/Utilities.h
./ionGL/Utilities.o: ./ionGL/Utilities.h
./ionGL/Buffer.o: ./ionGL/Buffer.h ./ionGL/Utilities.h
./ionGL/VertexArray.o: ./ionGL/VertexArray.h ./ionGL/Utilities.h
./ionGL/VertexArray.o: ./ionGL/Buffer.h
./ionGL/Shader.o: ./ionGL/Shader.h
./ionGL/Program.o: ./ionGL/Program.h ./ionGL/Buffer.h ./ionGL/Shader.h
./ionGUI/CGUIEventManager.o: ./ionGUI/CGUIEventManager.h ./ionGUI/Gwen.h
./ionGUI/OpenGL3.o: ./ionGUI/OpenGL3.h ./ionGUI/Gwen.h
./ionGUI/CGUIManager.o: ./ionGUI/CGUIManager.h ./ionGUI/CGUIWidget.h
./ionGUI/CGUIManager.o: ./ionGUI/Gwen.h ./ionGUI/OpenGL3Font.h
./ionGUI/CGUIManager.o: ./ionGUI/OpenGL3.h
./ionGUI/CGUIWidget.o: ./ionGUI/CGUIManager.h ./ionGUI/CGUIWidget.h
./ionGUI/CGUIWidget.o: ./ionGUI/Gwen.h
./ionGUI/OpenGL3Font.o: ./ionGUI/OpenGL3Font.h ./ionGUI/OpenGL3.h
./ionGUI/OpenGL3Font.o: ./ionGUI/Gwen.h ./ionGUI/FreeType.h
./ionGUI/CGUIConsoleWidget.o: ./ionGUI/CGUIConsoleWidget.h ./ionGUI/Gwen.h
./ionGUI/CGUIConsoleWidget.o: ./ionGUI/CGUIWidget.h ./ionGUI/CGUIManager.h
./ionGUI/CGUIProgressBarWidget.o: ./ionGUI/CGUIProgressBarWidget.h
./ionGUI/CGUIProgressBarWidget.o: ./ionGUI/Gwen.h ./ionGUI/CGUIWidget.h
./ionGUI/CGUIProgressBarWidget.o: ./ionGUI/CGUIManager.h
./ionScene/CImageLoader.o: ./ionScene/CImageLoader.h ./ionScene/CImage.h
./ionScene/CImageLoader.o: ./ionScene/CTexture.h ./ionScene/IRenderTarget.h
./ionScene/CCameraSceneObject.o: ./ionScene/CCameraSceneObject.h ionConfig.h
./ionScene/CCameraSceneObject.o: ./ionScene/ICameraSceneObject.h
./ionScene/CCameraSceneObject.o: ./ionScene/ISceneObject.h
./ionScene/CCameraSceneObject.o: ./ionScene/CBufferObject.h
./ionScene/CCameraSceneObject.o: ./ionScene/CShader.h ./ionScene/CTexture.h
./ionScene/CCameraSceneObject.o: ./ionScene/CImage.h
./ionScene/CCameraSceneObject.o: ./ionScene/IRenderTarget.h
./ionScene/CCameraSceneObject.o: ./ionScene/CShaderContext.h
./ionScene/CCameraSceneObject.o: ./ionScene/IRenderPass.h
./ionScene/CCameraSceneObject.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/CScene.h ionConfig.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/IScene.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/ICameraSceneObject.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/ISceneObject.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/CBufferObject.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/CShader.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/CTexture.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/CImage.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/IRenderTarget.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/CShaderContext.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/IRenderPass.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/CLightSceneObject.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/SUniform.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/CCameraSceneObject.h
./ionScene/CScene.ShaderVariables.o: ./ionScene/SAttribute.h
./ionScene/ISceneObject.o: ./ionScene/ISceneObject.h
./ionScene/ISceneObject.o: ./ionScene/CBufferObject.h ./ionScene/CShader.h
./ionScene/ISceneObject.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/ISceneObject.o: ./ionScene/IRenderTarget.h
./ionScene/ISceneObject.o: ./ionScene/CShaderContext.h
./ionScene/ISceneObject.o: ./ionScene/IRenderPass.h
./ionScene/ISceneObject.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneManager.o: ./ionScene/CSceneManager.h
./ionScene/CSceneManager.o: ./ionScene/CSceneObject.h
./ionScene/CSceneManager.o: ./ionScene/ISceneObject.h
./ionScene/CSceneManager.o: ./ionScene/CBufferObject.h ./ionScene/CShader.h
./ionScene/CSceneManager.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CSceneManager.o: ./ionScene/IRenderTarget.h
./ionScene/CSceneManager.o: ./ionScene/CShaderContext.h
./ionScene/CSceneManager.o: ./ionScene/IRenderPass.h
./ionScene/CSceneManager.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneManager.o: ./ionScene/CRenderable.h ./ionScene/SUniform.h
./ionScene/CSceneManager.o: ./ionScene/SAttribute.h
./ionScene/CSceneManager.o: ./ionScene/CMeshSceneObject.h ./ionScene/CMesh.h
./ionScene/CSceneManager.o: ./ionScene/SVertex.h
./ionScene/CSceneManager.o: ./ionScene/CFrameBufferObject.h
./ionScene/CSceneManager.o: ./ionScene/CRenderBufferObject.h
./ionScene/CSceneManager.o: ./ionScene/CSceneEffectManager.h
./ionScene/CSceneManager.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CSceneManager.o: ./ionScene/CCameraSceneObject.h ionConfig.h
./ionScene/CSceneManager.o: ./ionScene/ICameraSceneObject.h
./ionScene/CSceneManager.o: ./ionScene/CScene.h ./ionScene/IScene.h
./ionScene/CSceneManager.o: ./ionScene/CLightSceneObject.h
./ionScene/CSceneManager.o: ./ionScene/CDefaultColorRenderPass.h
./ionScene/CSceneManager.o: ./ionScene/CMultiOutRenderPass.h
./ionScene/CSceneManager.o: ./ionScene/CShaderLoader.h
./ionScene/CSceneManager.o: ./ionScene/CMeshLoader.h
./ionScene/CSceneManager.o: ./ionScene/CImageLoader.h
./ionScene/CSceneManager.o: ./ionScene/CDeferredShadingManager.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/CSceneObject.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/ISceneObject.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/CBufferObject.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/CShader.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/CTexture.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/CImage.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/IRenderTarget.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/CShaderContext.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/IRenderPass.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/CRenderable.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/SUniform.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/SAttribute.h
./ionScene/CSceneObject.ShaderManagement.o: ./ionScene/CShaderLoader.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/CSceneObject.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/ISceneObject.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/CBufferObject.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/CShader.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/CTexture.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/CImage.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/IRenderTarget.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/CShaderContext.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/IRenderPass.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/CRenderable.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/SUniform.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/SAttribute.h
./ionScene/CSceneObject.ContextManagement.o: ./ionScene/CImageLoader.h
./ionScene/CTexture.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CTexture.o: ./ionScene/IRenderTarget.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionScene/ISceneObject.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionScene/CBufferObject.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionScene/CShader.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionScene/CTexture.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionScene/CImage.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionScene/IRenderTarget.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionScene/CShaderContext.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionScene/IRenderPass.h
./ionScene/ISceneObject.StatisticMethods.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionScene/ISceneObject.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionScene/CBufferObject.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionScene/CShader.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionScene/CTexture.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionScene/CImage.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionScene/IRenderTarget.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionScene/CShaderContext.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionScene/IRenderPass.h
./ionScene/ISceneObject.SceneGraphMethods.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CMesh.o: ./ionScene/CMesh.h ./ionScene/SVertex.h
./ionScene/CMesh.o: ./ionScene/CBufferObject.h ./ionScene/CRenderable.h
./ionScene/CMesh.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CMesh.o: ./ionScene/IRenderPass.h ./ionScene/SUniform.h
./ionScene/CMesh.o: ./ionScene/CShaderContext.h ./ionScene/CShader.h
./ionScene/CMesh.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CMesh.o: ./ionScene/IRenderTarget.h ./ionScene/SAttribute.h
./ionScene/CShaderLoader.o: ./ionScene/CShaderLoader.h ./ionScene/CShader.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/CSceneObject.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/ISceneObject.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/CBufferObject.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/CShader.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/CTexture.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/CImage.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/IRenderTarget.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/CShaderContext.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/IRenderPass.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/CRenderable.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/SUniform.h
./ionScene/CSceneObject.RenderableManagement.o: ./ionScene/SAttribute.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/CRenderable.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/IRenderPass.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/SUniform.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/CShaderContext.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/CShader.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/CTexture.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/CImage.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/IRenderTarget.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/SAttribute.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/CBufferObject.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/CSceneObject.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/ISceneObject.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/IScene.h
./ionScene/CRenderable.UpdateMethods.o: ./ionScene/ICameraSceneObject.h
./ionScene/CMeshSceneObject.o: ./ionScene/CMeshSceneObject.h
./ionScene/CMeshSceneObject.o: ./ionScene/CShader.h ./ionScene/CMesh.h
./ionScene/CMeshSceneObject.o: ./ionScene/SVertex.h
./ionScene/CMeshSceneObject.o: ./ionScene/CBufferObject.h
./ionScene/CMeshSceneObject.o: ./ionScene/CRenderable.h
./ionScene/CMeshSceneObject.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CMeshSceneObject.o: ./ionScene/IRenderPass.h ./ionScene/SUniform.h
./ionScene/CMeshSceneObject.o: ./ionScene/CShaderContext.h
./ionScene/CMeshSceneObject.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CMeshSceneObject.o: ./ionScene/IRenderTarget.h
./ionScene/CMeshSceneObject.o: ./ionScene/SAttribute.h
./ionScene/CMeshSceneObject.o: ./ionScene/CSceneObject.h
./ionScene/CMeshSceneObject.o: ./ionScene/ISceneObject.h
./ionScene/CMeshSceneObject.o: ./ionScene/CShaderLoader.h
./ionScene/CScene.Details.o: ./ionScene/CScene.h ionConfig.h
./ionScene/CScene.Details.o: ./ionScene/IScene.h
./ionScene/CScene.Details.o: ./ionScene/ICameraSceneObject.h
./ionScene/CScene.Details.o: ./ionScene/ISceneObject.h
./ionScene/CScene.Details.o: ./ionScene/CBufferObject.h ./ionScene/CShader.h
./ionScene/CScene.Details.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CScene.Details.o: ./ionScene/IRenderTarget.h
./ionScene/CScene.Details.o: ./ionScene/CShaderContext.h
./ionScene/CScene.Details.o: ./ionScene/IRenderPass.h
./ionScene/CScene.Details.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.Details.o: ./ionScene/CLightSceneObject.h
./ionScene/CScene.Details.o: ./ionScene/SUniform.h
./ionScene/CScene.Details.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.Details.o: ./ionScene/CCameraSceneObject.h
./ionScene/CScene.o: ./ionScene/CScene.h ionConfig.h ./ionScene/IScene.h
./ionScene/CScene.o: ./ionScene/ICameraSceneObject.h
./ionScene/CScene.o: ./ionScene/ISceneObject.h ./ionScene/CBufferObject.h
./ionScene/CScene.o: ./ionScene/CShader.h ./ionScene/CTexture.h
./ionScene/CScene.o: ./ionScene/CImage.h ./ionScene/IRenderTarget.h
./ionScene/CScene.o: ./ionScene/CShaderContext.h ./ionScene/IRenderPass.h
./ionScene/CScene.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.o: ./ionScene/CLightSceneObject.h ./ionScene/SUniform.h
./ionScene/CScene.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.o: ./ionScene/CCameraSceneObject.h ./ionScene/SAttribute.h
./ionScene/CScene.Update.o: ./ionScene/CScene.h ionConfig.h
./ionScene/CScene.Update.o: ./ionScene/IScene.h
./ionScene/CScene.Update.o: ./ionScene/ICameraSceneObject.h
./ionScene/CScene.Update.o: ./ionScene/ISceneObject.h
./ionScene/CScene.Update.o: ./ionScene/CBufferObject.h ./ionScene/CShader.h
./ionScene/CScene.Update.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CScene.Update.o: ./ionScene/IRenderTarget.h
./ionScene/CScene.Update.o: ./ionScene/CShaderContext.h
./ionScene/CScene.Update.o: ./ionScene/IRenderPass.h
./ionScene/CScene.Update.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.Update.o: ./ionScene/CLightSceneObject.h
./ionScene/CScene.Update.o: ./ionScene/SUniform.h
./ionScene/CScene.Update.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.Update.o: ./ionScene/CCameraSceneObject.h
./ionScene/CSceneEffectManager.o: ./ionScene/CSceneEffectManager.h
./ionScene/CSceneEffectManager.o: ./ionScene/CFrameBufferObject.h
./ionScene/CSceneEffectManager.o: ./ionScene/CRenderBufferObject.h
./ionScene/CSceneEffectManager.o: ./ionScene/IRenderTarget.h
./ionScene/CSceneEffectManager.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CSceneEffectManager.o: ./ionScene/ISceneObject.h
./ionScene/CSceneEffectManager.o: ./ionScene/CBufferObject.h
./ionScene/CSceneEffectManager.o: ./ionScene/CShader.h
./ionScene/CSceneEffectManager.o: ./ionScene/CShaderContext.h
./ionScene/CSceneEffectManager.o: ./ionScene/IRenderPass.h
./ionScene/CSceneEffectManager.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneEffectManager.o: ./ionScene/SUniform.h
./ionScene/CSceneEffectManager.o: ./ionScene/CSceneManager.h
./ionScene/CSceneEffectManager.o: ./ionScene/CSceneObject.h
./ionScene/CSceneEffectManager.o: ./ionScene/CRenderable.h
./ionScene/CSceneEffectManager.o: ./ionScene/SAttribute.h
./ionScene/CSceneEffectManager.o: ./ionScene/CMeshSceneObject.h
./ionScene/CSceneEffectManager.o: ./ionScene/CMesh.h ./ionScene/SVertex.h
./ionScene/CSceneEffectManager.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CSceneEffectManager.o: ./ionScene/CCameraSceneObject.h ionConfig.h
./ionScene/CSceneEffectManager.o: ./ionScene/ICameraSceneObject.h
./ionScene/CSceneEffectManager.o: ./ionScene/CScene.h ./ionScene/IScene.h
./ionScene/CSceneEffectManager.o: ./ionScene/CLightSceneObject.h
./ionScene/CSceneEffectManager.o: ./ionScene/CDefaultColorRenderPass.h
./ionScene/CSceneEffectManager.o: ./ionScene/CMultiOutRenderPass.h
./ionScene/CSceneEffectManager.o: ./ionScene/CImageLoader.h
./ionScene/CSceneEffectManager.o: ./ionScene/CShaderLoader.h
./ionScene/CShader.o: ./ionScene/CShader.h
./ionScene/CFrameBufferObject.o: ./ionScene/CFrameBufferObject.h
./ionScene/CFrameBufferObject.o: ./ionScene/CRenderBufferObject.h
./ionScene/CFrameBufferObject.o: ./ionScene/IRenderTarget.h
./ionScene/CFrameBufferObject.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/ISceneObject.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/CBufferObject.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/CShader.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/CTexture.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/CImage.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/IRenderTarget.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/CShaderContext.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/IRenderPass.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/IScene.h
./ionScene/ISceneObject.UpdateMethods.o: ./ionScene/ICameraSceneObject.h
./ionScene/CMeshLoader.o: ./ionScene/CMeshLoader.h ./ionScene/CMesh.h
./ionScene/CMeshLoader.o: ./ionScene/SVertex.h ./ionScene/CBufferObject.h
./ionScene/CMeshLoader.o: ./ionScene/CRenderable.h
./ionScene/CMeshLoader.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CMeshLoader.o: ./ionScene/IRenderPass.h ./ionScene/SUniform.h
./ionScene/CMeshLoader.o: ./ionScene/CShaderContext.h ./ionScene/CShader.h
./ionScene/CMeshLoader.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CMeshLoader.o: ./ionScene/IRenderTarget.h ./ionScene/SAttribute.h
./ionScene/ISceneObject.CullingMethods.o: ./ionScene/ISceneObject.h
./ionScene/ISceneObject.CullingMethods.o: ./ionScene/CBufferObject.h
./ionScene/ISceneObject.CullingMethods.o: ./ionScene/CShader.h
./ionScene/ISceneObject.CullingMethods.o: ./ionScene/CTexture.h
./ionScene/ISceneObject.CullingMethods.o: ./ionScene/CImage.h
./ionScene/ISceneObject.CullingMethods.o: ./ionScene/IRenderTarget.h
./ionScene/ISceneObject.CullingMethods.o: ./ionScene/CShaderContext.h
./ionScene/ISceneObject.CullingMethods.o: ./ionScene/IRenderPass.h
./ionScene/ISceneObject.CullingMethods.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/ISceneObject.CullingMethods.o: ./ionScene/ICameraSceneObject.h
./ionScene/CSceneObject.o: ./ionScene/CSceneObject.h
./ionScene/CSceneObject.o: ./ionScene/ISceneObject.h
./ionScene/CSceneObject.o: ./ionScene/CBufferObject.h ./ionScene/CShader.h
./ionScene/CSceneObject.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CSceneObject.o: ./ionScene/IRenderTarget.h
./ionScene/CSceneObject.o: ./ionScene/CShaderContext.h
./ionScene/CSceneObject.o: ./ionScene/IRenderPass.h
./ionScene/CSceneObject.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneObject.o: ./ionScene/CRenderable.h ./ionScene/SUniform.h
./ionScene/CSceneObject.o: ./ionScene/SAttribute.h
./ionScene/CLightSceneObject.o: ./ionScene/CLightSceneObject.h
./ionScene/CLightSceneObject.o: ./ionScene/ISceneObject.h
./ionScene/CLightSceneObject.o: ./ionScene/CBufferObject.h
./ionScene/CLightSceneObject.o: ./ionScene/CShader.h ./ionScene/CTexture.h
./ionScene/CLightSceneObject.o: ./ionScene/CImage.h
./ionScene/CLightSceneObject.o: ./ionScene/IRenderTarget.h
./ionScene/CLightSceneObject.o: ./ionScene/CShaderContext.h
./ionScene/CLightSceneObject.o: ./ionScene/IRenderPass.h
./ionScene/CLightSceneObject.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CLightSceneObject.o: ./ionScene/SUniform.h
./ionScene/CPointLightSceneObject.o: ./ionScene/CPointLightSceneObject.h
./ionScene/CPointLightSceneObject.o: ./ionScene/ISceneObject.h
./ionScene/CPointLightSceneObject.o: ./ionScene/CBufferObject.h
./ionScene/CPointLightSceneObject.o: ./ionScene/CShader.h
./ionScene/CPointLightSceneObject.o: ./ionScene/CTexture.h
./ionScene/CPointLightSceneObject.o: ./ionScene/CImage.h
./ionScene/CPointLightSceneObject.o: ./ionScene/IRenderTarget.h
./ionScene/CPointLightSceneObject.o: ./ionScene/CShaderContext.h
./ionScene/CPointLightSceneObject.o: ./ionScene/IRenderPass.h
./ionScene/CPointLightSceneObject.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CPointLightSceneObject.o: ./ionScene/CMeshLoader.h
./ionScene/CPointLightSceneObject.o: ./ionScene/CMesh.h ./ionScene/SVertex.h
./ionScene/CPointLightSceneObject.o: ./ionScene/CRenderable.h
./ionScene/CPointLightSceneObject.o: ./ionScene/SUniform.h
./ionScene/CPointLightSceneObject.o: ./ionScene/SAttribute.h
./ionScene/CPointLightSceneObject.o: ./ionScene/CShaderLoader.h
./ionScene/CPointLightSceneObject.o: ./ionScene/IScene.h
./ionScene/CPointLightSceneObject.o: ./ionScene/ICameraSceneObject.h
./ionScene/CImage.o: ./ionScene/CImage.h ./ionScene/BitmapWriter.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/CRenderable.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/IRenderPass.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/SUniform.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/CShaderContext.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/CShader.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/CTexture.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/CImage.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/IRenderTarget.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/SAttribute.h
./ionScene/CRenderable.SShaderSetup.o: ./ionScene/CBufferObject.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CDirectionalLightSceneObject.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/ISceneObject.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CBufferObject.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CShader.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CTexture.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CImage.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/IRenderTarget.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CShaderContext.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/IRenderPass.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CMeshLoader.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CMesh.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/SVertex.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CRenderable.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/SUniform.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/SAttribute.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CShaderLoader.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CSceneEffectManager.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CFrameBufferObject.h
./ionScene/CDirectionalLightSceneObject.o: ./ionScene/CRenderBufferObject.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/CCameraSceneObject.h
./ionScene/CPerspectiveCameraSceneObject.o: ionConfig.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/ICameraSceneObject.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/ISceneObject.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/CBufferObject.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/CShader.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/CTexture.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/CImage.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/IRenderTarget.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/CShaderContext.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/IRenderPass.h
./ionScene/CPerspectiveCameraSceneObject.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/CRenderable.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/IRenderPass.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/SUniform.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/CShaderContext.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/CShader.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/CTexture.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/CImage.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/IRenderTarget.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/SAttribute.h
./ionScene/CRenderable.ShaderVariables.o: ./ionScene/CBufferObject.h
./ionScene/CRenderable.o: ./ionScene/CRenderable.h
./ionScene/CRenderable.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.o: ./ionScene/IRenderPass.h ./ionScene/SUniform.h
./ionScene/CRenderable.o: ./ionScene/CShaderContext.h ./ionScene/CShader.h
./ionScene/CRenderable.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CRenderable.o: ./ionScene/IRenderTarget.h ./ionScene/SAttribute.h
./ionScene/CRenderable.o: ./ionScene/CBufferObject.h
./ionScene/CInstanceSceneObject.o: ./ionScene/CInstanceSceneObject.h
./ionScene/CInstanceSceneObject.o: ./ionScene/CSceneObject.h
./ionScene/CInstanceSceneObject.o: ./ionScene/ISceneObject.h
./ionScene/CInstanceSceneObject.o: ./ionScene/CBufferObject.h
./ionScene/CInstanceSceneObject.o: ./ionScene/CShader.h ./ionScene/CTexture.h
./ionScene/CInstanceSceneObject.o: ./ionScene/CImage.h
./ionScene/CInstanceSceneObject.o: ./ionScene/IRenderTarget.h
./ionScene/CInstanceSceneObject.o: ./ionScene/CShaderContext.h
./ionScene/CInstanceSceneObject.o: ./ionScene/IRenderPass.h
./ionScene/CInstanceSceneObject.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CInstanceSceneObject.o: ./ionScene/CRenderable.h
./ionScene/CInstanceSceneObject.o: ./ionScene/SUniform.h
./ionScene/CInstanceSceneObject.o: ./ionScene/SAttribute.h
./ionScene/CInstanceSceneObject.o: ./ionScene/CMeshSceneObject.h
./ionScene/CInstanceSceneObject.o: ./ionScene/CMesh.h ./ionScene/SVertex.h
./ionScene/CInstanceSceneObject.o: ./ionScene/IScene.h
./ionScene/CInstanceSceneObject.o: ./ionScene/ICameraSceneObject.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionScene/ISceneObject.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionScene/CBufferObject.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionScene/CShader.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionScene/CTexture.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionScene/CImage.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionScene/IRenderTarget.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionScene/CShaderContext.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionScene/IRenderPass.h
./ionScene/ISceneObject.ModelTransformMethods.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CShaderContext.o: ./ionScene/CShaderContext.h ./ionScene/CShader.h
./ionScene/CShaderContext.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CShaderContext.o: ./ionScene/IRenderTarget.h
./ionScene/CRenderBufferObject.o: ./ionScene/CRenderBufferObject.h
./ionScene/CRenderBufferObject.o: ./ionScene/IRenderTarget.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/CSceneObject.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/ISceneObject.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/CBufferObject.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/CShader.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/CTexture.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/CImage.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/IRenderTarget.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/CShaderContext.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/IRenderPass.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/CRenderable.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/SUniform.h
./ionScene/CSceneObject.UpdateMethods.o: ./ionScene/SAttribute.h
./ionScene/CScene.Camera.o: ./ionScene/CScene.h ionConfig.h
./ionScene/CScene.Camera.o: ./ionScene/IScene.h
./ionScene/CScene.Camera.o: ./ionScene/ICameraSceneObject.h
./ionScene/CScene.Camera.o: ./ionScene/ISceneObject.h
./ionScene/CScene.Camera.o: ./ionScene/CBufferObject.h ./ionScene/CShader.h
./ionScene/CScene.Camera.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CScene.Camera.o: ./ionScene/IRenderTarget.h
./ionScene/CScene.Camera.o: ./ionScene/CShaderContext.h
./ionScene/CScene.Camera.o: ./ionScene/IRenderPass.h
./ionScene/CScene.Camera.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.Camera.o: ./ionScene/CLightSceneObject.h
./ionScene/CScene.Camera.o: ./ionScene/SUniform.h
./ionScene/CScene.Camera.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.Camera.o: ./ionScene/CCameraSceneObject.h
./ionScene/CScene.SLightBinding.o: ./ionScene/CScene.h ionConfig.h
./ionScene/CScene.SLightBinding.o: ./ionScene/IScene.h
./ionScene/CScene.SLightBinding.o: ./ionScene/ICameraSceneObject.h
./ionScene/CScene.SLightBinding.o: ./ionScene/ISceneObject.h
./ionScene/CScene.SLightBinding.o: ./ionScene/CBufferObject.h
./ionScene/CScene.SLightBinding.o: ./ionScene/CShader.h ./ionScene/CTexture.h
./ionScene/CScene.SLightBinding.o: ./ionScene/CImage.h
./ionScene/CScene.SLightBinding.o: ./ionScene/IRenderTarget.h
./ionScene/CScene.SLightBinding.o: ./ionScene/CShaderContext.h
./ionScene/CScene.SLightBinding.o: ./ionScene/IRenderPass.h
./ionScene/CScene.SLightBinding.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CScene.SLightBinding.o: ./ionScene/CLightSceneObject.h
./ionScene/CScene.SLightBinding.o: ./ionScene/SUniform.h
./ionScene/CScene.SLightBinding.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionScene/CScene.SLightBinding.o: ./ionScene/CCameraSceneObject.h
./ionScene/CRenderable.SMaterial.o: ./ionScene/CRenderable.h
./ionScene/CRenderable.SMaterial.o: ./ionScene/ISceneObject.Enumerations.h
./ionScene/CRenderable.SMaterial.o: ./ionScene/IRenderPass.h
./ionScene/CRenderable.SMaterial.o: ./ionScene/SUniform.h
./ionScene/CRenderable.SMaterial.o: ./ionScene/CShaderContext.h
./ionScene/CRenderable.SMaterial.o: ./ionScene/CShader.h
./ionScene/CRenderable.SMaterial.o: ./ionScene/CTexture.h ./ionScene/CImage.h
./ionScene/CRenderable.SMaterial.o: ./ionScene/IRenderTarget.h
./ionScene/CRenderable.SMaterial.o: ./ionScene/SAttribute.h
./ionScene/CRenderable.SMaterial.o: ./ionScene/CBufferObject.h
./ionWindow/CGamePad.o: ./ionWindow/CGamePad.h ./ionWindow/EGamePadButton.h
./ionWindow/CWindow.o: ./ionWindow/CWindow.h ./ionWindow/SKeyboardEvent.h
./ionWindow/CWindow.o: ./ionWindow/EKey.h ./ionWindow/SMouseEvent.h
./ionWindow/CWindow.o: ./ionWindow/SWindowResizedEvent.h
./ionWindow/CWindowManager.o: ./ionWindow/CWindowManager.h
./ionWindow/CWindowManager.o: ./ionWindow/CWindow.h
./ionWindow/CWindowManager.o: ./ionWindow/SKeyboardEvent.h ./ionWindow/EKey.h
./ionWindow/CWindowManager.o: ./ionWindow/SMouseEvent.h
./ionWindow/CWindowManager.o: ./ionWindow/SWindowResizedEvent.h
./ionWindow/CWindowManager.o: ./ionWindow/CGamePad.h
./ionWindow/CWindowManager.o: ./ionWindow/EGamePadButton.h
./ionScience/STable.o: ./ionScience/STable.h ./ionScience/SRange.h
./ionScience/STable.o: ./ionScience/IDataRecord.h ./ionScience/IDatabase.h
./ionScience/STable.Row.o: ./ionScience/STable.h ./ionScience/SRange.h
./ionScience/STable.Row.o: ./ionScience/IDataRecord.h
./ionScience/STable.Row.o: ./ionScience/IDatabase.h
./ionScience/MarchingCubes.o: ./ionScience/MarchingCubes.h
./ionScience/MarchingCubes.o: ./ionScience/SVolume.h
./ionScience/MarchingCubes.o: ./ionScience/Interpolation.h
./ionScience/MarchingCubes.o: ./ionScience/MarchingCubesLookupTables.h
./ionScience/MarchingCubes.o: ./ionScience/CColorTable.h
./ionScience/CColorTable.o: ./ionScience/CColorTable.h
./ionScience/CColorTable.o: ./ionScience/DefaultColorTable.h
./ionScience/IProgressBar.o: ./ionScience/IProgressBar.h
./ionScience/STable.FieldIterator.o: ./ionScience/STable.h
./ionScience/STable.FieldIterator.o: ./ionScience/SRange.h
./ionScience/STable.FieldIterator.o: ./ionScience/IDataRecord.h
./ionScience/STable.FieldIterator.o: ./ionScience/IDatabase.h
./ionScience/CKDTree.o: ./ionScience/CKDTree.h
./ionFramework/CCameraControl.o: ./ionFramework/CCameraControl.h ionScene.h
./ionFramework/CCameraControl.o: ionScene/ionScene.h ./ionScene/CMesh.h
./ionFramework/CCameraControl.o: ./ionScene/SVertex.h
./ionFramework/CCameraControl.o: ./ionScene/CBufferObject.h
./ionFramework/CCameraControl.o: ./ionScene/CRenderable.h
./ionFramework/CCameraControl.o: ./ionScene/ISceneObject.Enumerations.h
./ionFramework/CCameraControl.o: ./ionScene/IRenderPass.h
./ionFramework/CCameraControl.o: ./ionScene/SUniform.h
./ionFramework/CCameraControl.o: ./ionScene/CShaderContext.h
./ionFramework/CCameraControl.o: ./ionScene/CShader.h ./ionScene/CTexture.h
./ionFramework/CCameraControl.o: ./ionScene/CImage.h
./ionFramework/CCameraControl.o: ./ionScene/IRenderTarget.h
./ionFramework/CCameraControl.o: ./ionScene/SAttribute.h
./ionFramework/CCameraControl.o: ./ionScene/CMeshLoader.h
./ionFramework/CCameraControl.o: ./ionScene/CMeshSceneObject.h
./ionFramework/CCameraControl.o: ./ionScene/CSceneObject.h
./ionFramework/CCameraControl.o: ./ionScene/ISceneObject.h
./ionFramework/CCameraControl.o: ./ionScene/CInstanceSceneObject.h
./ionFramework/CCameraControl.o: ./ionScene/CShaderLoader.h
./ionFramework/CCameraControl.o: ./ionScene/CImageLoader.h
./ionFramework/CCameraControl.o: ./ionScene/CSceneManager.h
./ionFramework/CCameraControl.o: ./ionScene/CFrameBufferObject.h
./ionFramework/CCameraControl.o: ./ionScene/CRenderBufferObject.h
./ionFramework/CCameraControl.o: ./ionScene/CSceneEffectManager.h
./ionFramework/CCameraControl.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionFramework/CCameraControl.o: ./ionScene/CCameraSceneObject.h ionConfig.h
./ionFramework/CCameraControl.o: ./ionScene/ICameraSceneObject.h
./ionFramework/CCameraControl.o: ./ionScene/CScene.h ./ionScene/IScene.h
./ionFramework/CCameraControl.o: ./ionScene/CLightSceneObject.h
./ionFramework/CCameraControl.o: ./ionScene/CDefaultColorRenderPass.h
./ionFramework/CCameraControl.o: ./ionScene/CMultiOutRenderPass.h
./ionFramework/CCameraControl.o: ./ionScene/CDeferredShadingManager.h
./ionFramework/CCameraControl.o: ./ionScene/CPointLightSceneObject.h
./ionFramework/CCameraControl.o: ./ionScene/CDirectionalLightSceneObject.h
./ionFramework/CCameraControl.o: ./ionFramework/CApplication.h
./ionFramework/CCameraControl.o: ./ionFramework/CStateManager.h
./ionFramework/CCameraControl.o: ./ionFramework/IState.h
./ionFramework/CCameraControl.o: ./ionFramework/IEventListener.h
./ionFramework/CApplication.o: ./ionFramework/CApplication.h ionScene.h
./ionFramework/CApplication.o: ionScene/ionScene.h ./ionScene/CMesh.h
./ionFramework/CApplication.o: ./ionScene/SVertex.h
./ionFramework/CApplication.o: ./ionScene/CBufferObject.h
./ionFramework/CApplication.o: ./ionScene/CRenderable.h
./ionFramework/CApplication.o: ./ionScene/ISceneObject.Enumerations.h
./ionFramework/CApplication.o: ./ionScene/IRenderPass.h ./ionScene/SUniform.h
./ionFramework/CApplication.o: ./ionScene/CShaderContext.h
./ionFramework/CApplication.o: ./ionScene/CShader.h ./ionScene/CTexture.h
./ionFramework/CApplication.o: ./ionScene/CImage.h ./ionScene/IRenderTarget.h
./ionFramework/CApplication.o: ./ionScene/SAttribute.h
./ionFramework/CApplication.o: ./ionScene/CMeshLoader.h
./ionFramework/CApplication.o: ./ionScene/CMeshSceneObject.h
./ionFramework/CApplication.o: ./ionScene/CSceneObject.h
./ionFramework/CApplication.o: ./ionScene/ISceneObject.h
./ionFramework/CApplication.o: ./ionScene/CInstanceSceneObject.h
./ionFramework/CApplication.o: ./ionScene/CShaderLoader.h
./ionFramework/CApplication.o: ./ionScene/CImageLoader.h
./ionFramework/CApplication.o: ./ionScene/CSceneManager.h
./ionFramework/CApplication.o: ./ionScene/CFrameBufferObject.h
./ionFramework/CApplication.o: ./ionScene/CRenderBufferObject.h
./ionFramework/CApplication.o: ./ionScene/CSceneEffectManager.h
./ionFramework/CApplication.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionFramework/CApplication.o: ./ionScene/CCameraSceneObject.h ionConfig.h
./ionFramework/CApplication.o: ./ionScene/ICameraSceneObject.h
./ionFramework/CApplication.o: ./ionScene/CScene.h ./ionScene/IScene.h
./ionFramework/CApplication.o: ./ionScene/CLightSceneObject.h
./ionFramework/CApplication.o: ./ionScene/CDefaultColorRenderPass.h
./ionFramework/CApplication.o: ./ionScene/CMultiOutRenderPass.h
./ionFramework/CApplication.o: ./ionScene/CDeferredShadingManager.h
./ionFramework/CApplication.o: ./ionScene/CPointLightSceneObject.h
./ionFramework/CApplication.o: ./ionScene/CDirectionalLightSceneObject.h
./ionFramework/CApplication.o: ./ionFramework/CStateManager.h
./ionFramework/CApplication.o: ./ionFramework/IState.h
./ionFramework/CApplication.o: ./ionFramework/IEventListener.h
./ionFramework/COrthoCamera.o: ./ionFramework/COrthoCamera.h
./ionFramework/COrthoCamera.o: ./ionFramework/CApplication.h ionScene.h
./ionFramework/COrthoCamera.o: ionScene/ionScene.h ./ionScene/CMesh.h
./ionFramework/COrthoCamera.o: ./ionScene/SVertex.h
./ionFramework/COrthoCamera.o: ./ionScene/CBufferObject.h
./ionFramework/COrthoCamera.o: ./ionScene/CRenderable.h
./ionFramework/COrthoCamera.o: ./ionScene/ISceneObject.Enumerations.h
./ionFramework/COrthoCamera.o: ./ionScene/IRenderPass.h ./ionScene/SUniform.h
./ionFramework/COrthoCamera.o: ./ionScene/CShaderContext.h
./ionFramework/COrthoCamera.o: ./ionScene/CShader.h ./ionScene/CTexture.h
./ionFramework/COrthoCamera.o: ./ionScene/CImage.h ./ionScene/IRenderTarget.h
./ionFramework/COrthoCamera.o: ./ionScene/SAttribute.h
./ionFramework/COrthoCamera.o: ./ionScene/CMeshLoader.h
./ionFramework/COrthoCamera.o: ./ionScene/CMeshSceneObject.h
./ionFramework/COrthoCamera.o: ./ionScene/CSceneObject.h
./ionFramework/COrthoCamera.o: ./ionScene/ISceneObject.h
./ionFramework/COrthoCamera.o: ./ionScene/CInstanceSceneObject.h
./ionFramework/COrthoCamera.o: ./ionScene/CShaderLoader.h
./ionFramework/COrthoCamera.o: ./ionScene/CImageLoader.h
./ionFramework/COrthoCamera.o: ./ionScene/CSceneManager.h
./ionFramework/COrthoCamera.o: ./ionScene/CFrameBufferObject.h
./ionFramework/COrthoCamera.o: ./ionScene/CRenderBufferObject.h
./ionFramework/COrthoCamera.o: ./ionScene/CSceneEffectManager.h
./ionFramework/COrthoCamera.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionFramework/COrthoCamera.o: ./ionScene/CCameraSceneObject.h ionConfig.h
./ionFramework/COrthoCamera.o: ./ionScene/ICameraSceneObject.h
./ionFramework/COrthoCamera.o: ./ionScene/CScene.h ./ionScene/IScene.h
./ionFramework/COrthoCamera.o: ./ionScene/CLightSceneObject.h
./ionFramework/COrthoCamera.o: ./ionScene/CDefaultColorRenderPass.h
./ionFramework/COrthoCamera.o: ./ionScene/CMultiOutRenderPass.h
./ionFramework/COrthoCamera.o: ./ionScene/CDeferredShadingManager.h
./ionFramework/COrthoCamera.o: ./ionScene/CPointLightSceneObject.h
./ionFramework/COrthoCamera.o: ./ionScene/CDirectionalLightSceneObject.h
./ionFramework/COrthoCamera.o: ./ionFramework/CStateManager.h
./ionFramework/COrthoCamera.o: ./ionFramework/IState.h
./ionFramework/COrthoCamera.o: ./ionFramework/IEventListener.h
./ionFramework/CStateManager.o: ./ionFramework/CStateManager.h
./ionFramework/CStateManager.o: ./ionFramework/IState.h
./ionFramework/CStateManager.o: ./ionFramework/IEventListener.h
./ionFramework/CStateManager.o: ./ionFramework/CApplication.h ionScene.h
./ionFramework/CStateManager.o: ionScene/ionScene.h ./ionScene/CMesh.h
./ionFramework/CStateManager.o: ./ionScene/SVertex.h
./ionFramework/CStateManager.o: ./ionScene/CBufferObject.h
./ionFramework/CStateManager.o: ./ionScene/CRenderable.h
./ionFramework/CStateManager.o: ./ionScene/ISceneObject.Enumerations.h
./ionFramework/CStateManager.o: ./ionScene/IRenderPass.h
./ionFramework/CStateManager.o: ./ionScene/SUniform.h
./ionFramework/CStateManager.o: ./ionScene/CShaderContext.h
./ionFramework/CStateManager.o: ./ionScene/CShader.h ./ionScene/CTexture.h
./ionFramework/CStateManager.o: ./ionScene/CImage.h
./ionFramework/CStateManager.o: ./ionScene/IRenderTarget.h
./ionFramework/CStateManager.o: ./ionScene/SAttribute.h
./ionFramework/CStateManager.o: ./ionScene/CMeshLoader.h
./ionFramework/CStateManager.o: ./ionScene/CMeshSceneObject.h
./ionFramework/CStateManager.o: ./ionScene/CSceneObject.h
./ionFramework/CStateManager.o: ./ionScene/ISceneObject.h
./ionFramework/CStateManager.o: ./ionScene/CInstanceSceneObject.h
./ionFramework/CStateManager.o: ./ionScene/CShaderLoader.h
./ionFramework/CStateManager.o: ./ionScene/CImageLoader.h
./ionFramework/CStateManager.o: ./ionScene/CSceneManager.h
./ionFramework/CStateManager.o: ./ionScene/CFrameBufferObject.h
./ionFramework/CStateManager.o: ./ionScene/CRenderBufferObject.h
./ionFramework/CStateManager.o: ./ionScene/CSceneEffectManager.h
./ionFramework/CStateManager.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionFramework/CStateManager.o: ./ionScene/CCameraSceneObject.h ionConfig.h
./ionFramework/CStateManager.o: ./ionScene/ICameraSceneObject.h
./ionFramework/CStateManager.o: ./ionScene/CScene.h ./ionScene/IScene.h
./ionFramework/CStateManager.o: ./ionScene/CLightSceneObject.h
./ionFramework/CStateManager.o: ./ionScene/CDefaultColorRenderPass.h
./ionFramework/CStateManager.o: ./ionScene/CMultiOutRenderPass.h
./ionFramework/CStateManager.o: ./ionScene/CDeferredShadingManager.h
./ionFramework/CStateManager.o: ./ionScene/CPointLightSceneObject.h
./ionFramework/CStateManager.o: ./ionScene/CDirectionalLightSceneObject.h
./ionFramework/CFadeOutState.o: ./ionFramework/CFadeOutState.h
./ionFramework/CFadeOutState.o: ./ionFramework/CStateManager.h
./ionFramework/CFadeOutState.o: ./ionFramework/IState.h
./ionFramework/CFadeOutState.o: ./ionFramework/IEventListener.h
./ionFramework/CFadeOutState.o: ./ionFramework/CApplication.h ionScene.h
./ionFramework/CFadeOutState.o: ionScene/ionScene.h ./ionScene/CMesh.h
./ionFramework/CFadeOutState.o: ./ionScene/SVertex.h
./ionFramework/CFadeOutState.o: ./ionScene/CBufferObject.h
./ionFramework/CFadeOutState.o: ./ionScene/CRenderable.h
./ionFramework/CFadeOutState.o: ./ionScene/ISceneObject.Enumerations.h
./ionFramework/CFadeOutState.o: ./ionScene/IRenderPass.h
./ionFramework/CFadeOutState.o: ./ionScene/SUniform.h
./ionFramework/CFadeOutState.o: ./ionScene/CShaderContext.h
./ionFramework/CFadeOutState.o: ./ionScene/CShader.h ./ionScene/CTexture.h
./ionFramework/CFadeOutState.o: ./ionScene/CImage.h
./ionFramework/CFadeOutState.o: ./ionScene/IRenderTarget.h
./ionFramework/CFadeOutState.o: ./ionScene/SAttribute.h
./ionFramework/CFadeOutState.o: ./ionScene/CMeshLoader.h
./ionFramework/CFadeOutState.o: ./ionScene/CMeshSceneObject.h
./ionFramework/CFadeOutState.o: ./ionScene/CSceneObject.h
./ionFramework/CFadeOutState.o: ./ionScene/ISceneObject.h
./ionFramework/CFadeOutState.o: ./ionScene/CInstanceSceneObject.h
./ionFramework/CFadeOutState.o: ./ionScene/CShaderLoader.h
./ionFramework/CFadeOutState.o: ./ionScene/CImageLoader.h
./ionFramework/CFadeOutState.o: ./ionScene/CSceneManager.h
./ionFramework/CFadeOutState.o: ./ionScene/CFrameBufferObject.h
./ionFramework/CFadeOutState.o: ./ionScene/CRenderBufferObject.h
./ionFramework/CFadeOutState.o: ./ionScene/CSceneEffectManager.h
./ionFramework/CFadeOutState.o: ./ionScene/CPerspectiveCameraSceneObject.h
./ionFramework/CFadeOutState.o: ./ionScene/CCameraSceneObject.h ionConfig.h
./ionFramework/CFadeOutState.o: ./ionScene/ICameraSceneObject.h
./ionFramework/CFadeOutState.o: ./ionScene/CScene.h ./ionScene/IScene.h
./ionFramework/CFadeOutState.o: ./ionScene/CLightSceneObject.h
./ionFramework/CFadeOutState.o: ./ionScene/CDefaultColorRenderPass.h
./ionFramework/CFadeOutState.o: ./ionScene/CMultiOutRenderPass.h
./ionFramework/CFadeOutState.o: ./ionScene/CDeferredShadingManager.h
./ionFramework/CFadeOutState.o: ./ionScene/CPointLightSceneObject.h
./ionFramework/CFadeOutState.o: ./ionScene/CDirectionalLightSceneObject.h
