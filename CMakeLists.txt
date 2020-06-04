# CMakeList.txt : CMake project for helloLibevent, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.11)

project ("HelloCpp" VERSION 0.0.1)



include(./cmake/checkBuildType.cmake)

#-------------------------------------
#  spdlog settings
#-------------------------------------
include(./cmake/utils.cmake)


include(./.SET_LOCAL_PATH.cmake)


# --------------------------------------------------------------------------
# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-D__STDC_CONSTANT_MACROS")



if(MSVC)
    SET(CMAKE_CXX_FLAGS "/EHsc")  # deal with MSVC Warning C4530
endif(MSVC)


#-------------------------------------
#  PRE BUILD DEFINE
#-------------------------------------
if(WIN32)

elseIf(UNIX)
	add_definitions(-Wall)
endif()



#-------------------------------------
#  Threads
#-------------------------------------
find_package(Threads REQUIRED) 



#-------------------------------------
#  config.h.in settings
#-------------------------------------



######################################
#  Information
######################################
message(" ===================== Information ======================")
message(CMAKE_SOURCE_DIR         	    =  ${CMAKE_SOURCE_DIR})
message(PROJECT_SOURCE_DIR            =  ${PROJECT_SOURCE_DIR})
message(CMAKE_INCLUDE_PATH            =  ${CMAKE_INCLUDE_PATH})
message(CMAKE_LIBRARY_PATH            =  ${CMAKE_LIBRARY_PATH})
message(PROJECT_SOURCE_DIR            =  ${PROJECT_SOURCE_DIR})
message(CMAKE_BUILD_TYPE              =  ${CMAKE_BUILD_TYPE})

message(" ===================== SETTING ======================")



message(" ==================== LIBRARY PATH =====================")
message(CMAKE_THREAD_LIBS_INIT		  =  ${CMAKE_THREAD_LIBS_INIT})
message(CMAKE_DL_LIBS	         	    =  ${CMAKE_DL_LIBS})


message(" ==================== INCLUDE PATH =====================")




# Add source to this project's executable.
add_executable (${PROJECT_NAME}   
  "src/Main.cpp" 
  "src/TmpTest7.cpp" 
 )


target_include_directories( ${PROJECT_NAME}  
	PRIVATE 
		${PROJECT_SOURCE_DIR}/include
)


#spdlog_enable_warnings(${PROJECT_NAME})


target_link_libraries( ${PROJECT_NAME}  
	PRIVATE 
		${CMAKE_THREAD_LIBS_INIT}
		${CMAKE_DL_LIBS}

)



add_subdirectory("modules/helloHash")





