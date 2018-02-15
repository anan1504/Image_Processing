#include "Operations.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include<math.h>
#include<string.h>

using namespace std;

//returns pixel value function(input pixel value,threshold)


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

vector<vector<vector<unsigned char> > >Median_filter(vector<vector<vector<unsigned char> > >Imagedata,int R_Size, int C_Size,int BytesPerPixel)
{
	int N;
	cout<<"Enter N for median {3,5,7,9, or 11}"<<endl;
	cin>>N;
	if(!(N==3||N==5||N==9||N==11||N==7))
	{
		cout<<"Error! Please enter N again:";
		cin>>N;
	}
	int n=(N-1)/2;
	int i,j,k;

	vector<unsigned char> Out_Imagedata_Per_Pixel(BytesPerPixel,0);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row(C_Size,Out_Imagedata_Per_Pixel);
	vector<vector<vector<unsigned char> > >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);
	

	for(k=0;k<BytesPerPixel;k++)
		for(i=0;i<R_Size;i++)
		{
			for(j=0;j<C_Size;j++)
				
				{
					Out_Imagedata[i][j][k]=Imagedata[i][j][k]; //copy the data for in place operations
				}
		}

	
			
	int N_array=N*N;
	int median_gray[N_array];
	int N_temp;
	int p,l;
	int x,y;

	for(k=0;k<3;k++)
	{
		for(i=n;i<R_Size-n;i++)
		{
			for(j=n;j<C_Size-n;j++)
			{
				N_temp=0;
				for(x=i-n;x<=i+n;x++)//create a NxN window around the active pixel
					for(y=j-n;y<=j+n;y++)
					{
						median_gray[N_temp]=Imagedata[x][y][k]; //load all the neighbouring elements
						N_temp++;
					}
				qsort(median_gray,N_array,sizeof(int),cmpfunc); //arrange in ascending order and find the median
				p=median_gray[(N_array-1)/2];

				Out_Imagedata[i][j][k]=(unsigned char)p;
			}
		}
	}
	//to take care of the boundary conditions		
	unsigned char temp_col[2][C_Size][3];
	unsigned char temp_row[2][R_Size][3];
	for(k=0;k<3;k++)
	{
		for(j=0;j<C_Size;j++)
		{
			temp_col[0][j][k]=Out_Imagedata[n][j][k];
			temp_col[1][j][k]=Out_Imagedata[R_Size-1-n][j][k];
		}
	}
	for(k=0;k<3;k++)
	{
		for(j=0;j<R_Size;j++)
		{
			temp_row[0][j][k]=Out_Imagedata[j][n][k];
			temp_row[1][j][k]=Out_Imagedata[j][C_Size-1-n][k];
		}
	}

	for(k=0;k<3;k++)
	{
		for(i=0;i<=n;i++)
			for(j=0;j<C_Size;j++)
			{
				Out_Imagedata[i][j][k] = temp_col[0][j][k];
				Out_Imagedata[(R_Size-1)-i][j][k] = temp_col[1][j][k];
			}
	}

	for(k=0;k<3;k++)
	{
		for(i=0;i<=n;i++)
		{
			for(j=0;j<R_Size;j++)
			{
				Out_Imagedata[j][i][k]=temp_row[0][j][k];
				Out_Imagedata[j][(C_Size-1)-i][k]=temp_row[1][j][k];
			}
		}
	}
	return Out_Imagedata;
}

vector<vector<vector<unsigned char> > >Guassian_filter(vector<vector<vector<unsigned char> > >Out_Imagedata,int R_Size, int C_Size,int BytesPerPixel)
{
	vector<unsigned char> Out_Imagedata_Per_Pixel1(BytesPerPixel,0);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row1(C_Size,Out_Imagedata_Per_Pixel1);
	vector<vector<vector<unsigned char> > >Out_Imagedata1(R_Size,Out_Imagedata_Per_Row1);
	int i,j,k;
	int Ng;
	cout<<"Enter N for gaussian {3,5,7,9, or 11}"<<endl;
	cin>>Ng;
	if(!(Ng==3||Ng==5||Ng==9||Ng==11||Ng==7))
	{
		cout<<"Error! Please enter N again:";
		cin>>Ng;
	}
	
	int ng=(Ng-1)/2;

	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
			for(k=0;k<BytesPerPixel;k++)
			{
				Out_Imagedata1[i][j][k]=Out_Imagedata[i][j][k];//copy the elements for in place operations
			}
	}
	
	int count=0;
	int xg,yg,pg,xgg,ygg,xggg,yggg;
	
	int gaussian_sum;
	
	for(k=0;k<3;k++)
	{
		for(i=ng;i<R_Size-ng;i++)
		{
			for(j=ng;j<C_Size-ng;j++)
			{
				gaussian_sum=0;
				count=0;
				pg=0;
				for(xg=i-ng, xgg=0;xg<=i+ng;xg++,xgg++)
				{
					for(yg=j-ng,ygg=0;yg<=j+ng;yg++,ygg++)
					{
						xggg=xgg;
						yggg=ygg;
						if(xggg>ng)
							xggg=abs(Ng-xgg-1);
						if(yggg>ng)
							yggg=abs(Ng-ygg-1);
						gaussian_sum=gaussian_sum+(Out_Imagedata[xg][yg][k]*pow(2,(xggg+yggg))); //calculate the gaussain sum of the neighbouring pixels
						count=count+pow(2,xggg+yggg);
					}
				}
				pg=gaussian_sum/count;
				Out_Imagedata1[i][j][k]=(unsigned char)pg; //assign the gaussian sum to the existing pixel
			}
		}
	}
	//take care of the boundary conditions
	unsigned char temp_colg[2][C_Size][3];
	unsigned char temp_rowg[2][R_Size][3];


	 for(k=0;k<3;k++)
	 {
		for(j=0;j<C_Size;j++)
		{
			temp_colg[0][j][k]=Out_Imagedata1[ng][j][k];
			temp_colg[1][j][k]=Out_Imagedata1[R_Size-1-ng][j][k];
		}
	}
	for(k=0;k<3;k++)
	{
		for(j=0;j<R_Size;j++)
		{
			temp_rowg[0][j][k]=Out_Imagedata1[j][ng][k];
			temp_rowg[1][j][k]=Out_Imagedata1[j][C_Size-1-ng][k];
		}
	}

	for(k=0;k<3;k++)
	{
		for(i=0;i<=ng;i++)
			for(j=0;j<C_Size;j++)
			{
				Out_Imagedata1[i][j][k] = temp_colg[0][j][k];
				Out_Imagedata1[(R_Size-1)-i][j][k] = temp_colg[1][j][k];
			}
	}

	for(k=0;k<3;k++)
	{
		for(i=0;i<=ng;i++)
		{
			for(j=0;j<R_Size;j++)
			{
				Out_Imagedata1[j][i][k]=temp_rowg[0][j][k];
				Out_Imagedata1[j][(C_Size-1)-i][k]=temp_rowg[1][j][k];
			}
		}
	}
	return Out_Imagedata1;
}

vector<vector<vector<unsigned char> > >Hist_Specification(vector<vector<vector<unsigned char> > >Out_Imagedata1,vector<vector<vector<unsigned char> > >Out_Imagedata2,int N_Size,int BytesPerPixel)
{
	vector<unsigned char> Out_Imagedata_Per_Pixel_Main(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row_Main(N_Size,Out_Imagedata_Per_Pixel_Main);
	vector<vector<vector<unsigned char> > >Out_Imagedata_Main(N_Size,Out_Imagedata_Per_Row_Main);

	//Get the CDF histogram for the film image:
	int i,j,k;
	float dump1[256][3]={0};//dump intensity values

	int z=0;
	for(i=0;i<3;i++)
		for(j=0;j<256;j++)
			dump1[j][i]=0;
		
	for(k=0;k<3;k++)
		for(i=0;i<N_Size;i++)
			for(j=0;j<N_Size;j++)
			{
				z=Out_Imagedata1[i][j][k]; //Get intensity values of reference image
				dump1[z][k]++;
			}

	//normalise the histogram values
	for(k=0;k<3;k++)
		for(i=0;i<256;i++)
		{
			dump1[i][k]= dump1[i][k]/(N_Size*N_Size);//Normalising the values hence finding the probability 
		}
	float c_dump1[256][3]={0.0};

	c_dump1[0][0]=dump1[0][0];
	c_dump1[0][1]=dump1[0][1];
	c_dump1[0][2]=dump1[0][2];
	for(k=0;k<BytesPerPixel;k++)
	{
		for(i=1;i<256;i++)
		{
			c_dump1[i][k]= dump1[i][k]+c_dump1[i-1][k];   //CDf values for reference image
		}
	}

	float dump2[256][3]={0};//dump intensity values

	//int z;
	for(i=0;i<BytesPerPixel;i++)
		for(j=0;j<256;j++)
			dump2[j][i]=0;
		
	for(k=0;k<BytesPerPixel;k++)
		for(i=0;i<N_Size;i++)
			for(j=0;j<N_Size;j++)
			{
				z=Out_Imagedata2[i][j][k];//histogram equalisation of given image
				dump2[z][k]++;
			}

	//normalise the histogram values
	for(k=0;k<BytesPerPixel;k++)
		for(i=0;i<256;i++)
		{
			dump2[i][k]= dump2[i][k]/(N_Size*N_Size);//Normalising the values hence finding the probability 
		}
	float c_dump2[256][3]={0.0};

	c_dump2[0][0]=dump2[0][0];
	c_dump2[0][1]=dump2[0][1];
	c_dump2[0][2]=dump2[0][2];
	for(k=0;k<BytesPerPixel;k++)
		for(i=1;i<256;i++)
		{
			c_dump2[i][k]= dump2[i][k]+c_dump2[i-1][k];   //CDf values of the given image
		}

	float lookup[256][3]={0.0};
	float diff[256][3]={0.0};
	float min=0.0;
	int p=0;
	int r=0;
	//performing histogram specification:
	for(k=0;k<BytesPerPixel;k++)
	{
		for(i=0;i<256;i++)
		{
			for(j=0;j<256;j++)
			{
				diff[j][k]=abs(c_dump2[i][k]-c_dump1[j][k]); //difference between the CDF of the two images
			}
			min=diff[0][k];
			p=0;

			for(j=1;j<256;j++)
			{
				if(diff[j][k]<min)
				{
					min=diff[j][k];
					p=j;
				}
			}

			lookup[i][k]=p;
		}
	}

	//create look up table 
	int t_lookup=0;
	float new_dump[256][BytesPerPixel];
	for(k=0;k<BytesPerPixel;k++)
	{
		for(i=0;i<256;i++)
			new_dump[i][k]=0.0;
	}
	


	for(k=0;k<BytesPerPixel;k++)
	{
		for(i=0;i<256;i++)
		{
			t_lookup=lookup[i][k];//finding the corresponding values based on the look up table
			new_dump[i][k]=c_dump2[t_lookup][k];

		}
	}
	z=0;

	

	for(k=0;k<BytesPerPixel;k++)
	{
		for(i=0;i<N_Size;i++)
		{
			for(j=0;j<N_Size;j++)
			{
				z=Out_Imagedata2[i][j][k];
				Out_Imagedata_Main[i][j][k]=floor(255*new_dump[z][k]);
			}
		}
	}
	return Out_Imagedata_Main;
}


vector<vector<vector<unsigned char> > >Bilinear_Interpolation(vector<vector<vector<unsigned char> > >Imagedata1,int N_Size, int BytesPerPixel)
{
	//resizing the reference image

	float xf[N_Size];
	float yf[N_Size];
	float SC= 2.929;
	float SR= 3.906;
	int i,j,k;
	for(i=0;i<N_Size;i++)
	{
		
		xf[i]=(float)(i*SC);
		yf[i]=(float)(i*SR);
		
	}
	
	int x,y;
	float dx,dy;
	vector<unsigned char> Out_Imagedata_Per_Pixel(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row(N_Size,Out_Imagedata_Per_Pixel);
	vector<vector<vector<unsigned char> > >Out_Imagedata(N_Size,Out_Imagedata_Per_Row);

	int l,p;
	for(l=0;l<BytesPerPixel;l++)
	{
		for(j=0;j<N_Size;j++)
			for(k=0;k<N_Size;k++)
			{
				x=(int) xf[j];
				y=(int) yf[k];
				dx=(float)(xf[j]-x);
				dy=(float) yf[k]-y;
				
				Out_Imagedata[j][k][l]=(Imagedata1[x][y][l]*(1-dx)*(1-dy))+(Imagedata1[x+1][y][l]*(dx)*(1-dy))+(Imagedata1[x][y+1][l]*(1-dx)*(dy))
										+(Imagedata1[x+1][y+1][l]*(dx)*(dy));

			}
	}
	return Out_Imagedata;
	

}

vector<vector<vector<unsigned char> > >OilPaintingEffect(vector<vector<vector<unsigned char> > >Imagedata,int R_Size, int C_Size, int BytesPerPixel,int n)
{
	int graylevels[256]={0};
	int maxim,i,j,k,x,y,temp_gray,w,u,p;

	vector<unsigned char> Out_Imagedata_Per_Pixel(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row(C_Size,Out_Imagedata_Per_Pixel);
	vector<vector<vector<unsigned char> > >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);

	for(k=0;k<3;k++)
	{
		for(i=n;i<R_Size-n;i++)
		{
			for(j=n;j<C_Size-n;j++)
			{
				for(u=0;u<256;u++){
					graylevels[u]=0;
				}
				temp_gray=0;

				for(x=i-n;x<=i+n;x++) //creating a window at the current (i,j) point of the pixel equal to NxN
				{
					for(y=j-n;y<=j+n;y++)
					{
						temp_gray=Imagedata[x][y][k]; //finding the color values of the neighbouring pixels
						graylevels[temp_gray]++; 

					}
				}

				maxim=0;
				p=0;
				for(w=0;w<256;w++)
				{
					if(graylevels[w]>maxim)//finding the color which is most frequent and equating it to the center pixel
					{
						maxim=graylevels[w];
						p=w;
					}
				}

				Out_Imagedata[i][j][k]=(unsigned char)p;
			}
		}
	}
	return Out_Imagedata;

}

vector<vector<vector<unsigned char> > >Color_Quantisation(vector<vector<vector<unsigned char> > >Imagedata,int R_Size, int C_Size, int BytesPerPixel)
{
	vector<unsigned char> Out_Imagedata_Per_Pixel(BytesPerPixel);
	vector<vector<unsigned char> >Out_Imagedata_Per_Row(C_Size,Out_Imagedata_Per_Pixel);
	vector<vector<vector<unsigned char> > >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);

	int i,j,k;
	for(k=0;k<3;k++)//Quantisation of an image to 64 colors
	{
		for(i=0;i<R_Size;i++)
		{
			for(j=0;j<C_Size;j++)
			{
				if(Imagedata[i][j][k]<64)
					Out_Imagedata[i][j][k]=31;
				else if(Imagedata[i][j][k]<128)
					Out_Imagedata[i][j][k]=95;
				else if(Imagedata[i][j][k]<192)
					Out_Imagedata[i][j][k]=159;
				else
					Out_Imagedata[i][j][k]=223;
			}
		}
	}
	return Out_Imagedata;

}