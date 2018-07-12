/*
C program to zoom given image
Works on RAW image
*/


#include<stdio.h>
#include<fcntl.h>
#include<math.h>
#include <malloc.h>
#include<stdlib.h>

void main()		
{
	float zoom_factor;
	int input_file, output_file;
	int kj,l;
	int i,j,npix,nscan,scan,pix,npix1,nscan1,x,y;
	unsigned char *input_image;
	char input[100],output[100];
	kount=0;
	
	printf("Enter values of npix and nscan\n");
	scanf("%d %d", &npix, &nscan);

	printf("Enter the input file name\n");
	scanf("%s", input);

	//input file
	input_file=open(input, O_RDONLY);
	if(input_file<0){
		printf("Error Opening file!");
		exit(1);
	}

	printf("Enter the output file name\n");
	scanf("%s", output);

	//output file
	output_file=creat(output, 0666);
	if(output_file<0){
		printf("Error Creating file!");
		exit(1);
	}

	//zoom factor
	printf("Zoom factor: \n");		
	scanf("%f",&zoom_factor);

	nscan1=nscan*zoom_factor;	//new length
	npix1=npix*zoom_factor;		//new width
	printf("New size %d %d\n", npix1, nscan1);

	input_image=(unsigned char*)malloc(npix*sizeof(unsigned char));	

	unsigned char input2D[nscan][npix];	//2D array to store input
	unsigned char output_image[nscan1][npix1];	//output image
	int x1, y1;
	
	//storing input as a 2D array
	for(scan=0;scan<nscan;scan++){
		read(input_file, input_image, npix*sizeof(unsigned char));
		for(pix=0;pix<npix;pix++){
			input2D[scan][pix]=input_image[pix];
		}
	}
		
	for(i=0;i<nscan1;i++){
		for (j=0;j<npix1;j++){
			//finding value of original pix and scan
			x = i/zoom_factor;	
			y = j/zoom_factor;
			x1= (int)x;
			y1= (int)y;
			output_image[i][j]=input2D[x1][y1];
		}	    
		write(output_file, output_image, nscan1*npix1*sizeof(unsigned short));	//writing output
	}

	close(input_file);		
	close(output_file);		
}

