import cv2
import numpy as np

# Initialize face and eye cascade classifiers
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_eye.xml')

# Initialize the video capture object
cap = cv2.VideoCapture(0)

while True:
    # Read a frame from the camera
    ret, img = cap.read()
    if not ret:
        break
    
    # Convert frame to grayscale for face detection
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    # Detect faces using Haar cascades
    faces = face_cascade.detectMultiScale(gray, 1.3, 5)
    
    # Add text annotation for number of faces detected
    num_faces = len(faces)
    cv2.putText(img, f'Faces Detected: {num_faces}', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    
    for (x, y, w, h) in faces:
        # Draw rectangle around detected face
        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        
        # Region of Interest (ROI) for face detection
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
        
        # Detect eyes within the face region
        eyes = eye_cascade.detectMultiScale(roi_gray)
        
        # Draw rectangles around detected eyes
        for (ex, ey, ew, eh) in eyes:
            cv2.rectangle(roi_color, (ex, ey), (ex+ew, ey+eh), (0, 255, 0), 2)
        
        # Optional: Add more functionalities here
    
    # Display the frame with annotations
    cv2.imshow('img', img)
    
    # Exit the loop if 'Esc' key is pressed
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

# Release the video capture object and close all windows
cap.release()
cv2.destroyAllWindows()




