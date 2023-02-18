## About
This folder follows lectures of C++20 Fundamentals by Paul J. Deitel

## Compilation
Many C++20 features are not implemented in the standard library used by clang. Therefore, we use docker image gcc which supports most the feature.
### To compile using gcc
```
$ docker pull gcc # This will download gcc from docker hub
$ docker run --rm -it -v "$(pwd)":/usr/src gcc 
$ g++ -std=c++20 main.cpp -o gcc_executable/main
```
#### Note
+ $(pwd) is the current working directory where the docker run is executed. It is wise to navigate to the source code folder before running the code.
+ main.cpp can be replaced by any main file 