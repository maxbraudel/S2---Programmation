cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME FolderName)   
string(REPLACE " " "_" FolderName ${FolderName})

project(${FolderName}_Project)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

if (MSVC)
    add_compile_options(/W3)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -pedantic-errors)
endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE SRC_MAIN_FILES CONFIGURE_DEPENDS "src/main*.cpp")
file(GLOB_RECURSE EXERCISE_FILES CONFIGURE_DEPENDS "src/exercice*.cpp")

# Remove main files from SRC_FILES
foreach(SRC_MAIN_FILE ${SRC_MAIN_FILES})
    list(REMOVE_ITEM SRC_FILES ${SRC_MAIN_FILE})
endforeach()

# Remove exercise files from SRC_FILES
foreach(EXERCISE_FILE ${EXERCISE_FILES})
    list(REMOVE_ITEM SRC_FILES ${EXERCISE_FILE})
endforeach()

message(STATUS "SRC_FILES: ")
foreach(SRC_FILE ${SRC_FILES})
    message(STATUS "    ${SRC_FILE}")
endforeach()

message(STATUS "SRC_MAIN_FILES: ")
foreach(SRC_MAIN_FILE ${SRC_MAIN_FILES})
    message(STATUS "    ${SRC_MAIN_FILE}")
endforeach()

message(STATUS "EXERCISE_FILES: ")
foreach(EXERCISE_FILE ${EXERCISE_FILES})
    message(STATUS "    ${EXERCISE_FILE}")
endforeach()

foreach(SRC_MAIN_FILE ${SRC_MAIN_FILES})
    get_filename_component(SRC_MAIN_FILE_NAME ${SRC_MAIN_FILE} NAME)
    string(REPLACE ".cpp" "" SRC_MAIN_FILE_NAME ${SRC_MAIN_FILE_NAME})
    string(REPLACE "main_" "" SRC_MAIN_FILE_NAME ${SRC_MAIN_FILE_NAME})

    message(STATUS "Creating executable: ${SRC_MAIN_FILE_NAME}")
    add_executable(${SRC_MAIN_FILE_NAME} ${SRC_MAIN_FILE} ${SRC_FILES})
    target_compile_features(${SRC_MAIN_FILE_NAME} PUBLIC cxx_std_20)
    target_include_directories(${SRC_MAIN_FILE_NAME} PUBLIC "src/")
endforeach()

foreach(EXERCISE_FILE ${EXERCISE_FILES})
    get_filename_component(EXERCISE_FILE_NAME ${EXERCISE_FILE} NAME)
    string(REPLACE ".cpp" "" EXERCISE_FILE_NAME ${EXERCISE_FILE_NAME})

    message(STATUS "Creating executable: ${EXERCISE_FILE_NAME}")
    add_executable(${EXERCISE_FILE_NAME} ${EXERCISE_FILE} ${SRC_FILES})
    target_compile_features(${EXERCISE_FILE_NAME} PUBLIC cxx_std_20)
    target_include_directories(${EXERCISE_FILE_NAME} PUBLIC "src/")
endforeach()
