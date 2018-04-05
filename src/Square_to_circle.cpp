//////////////////////////////////////
///////ANANYA SINGH///////////////////
///////ananyasingh1216@gmail.com//////
//////////////////////////////////////
///////04/5/18///////////////////////
//////////////////////////////////////
//square to circle mapping
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
int main( )

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel=3;
	int R_Size = 512;
	int C_Size = 512;
	string input1= "panda.raw";;
	string output="panda_circle.raw";
	string output1="panda_square.raw";
	
	vector<vector<vector<unsigned char> > >Imagedata;

	Imagedata= Image_Input(input1.c_str(), R_Size, C_Size, BytesPerPixel);
	//Declare the output Image data for 3D
	vector<unsigned char> Out_Imagedata_Per_Pixel(BytesPerPixel,0);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row(C_Size,Out_Imagedata_Per_Pixel);
	vector<vector<vector<unsigned char> > >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);
	///////////////////////////////////////////
	//Write the Image processing code here
	//square to circle
	float c= R_Size/2+0.5;
	float u,v,x,y,dist,x1,y1,u1,v1;
	int i,j,k;
	int p,q;
	unsigned char pixel_value;
	for(k=0;k<BytesPerPixel;k++)
	{
		for(i=0;i<R_Size;i++)
		{
			for(j=0;j<C_Size;j++)
			{
				if(i<c && j<c)//2nd quadrant
				{
					y=c-i;
					x=-(c-j);

				}
				else if(i>=c && j<c)//3rd quadrant
				{
					y=-(i-c);
					x=-(c-j);
				}
				else if(i<c && j>=c)//1st quadrant
				{
					y=c-i;
					x=j-c;
				}
				else//4th quadrant
				{
					y=-(i-c);
					x=j-c;
				}
				x1=x/c;
				y1=y/c;
				u1=x1*(sqrt(1-(pow(y1,2)/2)));
				v1=y1*(sqrt(1-(pow(x1,2)/2)));
				u=u1*c;
				v=v1*c;
				cout<<"u= "<<(int)u<<"v= "<<v<<endl;
				dist=sqrt(pow(u,2)+pow(v,2));
				if(dist>c)
				{
					pixel_value=0;	
				}
				else
				{
					pixel_value=Imagedata[i][j][k];
					//cout<<"yay"<<(int)pixel_value;
				}

				if(u>0 && v>0)//1st quadrant
				{
					p=c-v;
					q=c+u;
				}
				else if(u<=0 && v>0)//2nd quadrant
				{
					p=c-v;
					q=c+u;
				}
				else if(u<=0 && v<=0)//3rd quadrant
				{
					p=c-v;
					q=u+c;
				}
				else //4th quadrant
				{
					p=c-v;
					q=c+u;
				}
				if(p>=0 && p<R_Size && q>=0 && q<C_Size)
				{
					cout<<p<<" "<<q<<endl;
					Out_Imagedata[p][q][k]=pixel_value;
				}
				else 
					cout<<"?"<<endl;
			}

		}
	}
	cout<<"done";
	if(!Image_Out(Out_Imagedata, output.c_str(), C_Size, R_Size, BytesPerPixel))
		cout<<"Error!";
	//circle to square mapping
	vector<unsigned char> Out_Imagedata_Per_Pixel1(BytesPerPixel,0);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row1(C_Size,Out_Imagedata_Per_Pixel1);
	vector<vector<vector<unsigned char> > >Out_Imagedata1(R_Size,Out_Imagedata_Per_Row1);

	float fp,fq,fu,fv,dp,dq;
	for(k=0;k<BytesPerPixel;k++)
	{
		for(i=0;i<R_Size;i++)
		{
			for(j=0;j<C_Size;j++)
			{
				if(i<c && j<c)//2nd quadrant
				{
					y=c-i;
					x=-(c-j);

				}
				else if(i>=c && j<c)//3rd quadrant
				{
					y=-(i-c);
					x=-(c-j);
				}
				else if(i<c && j>=c)//1st quadrant
				{
					y=c-i;
					x=j-c;
				}
				else//4th quadrant
				{
					y=-(i-c);
					x=j-c;
				}
				x1=x/c;
				y1=y/c;
				u1=x1*(sqrt(1-(pow(y1,2)/2)));
				v1=y1*(sqrt(1-(pow(x1,2)/2)));
				fu=u1*c;
				fv=v1*c;
				if(fu>0 && fv>0)//1st quadrant
				{
					fp=c-fv;
					fq=c+fu;
				}
				else if(fu<=0 && fv>0)//2nd quadrant
				{
					fp=c-fv;
					fq=c+fu;
				}
				else if(fu<=0 && fv<=0)//3rd quadrant
				{
					fp=c-fv;
					fq=fu+c;
				}
				else //4th quadrant
				{
					fp=c-fv;
					fq=c+fu;
				}
				p=floor(fp);
				q=floor(fq);
				dp=fp-p;
				dq=fq-q;
				
				if(p>=0 && p<R_Size && q>=0 && q<C_Size)
				{
					if (p==0 || p==R_Size-1 || p==0 || p==C_Size-1)
						pixel_value=Out_Imagedata[p][q][k];
					else
						pixel_value=(Out_Imagedata[p][q][k]*(1-dp)*(1-dq))+(Out_Imagedata[p+1][q][k]*(dp)*(1-dq))+//bilinear interpolation
									(Out_Imagedata[p][q+1][k]*(1-dp)*(dq))+(Out_Imagedata[p+1][q+1][k]*(dp)*(dq));
				}
				else 
					cout<<"?"<<endl;
				Out_Imagedata1[i][j][k]=pixel_value;

			}
		}
	}
	cout<<"done";
	if(!Image_Out(Out_Imagedata1, output1.c_str(), C_Size, R_Size, BytesPerPixel))
		cout<<"Error!";
	

	return 0;
}