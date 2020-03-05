#!/bin/sh

#set -x

SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-./.build}
BUILD_TYPE=${BUILD_TYPE:-debug}
#INSTALL_DIR=${INSTALL_DIR:-../${BUILD_TYPE}}

CXX=${CXX:-g++}

if [ ! -d $BUILD_DIR/$BUILD_TYPE ]; then
	mkdir -p $BUILD_DIR/$BUILD_TYPE
fi

cd $BUILD_DIR/$BUILD_TYPE \
	   && cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
	   $SOURCE_DIR \
	   && make $*


#-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
