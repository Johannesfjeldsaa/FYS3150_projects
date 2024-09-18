# ReadMe file for project 2

## Description
Source and plotting code used to solve project 2 in the UiO course FYS3150 autumn 2024. The main topics of the project are scaling of equations, eigenvalue problems and code/unit testing. For more details see [Project 2 — FYS3150_FYS4150 course material.pdf](Project2/projectInfo/Project 2 — FYS3150_FYS4150 course material.pdf). 

## Getting and running code

All source code is written in C++ and is runable by navigating from the repository root (`$REPO_ROOT`)to the project root (`$PROJ_ROOT`: `> cd Project2`) directory and running `> ./all_p2.sh` which will configure C++, build the programs and run them by calling `$PROJ_ROOT/.sh/configure.sh`, `$PROJ_ROOT/.sh/build.sh` and `$PROJ_ROOT/.sh/run.sh`. If you get *./someshfile.sh Permission denied* bash error run `chmod +x someshfile.sh`.  All external C++ libraries are linked using the `$REPO_ROOT/.gitmodules` file.  Subsequently figures can be reproduced by running `$PROJ_ROOT/plotting.ipynb` in a jupyter notebook. A conda enviroment containing the dependencies can be created by navigating to `$PROJ_ROOT/projectInfo/pyEnvYaml` and running `> conda env create -n proj2env -f proj2env.yaml`.

