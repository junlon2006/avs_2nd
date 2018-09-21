add_definitions("-DACSDK_LOG_MODULE=unisoundKeywordDetector")
add_library(UNISOUND SHARED
    UnisoundKeywordDetector.cpp)

target_include_directories(UNISOUND PUBLIC
	"${UNISOUND_KEY_WORD_DETECTOR_INCLUDE_DIR}"
	"${KWD_SOURCE_DIR}/include" 
	"${UNISOUND_SOURCE_DIR}/include")

target_link_libraries(UNISOUND KWD AVSCommon "${UNISOUND_KEY_WORD_DETECTOR_LIB_PATH}/libengine.so")

# install target
asdk_install()
