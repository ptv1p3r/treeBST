cmake_minimum_required(VERSION 3.7)
project(treeBST)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        driver.c
        eps.c
        eps.h
        item.c
        item.h
        tree.c
        tree.h
        treeType.h)

add_executable(treeBST ${SOURCE_FILES})
target_link_libraries(treeBST m)