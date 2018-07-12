/*
C program to rotate given image
Works on RAW Image (Preferable for Square Images, e.g. 256x256)
*/

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.14

void main(){
	unsigned char *input_image, *output_image;
	int input_file, output_file;
	char input_file_name[100], output_file_name[100];
	int pix, npix, scan, nscan, rotation, npix1, nscan1;
	int i, j, k;
	
	printf("Enter values of npix and nscan\n");
	scanf("%d %d", &npix, &nscan);

	int x[2][2];
	int y[2][2];

	printf("Enter the input file name\n");
	scanf("%s", input_file_name);

	//input file
	input_file=open(input_file_name, O_RDONLY);
	if(input_file<0){
		printf("Error Opening file!");
		exit(1);
	}

	printf("Enter the output file name\n");
	scanf("%s", output_file_name);

	//output file
	output_file=creat(output_file_name, 0666);
	if(output_file<0){
		printf("Error Creating file!");
		exit(1);
	}

	unsigned char image2D[npix][nscan];	//2D array to store input image

	input_image=(unsigned char*)malloc(npix*sizeof(unsigned char));	//input image
	for(scan=0; scan<nscan; scan++){	//storing image into 2D array
		read(input_file, input_image, npix*sizeof(unsigned char));		
		for(pix=0; pix<npix; pix++){	
			image2D[scan][pix]=input_image[pix];
		}
	}

	//rotation value
	printf("Enter the rotation value\n");
	scanf("%d", &rotation);

	//center of image
	int centerX=npix/2;
	int centerY=nscan/2;

	float angle=(rotation*PI)/180;

	printf("CenterX: %d\n", centerX);
	printf("CenterY: %d\n", centerY);

	//finding transformation of 4 co-ordinates (top-left, top-right, bottom-left, bottom-right)
	x[0][0]=round(-(centerX-1)*cos(angle)+(centerY)*sin(angle));
	x[0][1]=round(centerX*cos(angle)+centerY*sin(angle));
	x[1][0]=round(-(centerX-1)*cos(angle)-(centerY-1)*sin(angle));
	x[1][1]=round(centerX*cos(angle)-(centerY-1)*sin(angle));
	
	y[0][0]=round((centerX-1)*sin(angle)+(centerY)*cos(angle));
	y[0][1]=round(-centerX*sin(angle)+centerY*cos(angle));
	y[1][0]=round((centerX-1)*sin(angle)-(centerY-1)*cos(angle));
	y[1][1]=round(-centerX*sin(angle)-(centerY-1)*cos(angle));

	//max and min x co-ordinate
	int minX=x[0][0]<x[0][1]?x[0][0]:x[0][1];
	minX=minX<x[1][0]?minX:x[1][0];
	minX=minX<x[1][1]?minX:x[1][1];
	
	int maxX=x[0][0]>x[0][1]?x[0][0]:x[0][1];
	maxX=maxX>x[1][0]?maxX:x[1][0];
	maxX=maxX>x[1][1]?maxX:x[1][1];

	//max and min y co-ordinate
	int minY=y[0][0]<y[0][1]?y[0][0]:y[0][1];
	minY=minY<y[1][0]?minY:y[1][0];
	minY=minY<y[1][1]?minY:y[1][1];
	
	int maxY=y[0][0]>y[0][1]?y[0][0]:y[0][1];
	maxY=maxY>y[1][0]?maxY:y[1][0];
	maxY=maxY>y[1][1]?maxY:y[1][1];

	npix1=maxX-minX;	//new width
	nscan1=maxY-minY;	//new length

	int newX=minX;
	int newY=maxY;	//new y coordinate
	int oldX=0;
	int oldY=0;

	output_image=(unsigned char*)malloc(npix1*sizeof(unsigned char));	//output image

	for(scan=0; scan<=nscan1; scan++){
		newX=minX;	//new x coordinate
		for(pix=0; pix<=npix1; pix++){
			oldX=round(newX*cos(angle)-newY*sin(angle));	//old x with respect to new x and new y
			oldY=round(newX*sin(angle)+newY*cos(angle));	//old y with respect to new x and new y
			
			if(oldX<-(centerX-1) || oldX>centerX || oldY<-(centerY-1) || oldY>centerY){	//x and y are not in range of original then black space
				output_image[pix]=0;
			}
			else{
				//finding out original pix and scan value	
				if(0<=oldX && oldX<=centerX)
					oldX+=centerX;
				else if(-(centerX-1)<=oldX && oldX<0)
					oldX=oldX+(centerX-1);

				if(0<=oldY && oldY<=centerY)
					oldY=centerY-oldY;
				else if(-(centerY-1)<=oldY && oldY<0)
					oldY=centerY-oldY;
			
				output_image[pix]=image2D[oldY][oldX];	
			}
			newX++;
		}		
		newY--;
		write(output_file, output_image, npix1*sizeof(unsigned char));	//writing ouput
	}
	printf("\nsize of image %d %d", npix1, nscan1);

	close(input_file);
	close(output_file);
}

