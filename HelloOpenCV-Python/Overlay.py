import cv2
import numpy as np

def logoOverlay(image,logo,alpha=1.0,x=0, y=0, scale=1.0):
    (h, w) = image.shape[:2]
    image = np.dstack([image, np.ones((h, w), dtype="uint8") * 255])
    
    overlay = cv2.resize(logo, None,fx=scale,fy=scale)
    (wH, wW) = overlay.shape[:2]
    output = image.copy()
    # blend the two images together using transparent overlays
    try:
        if x<0 : x = w+x
        if y<0 : y = h+y
        if x+wW > w: wW = w-x  
        if y+wH > h: wH = h-y
        print(x,y,wW,wH)
        overlay=cv2.addWeighted(output[y:y+wH, x:x+wW],alpha,overlay[:wH,:wW],1.0,0)
        output[y:y+wH, x:x+wW ] = overlay
    except Exception as e:
        print("Error: Logo position is overshooting image!")
        print(e)
    
    output= output[:,:,:3]
    return output

background = cv2.imread('baboon.png')
overlay = cv2.imread('flaming_meteor.png', cv2.IMREAD_UNCHANGED)

print(overlay.shape) # must be (x,y,4)
print(background.shape) # must be (x,y,3)

# downscale logo by half and position on bottom right reference
out = logoOverlay(background,overlay,scale=2.0,y=-100,x=-100) 

cv2.imshow("test",out)
cv2.waitKey(0)