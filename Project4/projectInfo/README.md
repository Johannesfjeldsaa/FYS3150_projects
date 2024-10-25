# ReadMe file for project 4



# EVERYTHING ELSE FROM P3 EDIT

## Description
Source and plotting code used to solve project 3 in the UiO course FYS3150 autumn 2024. The main topics of the project include: 
- Methods for solving initial value problems (ODEs):
	- Main algorithm: Runge-Kutta, 4th order
- Coding:
	- Object-oriented programming, classes in C++
	- Use of the Armadillo library
- Pysics case: simulating a Penning trap 

## Getting and running code

- All source code is written in C++ and is runable by navigating from the repository root (`$REPO_ROOT`)to the project root (`$PROJ_ROOT`: `> cd Project3`) directory.
  - The files named all_*.sh will source CMakeLists.txt, then build and run the files. Ass is, `> ./all_p3.sh` will configure C++, build the problem 8 and run them by calling `$PROJ_ROOT/.sh/configure.sh`, `$PROJ_ROOT/.sh/build.sh` and `$PROJ_ROOT/.sh/run_p3.sh`. To run all code: 1. uncomment the executables in CMakeLists and in .sh/run_p3.sh then run. Note: problem 9 does not have a main function that will create all outputdata presented in the report. It is however the correct source code so it is only a metter of uncommenting/commenting some of the lines where $f$ and $\omega_v$ vectors are set. 
  - If you get *./someshfile.sh Permission denied* bash error run `chmod +x someshfile.sh`.  
  - The armadillo library is linked using the `$REPO_ROOT/.gitmodules` file.  
  - If it cmake dont find OpenBLAS and Lapack install it to the computer (e.g.: pkcon install llapack-dev) and relink aramdillo by running `cd $REPO_ROOT && rm -rf externals/armadillo && git submodule add  https://gitlab.com/conradsnicta/armadillo-code.git externals/armadillo`. Then navigate into `externals/armadillo/` run `mkdir build && cd build && cmake .. && make`. Now armadillo should automatically connect to OpenBLAS and lapack.  
- Subsequently figures can be reproduced by running `$PROJ_ROOT/plotting.ipynb` in a jupyter notebook. 
  - A conda enviroment containing the dependencies can be created by navigating to `$PROJ_ROOT/projectInfo/pyEnvYaml` and running `> conda env create -n proj2env -f proj2env.yaml`.

