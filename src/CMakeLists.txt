project(cpp-cli)

# PAHO linking
set(PAHO_CPP_LIB paho-mqttpp3)
set(PAHO_C_LIB paho-mqtt3as)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.65.1 COMPONENTS program_options)
if(Boost_FOUND)
  
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(bhoot main.cpp)
  target_link_libraries(bhoot ${Boost_LIBRARIES})
  add_executable(sample-mqtt sample.cc)
  target_link_libraries(bhoot ${Boost_LIBRARIES} ${PAHO_CPP_LIB} ${PAHO_C_LIB})
  target_link_libraries(sample-mqtt ${PAHO_CPP_LIB} ${PAHO_C_LIB})

endif()
# The main program

if(NOT Boost_FOUND)
  message(FATAL_ERROR "Boost lib not found")
endif()
