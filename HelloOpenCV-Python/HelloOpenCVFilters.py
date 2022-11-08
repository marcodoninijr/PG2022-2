import numpy as np
import cv2 as cv

img = cv.imread('pikachu.png') #original

imgGrayscale =  cv.cvtColor(img, cv.COLOR_BGR2GRAY)



imgBlurred5x5 = cv.blur(imgGrayscale,(5,5))
imgBlurred15x15 = cv.blur(imgGrayscale,(15,15))

imgGaussianBlurred5x5 = cv.GaussianBlur(imgGrayscale,(5,5),0)
imgGaussianBlurred15x15 = cv.GaussianBlur(imgGrayscale,(15,15),0)

imgCanny1 = cv.Canny(imgGrayscale,50,100)
imgCanny2 = cv.Canny(imgBlurred5x5,50,100)
imgCanny3 = cv.Canny(imgGaussianBlurred15x15,50,100)

kernel = np.ones((3,3),np.uint8)
imgDilation = cv.dilate(imgCanny2,kernel,iterations = 1)
imgErosion = cv.erode(imgDilation,kernel,iterations = 1)

#cv.imshow('Original',img)
cv.imshow('Grayscale',imgGrayscale)
#cv.imshow('Blur 5x5',imgBlurred5x5)
#cv.imshow('Blur15x15',imgBlurred15x15)
#cv.imshow('Gaussian Blur 5x5',imgGaussianBlurred5x5)
#cv.imshow('Gaussian Blur15x15',imgGaussianBlurred15x15)

#cv.imshow('Detecção de borda: Canny1',imgCanny1)
cv.imshow('Detecção de borda: Canny2',imgCanny2)
#cv.imshow('Detecção de borda: Canny3',imgCanny3)
cv.imshow('Dilation',imgDilation)
cv.imshow('Erosao',imgErosion)



k = cv.waitKey(0)
