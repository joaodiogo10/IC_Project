#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <map>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    Mat srcColors, srcGrey;
    if (argc < 2)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    srcColors = imread(argv[1], IMREAD_COLOR);
    srcGrey = imread(argv[1], IMREAD_GRAYSCALE);

    if (srcColors.empty() or srcGrey.empty())
    {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

    vector<Mat> bgr_planes;
    split(srcColors, bgr_planes);

    int histSize = 256;
    float range[] = {0, 256}; //the upper boundary is exclusive
    const float *histRange[] = {range};
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist, grey_hist;

    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&srcGrey, 1, 0, Mat(), grey_hist, 1, &histSize, histRange, uniform, accumulate);

    int hist_w = 512,
        hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);

    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    normalize(grey_hist, grey_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++)
    {
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
             Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
             Scalar(255, 0, 0), 2, 8, 0);
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
             Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
             Scalar(0, 255, 0), 2, 8, 0);
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
             Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
             Scalar(0, 0, 255), 2, 8, 0);
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(grey_hist.at<float>(i - 1))),
             Point(bin_w * (i), hist_h - cvRound(grey_hist.at<float>(i))),
             Scalar(128, 128, 128), 2, 8, 0);
    }

    double entropyBlue, entropyGreen, entropyRed, entropyGrey;
    float probtotalBlue = 0, probtotalGreen = 0, probtotalRed = 0, probtotalGrey = 0;
    map<int, double> probMapBlue, probMapGreen, probMapRed, probMapGrey;
    float totalBlue = 0, totalGreen = 0, totalRed = 0, totalGrey = 0;

    for (int i = 0; i < histSize; i++)
    {
        totalBlue += ((float)b_hist.at<float>(i));
        totalGreen += ((float)g_hist.at<float>(i));
        totalRed += ((float)r_hist.at<float>(i));
        totalGrey += ((float)grey_hist.at<float>(i));
    }

    for (int i = 0; i < histSize; i++)
    {
        probMapBlue[i] = ((float)b_hist.at<float>(i)) / totalBlue;
        probMapGreen[i] = ((float)g_hist.at<float>(i)) / totalGreen;
        probMapRed[i] = ((float)r_hist.at<float>(i)) / totalRed;
        probMapGrey[i] = ((float)grey_hist.at<float>(i)) / totalGrey;
        if (probMapBlue[i] != 0)
        {
            entropyBlue += probMapBlue[i] * log2(probMapBlue[i]);
        }
        if (probMapGreen[i] != 0)
        {
            entropyGreen += probMapGreen[i] * log2(probMapGreen[i]);
        }
        if (probMapRed[i] != 0)
        {
            entropyRed += probMapRed[i] * log2(probMapRed[i]);
        }
        if (probMapGrey[i] != 0)
        {
            entropyGrey += probMapGrey[i] * log2(probMapGrey[i]);
        }

        probtotalBlue += probMapBlue[i];
        probtotalGreen += probMapGreen[i];
        probtotalRed += probMapRed[i];
        probtotalGrey += probMapGrey[i];
    }

    std::cout << "Blue entropy"
              << ": " << -entropyBlue << '\n';

    std::cout << "Green entropy"
              << ": " << -entropyGreen << '\n';

    std::cout << "Red entropy"
              << ": " << -entropyRed << '\n';

    std::cout << "Grey entropy"
              << ": " << -entropyGrey << '\n';

    imshow("Source image", srcColors);
    imshow("calcHist Demo", histImage);
    waitKey();
    return EXIT_SUCCESS;
}