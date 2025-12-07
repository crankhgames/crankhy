cmake_minimum_required(VERSION 4.2)
project(crankhy)
    
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

file(COPY ${CMAKE_SOURCE_DIR}/assets/
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tools
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        ${SDL2_LIBRARIES}
        SDL2_image       

)