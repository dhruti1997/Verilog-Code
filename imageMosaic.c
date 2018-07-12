/*
C program to mosaic two images
Works on RAW image
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<math.h>

void main(){
	int input_file1, input_file2, output_file;
	unsigned char *input_image1, *input_image2, *output_image;
	int pix, npix1, scan, nscan1, npix2, nscan2, line;
	char input1[100], input2[100], output[100];	

	printf("Enter values of npix and nscan for input1\n");
	scanf("%d %d", &npix1, &nscan1);

	printf("Input 1 file\n");
	scanf("%s", input1);

	printf("Enter values of npix and nscan for input2\n");
	scanf("%d %d", &npix2, &nscan2);

	printf("Input 2 file\n");
	scanf("%s", input2);

	printf("Output file\n");
	scanf("%s", output);

	printf("Enter the line from which you want to append the image\n");
	scanf("%d", &line);

	//input files
	input_file1=open(input1, O_RDONLY);
	input_file2=open(input2, O_RDONLY);
	if(input_file1<0 || input_file2<0){
		printf("Error opening file(s)!");
		exit(1);
	}

	//output file
	output_file=creat(output, 0666);
	if(output_file<0){
		printf("Error creating file!");	
		exit(1);
	}

	input_image1=(unsigned char*)malloc(npix1*sizeof(unsigned char));	//input image 1
	input_image2= (unsigned char*)malloc(npix2*sizeof(unsigned char));	//input image 2
	output_image= (unsigned char*)malloc(npix1*2*sizeof(unsigned char));	//output image

	for(scan=0; scan<nscan1+line; scan++){
		//padding image 1
		if(scan<nscan1){	
			read(input_file1, input_image1, npix1*sizeof(unsigned char));	//reading input 1
			for(pix=0; pix<npix1; pix++){	//padding image
				output_image[pix]=input_image1[pix];
			}
		}
		else{	//padding remaining space (black space)
			for(pix=0; pix<npix1; pix++){
				output_image[pix]=0;
			}	
		}

		//padding image 2
		if(scan<line){	//padding remaining space (black space)
			for(pix=0; pix<npix2; pix++){
				output_image[pix+npix1]=0;
			}
		}
		else{	//padding image
			read(input_file2, input_image2, npix2*sizeof(unsigned char));	//reading input 2
			for(pix=0; pix<npix2; pix++){
				output_image[pix+npix1]=input_image2[pix];
			}

		}
		write(output_file, output_image, npix1*2*sizeof(unsigned char));	//writing output
	}
	
	printf("New Size of image %d %d", npix1+npix2, nscan1+line);
	
	close(input_file1);
	close(input_file2);
	close(output_file);
}
