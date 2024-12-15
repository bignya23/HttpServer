# CMakeList.txt : CMake project for HttpServer, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (HttpServer "HttpServer.cpp" "HttpServer.h" "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HttpServer PROPERTY CXX_STANDARD 20)
endif()

if(WIN32) 
	 target_link_libraries(HttpServer PRIVATE ws2_32)
endif()



# TODO: Add tests and install targets if needed.
