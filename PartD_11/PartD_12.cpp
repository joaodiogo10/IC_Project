#include <opencv2/opencv.hpp>
#include <math.h>


int main(int argc, char *argv[])
{     
    //validate input
    if(argc != 3) {
        std::cout << "Usage: PartD_12 <imagePathOriginal> <imagePathReduced>" << std::endl;
        return -1;
    }

    std::string filePathOriginal = argv[1];
    std::string filePathReduced = argv[2];

    cv::Mat imageOriginal = cv::imread( filePathOriginal, cv::IMREAD_COLOR );
    cv::Mat imageOriginalGrey = cv::imread( filePathOriginal, cv::IMREAD_GRAYSCALE);

    cv::Mat imageReduced = cv::imread( filePathReduced, cv::IMREAD_COLOR);
    cv::Mat imageReducedGrey = cv::imread( filePathReduced, cv::IMREAD_GRAYSCALE);

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
    int64_t sum = 0;
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
    std::cout << "PSNR: "<< PSNR << std::endl;

    /* Grey Scale */
    channels = imageOriginalGrey.channels();

    //copy image pixel by pixel (assuming size of unsigned char for each channel)
    nRows = imageOriginalGrey.rows;
    nCols = imageOriginalGrey.cols * channels;

    if (imageOriginalGrey.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    sum = 0;
    for(int i = 0; i < nRows; i++)
    {
        pOriginal = imageOriginalGrey.ptr<uchar>(i);
        pReduced = imageReducedGrey.ptr<uchar>(i);
        for(int j = 0; j < nCols; j++)
        {
            sum += std::pow(pOriginal[j] - pReduced[j], 2);
        }
    }

    MSE = sum/(nRows*nCols);
    MAX = std::pow(2,imageOriginalGrey.elemSize1() * 8) - 1;
    PSNR = 10* std::log10(std::pow(MAX,2)/MSE);
    std::cout << "PSNR grayscale:" << PSNR << std::endl;
}
