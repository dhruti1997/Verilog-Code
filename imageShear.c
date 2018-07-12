/*
C program to shear a image on left or right
Works on RAW image
*/


#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<math.h>

#define PI 3.14

void main(){
	int input_file, output_file;
	unsigned char *input_image, *output_image;
	int npix, nscan, scan, pix, pix1, rotation;	
	char input[100], output[100];

	printf("Enter values of npix and nscan\n");
	scanf("%d %d", &npix, &nscan);

	printf("Enter Input file\n");
	scanf("%s", input);

	printf("Enter Output file\n");
	scanf("%s", output);

	//input file
	input_file=open(input, O_RDONLY);
	if(input_file<0){
		printf("Error Opening file!\n");
		exit(1);
	}	

	//output file
	output_file=creat(output, 0666);
	if(output_file<0){
		printf("Error Creating file!\n");
		exit(1);
	}
	
	//rotation for shear
	printf("Enter Rotation value\n");
	scanf("%d", &rotation);

	int space[nscan];
	int i=0;
	int nscan1;
	int npix1;
	float angel;

	//shear on right side
	if(rotation<=90){
		angel=(rotation*PI)/180;
		nscan1=nscan;

		for(i=0; i<nscan; i++){
			space[i]=round(nscan1*tan(angel));
			nscan1--;
		}
		npix1=npix+space[0];
	}

	//shear on left side
	else{
		angel=(((rotation-90)*PI)/180);
		nscan1=0;
		
		for(i=0; i<nscan; i++){
			space[i]=round(nscan1*tan(angel));
			nscan1++;
		}
		npix1=npix+space[nscan-1];
	}
	
	
	input_image=(unsigned char*)malloc(npix*sizeof(unsigned char));	//input image
	output_image=(unsigned char*)malloc(npix1*sizeof(unsigned char));	//output image

	printf("New Size of Image is %d %d", npix1, nscan);
	
	for(scan=0; scan<nscan; scan++){
		read(input_file, input_image, npix*sizeof(unsigned char));	//reading input
	
		for(pix=0; pix<npix1; pix++){
			
			//padding remaining space (black space)
			if(pix<space[scan] || pix>npix+space[scan]){
				output_image[pix]=0;
			}
			else{ //padding input image
				output_image[pix]=input_image[pix-space[scan]];
			}
		}
		write(output_file, output_image, npix1*sizeof(unsigned char));	//writing output
	}

	close(input_file);
	close(output_file);
}
