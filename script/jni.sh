#!/bin/bash
# 设置项目的路径
PROJECT_DIR=$(pwd)/..
JAVA_SRC=Demo
CLASS_DIR=$PROJECT_DIR/lib/java


javac -h $PROJECT_DIR/code -d $CLASS_DIR  $PROJECT_DIR/code/java/$JAVA_SRC.java

if [[ "$1" == "-h" ]]; then
    exit 0
fi

echo "编译c++程序，创建.so动态链接库"
cd $PROJECT_DIR/build
rm -rf *
cmake  ..
make -j8

LIB_DIR=$PROJECT_DIR/lib

cd $PROJECT_DIR/code/java

echo ""
echo ""

echo "执行java："
java  -cp $CLASS_DIR  -Djava.library.path=$LIB_DIR $JAVA_SRC
echo ""