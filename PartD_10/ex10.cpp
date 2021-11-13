#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cv;

Mat &ScanImageAndReduceC(Mat &I, const uchar *table);

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    if (argc == 5 && !strcmp(argv[3], "G"))
        I = imread(argv[1], IMREAD_GRAYSCALE);
    else
        I = imread(argv[1], IMREAD_COLOR);

    if (I.empty())
    {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

    //! [dividewith]
    int divideWith = 0; // convert our input string to number - C++ style
    stringstream s;
    s << argv[3];
    s >> divideWith;

    if (!s || !divideWith)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }

    uchar table[256];
    for (int i = 0; i < 256; ++i)
        table[i] = (uchar)(divideWith * (i / divideWith));
    //! [dividewith]

    cv::Mat clone_i = I.clone();
    J = ScanImageAndReduceC(clone_i, table);

    imwrite(argv[2], J);

    return 0;
}

Mat &ScanImageAndReduceC(Mat &I, const uchar *const table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous())
    {
        nCols *= nRows;
        nRows = 1;
    }

    int i, j;
    uchar *p;
    for (i = 0; i < nRows; ++i)
    {
        p = I.ptr<uchar>(i);
        for (j = 0; j < nCols; ++j)
        {
            p[j] = table[p[j]];
        }
    }
    return I;
}