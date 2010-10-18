#! /bin/bash

set -e
set -u

MAKE_FLAGS=${MAKE_FLAGS=""}

# directory where third party libraries will be installed
PREFIX=${PREFIX="$(pwd)/prefix-thirdparty"}

# working directory 
WRKDIR=${WRKDIR="$(pwd)"}

# compile and install tcl
cd tcl/unix
./configure --prefix="$PREFIX" CC=${CC:=gcc} CXX=${CXX:=g++}
make install ${MAKE_FLAGS}
cd "${WRKDIR}"

# install tcllib
cd tcllib
"${PREFIX}"/bin/tclsh8.5 installer.tcl -no-gui -no-wait
cd "${WRKDIR}"

# compile and install blitz
cd blitz
./configure --prefix="$PREFIX" --disable-doxygen CXX=${CXX:=g++}
make install ${MAKE_FLAGS}
cd "${WRKDIR}"

# compile and install glog
cd glog
./configure --prefix="$PREFIX" CXX=${CXX:=g++}
make install ${MAKE_FLAGS}
cd "${WRKDIR}"

./configure --with-blitz="${PREFIX}" --with-tcl="${PREFIX}"/lib/ CXX=${CXX:=g++} 
make ${MAKE_FLAGS}
