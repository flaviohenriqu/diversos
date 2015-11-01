# OpenCV - Installation in Linux

These steps have been tested for Ubuntu 14.10 but should work with other distros as well.

## Install Dependencies

Cmake
Library to compilation of OpenCV:
``` bash
sudo apt-get install build-essential checkinstall cmake pkg-config yasm
```

Image I/O (Optional)
Library that provides support for image types that are not supported by OpenCV. Case is not installed, then the image types supported only by OpenCV will be considered:
``` bash
sudo apt-get install libtiff4-dev libjpeg-dev libjasper-dev
```

Video I/O (Optional)
Library for video capture / encoding / decoding for additional HighGUI module:
``` bash
sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libdc1394-22-dev libxine-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev
```

Python (Optional)
Packages needed to build Python programs with OpenCV:
``` bash
sudo apt-get install python-dev python-numpy
```

## Install and Compile OpenCV
To get a copy of the source code [here](http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/3.0.0/opencv-3.0.0.zip/download), extract and create a build directory. 

```bash
unzip -o opencv-3.0.0.zip
cd opencv/
mkdir release
cd release
mkdir build
cd build
```

Configure using CMake. You can use several options at this stage. I used the following:
```bash
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/home/user/opencv/release/build -D WITH_TBB=ON -D BUILD_EXAMPLES=ON ..
```


To start the compilation:
``` bash
make
```

If compiling ends without error, you can install, doing:
``` bash
sudo make install
```

Finally, make sure that your program can link to the OpenCV library at run time by adding the following line at the end of /etc/ld.so.conf:
``` bash
/usr/local/lib
```

And finally configure dynamic linker at run time:
``` bash
sudo ldconfig
```

## Test
An easy way to test if the build was successful, is to use the OpenCV test utilities. For example, to test the core module, just go to the path opencv/build/bin and run:
``` bash
./opencv_test_core
```

You should see something like this:
![OpenCV test core]
(http://4.bp.blogspot.com/-F51xkreNrmU/T7VDYUpa8fI/AAAAAAAABdk/fzMCRgtq764/s1600/opencv_test_core.png "OpenCV Test Core")