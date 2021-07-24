


set (include_dir "${CMAKE_CURRENT_LIST_DIR}/../include/ph_memory")
set (src_dir "${CMAKE_CURRENT_LIST_DIR}")

ph_create_modules (

	MODULES 
		"memory"
		"allocator"
		"arena"
		"memory_pool"

	INCLUDE
		"${include_dir}"

	SRC 
		"${src_dir}"
)

file(GLOB_RECURSE HEADER_LIST "${include_dir}/*.hpp")
file(GLOB SOURCE_LIST "${src_dir}/*.cpp")

set (self ${PROJECT_NAME})



add_library (${self} STATIC 
	${SOURCE_LIST}  ${HEADER_LIST} 
)

target_compile_definitions (${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:DEBUG> $<$<CONFIG:RELEASE>:RELEASE>")






ph_precompile (TARGET ${self} PUBLIC PCH ${std_pch} ${boost_pch})

add_library (ph::memory ALIAS ${self})
target_link_libraries (${self} PRIVATE ${Boost_LIBRARIES})
target_include_directories (${self} PUBLIC ${PROJECT_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})
# target_include_directories (${self} PUBLIC ph::coroutines)
target_compile_features (${self} PUBLIC cxx_std_20)


target_include_directories(${self} PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/${self}>
    $<INSTALL_INTERFACE:include/${self}>
)

target_include_directories(${self} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

else()
    set_target_properties(${PROJECT_NAME}          PROPERTIES FOLDER "dependencies/${PROJECT_NAME}")
endif()