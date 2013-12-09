option (BUILD_UTILS_TEST "build utils tests" OFF)
if (${BUILD_UTILS_TEST})
  add_subdirectory (test)
endif ()
