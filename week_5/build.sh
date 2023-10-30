#!/usr/bin/env bash

ROOTDIR=`pwd`
CONFIGS="debug release"

PICO_BOARD=adafruit_feather_rp2040

for CONFIG in $CONFIGS; do
    BUILDFOLDER=$ROOTDIR/build/$CONFIG

    mkdir -p $BUILDFOLDER  

    cd $BUILDFOLDER

    cmake -DPICO_BOARD=$PICO_BOARD -DCMAKE_BUILD_TYPE=$CONFIG $ROOTDIR || exit 1

    make

done
