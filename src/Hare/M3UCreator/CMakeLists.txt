
add_library(M3U-Creator MODULE M3UCreator.cpp)

target_link_libraries(M3U-Creator "aeencoder" "tag" "be")

set_property(TARGET M3U-Creator PROPERTY LIBRARY_OUTPUT_DIRECTORY ${HARE_BUILD_ADDONS_DIR})
