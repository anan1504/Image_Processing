#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include<math.h>
#include<string.h>

using namespace std;

#ifndef _Oil_H
#define _Oil_H

//To perform color quantisation
vector<vector<vector<unsigned char> > >Color_Quantisation(vector<vector<vector<unsigned char> > >Imagedata,int R_Size, int C_Size, int BytesPerPixel);

//to perform oil painting effect
vector<vector<vector<unsigned char> > >OilPaintingEffect(vector<vector<vector<unsigned char> > >Imagedata,int R_Size, int C_Size, int BytesPerPixel,int n);

#endif

#ifndef _Film_H
#define _Film_H

//perform histogram specification
vector<vector<vector<unsigned char> > >Hist_Specification(vector<vector<vector<unsigned char> > >Out_Imagedata1,vector<vector<vector<unsigned char> > >Out_Imagedata2,int N_Size,int BytesPerPixel);
//perform bilinear interpolation
vector<vector<vector<unsigned char> > >Bilinear_Interpolation(vector<vector<vector<unsigned char> > >Imagedata1,int N_Size, int BytesPerPixel);
#endif


#ifndef _Denoise_H
#define _Denoise_H

int cmpfunc (const void * a, const void * b);
//Median filter:
vector<vector<vector<unsigned char> > >Median_filter(vector<vector<vector<unsigned char> > >Imagedata,int R_Size, int C_Size,int BytesPerPixel);
//Gaussian filter:
vector<vector<vector<unsigned char> > >Guassian_filter(vector<vector<vector<unsigned char> > >Out_Imagedata,int R_Size, int C_Size,int BytesPerPixel);

#endif



