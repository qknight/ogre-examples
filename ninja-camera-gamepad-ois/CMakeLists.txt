PROJECT(ninja-camera-gamepad-ois)

cmake_minimum_required(VERSION 2.6)

INCLUDE_DIRECTORIES(
   ${CMAKE_SOURCE_DIR}
   "${CMAKE_SOURCE_DIR}/src"
#   ${CMAKE_CURRENT_SOURCE_DIR}
#   ${CMAKE_CURRENT_BINARY_DIR}
  "/usr/include/OGRE/"
  "/usr/include/OIS/"
  "/usr/include/SDL/"
)

ADD_EXECUTABLE(ninja-camera-gamepad-ois
  src/ExampleApplication.cpp
)

TARGET_LINK_LIBRARIES( ninja-camera-gamepad-ois "-DOGRE_GUI_gtk -DOGRE_THREAD_SUPPORT=2 -pthread -DOGRE_CONFIG_LITTLE_ENDIAN -Iinclude/OGRE -I/usr/include/OIS  -L/usr/lib -lOgreMain -lboost_thread -lOIS -lSDL -lpthread" )
