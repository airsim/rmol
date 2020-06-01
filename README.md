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

As RMOL depends on other
[Travel Market Simulator (TvlSim/AirSim)](https://github.com/airsim/)
modules, more specifically [StdAir](https://github.com/airsim/stdair)
and [AirRAC](https://github.com/airsim/airrac), it may be
convenient to use the
[MetaSim project](https://github.com/airsim/metasim),
which pulls at once all the components of TvlSim in the same place,
and then orchestrates the dependencies for the builds, installations
and use of components.

If MetaSim is not used, in order to customise the following to your
environment, you can alter the path to the installation directory:
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
  open file://${INSTALL_BASEDIR}/rmol-${RMOL_VER}/share/doc/rmol/html/index.html
```
* To browse the (just installed, if enabled) PDF documentation:
```bash
  open ${INSTALL_BASEDIR}/rmol-${RMOL_VER}/share/doc/rmol/html/refman.pdf
```
* To run the local binary version:
```
  ./rmol/rmol -b
```
* To run the installed version:
```bash
  ${INSTALL_BASEDIR}/rmol-$RMOL_VER/bin/rmol -b
```

# Python extension

The way to interact with a C++-based Python extension is extensively described
in the [OpenTREP project](https://github.com/trep/opentrep).
Only a quick start is given here.

## Python dependencies

* Install Python dependencies:
```bash
$ python3 -m pip install -U pip
$ python3 -m pip install -U wheel
$ python3 -m pip install -U build setuptools scikit-build tox pytest sphinx twine
```

## Build the Python extension

* Build the Python extension with SciKit-Build:
```bash
$ rm -rf _skbuild/ dist/ MANIFEST_
$ python3 setup.py --build-type=Debug build sdist bdist_wheel
```

* The Python artifacts should be similar to:
```bash
$ ls -lFh dist/
total 5872
-rw-r--r-- 1 user staff 2.0M Jun  1 15:49 rmol-1.0.5.post1-cp38-cp38-macosx_10_15_x86_64.whl
-rw-r--r-- 1 user staff 834K Jun  1 15:49 rmol-1.0.5.post1.tar.gz
```

* Updload the RMOL Python extension onto PyPi:
```bash
$ twine upload -u __token__ --repository-url https://upload.pypi.org/legacy/ dist/*
```

* The RMOL Python artifacts may then be browsed on PyyPI:
  https://pypi.org/project/rmol/

## Use the Python extension
* Launch the Python interpreter:
```bash
$ export PYTHONPATH=${PWD}/_skbuild/macosx-10.15-x86_64-3.8/cmake-install/lib:${PWD}/_skbuild/macosx-10.15-x86_64-3.8/cmake-install/lib/python3.8/site-packages/pyrmol
$ DYLD_INSERT_LIBRARIES=/Library/Developer/CommandLineTools/usr/lib/clang/11.0.0/lib/darwin/libclang_rt.asan_osx_dynamic.dylib ASAN_OPTIONS=detect_container_overflow=0 /usr/local/Cellar/python@3.8/3.8.3/Frameworks/Python.framework/Versions/3.8/Resources/Python.app/Contents/MacOS/Python
```
* Within the Python interpreter, import, initialize
  and use the RMOL Python extension:
```python
Python 3.8.3 (default, May 27 2020, 20:54:22) 
[Clang 11.0.3 (clang-1103.0.32.59)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> import pyrmol
>>> rmolLibrary = pyrmol.RMOLer()
>>> rmolLibrary.init('rmol.log', 40, 1, '')
True
>>> rmolLibrary.rmol(100, 10, 40.0)
'RMOL has completed the generation of the booking requests. See the log file for more details.\n'
>>> quit()
```

* Back to the Shell session, look for the results in the RMOL log file:
```bash
$ cat rmol.log
Python wrapper initialisation
[D]${STDAIR_PREFIX}/stdair/command/CmdBomManager.cpp:52: StdAir is building the BOM tree from built-in specifications.
Python wrapper initialised
Optimisation for 100 draws, capacity of 40, and with the following method: 10
[D]${RMOL_PREFIX}/rmol/service/RMOL_Service.cpp:491: Optimisation by Monte-Carlo performed in 0.000321
[D]${RMOL_PREFIX}/rmol/service/RMOL_Service.cpp:492: Result: 
Yield: 100.00, Protection: 70.48, Booking limit: 100.00
Yield: 70.00, Protection: 156.19, Booking limit: 29.52
Yield: 42.00, Protection: -0.00, Booking limit: -56.19
[D]${RMOL_PREFIX}/rmol/service/RMOL_Service.cpp:505: Bid-Price Vector (BPV): 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 100.00, 99.00, 99.00, 99.00, 99.00, 99.00, 98.00, 98.00, 97.00, 96.00, 96.00, 96.00, 96.00, 96.00, 95.00, 94.00, 94.00, 90.00, 90.00, 89.00, 88.00, 86.00, 84.00, 82.00, 80.00, 80.00, 79.00, 77.00, 76.00, 75.00, 72.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00, 70.00
End of the optimisation.
RMOL output: 
```

* Of course, a few more features could be added to the Python extension API,
  in order not to have to leave the Python interpreter to interact with the
  results of invoking the optimizer. Do not hesitate to contribute
  through [Pull Requests](https://github.com/airsim/rmol/pulls), which are
  always welcome!


