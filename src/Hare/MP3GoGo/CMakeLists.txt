
add_library(MP3-GoGo MODULE GoGoEncoder.cpp)

target_link_libraries(MP3-GoGo "audioinfo" "aeencoder" "tag" "be")

set_property(TARGET MP3-GoGo PROPERTY LIBRARY_OUTPUT_DIRECTORY ${HARE_BUILD_ADDONS_DIR})
