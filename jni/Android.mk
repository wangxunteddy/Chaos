LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := /Users/toseuser/Documents/boost_1_47_0 \
                      jni/chaos

LOCAL_LDLIBS    := -lGLESv2

LOCAL_MODULE    := chaos

### Add all source file names to be included in lib separated by a whitespace
LOCAL_SRC_FILES := chaos.cpp                                 \
                                                             \
                   chaos/math/ChsMath.cpp                    \
                   chaos/math/ChsMatrix.cpp                  \
                   chaos/math/ChsQuaternion.cpp              \
                   chaos/math/ChsVector2.cpp                 \
                   chaos/math/ChsVector3.cpp                 \
                   chaos/math/ChsVector4.cpp                 \
                                                             \
                   chaos/shader/ChsFragmentShader.cpp        \
                   chaos/shader/ChsShader.cpp                \
                   chaos/shader/ChsShaderManager.cpp         \
                   chaos/shader/ChsShaderProgram.cpp         \
                   chaos/shader/ChsVertexShader.cpp          \
                                                             \
                   chaos/ChsUtility.cpp                      \
                   chaos/ChsSingleton.cpp                    \
                   chaos/ChsEngine.cpp                       \
                   chaos/ChsRenderFactory.cpp                \
                   chaos/ChsRenderSystem.cpp
                   

include $(BUILD_SHARED_LIBRARY)
