cmake_minimum_required(VERSION 3.13)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(cplusplus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${CMAKE_SIZEOF_VOID_P} EQUAL "8")
    set (CMS_ARCHITECTURE "x64")
else ()
    set (CMS_ARCHITECTURE "x86")
endif ()

message("cmake current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# Create directory where CMSAPI will be copied on installation.
# For windows it will be project_dir/x64/windows/{Debug/Release}
# For Linux it will be project_dir/x64/unix/{Debug/Release}
if(CONAN_EXPORTED) # in conan local cache
    set(CMS_DESTINATION_DIR "${CMAKE_BINARY_DIR}/${CMS_ARCHITECTURE}/${CURRENT_SYSTEM_TYPE}/${CMAKE_BUILD_TYPE}")
else()
    set(CMS_DESTINATION_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${CMS_ARCHITECTURE}/${CURRENT_SYSTEM_TYPE}/${CMAKE_BUILD_TYPE}")
endif()

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    add_definitions(-DUNICODE -D_UNICODE)
elseif(UNIX)
    SET(CMAKE_C_FLAGS "-lrt")
    set(CMAKE_CXX_STANDARD_LIBRARIES -lpthread)
endif()

add_compile_definitions(_CONSOLE)

if(WIN32)
    add_compile_definitions(_WINSOCK_DEPRECATED_NO_WARNINGS)
elseif(UNIX)
endif()

if(WIN32)
    add_compile_definitions(WIN32)
endif()


set(HEADERS
    ${HEADERS}
)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/recursion.cpp
)

# Let's set compiler-specific flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # G++
    #target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    endif()

elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # MSVC
    #set(CMAKE_CXX_FLAGS_DEBUG "-g")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O3")

    # target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /MTd /W4 /c /sdl /GR- /FC /INCREMENTAL)
    # Set the DLLEXPORT variable to export symbols
    # target_compile_definitions(${PROJECT_NAME} PRIVATE WIN_EXPORT)

    #SET_TARGET_PROPERTIES(${targetname} PROPERTIES LINK_FLAGS_DEBUG "/WHOLEARCHIVE:${targetname}")

endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMS_DESTINATION_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMS_DESTINATION_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMS_DESTINATION_DIR})
    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMS_DESTINATION_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMS_DESTINATION_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMS_DESTINATION_DIR})

# Add CMS libraries.
add_executable(${PROJECT_NAME} 
            ${HEADERS}
            ${SOURCES}
)

#target_link_libraries(${PROJECT_NAME} CMSClient)