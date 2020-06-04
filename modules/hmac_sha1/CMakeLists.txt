


# https://github.com/Akagi201/hmac-sha1

######################################
#  hmac_sha1 Information
######################################
message(" ===================== hmac_sha1 Information ======================")
message(CMAKE_SOURCE_DIR         	    =  ${CMAKE_SOURCE_DIR})
message(PROJECT_SOURCE_DIR            =  ${PROJECT_SOURCE_DIR})
message(CMAKE_INCLUDE_PATH            =  ${CMAKE_INCLUDE_PATH})
message(CMAKE_LIBRARY_PATH            =  ${CMAKE_LIBRARY_PATH})
message(PROJECT_SOURCE_DIR            =  ${PROJECT_SOURCE_DIR})
message(CMAKE_BUILD_TYPE              =  ${CMAKE_BUILD_TYPE})
message(CMAKE_CURRENT_SOURCE_DIR      =  ${CMAKE_CURRENT_SOURCE_DIR})





add_executable( hmac_sha1 
	"main.cpp"
	"src/hmac_sha1.c"
	"src/sha1.c"
)



target_include_directories( hmac_sha1
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

