

## https://github.com/stbrumme/hash-library

######################################
#  HelloHash Information
######################################
message(" ===================== HelloHash Information ======================")
message(CMAKE_SOURCE_DIR         	    =  ${CMAKE_SOURCE_DIR})
message(PROJECT_SOURCE_DIR            =  ${PROJECT_SOURCE_DIR})
message(CMAKE_INCLUDE_PATH            =  ${CMAKE_INCLUDE_PATH})
message(CMAKE_LIBRARY_PATH            =  ${CMAKE_LIBRARY_PATH})
message(PROJECT_SOURCE_DIR            =  ${PROJECT_SOURCE_DIR})
message(CMAKE_BUILD_TYPE              =  ${CMAKE_BUILD_TYPE})
message(CMAKE_CURRENT_SOURCE_DIR      =  ${CMAKE_CURRENT_SOURCE_DIR})





add_executable( helloHash 
	"main.cpp"
	"src/md5.cpp"
	"src/sha1.cpp"
	"src/crc32.cpp"
)



target_include_directories( helloHash
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

