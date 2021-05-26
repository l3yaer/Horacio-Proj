cmake_minimum_required(VERSION 3.15)

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

target_link_libraries(core PRIVATE glm curl ${CMAKE_DL_LIBS})
set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
