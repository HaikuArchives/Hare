
add_executable(Hare Application.cpp
					AppView.cpp
					AppWindow.cpp
					CheckMark.cpp
					EditorView.cpp
					EncoderListView.cpp
					FileNamePatternView.cpp
					Settings.cpp
					StatusBarFilter.cpp)

find_library(TAGLIB tag)
if (NOT TAGLIB)
	message(FATAL_ERROR "libtag wasn't found. Please install it.")
endif(NOT TAGLIB)

target_link_libraries(Hare "santa" "aeencoder" "audioinfo" "tag" "be" "game" "media" "tracker")

set_property(TARGET Hare PROPERTY RUNTIME_OUTPUT_DIRECTORY ${HARE_BUILD_DIR})

haiku_add_resource_def(Hare Hare.rdef)

haiku_auto_mimetype(Hare)
