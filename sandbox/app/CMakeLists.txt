set(TARGET_NAME ElysianSandbox)




add_executable(${TARGET_NAME} main.cpp)
add_dependencies(${TARGET_NAME} ElysianRuntime)
target_link_libraries(${TARGET_NAME} ElysianRuntime)
target_include_directories(${TARGET_NAME} PRIVATE ${sandbox_root_dir} )
