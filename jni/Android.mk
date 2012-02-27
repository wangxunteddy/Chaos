LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := libs/boost_1_49_0 \
                      src src/chaos

LOCAL_LDLIBS    := -lGLESv2 -lEGL

LOCAL_MODULE    := chaos

### Add all source file names to be included in lib separated by a whitespace
LOCAL_SRC_FILES := chaos.cpp                                	 	\
                                                             		\
                   ../src/chaos/math/ChsMath.cpp                    \
                   ../src/chaos/math/ChsMatrix.cpp                  \
                   ../src/chaos/math/ChsQuaternion.cpp              \
                   ../src/chaos/math/ChsVector2.cpp                 \
                   ../src/chaos/math/ChsVector3.cpp                 \
                   ../src/chaos/math/ChsVector4.cpp                 \
                                                            		\
                   ../src/chaos/shader/ChsShader.cpp                \
                   ../src/chaos/shader/ChsShaderManager.cpp         \
                   ../src/chaos/shader/ChsShaderProgram.cpp         \
																	\
					../src/chaos/geometry/ChsPlane.cpp				\
					../src/chaos/geometry/ChsCube.cpp				\
                                                             		\
                   ../src/chaos/ChsEngine.cpp                       \
                   ../src/chaos/ChsEntity.cpp						\
                   ../src/chaos/ChsEntityManager.cpp				\
                   ../src/chaos/ChsGameBase.cpp						\
                   ../src/chaos/ChsIndexBuffer.cpp					\
                   ../src/chaos/ChsMaterial.cpp						\
                   ../src/chaos/ChsMesh.cpp							\
                   ../src/chaos/ChsRenderFactory.cpp                \
                   ../src/chaos/ChsRenderNode.cpp 		            \
                   ../src/chaos/ChsRenderSystem.cpp					\
                   ../src/chaos/ChsResourceManager.cpp				\
                   ../src/chaos/ChsSingleton.cpp                    \
                   ../src/chaos/ChsUtility.cpp                      \
                   ../src/chaos/ChsVertexBuffer.cpp					\
                   

include $(BUILD_SHARED_LIBRARY)
