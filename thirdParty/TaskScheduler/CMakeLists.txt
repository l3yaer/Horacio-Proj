set(_TaskScheduler_Sources
        ThirdParty/Squish/alpha.cpp
        ThirdParty/Squish/clusterfit.cpp
        ThirdParty/Squish/colourblock.cpp
        ThirdParty/Squish/colourfit.cpp
        ThirdParty/Squish/colourset.cpp
        ThirdParty/Squish/maths.cpp
        ThirdParty/Squish/rangefit.cpp
        ThirdParty/Squish/singlecolourfit.cpp
        ThirdParty/Squish/squish.cpp
        Scheduler/Source/MTDefaultAppInterop.cpp
        Scheduler/Source/MTFiberContext.cpp
        Scheduler/Source/MTScheduler.cpp
        Scheduler/Source/MTThreadContext.cpp
        ThirdParty/Boost.Context/fcontext.h)

source_group("" FILES ${_TaskScheduler_Sources})
add_library(taskScheduler STATIC ${_TaskScheduler_Sources})
target_include_directories(taskScheduler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Scheduler/Include ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Boost.Context ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Squish)