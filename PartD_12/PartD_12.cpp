#include <opencv2/opencv.hpp>
#include <math.h>

std::string filePathOriginal = "../imageSamples/original.jpeg";
std::string filePathReduced = "../imageSamples/reduced.jpeg";

int main()
{  
    cv::Mat imageOriginal = cv::imread( filePathOriginal, cv::IMREAD_COLOR );
    cv::Mat imageReduced = cv::imread( filePathReduced, cv::IMREAD_COLOR);
    if ( imageOriginal.empty() )
    {
        std::cout << "Could not read the image: " << filePathOriginal << std::endl;
        return false;
    }
    
    if ( imageReduced.empty() )
    {
        std::cout << "Could not read the image: " << filePathReduced << std::endl;
        return false;
    }
    int channels = imageOriginal.channels();

    //copy image pixel by pixel (assuming size of unsigned char for each channel)
    int nRows = imageOriginal.rows;
    int nCols = imageOriginal.cols * channels;

    if (imageOriginal.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    const uchar *pOriginal, *pReduced;
    int sum = 0;
    for(int i = 0; i < nRows; i++)
    {
        pOriginal = imageOriginal.ptr<uchar>(i);
        pReduced = imageReduced.ptr<uchar>(i);
        for(int j = 0; j < nCols; j++)
        {
            sum += std::pow(pOriginal[j] - pReduced[j], 2);
        }
    }

    int MSE = sum/(nRows*nCols);

    int MAX = std::pow(2,imageOriginal.elemSize1() * 8) - 1;
    float PSNR = 10* std::log10(std::pow(MAX,2)/MSE);
    std::cout << PSNR << std::endl;
}