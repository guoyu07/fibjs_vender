cmake_minimum_required(VERSION 2.6)

include(../tools/basic.cmake)

include_directories(
	"/usr/local/include/"
	"${PROJECT_SOURCE_DIR}/../icu/include"
)

add_definitions(
	-DV8_NO_FAST_TLS=1
	-DV8_DEPRECATION_WARNINGS=1
	-DV8_I18N_SUPPORT=1
	-DENABLE_HANDLE_ZAPPING=1
)

if(${BUILD_TYPE} STREQUAL "Debug")
	add_definitions(
		-DVERIFY_HEAP=1
		-DOBJECT_PRINT=1
		-DENABLE_DISASSEMBLER=1
		-DV8_ENABLE_CHECKS=1
		-DTRACE_MAPS=1
		-DENABLE_SLOW_DCHECKS=1
	)
endif()
