#!/bin/bash
g++ server.cpp -lcurl -pthread -std=c++11 -o server
./server &
