import numpy as np 
import cv2  
def yolo_load(img, net, output_layers, classes) :
    
    #img = cv2.resize(img,None,fx=0.4,fy=0.4)
    #blob img
    blob = cv2.dnn.blobFromImage(img, 0.00362, (416, 416), (0, 0, 0), True, crop = False)
    net.setInput(blob)
    outs = net.forward(output_layers)
    #showing info
    hight,width,channel = img.shape 
    boxes =[]
    confidances =[]
    class_ids =[]
    for out in outs:
        for detection in out:
            scores  = detection[5:]
            class_id = np.argmax(scores)
            confidance = scores[class_id]
            if confidance >= 0.5:
                center_x = int(detection[0] * width)
                center_y = int(detection[1] * hight)
                w = int(detection[2] * width)
                h = int(detection[3] * hight)
                #cv2.circle(img,(center_x, center_y),10,(0,255,0),2 )
                y = int(center_y -( h / 2) )
                x =  int(center_x - (w/ 2) )
                boxes.append([x,y,w,h])
                confidances.append(float(confidance))
                class_ids.append(class_id)

    #filter the repeat detection        
    indexes = cv2.dnn.NMSBoxes(boxes, confidances,0.6, 0.4)  
    #draw box with name around object
    for i in range(len(boxes)):
        if i in indexes:
            x, y, w, h = boxes[i]
            labels = str(classes[class_ids[i]])
            cv2.rectangle(img, (x, y), ((x + w), (y + h)),( 0, 255, 0), 2)   
            cv2.putText(img, labels, (x,y-20), cv2.FONT_HERSHEY_PLAIN, 1.5, (0,255,0), 3)
    return img

