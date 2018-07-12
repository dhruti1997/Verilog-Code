/*
C program to find out histogram on given image
Works on RAW Grays scale image (range: 0-255)
Use application like ImageJ in order to view RAW images
*/


#include<stdio.h>
#include<fcntl.h>
#include<math.h>
#include<stdlib.h>

void main(){
	int input_file;
	FILE *output_file;
	unsigned char *input_image;
	int npix, nscan, pix, scan;
	char input[100], output[100];
	int count[256];
	
	printf("Enter values of npix and nscan\n");
	scanf("%d %d", &npix, &nscan);

	printf("Enter Input file\n");
	scanf("%s", input);

	//input file
	input_file=open(input, O_RDONLY);
	if(input_file<0){
		printf("Error Opening file\n");
		exit(1);
	}

	//output file: file to store value of histogram
	output_file=fopen("histogram.txt", "w");
	if(output_file==NULL){
		printf("Error Creating file\n");
		exit(1);
	}

	int i;

	//inital zeros
	for(i=0; i<256; i++){
		count[i]=0;
	}

	input_image=(unsigned char*)malloc(npix*sizeof(unsigned char));	//input image

	for(scan=0; scan<nscan; scan++){
		read(input_file, input_image, npix*sizeof(unsigned char));	//reading image
		
		for(pix=0; pix<npix; pix++){
			count[input_image[pix]]++;	//increase count value for a particular gray scale value
		}		
	}
	
	for(i=0;i<256;i++)
	{
		fprintf(output_file, "%d \n",count[i]);	//writing data in a text file
		
	}

	fclose(output_file);
	close(input_file);
}
