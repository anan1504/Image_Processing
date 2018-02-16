//////////////////////////////////////
///////ANANYA SINGH///////////////////
//////////////////////////////////////
//////////////////////////////////////
///////ananyasingh1216@gmail.com
//////////////////////////////////////
///////02/25/18///////////////////////
//////////////////////////////////////

/*
Program description: Performs error diffusion of a grayscale image ising 3 methods:
1: Floyd-Steinberg
2: Jarvis, Judice, and Ninke, 
3: Stucki
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

//input: program_name input_image.raw output_image.raw [BytesPerPixel = 3] [R_Size = 256] [C_Size = 256]


int main()

{
	// Define file pointer and variables
	int BytesPerPixel=1;
	int R_Size = 512;
	int C_Size = 512;
	// Check for proper syntax
	string Input = "colorchecker.raw";
	string Output = "colorchecker_error_diffusion.raw";
	/*
	if (argc < 3)
	{
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 3] [R_Size = 256] [C_Size = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4)
	{
		BytesPerPixel = 1; // default is RGB image
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
	unsigned char *Inbuffer = (unsigned char*) calloc (R_Size*C_Size, sizeof(unsigned char));
	unsigned char *Outbuffer = (unsigned char*) calloc (R_Size*C_Size, sizeof(unsigned char));
	//double* Inbuffer = new double[R_Size*C_Size];
	int z=0;
	int i,j,p;
	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			
				Inbuffer[(i*C_Size)+j]=Imagedata[j][i][0];
			
		}
	}
	

	
	int e=0,u,v;
	float a,b,c,d;
	int threshold=127;
	int N;
	//Floyd-Steinberg’s error diffusion with the serpentine scanning, where the error diffusion matrix is:
	float ErrorMatrix[3][3]={{0,0,0},{0,0,7.0/16.0},{3.0/16.0,5.0/16.0,1.0/16.0}};
	float ErrorMatrix1[3][3]={{0,0,0},{7.0/16.0,0,0},{1.0/16.0,5.0/16.0,3.0/16.0}}; //for right to left
	//Error diffusion proposed by Jarvis, Judice, and Ninke (JJN),
	float ErrorMatrixJJN[5][5]={{0,0,0,0,0},
								{0,0,0,0,0},
								{0,0,0,7.0/48.0,5.0/48.0},
								{3.0/48.0,5.0/48.0,7.0/48.0,5.0/48.0,3.0/48.0},
								{1.0/48.0,3.0/48.0,5.0/48.0,3.0/48.0,1.0/48.0}};
	float ErrorMatrixJJN1[5][5]={{0,0,0,0,0},//for right to left
								{0,0,0,0,0},
								{7.0/48.0,5.0/48.0,0,0,0},
								{3.0/48.0,5.0/48.0,7.0/48.0,5.0/48.0,3.0/48.0},
								{1.0/48.0,3.0/48.0,5.0/48.0,3.0/48.0,1.0/48.0}};
	//Error diffusion proposed by Stucki,
	float ErrorMatrixS[5][5]={{0,0,0,0,0},
								{0,0,0,0,0},
								{0,0,0,8.0/42.0,4.0/42.0},
								{2.0/42.0,4.0/42.0,8.0/42.0,2.0/42.0,4.0/42.0},
								{1.0/42.0,2.0/42.0,4.0/42.0,2.0/42.0,1.0/42.0}};
	float ErrorMatrixS1[5][5]={{0,0,0,0,0},//for to right to left
								{0,0,0,0,0},
								{8.0/42.0,4.0/42.0,0,0,0},
								{2.0/42.0,4.0/42.0,8.0/42.0,2.0/42.0,4.0/42.0},
								{1.0/42.0,2.0/42.0,4.0/42.0,2.0/42.0,1.0/42.0}};



	cout<<"Enter the type of error diffusion: 1: Floyd-Steinberg, 2: Jarvis, Judice, and Ninke, 3: Stucki"<<endl;
	
	cin>>N;

	for(i=0;i<R_Size;i++)
	{
		if((i%2)==0)//to go from left to right
		{
		
			for(j=0;j<C_Size;j++)
			{
				//p=Inbuffer[(i*C_Size)+j];
				//cout<<e<<endl;
				e=0;
				if((int)Inbuffer[(i*C_Size)+j]<threshold)//check against the threshold
				{
					Out_Imagedata[j][i][0]=0;
					e=(int)Inbuffer[(i*C_Size)+j]-0;
				}
				else
				{
					Out_Imagedata[j][i][0]=255;
					e=(int)Inbuffer[(i*C_Size)+j]-255;
				}
				 
				if(N==1)
				{
					for(u=-1;u<=1;u++)//go through the matrix
					{
						for(v=-1;v<=1;v++)
						{
							z=Inbuffer[(i+u)*C_Size+(j+v)];//store value of pixel
							z+=(ErrorMatrix[u+1][v+1]*(float)e);//add the percentage of error from the matrix
							z=round(z);
							if(z<256)//if new value exceeds the upper limit adjust it to the upper limit
								Inbuffer[(i+u)*C_Size+(j+v)]=z;
							else
								Inbuffer[(i+u)*C_Size+(j+v)]=255;

							
						}
					}
				}
				 
				if(N==2)
				{
					for(u=-2;u<=2;u++)
					{
						for(v=-2;v<=2;v++)
						{
							z=Inbuffer[(i+u)*C_Size+(j+v)];
							z+=(ErrorMatrixJJN[u+2][v+2]*(float)e);
							z=round(z);
							if(z<256)
								Inbuffer[(i+u)*C_Size+(j+v)]=z;
							else
								Inbuffer[(i+u)*C_Size+(j+v)]=255;
						}
					}	
				}
				if(N==3)
				{
					for(u=-2;u<=2;u++)
					{
						for(v=-2;v<=2;v++)
						{
							z=Inbuffer[(i+u)*C_Size+(j+v)];
							z+=(ErrorMatrixS[u+2][v+2]*(float)e);
							z=round(z);
							if(z<256)
								Inbuffer[(i+u)*C_Size+(j+v)]=z;
							else
								Inbuffer[(i+u)*C_Size+(j+v)]=255;
						}
					}	
				}
			}
		}
		
		
		
		else//to go from right to left
		{
			for(j=C_Size-1;j>=0;j--)
			{
				//p=Inbuffer[(i*C_Size)+j];
				if((int)Inbuffer[(i*C_Size)+j]<threshold)
				{
					Out_Imagedata[j][i][0]=0;
					e=(int)Inbuffer[(i*C_Size)+j]-0;
				}
				else
				{
					Out_Imagedata[j][i][0]=255;
					e=(int)Inbuffer[(i*C_Size)+j]-255;
				}
				 
				if(N==1)
				{
					for(u=-1;u<=1;u++)
					{
						for(v=-1;v<=1;v++)
						{
							z=Inbuffer[(i+u)*C_Size+(j+v)];
							z+=(ErrorMatrix1[u+1][v+1]*(float)e);
							z=round(z);
							if(z<256)
								Inbuffer[(i+u)*C_Size+(j+v)]=z;
							else
								Inbuffer[(i+u)*C_Size+(j+v)]=255;
						}
					}
				}
				 
				if(N==2)
				{
					for(u=-2;u<=2;u++)
					{
						for(v=-2;v<=2;v++)
						{
							z=Inbuffer[(i+u)*C_Size+(j+v)];
							z+=(ErrorMatrixJJN1[u+2][v+2]*(float)e);
							z=round(z);
							if(z<256)
								Inbuffer[(i+u)*C_Size+(j+v)]=z;
							else
								Inbuffer[(i+u)*C_Size+(j+v)]=255;
						}
					}	
				}
				if(N==3)
				{
					for(u=-2;u<=2;u++)
					{
						for(v=-2;v<=2;v++)
						{
							z=Inbuffer[(i+u)*C_Size+(j+v)];
							z+=(ErrorMatrixS1[u+2][v+2]*(float)e);
							z=round(z);
							if(z<256)
								Inbuffer[(i+u)*C_Size+(j+v)]=z;
							else
								Inbuffer[(i+u)*C_Size+(j+v)]=255;
						}
					}	
				}
			}
		}
	}
	//Writing image into a file given by the user input
	if(!Image_Out(Out_Imagedata, Output.c_str(), R_Size, C_Size, BytesPerPixel))
		cout<<"Error!";
	

	return 0;
}

