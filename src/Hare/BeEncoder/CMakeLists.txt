
add_library(BeEncoder MODULE BeEncoder.cpp MediaMenuItem.cpp)

target_link_libraries(BeEncoder "audioinfo" "aeencoder" "string" "tag" "be" "media")

set_property(TARGET BeEncoder PROPERTY LIBRARY_OUTPUT_DIRECTORY ${HARE_BUILD_ADDONS_DIR})
