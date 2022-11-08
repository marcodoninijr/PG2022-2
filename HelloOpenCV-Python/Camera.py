import numpy as np
import cv2 as cv

capture = cv.VideoCapture(0)
if not capture.isOpened():
    print('Unable to open')
    exit(0)
while True:
    ret, frame = capture.read()
    if frame is None:
        break

    frame =  cv.cvtColor(frame, cv.COLOR_BGR2GRAY)
    frame = cv.blur(frame,(5,5))
    frame = cv.Canny(frame,50,80)
     # Display the resulting frame
    cv.imshow('frame', frame)

   
      
    # the 'q' button is set as the
    # quitting button you may use any
    # desired button of your choice
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
  
# After the loop release the cap object
capture.release()
    # Destroy all the windows
    #capture.destroyAllWindows()