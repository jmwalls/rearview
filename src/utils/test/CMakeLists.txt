add_executable (test-cellnn test_cellnn.cpp ../cellnn.h)
target_link_libraries (test-cellnn)

add_executable (test-dbscan test_dbscan.cpp ../dbscan.h)
target_link_libraries (test-dbscan)

add_executable (test-kdtree test_kdtree.cpp ../kdtree.h)
target_link_libraries (test-kdtree)
