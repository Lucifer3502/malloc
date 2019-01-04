cmake_minimum_required(VERSION 3.0)
set(TARGET_NAME memdemo)
set(TARGET_LIBS m_mem pthread)

set(COMMON_INCLUDE "${PROJECT_SOURCE_DIR}/include")

file(GLOB SOURCE_FILES "*.c" "*.cpp" "*.cc")
file(GLOB PRIVATE_HEADERS "*.h" "*.hpp")
file(GLOB PUBLIC_HEADERS "inc/*.h" "include/*.hpp")
file(GLOB COMMON_HEADERS "${COMMON_INCLUDE}/*.h" "${COMMON_INCLUDE}/*.hpp")

add_executable(${TARGET_NAME} ${SOURCE_FILES} ${PRIVATE_HEADERS} ${PUBLIC_HEADERS} ${COMMON_HEADERS})
target_link_libraries(${TARGET_NAME} ${TARGET_LIBS})

