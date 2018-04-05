//////////////////////////////////////
///////ANANYA SINGH///////////////////
///////ananyasingh1216@gmail.com//////
//////////////////////////////////////
///////04/5/18///////////////////////
//////////////////////////////////////
//perform sobel edge detection

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include "iostring.h"
#include<math.h>
#define PI 3.14159265
#include<string.h>
vector<vector<unsigned char> > Boundary_Extension(vector<vector<unsigned char> > Imagedata,int R_Size,int C_Size, int Extend);
vector<vector<unsigned char> > Sobel_Operator(vector<vector<unsigned char> > Imagedata,int R_Size,int C_Size, float dX[3][3], float dY[3][3]);

using namespace std;
int main( )

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel=3;
	int R_Size = 321;
	int C_Size = 481;
	string input1= "Boat.raw";
	string output1="boat_ext.raw";
	cout<<"gg";
	vector<vector<vector<unsigned char> > >Imagedata;

	Imagedata= Image_Input(input1.c_str(), R_Size, C_Size, BytesPerPixel);
	//Declare the output Image data for 3D
	vector<unsigned char> Out_Imagedata_Per_Pixel(C_Size,0);
	vector<vector<unsigned char> >Out_Imagedata(R_Size,Out_Imagedata_Per_Pixel);

	int i,j,k;
	//convert from rgb to grayscale
	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			Out_Imagedata[i][j]=(0.21*Imagedata[i][j][0]+0.72*Imagedata[i][j][1]+0.07*Imagedata[i][j][2]);
		}
	}
	cout<<"rgb to grayscale done";
	//boundary extension
	int Extend = 1;
	int R_Extend = R_Size + 2;
	int C_Extend = C_Size + 2;

	vector<unsigned char> Out_Imagedata_Per_Pixel_Extend(C_Extend , 0);
	vector<vector<unsigned char> >Out_Imagedata_Extend(R_Extend , Out_Imagedata_Per_Pixel_Extend);
	Out_Imagedata_Extend = Boundary_Extension(Out_Imagedata, R_Size, C_Size, Extend);
	float dX[3][3]={{-1.0/4.0,0,1.0/4.0},
				{-2.0/4.0,0,2.0/4.0},
				{-1.0/4.0,0,1.0/4.0}};
	float dY[3][3]={{1.0/4.0,2.0/4.0,1.0/4.0},
				{0,0,0},
				{-1.0/4.0,-2.0/4.0,-1.0/4.0}};


	vector<unsigned char> Out_Imagedata_Per_Pixel_mag(C_Size , 0);
	vector<vector<unsigned char> >Out_Imagedata_mag(R_Size , Out_Imagedata_Per_Pixel_mag);


	Out_Imagedata_mag = Sobel_Operator(Out_Imagedata_Extend, R_Size, C_Size , dX , dY); //calculate magnitude

	vector<unsigned char> Out_Imagedata_Per_Pixel_inv(C_Size , 0);
	vector<vector<unsigned char> >Out_Imagedata_inv(R_Size , Out_Imagedata_Per_Pixel_inv);

	int pixel_intensity = 255;
	for( i = 0; i < R_Size ; i++)
	{
		for( j = 0; j < C_Size ; j++)
		{
			Out_Imagedata_inv[i][j] = 255 - Out_Imagedata_mag[i][j];
			if (Out_Imagedata_inv[i][j] < pixel_intensity )
			{
				pixel_intensity = Out_Imagedata_inv[i][j];
			}
			
		}
	}

	vector<unsigned char> Out_Imagedata_Per_Pixel_final(C_Size , 0);
	vector<vector<unsigned char> >Out_Imagedata_final(R_Size , Out_Imagedata_Per_Pixel_final);

	for( i = 0; i < R_Size ; i++)
	{
		for( j = 0; j < C_Size ; j++)
		{
			if (Out_Imagedata_inv[i][j] > pixel_intensity + (255-pixel_intensity)*0.95 )
			{
				Out_Imagedata_final[i][j] = 255;
			}
			else 
				Out_Imagedata_final[i][j] = 0;
			
		}
	}

	


	unsigned char *Out_Imagebuffer = (unsigned char*) calloc (R_Size*C_Size*sizeof(unsigned char), sizeof(unsigned char));

	//write contents of the vector into the file
	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			*(Out_Imagebuffer + (i*C_Size + j)) = Out_Imagedata_final[i][j];
		}
	}

	if (!(file=fopen( output1.c_str(),"wb"))) {
		cout << "Cannot open file: " << output1.c_str() << endl;
		return 0;
	}
	fwrite(Out_Imagebuffer, sizeof(unsigned char), R_Size*C_Size, file);
	fclose(file);

	
	

	return 0;
}

vector<vector<unsigned char> > Sobel_Operator(vector<vector<unsigned char> > Imagedata,int R_Size,int C_Size, float dX[3][3], float dY[3][3])
{
	int i,j,u,v,x,y;
	float pixel_sum_X, pixel_sum_Y;
	vector<unsigned char> Out_Imagedata_Per_Row(C_Size,0);
	vector<vector<unsigned char> >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);
	for(i = 1; i < R_Size + 1 ; i++)
	{
		for( j = 1; j < C_Size + 1 ; j++)
		{
			pixel_sum_X = 0;
			pixel_sum_Y = 0;
			for(x = i-1 , u = 0; x <= i+1 ; x++, u++)
			{
				for(y = j-1 , v = 0;y <= j+1 ; y++, v++)
				{
					pixel_sum_X += (dX[u][v] * (int)(Imagedata[x][y]));
					pixel_sum_Y += (dY[u][v] * (int)(Imagedata[x][y]));
					Out_Imagedata[i-1][j-1] = pow( pow(pixel_sum_X , 2) + pow(pixel_sum_Y , 2), 0.5 );

				}
			}
			//Out_Imagedata[i - 1][j - 1] = pixel_sum;
		}
	}
	return Out_Imagedata;
}


vector<vector<unsigned char> > Boundary_Extension(vector<vector<unsigned char> > Imagedata,int R_Size,int C_Size, int Extend)
{
	int i,j;
	//int Extend=1;
	int R_Extend = R_Size + 2*Extend;
	int C_Extend = C_Size + 2*Extend;
	vector<unsigned char> Out_Imagedata_Per_Row(C_Extend,0);
	vector<vector<unsigned char> >Out_Imagedata(R_Extend,Out_Imagedata_Per_Row);
	cout<<"ggg";
	for(i = 0; i < R_Size; i++)
	{
		for(j = 0; j < C_Size; j++)
		{
			Out_Imagedata[i + Extend][j + Extend] = Imagedata[i][j]; //copy the image as is
		}
	}

	for(i= 0; i < Extend; i++)
	{
		for(j = Extend; j < C_Extend - Extend; j++)
		{
			Out_Imagedata[i][j] = Imagedata[i][j - Extend];
			Out_Imagedata[R_Extend - 1 - i][j] = Imagedata[R_Size - 1 - i][j - Extend];
		}
	}

	for( i = Extend; i < R_Extend - Extend ; i++)
	{
		for( j = 0; j < Extend; j++)
		{
			Out_Imagedata[i][j] = Imagedata[i - Extend][j];
			Out_Imagedata[i][C_Extend - j - 1] = Imagedata[i - Extend][C_Size - 1 - j];
		}
	}

	for( i = 0 ; i < Extend ; i++)
	{
		for( j = 0 ; j < Extend ; j++)
		{
			Out_Imagedata[i][j] = Imagedata[i][j];
			Out_Imagedata[R_Extend - i - 1][j] = Imagedata[R_Size - i - 1][j];
			Out_Imagedata[i][C_Extend - j - 1] = Imagedata[i][C_Size - j - 1];
			Out_Imagedata[R_Extend - i - 1][C_Extend - j - 1] = Imagedata[R_Size - i - 1][C_Size - j - 1];
		}
	}
	
	return Out_Imagedata;
}











