//////////////////////////////////////
///////ANANYA SINGH///////////////////
//////////////////////////////////////
//////////////////////////////////////
///////ananyasingh1216@gmail.com
//////////////////////////////////////
///////02/25/18///////////////////////
//////////////////////////////////////

/*
Program description: Performs thresholding of a grayscale image using 3 methods:  
1) Hard Thresholding
2) Random Thresholding
3)Dithering
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include<time.h>
#include<string.h>
#include "io.h"

using namespace std;

int Thresh_gray(unsigned char input_pixel, float threshold);
//int Display_four_gray(unsigned char input_pixel, float threshold);

int main()

{
	// Define file pointer and variables
	int BytesPerPixel=1;
	int R_Size = 512;
	int C_Size = 512;
	string Input = "colorchecker.raw";
	string Output1 = "colorchecker_gray_dither.raw";
	string Output2 = "colorchecker_gray_4.raw";
	/*
	// Check for proper syntax
	if (argc < 4) //user has to input the names of 2 output files
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw display_ouput_image.raw [BytesPerPixel = 3] [R_Size = 256] [C_Size = 256]" << endl;
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
		R_Size = atoi(argv[5]);
	if(argc >=6)
		C_Size = atoi(argv[6]);
		*/
		
	//declaring the input image vector
	vector<vector<vector<unsigned char> > >Imagedata;
	//calling the function to input image into the vector from the given file name
	Imagedata= Image_Input(Input.c_str(), R_Size, C_Size, BytesPerPixel);

	
	

	////////////////////////////////image processing code here////////////////////////////////////////////////////

	//Declare the output Image data for 3D
	vector<unsigned char> Out_Imagedata_Per_Pixel(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row(C_Size,Out_Imagedata_Per_Pixel);
	vector<vector<vector<unsigned char> > >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);
	///////////////////////////////////////////creating output vector for displaying the gray level values
	vector<unsigned char> Out_Imagedata_Per_Pixel1(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row1(C_Size,Out_Imagedata_Per_Pixel1);
	vector<vector<vector<unsigned char> > >Out_Imagedata1(R_Size,Out_Imagedata_Per_Row1);
	//Write the Image processing code here

	int i,j;
	int thresh_choose;
	cout<<"Enter 1 for Fixed Thresholding. 2 for Random Thresholding and 3 for Dithering Matrix "; cin>>thresh_choose;
	cout<<endl<<"Creating a display ready image for the screen with 4 gray levels: (0,85,170,255): ";
	float threshold;
	int N2=2, N4=4, N8=8;
	int I2[2][2]={{1,2},{3,0}}; //2x2 bayes matrix
	int I4[4][4]={{5,9,6,10},{13,1,14,2},{7,11,4,8},{15,3,12,0}}; //4x4 bayes matrix
	int I8[8][8]={{21,37,25,41,22,38,26,42}, //8x8 bayes matrix
					{53,5,57,9,54,6,58,10},
					{28,45,17,33,30,46,18,34},
					{61,13,49,1,62,14,50,2},
					{23,39,27,43,20,36,24,40},
					{55,7,59,11,52,4,56,8},
					{31,47,19,35,28,44,16,32},
					{65,15,51,3,60,12,48}};
	int N;

	if(thresh_choose==1)
	{
		threshold=127; //Fixed thresholding
		for(i=0;i<R_Size;i++)
		{
			for(j=0;j<C_Size;j++)
			{
				
				Out_Imagedata[i][j][0]=Thresh_gray(Imagedata[i][j][0],threshold); //Providing the decided threshold
				//Out_Imagedata1[i][j][0]=Display_four_gray(Imagedata[i][j][0], threshold); //displaying 4 level gray levels
			}
		}
		cout<<" The threshold is: "<<threshold<<endl;
	}
	else if(thresh_choose==2)
	{
		srand(time(NULL));
		threshold= rand() %256; //Random thresholding
		for(i=0;i<R_Size;i++)
		{
			for(j=0;j<C_Size;j++)
			{
				Out_Imagedata[i][j][0]=Thresh_gray(Imagedata[i][j][0],threshold); //Providing the decided threshold
				//Out_Imagedata1[i][j][0]=Display_four_gray(Imagedata[i][j][0], threshold); //displaying 4 level gray levels
			}
		}
		cout<<" The threshold is: "<<threshold<<endl;
	
	}
	else if(thresh_choose==3)
	{
		cout<<endl<<"Enter the n value (2,4 or 8) for Bayer's matrix: ";
		cin>>N;
		if(N!=2 && N!=4 && N!=8)
		{
			cout<<endl<<"Error! Please enter value of n again: ";
			cin>>N;
		}
		for(i=0;i<R_Size;i++)
		{
			for(j=0;j<C_Size;j++)
			{
				if(N==2)
					threshold=((I2[i%N2][j%N2]+0.5)/(N2*N2))*255; //threshold decided if 2x2 bayes matrix
				else if(N==4)
					threshold=((I4[i%N4][j%N4]+0.5)/(N4*N4))*255; ////threshold decided if 4x4 bayes matrix
				else if(N==8)
					threshold=((I8[i%N8][j%N8]+0.5)/(N8*N8))*255; ////threshold decided if 8x8 bayes matrix
				Out_Imagedata[i][j][0]=Thresh_gray(Imagedata[i][j][0],threshold); //Providing the decided threshold
				//Out_Imagedata1[i][j][0]=Display_four_gray(Imagedata[i][j][0], threshold); //displaying 4 level gray levels
			}
		}
	}

	float dump[256]={0};//dump intensity values

	int z;
	for(j=0;j<256;j++)
			dump[j]=0;
		
	
	for(i=0;i<R_Size;i++)
		for(j=0;j<C_Size;j++)
		{
			z=Imagedata[i][j][0];
			dump[z]++;
		}

	//normalise the histogram values
	for(i=0;i<256;i++)
	{
		dump[i]= dump[i]/(R_Size*C_Size);
	}
	float c_dump[256]={0.0};

	c_dump[0]=dump[0];
	for(i=1;i<256;i++)
	{
		c_dump[i]= dump[i]+c_dump[i-1];
	}
	int t1,t2,t3;
	for(i=0;i<256;i++)
	{
		if(c_dump[i]<= 0.25)
			t1=i;
		if(c_dump[i]<=0.5)
			t2=i;
		if(c_dump[i]<=0.75)
			t3=i;
		//cout<<c_dump[i]<<endl;
	}
	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			if(Imagedata[i][j][0]<t1)
				Out_Imagedata1[i][j][0]= 0;
			else if(t1< Imagedata[i][j][0] && Imagedata[i][j][0]<= t2)
				Out_Imagedata1[i][j][0]= 85;
			else if(t2< Imagedata[i][j][0] && Imagedata[i][j][0]<= t3)
				Out_Imagedata1[i][j][0]= 170;
			else 
				Out_Imagedata1[i][j][0]= 255;
		}
	}
	cout<<t1<<t2<<t3;

	

	

	




	//Writing image into a file given by the user input
	if(!Image_Out(Out_Imagedata, Output1.c_str(), R_Size, C_Size, BytesPerPixel))
		cout<<"Error!";
	//Writing output of 4 gray levels 
	if(!Image_Out(Out_Imagedata1, Output2.c_str(), R_Size, C_Size, BytesPerPixel))
		cout<<"Error!";
	

	return 0;
}

//returns pixel value function(input pixel value,threshold)
int Thresh_gray(unsigned char input_pixel, float threshold)
{
	if(input_pixel<threshold) 
		return 0; //If pixel value is less than threshold, assign ouptput value to black, else white
	else 
		return 255;
}




