#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

std::string fileInPath = "videoSamples/sample02.y4m"; 

int main(int argc, char* argv[])
{
    cv::VideoCapture videoIn(fileInPath);
    
    if (!videoIn.isOpened())
    {
        std::cout  << "Could not open reference " << fileInPath << std::endl;
        return -1;
    }

    std::string::size_type pAt = fileInPath.find_last_of('.');                          // Find extension point
    const std::string videoOutName = fileInPath.substr(0, pAt) + "_out" + ".avi";       // Form the new name with container
    int ex = static_cast<int>(videoIn.get(cv::CAP_PROP_FOURCC));                        // Get Codec Type- Int for

    // Transform from int to char
    union { int v; char c[5];} uEx ;
    uEx.v = ex;                             
    uEx.c[4]='\0';
    
    // Acquire input size
    cv::Size S = cv::Size((int) videoIn.get(cv::CAP_PROP_FRAME_WIDTH),
                  (int) videoIn.get(cv::CAP_PROP_FRAME_HEIGHT));

    // Open output video
    cv::VideoWriter videoOut;
    videoOut.open(videoOutName, ex, videoIn.get(cv::CAP_PROP_FPS), S, true);
    if(!videoOut.isOpened())
    {
        std::cout  << "Could not open the output video for write: " << fileInPath << std::endl;
        return -1;
    }

    std::cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
         << " of nr#: " << videoIn.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;
    std::cout << "Input codec type: " << uEx.c << std::endl;

    cv::Mat frameIn;
    int frameNum = -1;   //Frame counter
    

    for(;;)
    {
        videoIn >> frameIn;
        if(frameIn.empty()) break;
        videoOut << frameIn;
        frameNum++;
    }
    
    return 0;
}