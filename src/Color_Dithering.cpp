//////////////////////////////////////
///////ANANYA SINGH///////////////////
//////////////////////////////////////
//////////////////////////////////////
///////ananyasingh1216@gmail.com//////////////
//////////////////////////////////////
///////02/25/18///////////////////////
//////////////////////////////////////

/*
Program description:
Perfroms color dithering of the flower image
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include "io.h"
#include<math.h>
#include "Operations.h"
#include<string.h>

using namespace std;

//int *get_thresh_color(int red, int blue, int green);

int main()

{
	// Define file pointer and variables
	int BytesPerPixel=3;
	int R_Size = 700;
	int C_Size = 700;
	string Input = "flower.raw";
	string Output = "flower_color_dither.raw";
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

	
	

	////////////////////////////////image processing code here////////////////////////////////////////////////////

	//Declare the output Image data for 3D
	vector<unsigned char> Out_Imagedata_Per_Pixel(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row(C_Size,Out_Imagedata_Per_Pixel);
	vector<vector<vector<unsigned char> > >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);
	///////////////////////////////////////////
	//Write the Image processing code here
	unsigned char *Inbuffer = (unsigned char*) calloc (R_Size*C_Size*BytesPerPixel, sizeof(unsigned char));
	//unsigned char *Outbuffer = (unsigned char*) calloc (R_Size*C_Size, sizeof(unsigned char));
	//double* Inbuffer = new double[R_Size*C_Size];

	int z=0;
	int i,j,p,k;
	for(k=0;k<BytesPerPixel;k++)
	{
		for(i=0;i<R_Size;i++)
		{
			for(j=0;j<C_Size;j++)
			{
				
					Inbuffer[(i*C_Size+j)+(R_Size*C_Size)*k]=Imagedata[i][j][k];
				
			}
		}
	}
	int colortable[8][3]={{0,0,0},
							{255,0,0},
							{0,255,0},
							{0,0,255},
							{255,255,0},
							{255,0,255},
							{0,255,255},
							{255,255,255}};
	float dist[8];
	float sdist=1000.0;
	int s=0;

	
	int e[3]={0};
	int u,v,w;
	float a,b,c,d;
	int threshold=172;
	int N;
	int red_old,green_old,blue_old,red_new,green_new,blue_new;
	//Floyd-Steinberg’s error diffusion with the serpentine scanning, where the error diffusion matrix is:
	float ErrorMatrix[3][3]={{0,0,0},{0,0,7.0/16.0},{3.0/16.0,5.0/16.0,1.0/16.0}};
	float ErrorMatrix1[3][3]={{0,0,0},{7.0/16.0,0,0},{1.0/16.0,5.0/16.0,3.0/16.0}}; //for right to left
	

	for(i=0;i<R_Size;i++)
	{
		if((i%2)==0)//to go from left to right
		{
		
			for(j=0;j<C_Size;j++)
			{
				sdist=5000;
				red_old=Inbuffer[((i*C_Size)+j)+((R_Size*C_Size)*0)];
				green_old=Inbuffer[((i*C_Size)+j)+((R_Size*C_Size)*1)];
				blue_old=Inbuffer[((i*C_Size)+j)+((R_Size*C_Size)*2)];
				for(w=0;w<8;w++)
				{
					dist[w]=pow((pow(red_old-colortable[w][0],2)+pow(green_old-colortable[w][1],2)+pow(blue_old-colortable[w][2],2)),0.5);
					if(dist[w]<sdist)
					{
						s=w;

						sdist=dist[w];
					}

				}
				red_new= colortable[s][0];
				green_new= colortable[s][1];
				blue_new= colortable[s][2];
				e[0]=red_old-red_new;
				e[1]=green_old-green_new;
				e[2]=blue_old-blue_new;
				Out_Imagedata[i][j][0]=red_new;
				Out_Imagedata[i][j][1]=green_new;
				Out_Imagedata[i][j][2]=blue_new;
				for(k=0;k<3;k++)
				{
					for(u=-1;u<=1;u++)//go through the matrix
					{
						for(v=-1;v<=1;v++)
						{
							z=Inbuffer[((i+u)*C_Size+(j+v))+((R_Size*C_Size)*k)];//store value of pixel
							z+=(ErrorMatrix[u+1][v+1]*(float)e[k]);//add the percentage of error from the matrix
							z=round(z);
							if(z<256)//if new value exceeds the upper limit adjust it to the upper limit
								Inbuffer[((i+u)*C_Size+(j+v))+((R_Size*C_Size)*k)]=z;
							else
								Inbuffer[((i+u)*C_Size+(j+v))+((R_Size*C_Size)*k)]=255;
						}
					}
				}
				//cout<<i<<endl;
				//cout<<"After: "<<(int)Inbuffer[(i)*C_Size+(j+1)]<<endl;
			}
		}
	
		
		
		
		else//to go from right to left
		{
			for(j=C_Size-1;j>=0;j--)
			{
				sdist=5000;
				red_old=Inbuffer[((i*C_Size)+j)+((R_Size*C_Size)*0)];
				green_old=Inbuffer[((i*C_Size)+j)+((R_Size*C_Size)*1)];
				blue_old=Inbuffer[((i*C_Size)+j)+((R_Size*C_Size)*2)];
				for(w=0;w<8;w++)
				{
					dist[w]=pow((pow(red_old-colortable[w][0],2)+pow(green_old-colortable[w][1],2)+pow(blue_old-colortable[w][2],2)),0.5);
					if(dist[w]<sdist)
					{
						s=w;

						sdist=dist[w];
					}

				}
				red_new= colortable[s][0];
				green_new= colortable[s][1];
				blue_new= colortable[s][2];
				e[0]=red_old-red_new;
				e[1]=green_old-green_new;
				e[2]=blue_old-blue_new;
				Out_Imagedata[i][j][0]=red_new;
				Out_Imagedata[i][j][1]=green_new;
				Out_Imagedata[i][j][2]=blue_new;
				//cout<<i<<endl;
				for(k=0;k<BytesPerPixel;k++)
				{
					if(i==R_Size-1)
					{
						if(j==C_Size-1)
						{
							z=Inbuffer[((i)*C_Size+(j-1))+((R_Size*C_Size)*k)];
							z+=((float)e[k]*(7.0/17.0));
							z=round(z);
							//cout<<"k";
							if(z<256)
								Inbuffer[((i)*C_Size+(j-1))+((R_Size*C_Size)*k)]=z;
							else
								Inbuffer[((i)*C_Size+(j-1))+((R_Size*C_Size)*k)]=255;
						}
						else if(j==0)
						{
							continue;
						}
					}
					else{
						for(u=-1;u<=1;u++)
						{
							for(v=-1;v<=1;v++)
							{
								z=Inbuffer[((i+u)*C_Size+(j+v))+((R_Size*C_Size)*k)];
								z+=(ErrorMatrix1[u+2][v+2]*(float)e[k]);
								z=round(z);
								if(z<256)
									Inbuffer[((i+u)*C_Size+(j+v))+((R_Size*C_Size)*k)]=z;
								else
									Inbuffer[((i+u)*C_Size+(j+v))+((R_Size*C_Size)*k)]=255;
							}
						}
					}
				}
				
			}
		}
	}
	
	
	if(!Image_Out(Out_Imagedata, Output.c_str(), R_Size, C_Size, BytesPerPixel))
		cout<<"Error!";
	

	return 0;
}


