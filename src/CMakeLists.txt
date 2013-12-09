# configure cmake
set (CMAKE_C_FLAGS "-u MAIN__ -std=gnu99 -Wfloat-equal -Wall -Wundef -Wno-strict-aliasing -Wno-unused-function")
set (CMAKE_CXX_FLAGS "-u MAIN__ -Wall -Wundef -Wno-strict-aliasing --std=gnu++0x")

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
  add_definitions (-D_LINUX -D_x64)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "i386")
  add_definitions (-D_LINUX -D_x86)
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "i686")
  add_definitions (-D_LINUX -D_x86)
else ()
  message (SEND_ERROR 
      "Uknown CMAKE_SYSTEM_PROCESSOR=${CMAKE_SYSTEM_PROCESSOR}")
endif ()

# find external packages, libraries, and headers for the entire project
# find boost
find_package (Boost 1.46.0 COMPONENTS system date_time)
if (Boost_FOUND)
  include_directories (${Boost_INCLUDE_DIRS})
  mark_as_advanced (Boost_DIR boost_DIR)
  set (LIBBOOST ${Boost_LIBRARIES})
else ()
  message (SEND_ERROR "BOOST not found")
endif ()

find_package (OpenCV REQUIRED)
if (OpenCV_FOUND)
  include_directories (${OpenCV_INCLUDE_DIRS})
  mark_as_advanced (OpenCV_INCLUDE_DIRS OpenCV_DIR)
  set (LIBOPENCV ${OpenCV_LIBS})
else ()
  message (SEND_ERROR "OpenCV not found")
endif ()

# find eigen
#find_package (Eigen3 REQUIRED)
#include_directories (${EIGEN3_INCLUDE_DIR})

# add subdirs
add_subdirectory (capture)
add_subdirectory (utils)
