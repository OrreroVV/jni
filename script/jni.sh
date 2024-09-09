#!/bin/bash
# 设置项目的路径
PROJECT_DIR=$(pwd)/..
JAVA_SRC=Demo  # 替换为你的 Java 文件名
CLASS_DIR=$PROJECT_DIR/lib/java

# 检查是否传入了 -h 参数
if [[ "$1" == "-h" ]]; then
    echo "执行 -h 模式：只编译 Java 文件并生成头文件，不生成.so文件和运行Java程序"
    javac -d $CLASS_DIR -h $PROJECT_DIR/code/ $PROJECT_DIR/code/java/$JAVA_SRC.java

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