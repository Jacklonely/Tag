CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(vdbs)

SET(PROJECT_NAME vdbs)

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

SET(CMAKE_CXX_FLAGS "-std=c++11 -fPIC")
SET(CMAKE_C_FLAGS "-fPIC")

SET(TARGET_BUILD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../output/)

INCLUDE_DIRECTORIES( 
"${CMAKE_CURRENT_SOURCE_DIR}/include"
"${TARGET_BUILD_PATH}/include/"
#"${TARGET_BUILD_PATH}/include/infra"
#"${TARGET_BUILD_PATH}/include/3rdparty/aerospike"
)

IF(MSVC)
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
    ADD_DEFINITIONS(-DMSVC_VMG_ENABLED) #  /Z7)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /vmg")
ENDIF(MSVC)

FILE(GLOB_RECURSE all_files 
include/*.h
#include/*.tcc
src/*.cpp
)

source_group_by_dir(all_files)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR are: ${CMAKE_CURRENT_SOURCE_DIR}")

#add_library(vdbs SHARED ${all_files})

ADD_SUBDIRECTORY(test)

#SET(TARGET_BUILD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../output/)
#install(DIRECTORY DESTINATION ${TARGET_BUILD_PATH}/include)
#install(DIRECTORY DESTINATION ${TARGET_BUILD_PATH}/include/vdbs)
#install(DIRECTORY DESTINATION ${TARGET_BUILD_PATH}/lib)
#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${TARGET_BUILD_PATH}/include/vdbs)
#install(TARGETS vdbs LIBRARY DESTINATION ${TARGET_BUILD_PATH}/lib)

#add_custom_target(
#    uninstall 
#    COMMAND rm -rf ${TARGET_BUILD_PATH}/include/vdbs
#    )

#add_custom_target(
#    test 
#    COMMAND ./test/SpinlockTest
#    DEPENDS SpinlockTest
#    )
    
#SET(PACKAGE_NAME ${PROJECT_NAME}.tar.gz)

#add_custom_target(
#    pack 
#    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/pack.tmp/include/${PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/pack.tmp/lib
#    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/include/* ${CMAKE_CURRENT_BINARY_DIR}/pack.tmp/include/${PROJECT_NAME}/ -rf
#    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/lib${PROJECT_NAME}.so ${CMAKE_CURRENT_BINARY_DIR}/pack.tmp/lib/
#    COMMAND tar -czvf ${PROJECT_NAME}.tar.gz -C ${CMAKE_CURRENT_BINARY_DIR}/pack.tmp lib include
#    COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/pack.tmp
#    DEPENDS ${PROJECT} 
#    )
