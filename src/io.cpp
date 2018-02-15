#include "io.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include<string.h>

using namespace std;


//For file input and creating a input image vecto
vector<vector<vector<unsigned char> > >Image_Input(const char* filename, int R_Size, int C_Size, int BytesPerPixel) 	
{
	FILE *file;
	//declase file buffer 
	unsigned char *Imagebuffer = (unsigned char*) calloc (R_Size*C_Size*BytesPerPixel, sizeof(unsigned char));
	file=fopen(filename,"rb");
	//read from the file
	fread(Imagebuffer, sizeof(unsigned char), R_Size*C_Size*BytesPerPixel*sizeof(unsigned char), file);
	fclose(file);

	vector<vector<vector<unsigned char> > >Imagedata;

	int i,j,k;
	//write the contents into a vector
	for(i=0;i<R_Size;i++)
	{
		vector<vector<unsigned char> >Imagedata_Per_Row;
		for(j=0;j<C_Size;j++)
		{
			vector<unsigned char> Imagedata_Per_Pixel;
			for(k=0;k<BytesPerPixel;k++)
			{
				Imagedata_Per_Pixel.push_back(*(Imagebuffer+ ((i*C_Size+j) * BytesPerPixel) + k));
			}
			Imagedata_Per_Row.push_back(Imagedata_Per_Pixel);
		}
		Imagedata.push_back(Imagedata_Per_Row);
	}

	return Imagedata;
}

//for image output into file
int Image_Out(vector<vector<vector<unsigned char> > >Out_Imagedata, const char* filename_out, int R_Size, int C_Size, int BytesPerPixel) 
{
	FILE *file;

	unsigned char *Out_Imagebuffer = (unsigned char*) calloc (R_Size*C_Size*BytesPerPixel*sizeof(unsigned char), sizeof(unsigned char));
	int i,j,k;
	//write contents of the vector into the file
	for(i=0;i<R_Size;i++)
	
		for(j=0;j<C_Size;j++)
		
			for(k=0;k<BytesPerPixel;k++)
			{
				*(Out_Imagebuffer + (i*C_Size + j)*BytesPerPixel + k) = Out_Imagedata[i][j][k];
			}

	if (!(file=fopen(filename_out,"wb"))) {
		cout << "Cannot open file: " << filename_out << endl;
		return 0;
	}
	fwrite(Out_Imagebuffer, sizeof(unsigned char), R_Size*C_Size*BytesPerPixel, file);
	fclose(file);

	return 1;
			


}