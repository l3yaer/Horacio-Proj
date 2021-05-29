cmake_minimum_required(VERSION 3.15)

find_package(CURL CONFIG REQUIRED)

add_library(core
        World.cpp
        Movable.cpp
        Camera.cpp
        World.cpp
        Filesystem.cpp
		ResourceManager.cpp
		Resource.cpp
		Actor.cpp
		LogManager.cpp
		Log.cpp
		SceneNode.cpp
		Layer.cpp
		Map.cpp
		Area.cpp
		MoveAction.cpp
		SequenceAction.cpp
		RepeatAction.cpp
		WorkerQueue.h
		WorkerQueue.cpp)

if(WIN32)
target_link_libraries(core PRIVATE glm CURL::libcurl ${CMAKE_DL_LIBS})
else()
target_link_libraries(core PRIVATE glm curl ${CMAKE_DL_LIBS})
endif()

set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
