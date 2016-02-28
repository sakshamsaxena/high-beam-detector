% 0.Clear workspace and Initialize Frame count
clear all;
F=0;

% 1.Input Video Object Handler Definition
inputVideo = vision.VideoFileReader('../vids/Trip_LowRes_2.mp4');
videoPlayer = vision.VideoPlayer;

% 2.Cropping Height and Width of frame. Subject to convenient
%	adjustments according to the position of camera. Mainly using to
%	crop out street lights from the top of the frame.
height = floor(inputVideo.info().VideoSize(2)*0.7);
width = inputVideo.info().VideoSize(1);
crop = vision.ImagePadder(...
							'SizeMethod','Output size', ...
							'NumOutputRowsSource','Property', ...
							'RowPaddingLocation','Top', ...
							'NumOutputRows', height, ...
							'NumOutputColumns', width);

% 3.Frame Conversion from True Colour to Grayscale
gray = vision.ColorSpaceConverter;
gray.Conversion = 'RGB to intensity';

% 4.Implementation on individual frames till the end of video.
while(~isDone(inputVideo))
	% Current Frame number
	F = F + 1;
	% Current Frame
	currentFrame = step(inputVideo);
	% Crop
	currentFrame = step(crop, currentFrame);
	% Convert to Grayscale
	currentFrame = step(gray, currentFrame);
	% Threshold
	currentFrame(currentFrame<0.7843) = 0;
	% Detect MSER Regions
	regions = detectMSERFeatures(currentFrame, ...
								'RegionAreaRange', [800 3000], ...
								'ThresholdDelta', 4);
	% Check for 'big bright blob(s)', or high incoming beam
	% and output detected blob count and corresponding frame
	if(regions.Count >= 2 && regions.Count <=6)
		disp([regions.Count, F]);
	end
	% Port frame to player
	step(videoPlayer,currentFrame);
end

% 5.Release both player and video file instances
release(inputVideo);
release(videoPlayer);