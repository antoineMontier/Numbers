#! /bin/bash

function execution () {
    rm main
    make
    ./main
}

execution