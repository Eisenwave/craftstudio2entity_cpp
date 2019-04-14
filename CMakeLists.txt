cmake_minimum_required(VERSION 3.13)
project(craftstudio2entity_cpp)

set(CMAKE_CXX_STANDARD 14)

# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")

# If you only include this third party in PRIVATE source files, you do not
# need to install it when your main project gets installed.
set(JSON_Install OFF CACHE INTERNAL "")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

# Don't use include(nlohmann_json/CMakeLists.txt) since that carries with it
# unintended consequences that will break the build.  It's generally
# discouraged (although not necessarily well documented as such) to use
# include(...) for pulling in other CMake projects anyways.
add_subdirectory(src/nlohmann_json)

add_executable(craftstudio2entity
        src/main.cpp
        src/math_util.cpp
        src/math_util.hpp
        src/bedrock_model.hpp
        src/craftstudio_model.hpp
        src/io_util.hpp
        src/model_io.hpp)

target_link_libraries(craftstudio2entity PRIVATE nlohmann_json::nlohmann_json)

#install(TARGETS craftstudio2entity DESTINATION ./bin)