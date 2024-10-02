cmake_minimum_required(VERSION 3.11)
project(Project3)

########################
### Handle libraries ###
########################

# Find LAPACK and BLAS
find_package(LAPACK REQUIRED)
find_package(BLAS REQUIRED)

# Add Armadillo subdirectory
add_subdirectory(../externals/armadillo armadillo_build)

# create static library from .cpp files
foreach(source Particle PenningTrap)
    add_library(${source}_lib STATIC src/${source}.cpp)
    target_link_libraries(${source}_lib
        armadillo
        ${LAPACK_LIBRARIES}
        ${BLAS_LIBRARIES}
    )
    target_compile_definitions(${source}_lib PRIVATE ARMA_USE_LAPACK ARMA_USE_BLAS)
endforeach()


#####################################################################################
### create executable from pX.cpp files and link with Armadillo, LAPACK, and BLAS ###
#####################################################################################

add_executable(test solutions/test.cpp)
add_executable(main solutions/main.cpp)


foreach(exec test main)
    target_link_libraries(${exec}
        Particle_lib
        PenningTrap_lib
        armadillo
        ${LAPACK_LIBRARIES}
        ${BLAS_LIBRARIES}
    )
endforeach()


foreach(exec test main)
    target_compile_definitions(${exec} PRIVATE ARMA_USE_LAPACK ARMA_USE_BLAS)
endforeach()
