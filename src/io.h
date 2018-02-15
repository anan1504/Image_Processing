#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include<string.h>

using namespace std;

#ifndef _FileIO_H
#define _FileIO_H


//Acess file to read the image
vector<vector<vector<unsigned char> > >Image_Input(const char* filename, int R_Size, int C_Size, int BytesPerPixel);
//Write image data into file
int Image_Out(vector<vector<vector<unsigned char> > >Out_Imagedata, const char* filename_out, int R_Size, int C_Size, int BytesPerPixel);

#endif


