cmake_minimum_required(VERSION 2.8.4)
project(mender)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-int-to-void-pointer-cast")

# include(${CMAKE_CURRENT_SOURCE_DIR}/render/render_files.cmake)

#set(SOURCE_FILES ${RENDER_FILES}
set(SOURCE_FILES
        main.cpp)

# Add mender files to source files
set(SOURCE_FILES ${SOURCE_FILES}
        mender/app/AppBase.cpp  mender/app/AppBase.h
        mender/app/AppMacOs.cpp mender/app/AppMacOS.h)


# Add mm files to source files
set(SOURCE_FILES ${SOURCE_FILES}
        window_macos.mm
        ext/include/mtlpp/mtlpp.mm)

# Compile mm files as Objective C++ (Not sure if there is a cleaner way to do this for all mm files)
set_source_files_properties(window_macos.mm            PROPERTIES COMPILE_FLAGS "-x objective-c++")
set_source_files_properties(ext/include/mtlpp/mtlpp.mm PROPERTIES COMPILE_FLAGS "-x objective-c++")


find_library(COCOA_LIBRARY          Cocoa          REQUIRED)
find_library(METAL_LIBRARY          Metal          REQUIRED)
find_library(METALKIT_LIBRARY       MetalKit       REQUIRED)


include_directories(mender ext/include)

#if(APPLE)
#    link_directories(ext/libs-lldb)
#elseif(WIN32 AND MINGW)
#    link_directories(ext/libs-ming64)
#endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)

target_link_libraries(${PROJECT_NAME} ${COCOA_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${METAL_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${METALKIT_LIBRARY})


target_link_libraries(${PROJECT_NAME} "-fobjc-link-runtime")
