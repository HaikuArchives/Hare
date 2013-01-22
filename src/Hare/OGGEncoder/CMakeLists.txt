
add_library(OGG-Encoder MODULE OggEncoder.cpp)

target_link_libraries(OGG-Encoder "audioinfo" "aeencoder" "tag" "be")

set_property(TARGET OGG-Encoder PROPERTY LIBRARY_OUTPUT_DIRECTORY ${HARE_BUILD_ADDONS_DIR})
