/*
C program to calculate and save 8x8 haar transform basis image
Generate Basis for 8x8 Haar matrix
*/

#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include<fcntl.h>

void main()
{
	int N;  //dimension of H matrix

	printf("Enter order of matrix:");
	scanf("%d",&N);

	int row=N,col=N,n,p,i,j,k,m,l,g,s,cn;
	float r;
	float H[row][col],H_tr[row][col],im[row][col][N*N];
	float t[N],temp;

	for(i=0;i<N;i++)
	   t[i]=(float)i/N;    //create N different time instances within 0 to 1

	for(i=0;i<row;i++){
	   for(j=0;j<col;j++)
		  H[i][j]=0;  //initialize H by 0s
	}

	//generate H matrix based on equations of Haar
	for(i=0;i<col;i++){
	   if(t[i]>=0 && t[i]<1)
		  H[0][i]=1;

	   for(p=0;p<=2;p++){
		  r=pow(2,p);

		  for(n=0;n<=r-1;n++){
		      if(t[i]>=n/r && t[i]<(n+0.5)/r)
		          H[(int)r+(int)n][i]=sqrt((int)r);

		      else if(t[i]>=(n+0.5)/r && t[i]<(n+1)/r)
		          H[(int)r+(int)n][i]=-sqrt((int)r);
		  }
	   }
	}

	for(i=0;i<row;i++){
	   for(j=0;j<col;j++)
		  H[i][j]=(1/sqrt(N))*H[i][j];    //normalize H matrix
	}

	for(i=0;i<row;i++){
	   for(j=0;j<col;j++)
		  printf("%f\t",H[i][j]); //display H
	   printf("\n");
	}
	printf("\n");

	for(i=0;i<row;i++){
	   for(j=0;j<col;j++)
		  H_tr[i][j]=H[j][i]; //generate H transpose
	}

	for(i=0;i<=(N*N);i++){
	   for(j=0;j<row;j++){
		  for(k=0;k<col;k++)
		      im[j][k][i]=0;  //initialize image matrix by 0s
	   }
	}

	//generate Haar basis images
	k=1;
	for(l=0;l<N;l++){
	   for(i=0;i<N;i++){
		  for(j=0;j<N;j++){
		      for(m=0;m<N;m++){
		           im[j][m][k]=im[j][m][k]+(H_tr[j][l]*H[i][m]);
		      }
		  }
		  k++;
	   }
	}

	for(i=1;i<=(N*N);i++){
	   printf("Basis image %d\n",i);
	   for(j=0;j<N;j++){
		  for(k=0;k<N;k++){
		      printf("%f\t",im[j][k][i]); //display Haar basis images
		  }
		  printf("\n");
	   }
	   printf("\n\n\n");
	}

	float max[N*N];
	float min[N*N];

	for(k=1;k<=N*N;k++){
	   max[k]=0;
	   for(i=0;i<N;i++){
		  for(j=0;j<N;j++)
		  {
		      if(im[i][j][k]>max[k])
		          max[k]=im[i][j][k]; //calculate maximum element from each image
		  }
	   }
	}

	for(k=1;k<=N*N;k++){
	   min[k]=0;
	   for(i=0;i<N;i++)
	   {
		  for(j=0;j<N;j++)
		  {
		      if(im[i][j][k]<min[k])
		          min[k]=im[i][j][k]; //calculate minimum element from each image
		  }
	   }
	}

	float m1[N*N],c[N*N];
	for(k=1;k<=N*N;k++){
	   m1[k]=255/(max[k]-min[k]);  //calculate slope m
	   c[k]=(255*min[k])/(min[k]-max[k]);  //calculate constant c
	}

	float y[row][col][N*N];
	for(k=1;k<=N*N;k++){
	   printf("output image:%d\n",k);
	   for(i=0;i<N;i++){
		  for(j=0;j<N;j++){
		      y[i][j][k]=round((m1[k]*im[i][j][k])+c[k]); //map elements to 0 to 255 for generating image
		      printf("%f\t",y[i][j][k]);
		  }
		  printf("\n");
	   }
	   printf("\n");
	}

	int npix=N*N;
	unsigned char image[npix][npix];
	char out_file[100];
	int *fp1;

	for(k=1;k<=N*N;k++){
		sprintf(out_file,"output file %d",k);
		fp1=creat(out_file,0666);

		if(fp1<0){
			printf("Error");
			exit(1);
		}

		int pix,scan;
		for(pix=0;pix<N*N;pix++){
			for(scan=0;scan<N*N;scan++){
			 image[pix][scan]=y[pix/N][scan/N][k];  //assign N*N to (N^2)*(N^2) for bigger picture of image

			}
		}
		write(fp1,image,npix*npix*sizeof(unsigned char));
	}
}
