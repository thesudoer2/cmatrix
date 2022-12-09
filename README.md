# cmatrix
a simple cmatrix program using C++ and ncurses library

to use this program:
    1. install ncurses:
    
        - on Ubuntu:
            #apt-get install -y libncurses5-dev libncursesw5-dev

        - on RockyLinux and CentOS:
            #dnf install -y ncurses-devel


to compile source code files (manually):

      #gcc main.cpp tic_tac_toe.cpp -lstdc++ -lncurses -std=c++11 -O2 -o <output_name>


to compile souce code files by make file, stay on src/ directory and:

      #make
      
NOTE: of course, before using "make" program to compile the project, you must
      install the "make" package:
      
      - on Ubuntu:
         #apt-get install -y make

      - on RockyLinux and CentOS:
         #dnf install -y make
      


a sample of functionality of this program:


https://user-images.githubusercontent.com/112639283/202496321-20e3e490-2201-4284-addd-630329a97b31.mp4
