#!/bin/bash
# 获取当前脚本所在目录
current_dir=$(cd $(dirname $0); pwd)
#echo $current_dir
target=./code/bin/chess

include=-I/home/lisai/tool/zlib/include
include+=" -I/home/lisai/tool/png/include"
include+=" -I./code/src/"
include+=" -I./code/src/image"
include+=" -I./code/src/screen"
include+=" -I./code/src/event"
include+=" -I./code/src/log"

lib_path=-L/home/lisai/tool/zlib/lib
lib_path+=" -L/home/lisai/tool/png/lib"
lib_path+=" -L/home/lisai/jpeg/lib"

lib=-lpng
lib+=" -lz"
lib+=" -ljpeg"
lib+=" -lpthread"

src=./code/src/main.cpp
src+=" ./code/src/image/handleIf.cpp"
src+=" ./code/src/image/BMPHandle.cpp"
src+=" ./code/src/image/JPEGHandle.cpp"
src+=" ./code/src/image/PNGHandle.cpp"
src+=" ./code/src/image/imageHandle.cpp"
src+=" ./code/src/image/image.cpp"
src+=" ./code/src/screen/screenmgr.cpp"
src+=" ./code/src/event/event.cpp"
src+=" ./code/src/event/eventManager.cpp"
src+=" ./code/src/event/touchEvent.cpp"
src+=" ./code/src/log/log.cpp"

arg=-D__PRINTFILE__ 

if test -f $target; then
    rm $target
fi

#for file in *
#do
#    echo "$file"
#done

#g++ ./code/src/main.cpp -o $target
/home/lisai/arm-2014.05/bin/arm-none-linux-gnueabi-g++ -std=c++11 $src $include $lib_path $lib $arg -o $target

#export LDFLAGS="${LDFLAGS} -L/home/lisai/tool/zlib/lib"
#export CFLAGS="${CFLAGS} -I/home/lisai/tool/zlib/include"
#export CPPFLAGS="${CPPFLAGS} -I/home/lisai/tool/zlib/include"


#./configure --prefix=/home/lisai/tool/png --host=arm-none-linux-gnueabi
#./configure --prefix=/home/lisai/tool/zlib/ --host=arm-none-linux-gnueabi


