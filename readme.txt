This is a image processing software which has the followig programs:
1) Perfrom Oil Painting effect on Star_Wars image :Star_Wars.raw
and get color quantised output(64 colors) :Star_Wars_quantised.raw
and oil painting effect output: Star_Wars_oil_effect.raw
2) Perfrom film effect on Girl image: Girl.raw
which replicates the effect on Film.raw (before: Original.raw)
the output is: Girl_film_effect.raw
3) Denoising performed on Lena_mixed.raw image by two methods
Median and Guassian filters. Output is stored in: Lena_denoised.raw
4) Dithering on a color image (flower.raw)
output stored in flower_color_dither.raw
5) Dithering on a grayscale image 
input: colorchecker.raw
output: colorchecker_thresh.raw
6) Error diffusion performed using 3 methods on 
input: colorchecker.raw
output: colorchecker_error_diffusion.raw
7) Panoramic Stitching of three input images to get a obtain one stiched panoramic image.
input: left.raw
		middle.raw
		right.raw
output: stitching.raw
8) Identify identical pieces in an image
input: board.raw
output: board_rectangle.raw
9) Applying sobel edge detection
input: Boat.raw
output: boat_ext.raw
10) Square image to circle geometric transform and reversed
input: panda.raw
output: panda_circle.raw
		panda_square.raw
11) Texture classification
input: comb.raw
output: Extended_composite.raw

No external libraries like OpenCV or Matlab are used to implement these operations.

OS:
MacOS Sierra

C++ Compiler:
g++ 4.2.1

Apple LLVM version 9.0.0

Installation:
Unzip source code zip file
make clean && make

Testing:
cd bin/

1. For oil painting:
	Usage: ./oil_painting 

2. For film effect:
	Usage: ./film

3. For denoising:
	Usage: ./denoising 

4. For color dithering:
	Usage: ./color_dithering 

5. For gray dithering:
	Usage: ./gray_dithering

6. For error diffusion:
	Usage: ./error_diffusion 

7. Panoramic stitching
	Usage: ./Panoramic_stitching

8) Identify unique pieces 
	Usage: ./puzzle

9) Sobel Edge detection:
	Usage: ./sobel

10) Geometric mapping:
	Usage: ./square_to_circle

11) Texture Classification:
	Usage: ./texture



information of the input images:

1. Oil Painting
	Star_Wars.raw		600x338		24 bit RGB

2. Film Effect
	Original.raw		1000x750	24 bit RGB
	Film.raw			1000x750	24 bit RGB
	Girl.raw			256x256		24 bit RGB

3. Denoising
	Lena_mixed.raw		512x512		24 bit RGB

4. Color Dithering
	flower.raw			700x700		24 bit RGB

5. Gray Dithering and 6. error diffusion
	colorchecker.raw	512x512		8 bit gray	

Images can be opened using ImageJ software

Screenshots of the input and output images have been provided



