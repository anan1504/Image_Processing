//////////////////////////////////////
///////ANANYA SINGH///////////////////
//////////////////////////////////////
//////////////////////////////////////
///////ananyasingh1216@gmail.com
//////////////////////////////////////
///////02/25/18///////////////////////
//////////////////////////////////////

/*
Program description: Performs an oil painting effect on the star wars image
first we perfrom color quantisation to get an image with 64 colors
next the oil painitng effect is created by finding the most frequent color in the NxN window
we get 2 outputs. the color quantised image and the oil painting effect image 
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include<time.h>
#include "io.h"
#include "Operations.h"
#include<string.h>


//input: program_name input_image.raw color_quantisation_output.raw oileffect.raw [BytesPerPixel = 3] [R_Size = 256] [C_Size = 256]

using namespace std;
vector<vector<vector<unsigned char> > >Color_Quantisation(vector<vector<vector<unsigned char> > >Imagedata,int R_Size, int C_Size, int BytesPerPixel);
vector<vector<vector<unsigned char> > >OilPaintingEffect(vector<vector<vector<unsigned char> > >Imagedata,int R_Size, int C_Size, int BytesPerPixel,int n);

int main()

{
	// Define file pointer and variables
	int BytesPerPixel=3;
	int R_Size=338;
	int C_Size=600;
	string Input = "Star_Wars.raw";
	string Output1 = "Star_Wars_quantised.raw";
	string Output2 = "Star_Wars_oil_effect.raw";
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
		BytesPerPixel = atoi(argv[4]);
	}

		// Check if size is specified
	if (argc >= 5)
		C_Size = atoi(argv[5]);
	if(argc >=6)
		R_Size = atoi(argv[6]);
		*/
		
	//call function(string filename, r_size,c_size,bytesperpixel) it returns vector	
	vector<vector<vector<unsigned char> > >Imagedata;

	Imagedata= Image_Input(Input.c_str(), R_Size, C_Size, BytesPerPixel);


	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	//Reading image from buffer into the input vector
	int i,j,k;


	////////////////////////////////////////////////////////////////////////////////////

	//Declare the output Image data for 3D

	vector<unsigned char> Out_Imagedata_Per_Pixel(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row(C_Size,Out_Imagedata_Per_Pixel);
	vector<vector<vector<unsigned char> > >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);
	///////////////////////////////////////////
	//Write the Image processing code here

	//Function to perform color quantisation
	Out_Imagedata=Color_Quantisation(Imagedata,R_Size,C_Size,BytesPerPixel);
	//reduced color set= 31,95,159,223

	int N;

	cout << "Enter N which is the kernel size for the oil painting, N must be odd and ranging between 3 and 11: ";
	cin >> N;
	if(N%2==0)
	{
		cout<<"N must be odd! Please enter the value again!";
		cin>>N;
	}
	if(N<3 && N>11)
	{
		cout<<"Enter N which lies in the range of 3 and 11";
		cin>>N;
	}

	int n=(N-1)/2;
	
	vector<unsigned char> Out_Imagedata_Per_Pixel1(BytesPerPixel, 0);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row1(C_Size,Out_Imagedata_Per_Pixel1);
	vector<vector<vector<unsigned char> > >Out_Imagedata1(R_Size,Out_Imagedata_Per_Row1);

	Out_Imagedata1= OilPaintingEffect(Out_Imagedata,R_Size,C_Size,BytesPerPixel,n);

	


		
	// Write the output buffer to the output file
	if(!Image_Out(Out_Imagedata, Output1.c_str(), R_Size, C_Size, BytesPerPixel))
		cout<<"Error!";
	

	if(!Image_Out(Out_Imagedata1, Output2.c_str(), R_Size, C_Size, BytesPerPixel))
		cout<<"Error!";
	

	return 0;
}
