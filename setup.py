
import os, sys, setuptools
from skbuild import setup

with open("README.md", "r") as fh:
    long_description = fh.read()

setup (
    name='rmol',
    version='0.7.7-1',
    author='Denis Arnaud',
    author_email='denis.arnaud_pypi@m4x.org',
    description=('''Simple Python wrapper for RMOL'''),
    license='MIT',
    keywords='api python rmol revenue management package',
    url='https://github.com/airsim/rmol',
    packages=setuptools.find_packages(),
    long_description=long_description,
    long_description_content_type="text/markdown",
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    cmake_args = [
      '-DINSTALL_DOC:BOOL=OFF',
      '-DRUN_GCOV:BOOL=OFF',
      '-DLIB_SUFFIX='
      ] + (
      ['-DREADLINE_ROOT=/usr/local/opt/portable-readline',
       '-DREADLINE_INCLUDE_DIR=/usr/local/opt/portable-readline/include',
       '-DREADLINE_LIBRARY=/usr/local/opt/libedit/lib/libedit.dylib',
       '-DICU_ROOT=/usr/local/opt/icu4c'] if sys.platform.startswith("darwin") else []
      )
)

