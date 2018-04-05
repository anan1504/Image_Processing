//////////////////////////////////////
///////ANANYA SINGH///////////////////
//////////////////////////////////////
//////////////////////////////////////
///////ananyasingh1216@gmail.com//////
///////02/25/18///////////////////////
//////////////////////////////////////

/*
Program description: Perfroms 2 types of denoising to Lena_mixed image. 
Using the median filter followed by Gaussian filter
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include<time.h>
//#include "io.h"
#include "iostring.h"
#include "Operations.h"
#include<string.h>


//input: program_name  input_image.raw output_image [BytesPerPixel = 3] [R_Size = 256] [C_Size = 256]

using namespace std;



int main()

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel=3;
	int R_Size = 512;
	int C_Size = 512;
	string Input = "Lena_mixed.raw";
	string Output = "Lena_denoised.raw";
	/*
	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 3] [R_Size = 256] [C_Size = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4)
	{
		BytesPerPixel = 3; // default is RGB image
	} 
	else 
	{
		BytesPerPixel = atoi(argv[3]);
	}

		// Check if size is specified
	if (argc >= 5)
		R_Size = atoi(argv[4]);
	if(argc >=6)
		C_Size = atoi(argv[5]);
		*/
		
		
	
	
	//declaring the input image vector
	vector<vector<vector<unsigned char> > >Imagedata;
	//calling the function to input image into the vector from the given file name
	Imagedata= Image_Input(Input.c_str(), R_Size, C_Size, BytesPerPixel);

	////////////////////////////////////////////////////////////////////////////////////
	

	//Declare the output Image data for 3D
	vector<unsigned char> Out_Imagedata_Per_Pixel(BytesPerPixel,0);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row(C_Size,Out_Imagedata_Per_Pixel);
	vector<vector<vector<unsigned char> > >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);
	///////////////////////////////////////////
	//Write the Image processing code here
	Out_Imagedata=Median_filter(Imagedata,R_Size,C_Size,BytesPerPixel);

	
	////////Gaussian filter

			
	vector<unsigned char> Out_Imagedata_Per_Pixel1(BytesPerPixel,0);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row1(C_Size,Out_Imagedata_Per_Pixel1);
	vector<vector<vector<unsigned char> > >Out_Imagedata1(R_Size,Out_Imagedata_Per_Row1);

	Out_Imagedata1=Guassian_filter(Out_Imagedata,R_Size,C_Size,BytesPerPixel);


	//Store the output image
	if(!Image_Out(Out_Imagedata1, Output.c_str(), R_Size, C_Size, BytesPerPixel))
		cout<<"Error!";

	return 0;
}
