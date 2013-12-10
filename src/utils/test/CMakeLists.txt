add_executable (test-cellnn test_cellnn.cpp ../fixedradnn.h)
target_link_libraries (test-cellnn)

add_executable (test-dbscan test_dbscan.cpp ../dbscan.h)
target_link_libraries (test-dbscan)
