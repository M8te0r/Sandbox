
set(sandbox_root_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(3rd_root_dir ${sandbox_root_dir}/3rdparty)
set(app_root_dir ${sandbox_root_dir}/app)
set(runtime_root_dir ${sandbox_root_dir}/runtime)






add_subdirectory(3rdparty)
add_subdirectory(app)
add_subdirectory(runtime)