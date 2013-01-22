
add_library(MP3-Lame MODULE MP3Lame.cpp)

target_link_libraries(MP3-Lame "audioinfo" "aeencoder" "tag" "be")

set_property(TARGET MP3-Lame PROPERTY LIBRARY_OUTPUT_DIRECTORY ${HARE_BUILD_ADDONS_DIR})
