import cv2
import face_recognition

# Load the image for your face or run the take faces file
# Train the face recognition model
known_image = face_recognition.load_image_file("My_PIC\Mario_0.jpg")
known_encoding = face_recognition.face_encodings(known_image)[0]

# Initialize the camera
cap = cv2.VideoCapture(0)

# Recognize the user
while True:
    # Capture the image from the camera
    ret, img = cap.read()
    #img = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

    # Find faces in the image
    face_locations = face_recognition.face_locations(img)
    face_encodings = face_recognition.face_encodings(img, face_locations)
    
    # Check if the user is present in the image
    for face_encoding in face_encodings:
        matches = face_recognition.compare_faces([known_encoding], face_encoding)
        print(matches[0])
        if matches[0] >0.8:
            print("User recognized!")
            # Do something here

            # Display the image
            for (top, right, bottom, left) in face_locations:
                cv2.rectangle(img, (left, top), (right, bottom), (0, 0, 255), 2)
    cv2.imshow('image', img)

    # Quit the program if the 'q' key is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera and close the window
cap.release()
cv2.destroyAllWindows()
