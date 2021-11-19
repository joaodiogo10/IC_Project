#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
    if(argc != 2){
        cout << "Needs 1 argument" << endl;
        return 1;
    }
    
    if(argv[1].endsWith(".jpg")){
        // Read the image file
        Mat image = imread(argv[1]);

        // Check for faliure
        if(image.empty()){
            cout << "Could not open or find the image" << endl;
            cin.get();  // Wait for any key press
            return -1;
        }

        String windowName = "Image1";   // Name of the window
        namedWindow(windowName);    // Create a window
        imshow(windowName, image);  // Show our image inside the created window
        waitKey(0); // Wait for any keystroke in the window
        destroyWindow(windowName);  // Destroy the created window

        return 0;
    }

    else if (argv[1].endsWith(".mp4")){
        // Open the video file for reading
        VideoCapture cap(argv[1]);

        // If not success, exit program
        if(cap.isOpened() == false){
            cout << "Cannot open the video file" << endl;
            cin.get();  // Wait for any key press
            return -1;
        }

        // Get the frames rate of the video
        double fps = cap.get(CAP_PROP_FPS);
        cout << "Frames per seconds : " << fps << endl;

        String window_name = "Video1";

        nameWindow(window_name, WINDOW_NORMAL); // Create a window

        while(true){
            Mat frame;
            bool bSuccess = cap.read(frame);    // Read a new frame from video

            // Breaking the while loop at the end of the video
            if(bSuccess == false){
                cout << "Found the end of the video" << endl;
                break;
            }

            // Show the frame in the created window
            imshow(window_name, frame);

            // Wait for for 10 ms until any key is pressed.  
            // If the 'Esc' key is pressed, break the while loop.
            // If the any other key is pressed, continue the loop 
            // If any key is not pressed withing 10 ms, continue the loop
            if(waitkey(10) == 27){
                cout << "Esc key is pressed by user. Stopping the video" << endl;
                break;
            }
        }

        return 0;
    }

    return 0;
}   
