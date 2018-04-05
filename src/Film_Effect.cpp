//////////////////////////////////////
///////ANANYA SINGH///////////////////
//////////////////////////////////////
///////ananyasingh1216@gmail.com//////
//////////////////////////////////////
///////02/25/18///////////////////////
//////////////////////////////////////

/*
Program description: Replicates the film effect as shown in the original and film images on the Girl image by performing histogram specification.
First bilinear interpolation is performed on the reference image. 
Then we perform reflection and color inversion on the girl image followed by histogram specification on the two images
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

//input: program_name reference_image.raw input_image.raw output_image [BytesPerPixel = 3] [R_Size = 256] [C_Size = 256]

using namespace std;

int main()

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel=3;
	int R_Size = 750;
	int C_Size = 1000;
	int N_Size=256;
	//int N_C_Size=256;
	float SC= 2.929;
	float SR= 3.906;
	string Ref_Input = "Film.raw";
	string Input = "Girl.raw";
	string Output = "Girl_film_effect.raw";
	/*
	// Check for proper syntax
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 3] [R_Size = 256] [C_Size = 256]" << endl;
		return 0;
	}
	*/
	

		
	//call function(string filename, r_size,c_size,bytesperpixel) it returns vector	
	vector<vector<vector<unsigned char> > >Imagedata1;
	//get the reference image
	Imagedata1= Image_Input(Ref_Input.c_str(), R_Size, C_Size, BytesPerPixel);


	////////////////////////////////////////////////////////////////////////////////////

	//Declare the output Image data for 3D
	vector<unsigned char> Out_Imagedata_Per_Pixel1(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row1(N_Size,Out_Imagedata_Per_Pixel1);
	vector<vector<vector<unsigned char> > >Out_Imagedata1(N_Size,Out_Imagedata_Per_Row1);
	///////////////////////////////////////////
	
	//resizing the reference image
	Out_Imagedata1=Bilinear_Interpolation(Imagedata1,N_Size,BytesPerPixel);
	
	//Take the input of the 256x256 girl image:
	vector<vector<vector<unsigned char> > >Imagedata2;

	Imagedata2= Image_Input(Input.c_str(), N_Size, N_Size, BytesPerPixel);
	
	//////////image processing on Girl

	vector<unsigned char> Out_Imagedata_Per_Pixel2(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row2(N_Size,Out_Imagedata_Per_Pixel2);
	vector<vector<vector<unsigned char> > >Out_Imagedata2(N_Size,Out_Imagedata_Per_Row2);

	int i,j,k;

	for(k=0;k<3;k++)
	{
		for(i=0;i<N_Size;i++)
		{
			for(j=0;j<N_Size;j++)
			{
				Out_Imagedata2[i][j][k]=Imagedata2[i][N_Size-1-j][k];     //REFLECTION
			}
		}
	}

			

	for(k=0;k<3;k++)
	{
		for(i=0;i<N_Size;i++)
		{
			for(j=0;j<N_Size;j++)
			{
				if(k == 0)
					Out_Imagedata2[i][j][k]=abs(Out_Imagedata2[i][j][k]-255);   // CMY TRANSFORM
				else if(k==2)
					Out_Imagedata2[i][j][k]=abs(Out_Imagedata2[i][j][k]-255);   // CMY TRANSFORM
				else 
					Out_Imagedata2[i][j][k]=abs(Out_Imagedata2[i][j][k]-255);   // CMY TRANSFORM
			}
		}
	}
	
	//Histogram Specification
	vector<unsigned char> Out_Imagedata_Per_Pixel_Main(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row_Main(N_Size,Out_Imagedata_Per_Pixel_Main);
	vector<vector<vector<unsigned char> > >Out_Imagedata_Main(N_Size,Out_Imagedata_Per_Row_Main);

	Out_Imagedata_Main=Hist_Specification(Out_Imagedata1,Out_Imagedata2,N_Size,BytesPerPixel);

	//Store the output image
	if(!Image_Out(Out_Imagedata_Main, Output.c_str(), N_Size, N_Size, BytesPerPixel))
		cout<<"Error!";

	return 0;
}

