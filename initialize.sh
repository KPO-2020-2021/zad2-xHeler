#!/bin/bash

if [[ ! -f build ]]
then
    mkdir build
fi

cd build 

cmake ..

make

clear
echo ""
echo "########## SUCCESS ##########"
echo ""

echo ""
echo "########## RUNING TESTS ##########"
echo ""

./test/complex_test