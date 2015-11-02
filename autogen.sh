#!/bin/bash

case `uname` in
    Darwin) libtoolize=glibtoolize ;;
    *)      libtoolize=libtoolize  ;;
esac

INSTALL_DIR=$(cd "$(dirname "$0")"; pwd)  #将安装目录设置为当前脚本执行目录

make distclean
set -x
$libtoolize --force --automake --copy
aclocal -I build/acmacros
automake --foreign --add-missing --copy
autoconf
CFLAGS=-m64 CXXFLAGS=-m64 LDFLAGS=-m64 ./configure --prefix=$INSTALL_DIR
make 
make install
