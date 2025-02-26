#!/bin/bash
g++ -I/usr/include/opencv4 1_1.cpp -o ./bin/1_1 `pkg-config --cflags --libs opencv4`
./bin/1_1 ./img/test.png  
./bin/1_1 ./img/test.jpeg
g++ -I/usr/include/opencv4 1_2.cpp -o ./bin/1_2 `pkg-config --cflags --libs opencv4`
./bin/1_2 ./img/a.png ./img/test.jpeg