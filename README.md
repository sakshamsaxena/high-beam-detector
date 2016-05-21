# What's this branch ?

It contains both OpenCV (```attempt.cpp```) and MATLAB (```master.m```) code which processes a prerecorded video (not included) and writes to a file the frames where high beam was detected. Because the oncoming beam will sustain its intensity over subsequent frames, this test would detect the first frame and shall contigously skip subsequent frames with high beam.

# Result ?

Open CV showed much more stable response than MATLAB, as it contigously detected the required frames, unlike MATLAB which failed to satisfy the criteria in between for some frames, making it unstable.
