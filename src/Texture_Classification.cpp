//////////////////////////////////////
///////ANANYA SINGH///////////////////
///////ananyasingh1216@gmail.com//////
//////////////////////////////////////
///////04/5/18///////////////////////
//////////////////////////////////////
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include<cmath>
#define PI 3.14159265
#include<string.h>
using namespace std;

#define number_of_feats 9
#define number_of_data_points 270000

vector<vector<unsigned char> > Image_Input(const char* filename, int R_Size, int C_Size); //input for the image
vector<vector<float> > FilterOperation(vector<vector<float> > &Imagedata, int R_Size, int C_Size, float filter[3][3]);//performing convolutional operation
int * kmeans(vector<vector<float> >&feat_vec, int K);
vector<vector<float> > Boundary_Extension_float(vector<vector<float> > Imagedata,int R_Size,int C_Size, int Extend);
vector<vector<float> > Average_Image (vector<vector<float> > &Imagedata, int R_Size , int C_Size);
vector<vector<unsigned char> > Boundary_Extension(vector<vector<unsigned char> > Imagedata,int R_Size,int C_Size, int Extend);


int main( )

{
	FILE *file;
	int i,j,x,y,u,v;
	string input1 = "comb.raw";
	string output1 = "Extended_composite.raw"; 
	cout<<"input done ";
	//read the input image
	int R_Size = 450;
	int C_Size = 600;
	vector<vector<unsigned char> >Imagedata;//vector for the texture image

	Imagedata= Image_Input(input1.c_str(), R_Size, C_Size);

	cout<<"input done ";
	
	//extend the input image by 12
	int Extend = 22;
	int R_Extend = R_Size + 2 * Extend;
	int C_Extend = C_Size + 2 * Extend;

	vector<unsigned char> Out_Imagedata_Per_Pixel_Extend(C_Extend , 0);
	vector<vector<unsigned char> >Out_Imagedata_Extend(R_Extend , Out_Imagedata_Per_Pixel_Extend);

	Out_Imagedata_Extend = Boundary_Extension(Imagedata, R_Size, C_Size, Extend);//extended image

	

	//calculating the average image
	float p;
	float pixel_sum;

	vector<float> Imagedata_average_Per_Pixel(C_Size , 0.0);
	vector<vector<float> >Imagedata_average(R_Size , Imagedata_average_Per_Pixel);

	//take a 25*25 window and get the mean of all the pixels
	for( i = 22; i < R_Size + 22; i++)
	{
		for( j = 22; j < C_Size + 22; j++)
		{
			p = (float)Out_Imagedata_Extend[i][j];
			pixel_sum = 0.0;
			for(x = i-22 ; x <= i+22; x++)
			{
				for(y = j-22 ;y <= j+22; y++)
				{
					pixel_sum += (int)(Out_Imagedata_Extend[x][y]);
				}
			}
			Imagedata_average[i - 22][j -22] =(float) p - (float)(pixel_sum/(45 * 45));
		}
	}

	

	//extended image for the filter calculation
	int Extend1 = 1;
	int R_Extend1 = R_Size + 2 * Extend1;
	int C_Extend1 = C_Size + 2 * Extend1;

	vector<float> Imagedata_average_Per_Pixel_Extend1(C_Extend1 , 0.0);
	vector<vector<float> >Imagedata_average_Extend(R_Extend1 , Imagedata_average_Per_Pixel_Extend1);

	Imagedata_average_Extend = Boundary_Extension_float(Imagedata_average, R_Size, C_Size, Extend1);//extended image

	//applying the 9 filters to all the pixels

	vector<vector<vector<float> > >Imagedata_nine;

	float L3TE3[3][3] = { {-1.0/12.0, 0.0 , 1.0/12.0},
						{-2.0/12.0, 0.0 , 2.0/12.0},
						{-1.0/12.0, 0.0 , 1.0/12.0}};

	float S3TE3[3][3] = { {1.0/4.0, 0.0 , -1.0/4.0},
						{-2.0/4.0, 0.0 , 2.0/4.0},
						{1.0/4.0, 0.0 , -1.0/4.0}};

	float E3TE3[3][3] = { {1.0/4.0, 0.0 , -1.0/4.0},
						{0.0, 0.0 , 0.0},
						{-1.0/4.0, 0.0 , 1.0/4.0}};

	float E3TL3[3][3] = { {-1.0/12.0, -2.0/12.0 , -1.0/12.0},
						{0.0, 0.0 , 0.0},
						{1.0/12.0, 2.0/12.0 , 1.0/12.0}};

	float E3TS3[3][3] = { {1.0/4.0, -2.0/4.0 , 1.0/4.0},
						{0.0, 0.0 , 0.0},
						{-1.0/4.0, 2.0/4.0 , -1.0/4.0}};

	float L3TS3[3][3] = { {-1.0/12.0, 2.0/12.0 , -1.0/12.0},
						{-2.0/12.0, 4.0/12.0 , -2.0/12.0},
						{-1.0/12.0, 2.0/12.0 , -1.0/12.0}};

	float S3TL3[3][3] = { {-1.0/12.0, -2.0/12.0 , -1.0/12.0},
						{2.0/12.0, 4.0/12.0 , 2.0/12.0},
						{-1.0/12.0, -2.0/12.0 , -1.0/12.0}};

	float L3TL3[3][3] = { {1.0/36.0, 2.0/36.0 , 1.0/36.0},
						{2.0/36.0, 4.0/36.0 , 2.0/36.0},
						{1.0/36.0, 2.0/36.0 , 1.0/36.0}};	

	float S3TS3[3][3] = { {1.0/4.0, -2.0/4.0 , 1.0/4.0},
						{-2.0/4.0, 4.0/4.0 , -2.0/4.0},
						{1.0/4.0, -2.0/4.0 , 1.0/4.0}};	

	//apply the 9 filters to each pixel of the image:
	Imagedata_nine.push_back(FilterOperation(Imagedata_average_Extend, R_Size, C_Size, L3TE3));
	Imagedata_nine.push_back(FilterOperation(Imagedata_average_Extend, R_Size, C_Size, S3TE3));
	Imagedata_nine.push_back(FilterOperation(Imagedata_average_Extend, R_Size, C_Size, E3TE3));
	Imagedata_nine.push_back(FilterOperation(Imagedata_average_Extend, R_Size, C_Size, E3TL3));
	Imagedata_nine.push_back(FilterOperation(Imagedata_average_Extend, R_Size, C_Size, E3TS3));
	Imagedata_nine.push_back(FilterOperation(Imagedata_average_Extend, R_Size, C_Size, L3TS3));
	Imagedata_nine.push_back(FilterOperation(Imagedata_average_Extend, R_Size, C_Size, S3TL3));
	Imagedata_nine.push_back(FilterOperation(Imagedata_average_Extend, R_Size, C_Size, L3TL3));
	Imagedata_nine.push_back(FilterOperation(Imagedata_average_Extend, R_Size, C_Size, S3TS3));				
	

	//calculate the average energy of each pixel

	//first step is to extend the filter output images by 15 pixels
	#if 1
	vector<vector<vector<float> > >Imagedata_nine_extended;
	vector<vector<vector<float> > >Imagedata_nine_average_energy;
	int Extend2 = 45;
	for( i = 0; i < 9 ; i++)
	{
		Imagedata_nine_extended.push_back(Boundary_Extension_float(Imagedata_nine[i], R_Size, C_Size, Extend2));
		
	}
	cout<<endl;
	cout<<Imagedata_nine_extended.size();
	cout<<endl;
	cout<<Imagedata_nine_extended.front().size();
	cout<<endl;
	cout<<Imagedata_nine_extended.front().front().size();
	#endif

	//get feature vector which is of size numberofpixels x 9

	for( i = 0; i < 9 ; i++)
	{
		Imagedata_nine_average_energy.push_back(Average_Image (Imagedata_nine_extended[i],R_Size ,C_Size));
	}
	cout<<endl;
	cout<<Imagedata_nine_average_energy.size();
	cout<<endl;
	cout<<Imagedata_nine_average_energy.front().size();
	cout<<endl;
	cout<<Imagedata_nine_average_energy.front().front().size();

	vector<float> feat_vec_Per_Pixel(number_of_feats , 0.0);
	vector<vector<float> >feat_vec(R_Size * C_Size , feat_vec_Per_Pixel);

	int k;

	for( i = 0 ; i < R_Size ; i++)
	{
		for( j = 0 ; j < C_Size ; j++)
		{
			for( k = 0; k < number_of_feats ; k++)
			{
				feat_vec[i * C_Size + j][k] = Imagedata_nine_average_energy[k][i][j];

			}
		}
	}



	//k means algorithm
	int *cluster;
	int K = 6;
	cluster = kmeans(feat_vec , K);
	vector<unsigned char> Out_Imagedata_Per_Pixel_final(C_Size , 0);
	vector<vector<unsigned char> >Out_Imagedata_final(R_Size , Out_Imagedata_Per_Pixel_final);
	int q;
	for( i = 0 ; i < R_Size ; i++)
	{
		for( j = 0 ; j < C_Size ; j++)
		{
			//for displaying the output classification
			q = cluster[i * C_Size + j];
			if ( q == 0)
			{
				Out_Imagedata_final[i][j] = 0;
			}
			else if ( q == 1)
			{
				Out_Imagedata_final[i][j] = 51;
			}
			else if ( q == 2)
			{
				Out_Imagedata_final[i][j] = 102;
			}
			else if ( q == 3)
			{
				Out_Imagedata_final[i][j] = 153;
			}
			else if ( q == 4)
			{
				Out_Imagedata_final[i][j] = 204;
			}
			else if ( q == 5)
			{
				Out_Imagedata_final[i][j] = 255;
			}
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

//get a 2d image vector and calculate the average energy along the window size 30x30
vector<vector<float> > Average_Image (vector<vector<float> > &Imagedata, int R_Size , int C_Size)
{
	vector<float> Out_Imagedata_Per_Pixel(C_Size , 0.0);
	vector<vector<float> >Out_Imagedata(R_Size , Out_Imagedata_Per_Pixel);

	int i,j,x,y;
	double pixel_sum;
	for(i = 15; i < R_Size + 15 ; i++)
	{
		for( j = 15; j < C_Size + 15 ; j++)
		{
			pixel_sum = 0.0;
			for(x = i - 15 ; x <= i+15 ; x++)
			{
				for(y = j - 15 ; y <= j+15 ; y++)
				{
					pixel_sum += pow((float)(Imagedata[x][y]), 2);
				}
			}
			Out_Imagedata[i - 15][j - 15] = (float)pixel_sum / (float)(15 * 15);
		}
	}

	return Out_Imagedata;

}

int * kmeans(vector<vector<float> >&feat_vec, int K)
{
	//K = 4;
	//const int number_of_features = 9;
	//const int number_of_data_points = 12;
	float new_centroid[6][number_of_feats];
	//int class = 1;
	int count1, count2;
	int i,j,k;

	//vector<vector<vector<float> > > centroid;
	vector<float> centroid_per_data_point(number_of_data_points , 0.0);
	vector<vector<float> >initial_centroid(number_of_feats , centroid_per_data_point);

	printf("Inital centroid: ");
	for( i = 0, j = 0; j < number_of_data_points ; j++)
	{
		//if( j == 40158 || j == 36460 || j == 108160 || j == 115050 || j == 174600 || j == 171490)
		if( j == 1000 || j == 15000 || j == 100000 || j == 115050 || j == 174600 || j == 171490)
		{
			for( k = 0; k < number_of_feats ; k++)
			{
				
					new_centroid[i][k] = feat_vec[j][k];
					//printf("%0.2f ", new_centroid[i][k]);

			}
			i++;
		}
		//printf("\n");
	}

	//manual selection of initial centroids is done
	//float eucledian_distance[K];
	float distance = 0.0;
	//float *min;
	float min;
	int cluster_initial[number_of_data_points];
	static int cluster_final[number_of_data_points];
	int iterations = 0;
	//first iteration
	
	//next iterations:
	//find the new centoids
	float new_sum[number_of_feats] = {0.0};
	
	int cluster_prev[number_of_data_points];
	

	while(iterations < 500)
	{
		iterations++;

		//got the new centroids. now new centroids is old initital_centroid
		for( i = 0 ; i < number_of_data_points ; i++)
		{
			for( k = 0 ; k < K ; k++)
			{
				distance = 0.0;
				for( j = 0; j < number_of_feats ; j++)
				{
					distance += pow( new_centroid[k][j] - feat_vec[i][j] , 2);
				} 
				if(k == 0)
				{
					min = distance;
					//cluster_final[i] = 0;
				}
				//eucledian_distance[k] = distance;
				if(distance <= min)
				{
					min = distance;
					cluster_final[i] = k;
				}
			}
		}
		count2 = 0;
		

		if((memcmp(cluster_prev, cluster_final, sizeof(cluster_final)) == 0))

		{
			break;
		}
		else
		{

			for( k = 0; k < K; k++)
			{
				count1 = 0;
				memset(new_sum, 0, sizeof(float) * number_of_feats);
				for( i = 0; i < number_of_data_points ; i++)
				{

					if(cluster_final[i] == k)
					{
						count1++;
						for(j = 0; j < number_of_feats ; j++)
						{
							new_sum[j] +=	feat_vec[i][j];
						}
					}
				}
				//cout<<endl;
				for( j = 0; j < number_of_feats ; j++)
				{
					new_centroid[k][j] = new_sum[j] / count1;
					//cout<<new_centroid[k][j]<<'\t';
				}
				cout<<endl;//<<"k "<<k<<" count1 : "<<count1<<endl;

				
			}



			for( i = 0; i < number_of_data_points ; i++)
			{
				cluster_prev[i] = cluster_final[i];
			}
		}
	}
	cout<<endl;
	
	cout<<"Number of iterations"<<iterations<<endl;

	return cluster_final;

}

#if 0

//function get rsize csize input.str 
vector <float> Oper(string filename)
{
	int R_Size = 128;
	int C_Size = 128;
	vector<vector<unsigned char> >Imagedata;//vector for the texture image

	Imagedata= Image_Input(filename.c_str(), R_Size, C_Size);

	//now calculate the average of all the pixels in the image
	float average_original;
	average_original = CalculateAverage(Imagedata, R_Size, C_Size);
	//cout<<average_original<<endl;

	vector<float> Imagedata_Per_Pixel1(C_Size , 0.0);
	vector<vector<float> >Imagedata1(R_Size , Imagedata_Per_Pixel1);

	int i,j;
	for( i = 0; i < R_Size ; i++)
	{
		for( j = 0; j < C_Size ; j++)
		{
			Imagedata1[i][j] = Imagedata[i][j];// - average_original;
		}
	}

	//extend the image
	int Extend = 2;
	int R_Extend = R_Size + 2 * Extend;
	int C_Extend = C_Size + 2 * Extend;

	vector<float> Out_Imagedata_Per_Pixel_Extend(C_Extend , 0.0);
	vector<vector<float> >Out_Imagedata_Extend(R_Extend , Out_Imagedata_Per_Pixel_Extend);

	Out_Imagedata_Extend = Boundary_Extension(Imagedata1, R_Size, C_Size, Extend);//extended image
	//cout<<"Boundary extended!"<<endl;

	//now calculate the feature vectors using laws filter
	float E5tS5[5][5] = { {1.0/24.0, 0.0 , -2.0/24.0, 0.0, 1.0/24.0},
					{2.0/24.0, 0.0 , -4.0/24.0, 0.0, 2.0/24.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{-2.0/24.0, 0.0, 4.0/24.0, 0.0, -2.0/24.0},
					{-1.0/24.0, 0.0 , 2.0/24.0, 0.0, -1.0/24.0}};

	float S5tE5[5][5] = { {1.0/24.0, 2.0/24.0 , 0.0, -2.0/24.0, -1.0/24.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{-2.0/24.0, -4.0/24.0, 0.0, 4.0/24.0, 2.0/24.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{1.0/24.0, 2.0/24.0 , 0.0, -2.0/24.0, -1.0/24.0}};

	float S5tW5[5][5] = { {1.0/24.0, -2.0/24.0 , 0.0, 2.0/24.0, -1.0/24.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{-2.0/24.0, 4.0/24.0, 0.0, -4.0/24.0, 2.0/24.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{1.0/24.0, -2.0/24.0 , 0.0, 2.0/24.0, -1.0/24.0}};

	float W5tS5[5][5] = { {1.0/24.0, 0.0 , -2.0/24.0, 0.0, 1.0/24.0},
					{-2.0/24.0, 0.0 , 4.0/24.0, 0.0, -2.0/24.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{2.0/24.0, 0.0, -4.0/24.0, 0.0, 2.0/24.0},
					{-1.0/24.0, 0.0 , 2.0/24.0, 0.0, -1.0/24.0}};

	float E5tW5[5][5]= { {1.0/36.0, -2.0/36.0, 0.0, 2.0/36.0, -1.0/36.0},
					{2.0/36.0, -4.0/36.0, 0.0 , 4.0/36.0, -2.0/36.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{-2.0/36.0, 4.0/36.0, 0.0 , -4.0/36.0, 2.0/36.0},
					{-1.0/36.0, 2.0/36.0, 0.0, -2.0/36.0, 1.0/36.0}};

	float W5tE5[5][5]= { {1.0/36.0, 2.0/36.0, 0.0, -2.0/36.0, -1.0/36.0},
					{-2.0/36.0, -4.0/36.0, 0.0 , 4.0/36.0, 2.0/36.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{2.0/36.0, 4.0/36.0, 0.0 , -4.0/36.0, -2.0/36.0},
					{-1.0/36.0, -2.0/36.0, 0.0, 2.0/36.0, 1.0/36.0}};

	float E5tE5[5][5]={ {1.0/36.0, 2.0/36.0, 0.0, -2.0/36.0, -1.0/36.0},
					{2.0/36.0, 4.0/36.0, 0.0 , -4.0/36.0, -2.0/36.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{-2.0/36.0, -4.0/36.0, 0.0 , 4.0/36.0, 2.0/36.0},
					{-1.0/36.0, -2.0/36.0, 0.0, 2.0/36.0, 1.0/36.0}};

	float S5tS5[5][5]={ {1.0/16.0, 0.0 , -2.0/16.0, 0.0, 1.0/16.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{-2.0/16.0, 0.0, 4.0/16.0, 0.0, -2.0/16.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{1.0/16.0, 0.0 , -2.0/16.0, 0.0, 1.0/16.0}};

	float W5tW5[5][5]={ {1.0/36.0, -2.0/36.0, 0.0, 2.0/36.0, -1.0/36.0},
					{-2.0/36.0, 4.0/36.0, 0.0 , -4.0/36.0, 2.0/36.0},
					{0.0, 0.0, 0.0, 0.0, 0.0},
					{2.0/36.0, -4.0/36.0, 0.0 , 4.0/36.0, -2.0/36.0},
					{-1.0/36.0, 2.0/36.0, 0.0, -2.0/36.0, 1.0/36.0}};

	//float average1[10];

	vector <float> average1;

	average1.push_back(FilterOperation(Out_Imagedata_Extend, R_Size, C_Size, E5tS5));
	average1.push_back(FilterOperation(Out_Imagedata_Extend, R_Size, C_Size, S5tE5));
	average1.push_back(FilterOperation(Out_Imagedata_Extend, R_Size, C_Size, S5tW5));
	average1.push_back(FilterOperation(Out_Imagedata_Extend, R_Size, C_Size, W5tS5));
	average1.push_back(FilterOperation(Out_Imagedata_Extend, R_Size, C_Size, E5tW5));
	average1.push_back(FilterOperation(Out_Imagedata_Extend, R_Size, C_Size, W5tE5));
	average1.push_back(FilterOperation(Out_Imagedata_Extend, R_Size, C_Size, E5tE5));
	average1.push_back(FilterOperation(Out_Imagedata_Extend, R_Size, C_Size, S5tS5));
	average1.push_back(FilterOperation(Out_Imagedata_Extend, R_Size, C_Size, W5tW5));
	//average1[9] = average_original;
/*
	for( i = 0; i < 10; i++)
	{
		cout<<average1[i]<<"    ";
	}
	cout<<endl;
	*/
	cout<<endl;
	return average1;



}
#endif 
//calculate the convolutional value of each pixel and calculate the mean for each image:input: image, Rsize, Csize, filter
vector<vector<float> > FilterOperation(vector<vector<float> > &Imagedata, int R_Size, int C_Size, float filter[3][3])
{

	vector<float> Out_Imagedata_Per_Pixel(C_Size , 0.0);
	vector<vector<float> >Out_Imagedata(R_Size , Out_Imagedata_Per_Pixel);

	double sum = 0.0;
	float average;
	float pixel_sum;
	double d = 0.0;

	int i,j,u,v,x,y;

	for(i = 1; i < R_Size + 1 ; i++)
	{
		for( j = 1; j < C_Size + 1 ; j++)
		{
			pixel_sum = 0.0;
			for(x = i-1 , u = 0; x <= i+1 ; x++, u++)
			{
				for(y = j-1 , v = 0;y <= j+1 ; y++, v++)
				{
					pixel_sum += (filter[u][v] * (float)(Imagedata[x][y]));
				}
			}
			Out_Imagedata[i - 1][j - 1] = (float)pixel_sum;
			//cout<<pixel_sum<<endl;
			//d = (fabs)pixel_sum;
			//sum += pixel_sum;
		}
	}
	
	return Out_Imagedata;
	//return average;

}


//calculate average of all pixels: vector, rsize, csize. return:average
float CalculateAverage(vector<vector<unsigned char> > Imagedata, int R_Size, int C_Size)
{
	float average;
	double sum = 0;
	int i,j;

	for( i = 0; i < R_Size ; i++)
	{
		for( j = 0; j < C_Size ; j++)
		{
			sum += Imagedata[i][j];
		}
	}
	average = sum / (float)(R_Size * C_Size);
	return average;
}


vector<vector<unsigned char> > Boundary_Extension(vector<vector<unsigned char> > Imagedata,int R_Size,int C_Size, int Extend)
{
	int i,j;
	//int Extend=2;
	int R_Extend = R_Size + 2*Extend;
	int C_Extend = C_Size + 2*Extend;
	vector<unsigned char> Out_Imagedata_Per_Row(C_Extend,0);
	vector<vector<unsigned char> >Out_Imagedata(R_Extend,Out_Imagedata_Per_Row);
	//cout<<"ggg";
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
			Out_Imagedata[i][j] = Imagedata[Extend - i][j - Extend];
			Out_Imagedata[R_Extend - 1 - i][j] = Imagedata[R_Size - 1 - Extend + i][j - Extend];
		}
	}

	for( i = Extend; i < R_Extend - Extend ; i++)
	{
		for( j = 0; j < Extend; j++)
		{
			Out_Imagedata[i][j] = Imagedata[i - Extend][Extend - j];
			Out_Imagedata[i][C_Extend - j - 1] = Imagedata[i - Extend][C_Size - 1 - Extend + j];
		}
	}

	for( i = 0 ; i < Extend ; i++)
	{
		for( j = 0 ; j < Extend ; j++)
		{
			Out_Imagedata[i][j] = Imagedata[Extend - i][Extend - j];
			Out_Imagedata[R_Extend - i - 1][j] = Imagedata[R_Size - Extend + i - 1][Extend - j];
			Out_Imagedata[i][C_Extend - j - 1] = Imagedata[Extend - i][C_Size - Extend + j - 1];
			Out_Imagedata[R_Extend - i - 1][C_Extend - j - 1] = Imagedata[R_Size - Extend + i - 1][C_Size - Extend + j - 1];
		}
	}
	
	return Out_Imagedata;
}

vector<vector<float> > Boundary_Extension_float(vector<vector<float> > Imagedata,int R_Size,int C_Size, int Extend)
{
	int i,j;
	//int Extend=2;
	int R_Extend = R_Size + 2*Extend;
	int C_Extend = C_Size + 2*Extend;
	vector<float> Out_Imagedata_Per_Row(C_Extend,0.0);
	vector<vector<float> >Out_Imagedata(R_Extend,Out_Imagedata_Per_Row);
	//cout<<"ggg";
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
			Out_Imagedata[i][j] = Imagedata[Extend - i][j - Extend];
			Out_Imagedata[R_Extend - 1 - i][j] = Imagedata[R_Size - 1 - Extend + i][j - Extend];
		}
	}

	for( i = Extend; i < R_Extend - Extend ; i++)
	{
		for( j = 0; j < Extend; j++)
		{
			Out_Imagedata[i][j] = Imagedata[i - Extend][Extend - j];
			Out_Imagedata[i][C_Extend - j - 1] = Imagedata[i - Extend][C_Size - 1 - Extend + j];
		}
	}

	for( i = 0 ; i < Extend ; i++)
	{
		for( j = 0 ; j < Extend ; j++)
		{
			Out_Imagedata[i][j] = Imagedata[Extend - i][Extend - j];
			Out_Imagedata[R_Extend - i - 1][j] = Imagedata[R_Size - Extend + i - 1][Extend - j];
			Out_Imagedata[i][C_Extend - j - 1] = Imagedata[Extend - i][C_Size - Extend + j - 1];
			Out_Imagedata[R_Extend - i - 1][C_Extend - j - 1] = Imagedata[R_Size - Extend + i - 1][C_Size - Extend + j - 1];
		}
	}
	
	return Out_Imagedata;
}





vector<vector<unsigned char> > Image_Input(const char* filename, int R_Size, int C_Size) 	
{
	FILE *file;
	//declase file buffer 
	unsigned char *Imagebuffer = (unsigned char*) calloc (R_Size*C_Size, sizeof(unsigned char));
	file=fopen(filename,"rb");
	//read from the file
	fread(Imagebuffer, sizeof(unsigned char), R_Size*C_Size*sizeof(unsigned char), file);
	fclose(file);

	vector<vector<unsigned char> >Imagedata;

	int i,j;
	//write the contents into a vector
	for(i=0;i<R_Size;i++)
	{
		vector<unsigned char> Imagedata_Per_Pixel;
		for(j=0;j<C_Size;j++)
		{
			Imagedata_Per_Pixel.push_back(*(Imagebuffer+ (i*C_Size+j)));
		}
		Imagedata.push_back(Imagedata_Per_Pixel);
	}

	return Imagedata;
}




