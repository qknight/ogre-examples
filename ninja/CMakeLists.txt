#http://www.ogre3d.org/wiki/index.php/Building_Your_Projects_With_CMake

PROJECT(ninja)

#set(CMAKE_MODULE_PATH 
# 	/usr/lib/OGRE/cmake
#)

#FIND_PACKAGE(OGRE)

cmake_minimum_required(VERSION 2.6)

INCLUDE_DIRECTORIES(
  ${OGRE_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}
  "${CMAKE_SOURCE_DIR}/src"
  "/usr/include/OGRE"
)

ADD_EXECUTABLE(ninja
  src/ExampleApplication.cpp
)

TARGET_LINK_LIBRARIES(ogre3dTest
# 	${OpenGL_LIBRARIES}
# 	${OIS_LIBRARIES}
# 	${OGRE_LIBRARIES}
  )

TARGET_LINK_LIBRARIES( ninja "-DOGRE_GUI_gtk -DOGRE_THREAD_SUPPORT=2 -pthread -DOGRE_CONFIG_LITTLE_ENDIAN -Iinclude/OGRE -I/usr/include/OIS  -L/usr/lib -lOgreMain -lboost_thread -lOIS -lpthread" )
