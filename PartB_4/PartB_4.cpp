#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat copyMat(const cv::Mat &source);
bool writeVideoToFile(std::string fileInPath, std::string fileOutPath);
bool writeImageToFile(std::string fileInPath, std::string fileOutPath);

int main(int argc, char** argv )
{
    //validate input
    if(argc != 4 || (std::string(argv[1]) != "image" && std::string(argv[1]) != "video") ) {
        std::cout << "Usage: imageCopy [image | video] <fileIn> <fileOut>" << std::endl;
        return -1;
    }

    std::string fileType = argv[1];
    std::string fileInPath = argv[2];
    std::string fileOutPath = argv[3];

    int result = 0;
    if(fileType == "image") {
        result = writeImageToFile(fileInPath,fileOutPath);
    }
    else{
        result = writeVideoToFile(fileInPath,fileOutPath);
    }
    
    if(!result)
    {
        std::cout << "ERROR: Failed writing output image file!" << std::endl;
        return -1;
    }

    std::cout << "File saved sucessfully!" << std::endl;
    return 0;
}

bool writeVideoToFile(std::string fileInPath, std::string fileOutPath) {
    cv::VideoCapture videoIn(fileInPath);
    
    if (!videoIn.isOpened())
    {
        std::cout  << "Could not open reference " << fileInPath << std::endl;
        return false;
    }

    std::string videoOutName;                                                            // Form the new name with container
    videoOutName = fileOutPath + ".avi";

    int ex = static_cast<int>(videoIn.get(cv::CAP_PROP_FOURCC));                         // Get Codec Type- Int for

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
        return false;
    }

    std::cout << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
         << " of nr#: " << videoIn.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;
    std::cout << "Input codec type: " << uEx.c << std::endl;

    cv::Mat frameIn;
    while(true)
    {
        videoIn >> frameIn;
        if(frameIn.empty()) break;
        videoOut << copyMat(frameIn);
    }

    return true;
}

bool writeImageToFile(std::string fileInPath, std::string fileOutPath)
{
    cv::Mat imageIn = cv::imread( fileInPath, cv::IMREAD_COLOR );

    if ( imageIn.empty() )
    {
        std::cout << "Could not read the image: " << fileInPath << std::endl;
        return false;
    }

    cv::Mat imageOut = copyMat(imageIn);
    
    //Write result file   
    bool writeResult = false;

    try
    {
        writeResult = cv::imwrite(fileOutPath, imageOut);
    }
    catch(const cv::Exception& ex)
    {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
    }
    if (!writeResult)
        return false;
    
    return true;
}

cv::Mat copyMat(const cv::Mat &source) 
{
    int channels = source.channels();

    //create new image Matrix 
    cv::Mat imageOut = cv::Mat::zeros(source.rows,source.cols,source.type());

    //copy image pixel by pixel (assuming size of unsigned char for each channel)
    int nRows = source.rows;
    int nCols = source.cols * channels;

    if (source.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    const uchar* pIn;
    uchar* pOut;
    for(int i = 0; i < nRows; i++)
    {
        pIn = source.ptr<uchar>(i);
        pOut = imageOut.ptr<uchar>(i);
        for(int j = 0; j < nCols; j++)
        {
            pOut[j] = pIn[j];
        }
    }

    return imageOut;
} 