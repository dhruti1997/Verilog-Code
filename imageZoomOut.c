/*
C program to zoom out from an image
Works on RAW image
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<math.h>

void main(){
	unsigned short *input_image, *output_image;
	int pix, npix, scan, nscan, zoom_factor;
	char input_file_name[100], output_file_name[100];
	int input_file, output_file;

	printf("Enter values of npix and nscan\n");	
	scanf("%d %d", &npix, &nscan);

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

	//zoom factor
	printf("Enter the zoom factor\n");
	scanf("%d", &zoom_factor);

	int kj, l;
	int sum[npix/zoom_factor];
	
	input_image=(unsigned short*)malloc(npix*sizeof(unsigned short));	//input image
	output_image=(unsigned short*)malloc(npix/zoom_factor*sizeof(unsigned short));	//output image

	
	for(scan=0;scan<nscan/zoom_factor;scan++){
		for (pix=0;pix<npix/zoom_factor;pix++){	//initial zeros
			sum[pix]=0;
		}
		for (kj=0;kj<zoom_factor;kj++){
			read(input_file, input_image, npix*sizeof(unsigned short));
			for (pix=0;pix<npix/zoom_factor;pix++){
				for (l=0;l<zoom_factor;l++){
					sum[pix]=sum[pix]+input_image[pix*zoom_factor+l];	//sum of all zoom*zoom pixels
				}
			}
		}
		for (pix=0;pix<npix/zoom_factor;pix++){
			output_image[pix]=sum[pix]/(zoom_factor);	//storing output as average of all zoom*zoom pixels
		}
		write(output_file, output_image, npix/zoom_factor*sizeof(unsigned short));	//writing output
	}

	printf("New size of Image: %d %d", npix/zoom_factor, nscan/zoom_factor);

	close(input_file);
	close(output_file);
}
