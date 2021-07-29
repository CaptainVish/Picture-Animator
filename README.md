# Animating Pictures
We enhance static pictures by introducing subtle motions to passive elements, responses to natural forces like the wind. We follow the approach of the paper ["Animating Pictures with Stochastic Motion Textures"](http://grail.cs.washington.edu/projects/StochasticMotionTextures/) by Chuang et al.

## Outcome
<p align="middle" float="left">
<img src="https://github.com/CSE-333-Computer-Graphics-2020/Animating-Pictures/blob/master/bridgeMonet.jpg" width="300" />
<img src="https://github.com/CSE-333-Computer-Graphics-2020/Animating-Pictures/blob/master/bridgeCG.gif" width="300" />
</p>  

## Dependencies
GLFW https://www.glfw.org/   \
OpenCV https://opencv.org/releases/  

## Build Instructions 
Run the follwoing commands on the linux terminal:
```sh
cd Animating-Pictures
make
./main -f background2.png -b boat2.png -t tree2.png -c cloud2.png -w water2.png 
```
Then click the **show** button on the GUI to see the image animated.

### To animate an image of your choice
```sh
cd Animating-Pictures 
make
./main -f <image/path>
```
Then follow the steps given below.

## Usage

### GUI
The GUI contains:
- Cloud, Boat, Tree and Water buttons - allows users to mark the area of the respective object in a pop up window. 
- Boat Point & Tree Point - allow the user to select a point on the object along which the transformations occur. 
- Wind Slider - allows user to control the wind speed which affects the objects in different ways.  
- Show button - to show the animated outcome after segmentation. 

### Steps
Click the respective *object* buttons to get a pop up window to select objects you want to segment. \
In the new window 
- **mark/draw over** the areas of the unsegmented object you clicked the button of.
- click the **r** key to reset the new window.
- click **esc** key to close the new window .
- click the **s** key to segment the object and inpaint the background. 

Click *show* to see the animated objects. 
