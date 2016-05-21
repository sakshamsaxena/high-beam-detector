# Open CV based demo code to detect oncoming high beams on road
Using [Open CV](http://opencv.org/) in C++ to process feed and [wiringPi](http://wiringpi.com/) in C to control GPIO of [Raspberry Pi](https://www.raspberrypi.org/). Cross-compiling using CMake and GCC.

# Build Instructions (master branch, Linux flavours)
1. ```git clone THIS_REPOSITORY```
2. ```cd THIS_REPOSITORY```
3. ```cmake . && make```
4. ```./attempt```

# Additional Notes
```master ``` contains standalone code, optimsed for production.

```visual-demo``` contains the video output as well for testing and analysing. Need to be booted into a GUI to run this.

```datadump ``` contains comparison between output of [MSER](https://en.wikipedia.org/wiki/Maximally_stable_extremal_regions) application on a pre-recorded video processed using Open CV and [MatLab](http://in.mathworks.com/help/vision/ref/detectmserfeatures.html) separately.
