#!/bin/sh

#
# Author: Bohdan Turkynewych, 2007-06-12, Distributed under the terms of GPLv2.
# gh0st@voxs.cv.ua, tb0hdan@gmail.com
#

TESSADIR="tessa"
TESSAREVISION=62
TESSABINDINGS=$TESSADIR/tessa/bindings
DISTDIR="$TESSADIR/distfiles"
GLOOXDIR="$TESSADIR/gloox"
GLOOXURL="http://camaya.net/download"
GLOOXBINDINGSDIR="$TESSADIR/glooxbindings"
GLOOXFILE="gloox-0.9-rc1.tar.bz2"
GLOOXBINDINGSFILE="glooxbindings-0.1.2-tmp.tar.bz2"
PATH=$PATH:$HOME/local:$HOME/local/lib:$HOME/local/bin:$HOME/local/include:$HOME/local/share
curdir=`pwd`
#
tessa_init(){
mkdir -p $DISTDIR
#mkdir -p $GLOOXDIR
#mkdir -p $GLOOXBINDINGSDIR
}

get_tessa(){
if [ ! -d $TESSADIR ]; then
    mkdir $TESSADIR
    svn checkout -r $TESSAREVISION http://tessa.googlecode.com/svn/trunk/ $TESSADIR
else
    cd $TESSADIR
    svn checkout -r $TESSAREVISION http://tessa.googlecode.com/svn/trunk/ $TESSADIR
    svn update -r $TESSAREVISION
    cd $curdir
fi
}

get_gloox(){
if [ ! -f $DISTDIR/$GLOOXFILE ]; then
    wget -Nc -P$DISTDIR $GLOOXURL/$GLOOXFILE
fi
if [ ! -f $DISTDIR/$GLOOXBINDINGSFILE ]; then
    wget -Nc -P$DISTDIR $GLOOXURL/$GLOOXBINDINGSFILE
fi
tar -xjpf $DISTDIR/$GLOOXFILE -C $TESSADIR
mv $TESSADIR/`echo $GLOOXFILE|awk -F.tar.bz2 '{print $1}'` $GLOOXDIR
tar -xjpf $DISTDIR/$GLOOXBINDINGSFILE -C $TESSADIR
mv $TESSADIR/`echo $GLOOXBINDINGSFILE|awk -F.tar.bz2 '{print $1}'` $GLOOXBINDINGSDIR
}

fix_link(){
sudo ln -s /usr/lib/liblua.a /usr/lib/liblua5.1.a
}

compile_gloox() {
GDIR=`pwd`
cd $GLOOXDIR
./configure --prefix=$HOME/local
make
make install
make clean
cd $GDIR

}

compile_bindings() {
echo "GLOOX_SRC_DIR=$curdir/$GLOOXDIR" > $TESSABINDINGS/Build
echo "GLOOX_BINDINGS_DIR=$curdir/$GLOOXBINDINGSDIR" >> $TESSABINDINGS/Build
cat $TESSABINDINGS/buildluamodule|grep -v 'GLOOX_SRC_DIR='|grep -v 'GLOOX_BINDINGS_DIR='  >> $TESSABINDINGS/Build
CBD=`pwd`
cd $TESSABINDINGS
chmod 755 ./Build
./Build
cd $CBD
if [ -f $TESSABINDINGS/gloox.so ]; then
    cp $TESSABINDINGS/gloox.so $TESSADIR/tessa/src
else
    echo Gloox.so was not built. Exiting..
fi    
}
compile_tessa() {
echo Compiling Tessa...
cd $TESSADIR/tessa/src
g++ *.cpp -I/usr/include/lua5.1 `wx-config --cxxflags --libs`-llua5.1 -o tessa
mkdir -p $HOME/local/bin
echo -n Installing Tessa...
if [ -f tessa ]; then
    cp tessa $HOME/local/bin
    echo Ok.
else
    echo Err.
    echo Compilation failed.
    echo Aborting.
    exit 1
fi        
}
##########################################################
#
#
##########################################################
tessa_init
get_tessa
get_gloox
fix_link
compile_gloox
compile_bindings
compile_tessa