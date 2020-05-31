C++ library of Revenue Management and Optimisation Library
==========================================================

# Summary
RMOL is a C++ library of Revenue Management and Optimisation classes 
and functions. Typically, that library may be used by service providers
(_e.g._, airlines offering flight seats, hotels offering rooms, rental car
companies offering rental days, broadcasting company offering advertisement 
slots, theaters offering seats, _etc_) to help in optimising their revenues 
from seat capacities.
Most of the algorithms implemented are public and documented in the 
following book:
The Theory and practice of Revenue Management, by Kalyan T. Talluri and
Garrett J. van Ryzin, Kluwer Academic Publishers, 2004, ISBN 1-4020-7701-7

RMOL makes an extensive use of existing open-source libraries for
increased functionality, speed and accuracy. In particular the
Boost (C++ Standard Extensions: http://www.boost.org) library is used.

RMOL is the one of the components of the Travel Market Simulator
(https://travel-sim.org). However, it may be used in a
stand-alone mode.

# Installation

## On Fedora/CentOS/RedHat distribution
Just use DNF:
```bash
$ dnf -y install rmol-devel rmol-doc
```

You can also get the RPM packages (which may work on Linux
distributions like Suse and Mandriva) from the Fedora repository
(_e.g._, for Fedora 32, 
https://fr2.rpmfind.net/linux/RPM/fedora/32/x86_64/)


## Building the library and test binary from Git repository
The Git repository may be cloned as following:
```bash
$ git clone git@github.com:airsim/rmol.git rmolgit # through SSH
$ git clone https://github.com/airsim/rmol.git # if the firewall filters SSH
$ cd rmolgit
```

Then, you need the following packages (Fedora/RedHat/CentOS names here, 
but names may vary according to distributions):
* `cmake`
* `gcc-c++`
* `boost-devel` / `libboost-dev`
* `python-devel` / `python-dev`
* `gettext-devel` / `gettext`
* `sqlite3-devel` / `libsqlite3-dev`
* `readline-devel` / `libreadline-dev`
* `libncurses5-devel`
* `soci-mysql-devel`, `soci-sqlite3-devel`
* `stdair-devel` / `libstdair-dev`
* `airrac-devel` / `libairrac-dev`
* `doxygen`, `ghostscript`, `graphviz`
* `tetex-latex` (optional)
* `rpm-build` (optional)


## Building the library and test binary from the tarball
The latest stable source tarball (`rmol*.tar.gz` or `.bz2`) can be
found on GitHub: http://github.com/airsim/rmol/releases, _e.g._,
https://github.com/airsim/rmol/archive/rmol-1.00.6.tar.gz

To customise the following to your environment, you can alter the path
to the installation directory:
```bash
export INSTALL_BASEDIR="${HOME}/dev/deliveries"
export RMOL_VER="1.00.6"
if [ -d /usr/lib64 ]; then LIBSUFFIX="64"; fi
export LIBSUFFIX_4_CMAKE="-DLIB_SUFFIX=$LIBSUFFIX"
```

Then, as usual:
* To configure the project, type something like:
```bash
  mkdir build && cd build
  cmake -DCMAKE_INSTALL_PREFIX=${INSTALL_BASEDIR}/rmol-$RMOL_VER \
   -DWITH_STDAIR_PREFIX=${INSTALL_BASEDIR}/stdair-stable \
   -DWITH_AIRRAC_PREFIX=${INSTALL_BASEDIR}/airrac-stable \
   -DCMAKE_BUILD_TYPE:STRING=Debug -DENABLE_TEST:BOOL=ON -DINSTALL_DOC:BOOL=ON \
   -DRUN_GCOV:BOOL=OFF ${LIBSUFFIX_4_CMAKE} ..
   ${LIBSUFFIX_4_CMAKE} ..
```
* To build the project, type:
```bash
  make
```
* To test the project, type:
```bash
  make check
```
* To install the library (`librmol*.so*`) and the binary (`rmol`),
```bash
  make install
  cd ${INSTALL_BASEDIR}
  rm -f rmol-stable && ln -s rmol-${RMOL_VER} rmol-stable
  cd -
```
* To package the source files, type:
```bash
  make dist
```
* To package the binary and the (HTML and PDF) documentation:
```bash
  make package
```
* To browse the (just installed, if enabled) HTML documentation:
```bash
  midori file://${INSTALL_BASEDIR}/rmol-${RMOL_VER}/share/doc/rmol/html/index.html
```
* To browse the (just installed, if enabled) PDF documentation:
```bash
  evince ${INSTALL_BASEDIR}/rmol-${RMOL_VER}/share/doc/rmol/html/refman.pdf
```
* To run the local binary version:
```
  ./rmol/rmol -b
```
* To run the installed version:
```bash
  ${INSTALL_BASEDIR}/rmol-$RMOL_VER/bin/rmol -b
```

Denis Arnaud (June 2015)

