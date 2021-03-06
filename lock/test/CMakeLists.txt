CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(vdbs-test)

MACRO(source_group_by_dir source_files)
    SET(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
    FOREACH(sgbd_file ${${source_files}})
        STRING(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
        STRING(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
        STRING(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
        IF(MSVC)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
        ENDIF(MSVC)
        IF(sgbd_nogroup)
            SET(sgbd_group_name "\\")
        ENDIF(sgbd_nogroup)
        SOURCE_GROUP(${sgbd_group_name} FILES ${sgbd_file})
    ENDFOREACH(sgbd_file)
ENDMACRO(source_group_by_dir)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -O2  -fprofile-arcs -ftest-coverage")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb ")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage -lgcov")

#SET(TARGET_BUILD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../output/)

INCLUDE_DIRECTORIES( 
)

FILE(GLOB_RECURSE all_files
${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp
)

source_group_by_dir(all_files)

#link_directories("${TARGET_BUILD_PATH}/lib")

ADD_EXECUTABLE(SpinlockTest ${all_files})

#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../src/vdbs/dbconfig.txt  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build)

TARGET_LINK_LIBRARIES(SpinlockTest pthread) #protobuf)
