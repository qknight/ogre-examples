PROJECT(mars-rings-shader-cg)

cmake_minimum_required(VERSION 2.6)

INCLUDE_DIRECTORIES(
   ${CMAKE_SOURCE_DIR}
   "${CMAKE_SOURCE_DIR}/src"
#   ${CMAKE_CURRENT_SOURCE_DIR}
#   ${CMAKE_CURRENT_BINARY_DIR}
  "/usr/include/OGRE/"
  "/usr/include/OIS/"
)

ADD_EXECUTABLE(mars-rings-shader-cg 
  src/CreateRing.cpp 
  src/CreateSphere.cpp
  src/ExampleApplication.cpp
  src/DynamicLines.cpp
  src/DynamicRenderable.cpp
)

TARGET_LINK_LIBRARIES( mars-rings-shader-cg "-DOGRE_GUI_gtk -DOGRE_THREAD_SUPPORT=2 -pthread -DOGRE_CONFIG_LITTLE_ENDIAN -Iinclude/OGRE -I/usr/include/OIS  -L/usr/lib -lOgreMain -lboost_thread -lOIS -lpthread" )
