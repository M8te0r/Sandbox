
# runtime库的名字
set(RUNTIME_NAME ElysianRuntime)

file(GLOB_RECURSE runtime_head_files "*.h")
file(GLOB_RECURSE runtime_source_files "*.cpp")

add_library(${RUNTIME_NAME} ${runtime_head_files} ${runtime_source_files})
add_dependencies(${RUNTIME_NAME} glad)

# 头文件路径
target_include_directories(
    ${RUNTIME_NAME}
    PRIVATE
    ${runtime_root_dir}
    ${3rd_root_dir}
    ${3rd_root_dir}/glad/include
    # ${3rd_root_dir}/glew/include #glew
    # ${glm_DIR} #glm
    # ${3rd_root_dir}/assimp/include
    ${GLM_INCLUDE_DIRS}
)

# 链接的库文件
target_link_libraries(
    ${RUNTIME_NAME} 
    PRIVATE
    glad
)



