project(cpp-cli)

find_package(Boost 1.65.1 COMPONENTS program_options)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(bhoot main.cpp)
  target_link_libraries(bhoot ${Boost_LIBRARIES})
endif()
# The main program

if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost lib not found")
endif()
