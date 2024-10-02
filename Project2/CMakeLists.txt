cmake_minimum_required(VERSION 3.11)
project(Project2)

# Find LAPACK and BLAS
find_package(LAPACK REQUIRED)
find_package(BLAS REQUIRED)

# Add Armadillo subdirectory
add_subdirectory(../externals/armadillo armadillo_build)

# create static library from pX.cpp files
foreach(source p2 p3)
    add_library(${source}_lib STATIC solutions/${source}.cpp)
    target_link_libraries(${source}_lib
        armadillo
        ${LAPACK_LIBRARIES}
        ${BLAS_LIBRARIES}
    )
    target_compile_definitions(${source}_lib PRIVATE ARMA_USE_LAPACK ARMA_USE_BLAS)
endforeach()

add_library(p4_lib STATIC solutions/p4.cpp)
target_link_libraries(p4_lib
    p2_lib
    p3_lib
    armadillo
    ${LAPACK_LIBRARIES}
    ${BLAS_LIBRARIES}
)
target_compile_definitions(p4_lib PRIVATE ARMA_USE_LAPACK ARMA_USE_BLAS)


#####################################################################################
### create executable from pX.cpp files and link with Armadillo, LAPACK, and BLAS ###
#####################################################################################

add_executable(problem2 solutions/p2.cpp)
add_executable(problem3 solutions/p3.cpp)
add_executable(problem4 solutions/p4.cpp)
add_executable(problem5 solutions/p5.cpp)
add_executable(problem6 solutions/p6.cpp)

# link problems with packages 
#   link all problems with Armadillo, LAPACK, and BLAS
#   in addition:
#       link problem 4 with p2_lib and p3_lib 
#       link problem 5 and 6 with p2_lib, p3_lib, and p4_lib
foreach(exec problem2 problem3)
    target_link_libraries(${exec}
        armadillo
        ${LAPACK_LIBRARIES}
        ${BLAS_LIBRARIES}
    )
endforeach()

target_link_libraries(problem4
    p2_lib
    p3_lib
    armadillo
    ${LAPACK_LIBRARIES}
    ${BLAS_LIBRARIES}
)

foreach(exec problem5 problem6)
    target_link_libraries(${exec}
        p2_lib
        p3_lib
        p4_lib
        armadillo
        ${LAPACK_LIBRARIES}
        ${BLAS_LIBRARIES}
    )
endforeach()

foreach(exec problem2 problem3 problem4 problem5 problem6)
    target_compile_definitions(${exec} PRIVATE COMPILE_AS_MAIN ARMA_USE_LAPACK ARMA_USE_BLAS)
endforeach()

foreach(exec problem5 problem6)
    target_compile_definitions(${exec} PRIVATE ARMA_USE_LAPACK ARMA_USE_BLAS)
endforeach()
