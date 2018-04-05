//////////////////////////////////////
///////ANANYA SINGH///////////////////
///////ananyasingh1216@gmail.com//////
//////////////////////////////////////
///////04/5/18///////////////////////
//////////////////////////////////////

//Program to perfrom panoramic stitching

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include "iostring.h"
#include<math.h>
#define PI 3.14159265
#include<string.h>

using namespace std;

void multiplyMatrices(float A[][4],float B[][4], float mult[][4],int Row_A, int Col_A, int Row_B, int Col_B);

int main( )

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel=3;
	int R_Size = 640;
	int C_Size = 480;
	string input1= "middle.raw";
	string input2="left.raw";
	string input3="right.raw";
	string output="stitching.raw";
	// Check for proper syntax
	
		
	//call function(string filename, r_size,c_size,bytesperpixel) it returns vector	
	cout<<"Assigning first image"<<endl;
	vector<vector<vector<unsigned char> > >Imagedata;

	Imagedata= Image_Input(input1.c_str(), R_Size, C_Size, BytesPerPixel);
	
	cout<<"f";

	////////////////////////////////////////////////////////////////////////////////////
	
	int N_Rsize=2000;
	int N_Csize=2000;
	float cR=(float)R_Size/2;
	float cC=(float)C_Size/2;
	cout<<"ss";
	//Declare the output Image data for 3D
	vector<unsigned char> Out_Imagedata_Per_Pixel(BytesPerPixel,0);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row(N_Csize,Out_Imagedata_Per_Pixel);
	vector<vector<vector<unsigned char> > >Out_Imagedata(N_Rsize,Out_Imagedata_Per_Row);
	///////////////////////////////////////////
	//Write the Image processing code here


	float mult[4][4];
	float A[4][4],B[4][4];
	int i,j,k,l1,m1;
	float l,m;
	float x,y,x1,y1,x2,y2;
	float tx,ty;
	float angle=30;//angle for rotation in degrees;
	float angle_radian=(angle*PI)/180;
	tx=700;
	ty=700;
	int new_pixel_value;
	cout<<"starting:";
	for(k=0;k<BytesPerPixel;k++)
	{
		for(i=0;i<N_Rsize;i++)
		{
			for(j=0;j<N_Csize;j++)
				Out_Imagedata[i][j][k]=0;
		}
	}
	
	
	
	float w1;
		
	//for left image
	vector<vector<vector<unsigned char> > >Imagedata1;

	Imagedata1= Image_Input(input2.c_str(), R_Size, C_Size, BytesPerPixel);

	//stiching left image:
	for(k=0;k<3;k++)
	{
		for(l=0;l<N_Rsize;l++)//from destination to source mapping
		{
			for(m=0;m<N_Csize;m++)//854
			{
				
				
				y=N_Rsize-0.5-l;//input image to cartesian
				x=m+0.5;//image to cartesian
				A[0][0]= 0.5742;//homography matrix inverse
				A[0][1]=0.0247;
				A[0][2]=-211.3984;
				A[1][0]=-0.1786;
				A[1][1]=0.7757;
				A[1][2]=-403.8297;
				A[2][0]=-0.0005;
				A[2][1]=0.0;
				A[2][2]=1.1635;
				B[0][0]=x;
				B[1][0]=y;
				B[2][0]=1;

				multiplyMatrices(A,B,mult,3,3,3,1);
				x1=mult[0][0];
				y1=mult[1][0];
				w1=mult[2][0];

				x2=x1/w1;//finding corresponding cartesian coordinates from homogeneous coordinates
				y2=y1/w1;
				
				
				i=R_Size-0.5-y2;
				j=x2-0.5;

				float dx=i-l1;
				float dy=j-m1;

				l1=floor(i);//cartesian to output image
				m1=floor(j);//cartesian to output image
				
				if(l1>=0 && l1<R_Size && m1>=0 && m1<C_Size)
				{
					//cout<<x2<<" "<<y2<<" "<<w1<<" "<<m<<" "<<new_pixel_value<<endl;
				
					
					new_pixel_value=Imagedata1[l1][m1][k];
					Out_Imagedata[l][m][k]=new_pixel_value;
					
				}
			}
		}
	}
	
	vector<vector<vector<unsigned char> > >Imagedata2;

	Imagedata2= Image_Input(input3.c_str(), R_Size, C_Size, BytesPerPixel);

	//stiching right image:
	for(k=0;k<3;k++)
	{
		for(l=0;l<N_Rsize;l++)//from destination to source mapping
		{
			for(m=0;m<N_Csize;m++)//854
			{
				
				
				y=N_Rsize-0.5-l;//input image to cartesian
				x=m+0.5;//image to cartesian

				A[0][0]= 1.1744;//homoggraphy matrix inverse
				A[0][1]=-0.00793;
				A[0][2]=-1056.7;
				A[1][0]=0.2155;
				A[1][1]=1.0747;
				A[1][2]=-972.1335;
				A[2][0]=0.0006;
				A[2][1]=-0.00000;
				A[2][2]=0.4500;
				B[0][0]=x;
				B[1][0]=y;
				B[2][0]=1;

				multiplyMatrices(A,B,mult,3,3,3,1);
				x1=mult[0][0];
				y1=mult[1][0];
				w1=mult[2][0];

				x2=(x1/w1);//finding corresponding cartesian coordinates from homogeneous coordinates
				y2=(y1/w1);
				
				
				i=R_Size-0.5-y2;
				j=x2-0.5;

				float dx=i-l1;
				float dy=j-m1;

				l1=floor(i);//cartesian to output image
				m1=floor(j);//cartesian to output image
				
				if(l1>=0 && l1<R_Size && m1>=0 && m1<C_Size)
				{
					new_pixel_value=Imagedata2[l1][m1][k];
					Out_Imagedata[l][m][k]=new_pixel_value;
					
				}
			}
		}
	}

	//Output 
	for(k=0;k<3;k++)
	{
		for(l=0;l<N_Rsize;l++)//from destination to source mapping
		{
			for(m=0;m<N_Csize;m++)//854
			{
				
				
				y=N_Rsize-0.5-l;//input image to cartesian
				x=m+0.5;//image to cartesian
				
				y1=y-ty;//translation
				x1=x-tx;//translation
				i=R_Size-0.5-y1;
				j=x1-0.5;
				l1=floor(i);//cartesian to output image
				m1=floor(j);//cartesian to output image
				
				if(l1>=0 && l1<R_Size && m1>=0 && m1<C_Size)
				{
					
					Out_Imagedata[l][m][k]=Imagedata[l1][m1][k];
					
				}	 
							
				
				//Out_Imagedata[l][m][k]=new_pixel_value;
				
		
				

			}
		}
	}

	if(!Image_Out(Out_Imagedata, output.c_str(), N_Csize, N_Rsize, BytesPerPixel))
		cout<<"Error!";
	

	return 0;
}
//function to multiply two matrices

void multiplyMatrices(float A[][4],float B[][4], float mult[][4],int Row_A, int Col_A, int Row_B, int Col_B)
{
	int i,j,k;
	for(i=0;i<Row_A;i++)//initialise entries of the product matrix
	{
		for(j=0;j<Col_B;j++)
		{
			mult[i][j]=0.0;
		}
	}

	for(i=0;i<Row_A;i++)
	{
		for(j=0;j<Col_B;j++)
		{
			for(k=0;k<Col_A;k++)
			{
				mult[i][j]+= A[i][k]*B[k][j];
			}
		}
	}

}
