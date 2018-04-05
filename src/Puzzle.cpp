//////////////////////////////////////
///////ANANYA SINGH///////////////////
///////ananyasingh1216@gmail.com//////
//////////////////////////////////////
///////04/5/18///////////////////////
//////////////////////////////////////

//Program name: puzzle
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include<vector>
#include<fstream>
#include "iostring.h"
#include<math.h>
#include<string.h>
#include<set>

using namespace std;

vector<vector<unsigned char> > ConvertToBinary(vector<vector<vector<unsigned char> > >Imagedata,int R_Size, int C_Size);
vector<vector<unsigned char> > Perform_Rect(vector<vector<unsigned char> > Imagedata,int R_Size,int C_Size, int BG, int FG);
void Count_Rect(vector<vector<unsigned char> > Imagedata, int label_track[][372], int R_Size,int C_Size);
int Compare_Puzzle(int label_track[][372], int R_Size, int C_Size, int p1, int p2);
int Compare_2Pieces(vector<vector<vector<unsigned char> > >Label_data, int p1, int p2);

unsigned char checking_corners[]= {0xc1,0x70, 0x1c, 0x07, 0xF1, 0x1F};//if these do nothing =5
int main( )

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel=1;
	int R_Size = 372;
	int C_Size = 372;
	string input1= "board.raw";
	//string input2="left.raw";
	//string input3="right.raw";
	string output1="board_rectangle.raw";
	string output2="labels.raw";
	
	vector<vector<vector<unsigned char> > >Imagedata;

	Imagedata= Image_Input(input1.c_str(), R_Size, C_Size, BytesPerPixel);
	
	//Declare the output Image data for 2D
	vector<unsigned char> Out_Imagedata_Per_RowB(C_Size,0);
	vector<vector<unsigned char> >Out_ImagedataB(R_Size,Out_Imagedata_Per_RowB);//create the binary image
	
	///////////////////////////////////////////
	//Write the Image processing code here

	//Step 1 convert to binary picture:
	Out_ImagedataB=ConvertToBinary(Imagedata,R_Size,C_Size);//here 255 is white and 0 is black;
	int BG=255;//background is white
	int FG=0;//foreground is black;
	int i,j;
	cout<<endl<<"binarised";
	vector<unsigned char> Final_Out_Imagedata_Per_Row(C_Size,BG);
	vector<vector<unsigned char> >Final_Out_Imagedata(R_Size,Final_Out_Imagedata_Per_Row);//output of rectangular function

	vector<unsigned char> Final_Out_Imagedata_Per_RowC(C_Size,BG);
	vector<vector<unsigned char> >Final_Out_Imagedata_Copy(R_Size,Final_Out_Imagedata_Per_RowC);//copy of rectangular function
	int count=0;
	cout<<endl;
	cout<<"count set";
	do//get the rectangles!
	{
		if(count==0)
		{
			//cout<<"first time";
			Final_Out_Imagedata=Perform_Rect(Out_ImagedataB,R_Size,C_Size,BG,FG);//perform morphology function

		}

		if(count)//copy the previous copy after the first iteration
		{
			//cout<<endl<<"copying";
			for(i=0;i<R_Size;i++)
			{
				for(j=0;j<C_Size;j++)
				{
					Final_Out_Imagedata_Copy[i][j]=Final_Out_Imagedata[i][j];
				}
			}
			Final_Out_Imagedata=Perform_Rect(Final_Out_Imagedata_Copy,R_Size,C_Size,BG,FG);

		}
		//number of iterations? check if previous image is same as new on. if yes then stop.
		count++;

		if((Final_Out_Imagedata==Final_Out_Imagedata_Copy) && count>1)
		{
			cout<<endl<<"same!";
			break;
		}
	}while(1);

	//now we want to label each rectangle obtained
	int label_track[372][372]={0};

	vector<unsigned char> label_row(C_Size,BG);
	vector<vector<unsigned char> >label_image(R_Size,label_row);

	Count_Rect(Final_Out_Imagedata, label_track, R_Size, C_Size);
	
	for(i=0;i<R_Size;i++)
	{
		//cout<<endl;
		for(j=0;j<C_Size;j++)
		{
			//cout<<" "<<label_track[i][j];
			if(label_track[i][j]==1)
			{
				label_image[i][j]=Out_ImagedataB[i][j];
			}

		}
	} 
	
	//Now we have an array which shows where all the jigsaw puzzles are. Now we extract all of them.
	//we want to get the jigsaw piece by providing the piece number and binary image
	//first we have to find how many pieces are there
	int number=0;
	int label;
	for (i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			label=label_track[i][j];
			if(label)
			{
				if(label>number)
					number++;
			}
		}
	}
	cout<<"Number of jigsaw puzzles are: "<<number<<endl;//that it 16
	//now we want to create a 3d vector. the first vector will contain the label. second and thrid will have corresponding jigsaw pieces
	int l_counter=0;
	int l_rows,l_rowe,l_cols,l_cole;
	int k;
	vector<vector<vector<unsigned char> > >Label_data;
	int x,y,z;
	int l_label=0;
	for(k=0;k<number;k++)
	{
		l_label=k+1;
		l_counter=0;
		l_rowe=0;l_cole=0;l_cols=0;l_rows=0;
		for(i=1;i<R_Size;i++)
		{
			for(j=1;j<C_Size;j++)
			{
				if(label_track[i][j]==l_label && label_track[i][j-1]==0 && label_track[i-1][j]==0)//corner point 
				{
					l_rows=i;
					l_cols=j;
				}
				if(label_track[i][j]==l_label && label_track[i][j+1]==0 && label_track[i-1][j]==0)//corner point 
				{
					//l_rows=i;
					l_cole=j;
				}
				if(label_track[i][j]==l_label && label_track[i][j-1]==0 && label_track[i+1][j]==0)//corner point 
				{
					l_rowe=i;
					//l_cols=j;
				}
				if(label_track[i][j]==l_label && label_track[i][j+1]==0 && label_track[i+1][j]==0)//corner point 
				{
					//l_rows=i;
					l_cole=j;
				}
				if(label_track[i][j]==l_label)
				{
					l_counter++;
				}
			}
		}
		//cout<<"For label "<<k<<" 1 st point is "<<l_cols<<" "<<l_rows<<" last point is "<<l_cole<<" "<<l_rowe<<endl;
		//now we have all corner point for each label. now we have to pass the pixels from that point to the last
		
		int n_rows=l_rowe - l_rows;
		int n_cols = l_cole - l_cols;
		
		vector<vector<unsigned char> >Label_data_per_row;
		for(i=0, y= l_rows ;i<= n_rows; i++, y++)
		{
			vector<unsigned char> Label_data_per_col;
			for(j=0, x = l_cols; j<= n_cols; j++, x++)
			{
				Label_data_per_col.push_back(Out_ImagedataB[y][x]);
			}
			Label_data_per_row.push_back(Label_data_per_col);	
		}
		Label_data.push_back(Label_data_per_row);
	}

	int same=0;
	int unique=0;
	vector <int> n_unique;
	//int same_piece=0;
	for(i=1;i<number;i++)
	{
		for(j=i+1;j<=number;j++)
		{
			same= Compare_Puzzle(label_track, R_Size, C_Size, i, j);
			if(same)
			{
				//cout<<i<<" "<<j<<" are same!"<<endl;
				//if pieces are of same area then we compare the shapes
				int r= Compare_2Pieces(Label_data, i, j);
				if(r)
				{
					cout<<i<<" "<<j<<" are same!"<<endl;
					unique++;
					n_unique.push_back(i);
					n_unique.push_back(j);
				}
			}
			 
				//cout<<i<<" "<<j<<" are  not same!"<<endl;
			
		}
	}
	int n_u= n_unique.size();
	vector <int> final;
	int f;
	for ( i = 0; i != n_u; i++) 
	{ // Go through the list once.      
	    for ( j = 0; j != i; j++)
	    { // And check if this number has already appeared in the list:
	        if((i != j) && (n_unique[j] == n_unique[i]))
	        { // A duplicate number!        
	            f++; 
	            break;
	        }
	    }
    }

    cout << endl << n_u - f << " unique pieces!" << endl;

			
	

	//output the 2d image
	unsigned char *Out_Imagebuffer = (unsigned char*) calloc ((R_Size)*(C_Size)*BytesPerPixel*sizeof(unsigned char), sizeof(unsigned char));
	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			*(Out_Imagebuffer + (i*(C_Size) + j)) = Final_Out_Imagedata[i][j];
		}
	}


	// Write the output buffer to the output file

	if (!(file=fopen(output1.c_str(),"wb"))) {
		cout << "Cannot open file: " ;//<< argv[2] << endl;
		exit(1);
	}
	fwrite(Out_Imagebuffer, sizeof(unsigned char), (R_Size)*(C_Size)*BytesPerPixel, file);
	fclose(file);

	unsigned char *Out_Imagebuffer1 = (unsigned char*) calloc ((R_Size)*(C_Size)*BytesPerPixel*sizeof(unsigned char), sizeof(unsigned char));
	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			*(Out_Imagebuffer1 + (i*(C_Size) + j)) = label_image[i][j];
		}
	}

	// Write the output buffer to the output file

	if (!(file=fopen(output2.c_str(),"wb"))) {
		cout << "Cannot open file: " ;//<< argv[2] << endl;
		exit(1);
	}
	fwrite(Out_Imagebuffer1, sizeof(unsigned char), (R_Size)*(C_Size)*BytesPerPixel, file);
	fclose(file);

	

	return 0;
}
//function to compare the two images by rotation etc
int Compare_2Pieces(vector<vector<vector<unsigned char> > >Label_data, int p1, int p2)
{
	int i,j,k;
	int l1=p1-1;
	int l2=p2-1;
	int c1=Label_data[l1][0].size();
	int r1= Label_data[l1].size();//f0r 0 degrees rotation
	int c2=Label_data[l2][0].size();
	int r2= Label_data[l2].size();//f0r 0 degrees rotation
	int same=0;
	float perc;

	if(r1==c2 && c1==r2)//rotation by 1 and 3 times of image 2
	{
		same=0;
		for(k=0;k<r1;k++)//rotation by 1 time
		{
			//unsigned char arr1[c1];
			//unsigned char arr2[c1];
			for(i=0;i<c1;i++)
			{
				if((Label_data[l1][k][i]== 0 && Label_data[l2][c1-i-1][k]== 0 )|| (Label_data[l1][k][i]== 255 && Label_data[l2][c1-i-1][k]== 255))
					same++;
			}
		}
		perc= (float)same/(float)(r1*c1);
		
		//cout<<"Percentage of similarity between "<< p1<<" and "<< p2<<" : "<<perc<<endl;
		if(perc>0.97)
		{
			cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
			return 1;
		}
		same=0;
		for(k=0;k<r1;k++)//rotation 3 times
		{
			//unsigned char arr1[c1];
			//unsigned char arr2[c1];
			for(i=0;i<c1;i++)
			{
				if((Label_data[l1][k][i]== 0 && Label_data[l2][c1-i-1][r1-k-1]== 0)||(Label_data[l1][k][i]== 255 && Label_data[l2][c1-i-1][r1-k-1]== 255))
					same++;
			}
		}
		perc= (float)same/(float)(r1*c1);
		
		//cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
		if(perc>0.97)
		{
			cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
			return 1;
		}
		same=0;
		for(k=0;k<r1;k++)//flip it
		{
			//unsigned char arr1[c1];
			//unsigned char arr2[c1];
			for(i=0;i<c1;i++)
			{
				if((Label_data[l1][k][i]== 0 && Label_data[l2][i][r1-k-1]== 0)||(Label_data[l1][k][i]== 255 && Label_data[l2][i][r1-k-1]== 255))
					same++;
			}
		}
		perc= (float)same/(float)(r1*c1);
		
		//cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
		if(perc>0.97)
		{
			cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
			return 1;
		}
		same=0;
		for(k=0;k<r1;k++)//flip it again
		{
			//unsigned char arr1[c1];
			//unsigned char arr2[c1];
			for(i=0;i<c1;i++)
			{
				if((Label_data[l1][k][i]==0 && Label_data[l2][i][k]== 0)||(Label_data[l1][k][i]==255 && Label_data[l2][i][k]== 255))
					same++;
			}
		}
		perc= (float)same/(float)(r1*c1);
		
		//cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
		if(perc>0.97)
		{
			cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
			return 1;
		}
		same=0;
	}
	if(r1==r2 && c1==c2)
	{
		same=0;
		for(k=0;k<r1;k++)//no rotation
		{
			for(i=0;i<c1;i++)
			{
				if((Label_data[l1][k][i]== 0 && Label_data[l2][k][i]==0)||(Label_data[l1][k][i]== 255 && Label_data[l2][k][i]==255))
				{
					same++;
				}
			}
		}
		perc= (float)same/(float)(r1*c1);
		
		//cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
		if(perc>0.97)
		{
			cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
			return 1;
		}
		same=0;
		for(k=0;k<r1;k++)//1 rotation
		{
			for(i=0;i<c1;i++)
			{
				if((Label_data[l1][k][i]== 0 && Label_data[l2][r1-k-1][i]==0)||(Label_data[l1][k][i]== 255 && Label_data[l2][r1-k-1][i]==255))
				{
					same++;
				}
			}

		}
		perc= (float)same/(float)(r1*c1);

		//cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
		if(perc>0.97)
		{
			cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
			return 1;
		}
		same=0;
		for(k=0;k<r1;k++)//1 flip
		{
			for(i=0;i<c1;i++)
			{
				if((Label_data[l1][k][i]== 0 && Label_data[l2][r1-k-1][c1-i-1]== 0)||(Label_data[l1][k][i]== 255 && Label_data[l2][r1-k-1][c1-i-1]== 255))
				{
					same++;
				}
			}

		}
		perc= (float)same/(float)(r1*c1);
		//cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
		if(perc>0.97)
		{
			cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
			return 1;
		}
		same=0;
		for(k=0;k<r1;k++)//1 flip
		{
			for(i=0;i<c1;i++)
			{
				if((Label_data[l1][k][i]== 0 && Label_data[l2][k][c1-i-1]==0)||(Label_data[l1][k][i]== 255 && Label_data[l2][k][c1-i-1]==255))
				{
					same++;
				}
			}

		}
		perc= (float)same/(float)(r1*c1);
		//cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
		if(perc>0.97)
		{
			cout<<"Percentage of similarity: "<< p1<<" and "<< p2<<" : "<<perc<<endl;
			return 1;
		}
		same=0;
	}
		
	return 0;
}
//function to obtain the same images
int Compare_Puzzle(int label_track[][372], int R_Size, int C_Size, int p1, int p2)
{
	int i,j;
	int p1_count=0;
	int p2_count=0;
	//when we meet the first label get the coordinates
	int p1_r,p1_c,p2_r,p2_c;
	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			if(label_track[i][j]==p1)
			{
				p1_count++;
				if(p1_count)
				{
					p1_r=i;
					p1_c=j;
				}
			}
			if(label_track[i][j]==p2)
			{
				p2_count++;
				if(p2_count)
				{
					p2_r=i;
					p2_c=j;
				}
			}
		}
	}

	if(p1_count==p2_count)//area is the same then continue:
	{
		//now we extract the twoimages and compare
		//cout<<p1_r<<" "<<p1_c<<" "<<p2_r<<" "<<p2_c<<" ";
		return 1;
	}
	else 
		return 0;
	
}
	
//function to label each rectangle
void Count_Rect(vector<vector<unsigned char> > Imagedata,int label_track[][372],int R_Size,int C_Size)
{
	//int label_track[372][372]={0};
	int i,j;
	int label=0;
	int FG=0;
	int BG=255;
	int label_prev=0;
	for(i=1;i<R_Size-1;i++)
	{
		for(j=1;j<C_Size-1;j++)
		{
			if(Imagedata[i][j]==FG)
			{
				 if(Imagedata[i][j-1]==BG && Imagedata[i-1][j]==FG)//if no left
				{
					label=label_track[i-1][j];//take label value from up
					label_track[i][j]=label;
				}
				else if(Imagedata[i][j-1]==FG && Imagedata[i-1][j]== BG)
				{
					label=label_track[i][j-1];//take label value from left pixel
					label_track[i][j]=label;
				}
				else if(Imagedata[i][j-1]==FG && Imagedata[i-1][j]== FG)
				{
					label=label_track[i][j-1];//take label value from left pixel
					label_track[i][j]=label;
				}
				
				if(Imagedata[i][j-1]==BG && Imagedata[i-1][j]==BG)//if left and up are BG
				{
					label_prev++;
					//label++;
					label_track[i][j]=label_prev;
					//we've reached a new rectangle
				}
				
				
				
			}
		}
	}
}


//function to dilate in a rectangular fashion
vector<vector<unsigned char> > Perform_Rect(vector<vector<unsigned char> > Imagedata,int R_Size,int C_Size, int BG, int FG)
{
	int i,j,w,u,v;
	int Extend=2;
	unsigned char pixel, pixelstack,pixel_neighbour;
	vector<unsigned char> Out_Imagedata_Per_Row(C_Size,0);
	vector<vector<unsigned char> >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);
	//to work with bits
	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			if(Imagedata[i][j]==BG)
			{
				Imagedata[i][j]=0;
				Out_Imagedata[i][j]=0;//copy the input to the output to perform manipulations
			}
			else 
			{
				Imagedata[i][j]=255;
				Out_Imagedata[i][j]=255;
			}
		}
	}
	

	//whichever pixel is a hit has value 255
	int corner=0;
	for(i=1;i<R_Size-1;i++)
	{
		for(j=1;j<C_Size-1;j++)
		{
			pixel=Imagedata[i][j];
			pixelstack=0;
			corner=0;
			if(pixel==255)//step 1: if hit make the pixel stack to check for corners
			{
				pixel_neighbour=Imagedata[i][j+1];//X0
				pixelstack=pixelstack>>1;
				if(pixel_neighbour==255)
				{
					pixelstack=pixelstack|(0x80);
				}
				pixel_neighbour=Imagedata[i-1][j+1];//X1
				pixelstack=pixelstack>>1;
				if(pixel_neighbour==255)
				{
					pixelstack=pixelstack|(0x80);
				}
				
				pixel_neighbour=Imagedata[i-1][j];//X2
				pixelstack=pixelstack>>1;
				if(pixel_neighbour==255)
				{
					pixelstack=pixelstack|(0x80);
				}
				
				pixel_neighbour=Imagedata[i-1][j-1];//X3
				pixelstack=pixelstack>>1;
				if(pixel_neighbour==255)
				{
					pixelstack=pixelstack|(0x80);
				}
				
				pixel_neighbour=Imagedata[i][j-1];//X4
				pixelstack=pixelstack>>1;
				if(pixel_neighbour==255)
				{
					pixelstack=pixelstack|(0x80);
				}
				
				pixel_neighbour=Imagedata[i+1][j-1];//X5
				pixelstack=pixelstack>>1;
				if(pixel_neighbour==255)
				{
					pixelstack=pixelstack|(0x80);
				}
				
				pixel_neighbour=Imagedata[i+1][j];//X6
				pixelstack=pixelstack>>1;
				if(pixel_neighbour==255)
				{
					pixelstack=pixelstack|(0x80);
				}
				
				pixel_neighbour=Imagedata[i+1][j+1];//X7
				pixelstack=pixelstack>>1;
				if(pixel_neighbour==255)
				{
					pixelstack=pixelstack|(0x80);
				}

				for(w=0;w<5;w++)//check if a corner exists
				{
					if(pixelstack==checking_corners[w])
					{
						corner=1;
					}
				}
				if(!(corner))//if corner doesnt exist, continue operation
				{
					if(Imagedata[i+1][j-1]==255)//input image X5
					{
						Out_Imagedata[i][j-1]=255;//output image X4
						Out_Imagedata[i+1][j]=255;//X6
					}
					if(Imagedata[i+1][j+1]==255)//X7
					{
						Out_Imagedata[i+1][j]=255;//X6
						Out_Imagedata[i][j+1]=255;//X0
					}
					if(Imagedata[i-1][j-1]==255)//X3
					{
						Out_Imagedata[i-1][j]=255;//X2
						Out_Imagedata[i][j-1]=255;//X4
					}
					if(Imagedata[i-1][j+1]==255)//X1
					{
						Out_Imagedata[i-1][j]=255;//X2
						Out_Imagedata[i][j+1]=255;//X0
					}

				}
			}
		}
	}
	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			if(Out_Imagedata[i][j]==0)
			{
				Out_Imagedata[i][j]=BG;//convert according to the actual fg/bg
			}
			else 
			{
				Out_Imagedata[i][j]=FG;
			}
		}
	}
	//set corner values to BG pixels
	for(i=0;i<R_Size;i++)
	{
		for(j=0;j<C_Size;j++)
		{
			if(i==0 || i==R_Size-1 || j==0 || j==C_Size-1)//boundary
			{
				Out_Imagedata[i][j]=BG;
			}
		}
	}
	return Out_Imagedata;
}
				






//function to binarise the image
vector<vector<unsigned char> > ConvertToBinary(vector<vector<vector<unsigned char> > >Imagedata,int R_Size, int C_Size)
{
	int i,j;
	vector<unsigned char> Out_Imagedata_Per_Row(C_Size);
	vector<vector<unsigned char> >Out_Imagedata(R_Size,Out_Imagedata_Per_Row);
	for (i=1;i<R_Size-1;i++)
	{
		for(j=1;j<C_Size-1;j++)
		{
			//cout<<"before"<<(int)Imagedata[i][j][0];

			if(Imagedata[i][j][0]<=127)
				Out_Imagedata[i][j]=0;
			else
				Out_Imagedata[i][j]=255;
			//cout<<"after"<<(int)Out_Imagedata[i][j]<<endl;
		}
	}
	return Out_Imagedata;
}
