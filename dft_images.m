%Matlab code to swap the amplitudes of two different image using DFT
%Dhruti Chandarana
%201501015

%observations
%Images are distorted after swapping, both images have features of both of them
%parts of images with high intensity are not much affected by the other image
%edges of image are not affected as much as other part of the image

clc;

%reading image
img1=imread('subject01.glasses.gif');
img2=imread('subject02.normal');

%dft of image
dft1= fft(img1);
dft2= fft(img2);

%finding amplitude
m1= abs(dft1);
m2= abs(dft2);

%finding phase
p1= angle(dft1);
p2= angle(dft2);

%swapping amplitude
si1= m2.*exp(1j*p1);
si2= m1.*exp(1j*p2);

%inverse dft 
i1= ifft(si1);
i2= ifft(si2);

%inverse dft to image
final1 = uint8(real(i1));
final2 = uint8(real(i2));

%ploting
figure();
imshow(img1);
title('person: 1 before swapping amplitude');
figure();
imshow(final1);
title('person: 1 after swapping amplitude');
figure();
imshow(img2);
title('person: 2 before swapping amplitude');
figure();
imshow(final2);
title('person: 2 after swapping amplitude');

