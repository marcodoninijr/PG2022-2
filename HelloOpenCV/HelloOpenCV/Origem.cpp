#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void drawText(Mat& image);

int main()
{
    cout << "Built with OpenCV " << CV_VERSION << endl;
    Mat img, img2, img3;
  
    img = imread("baboon.png");
    img2 = imread("baboon.png");
    img3 = imread("baboon.png");

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            Vec3b &bgrPixel2 = img2.at<Vec3b>(i, j);
            Vec3b &bgrPixel3 = img3.at<Vec3b>(i, j);

            float media = bgrPixel2.val[0] * 0.3333 + bgrPixel2.val[1] * 0.3333 + bgrPixel2.val[2] * 0.3333;
            float mediaPond = bgrPixel3.val[0] * 0.07 + bgrPixel3.val[1] * 0.71 + bgrPixel3.val[2] * 0.21;
            
            bgrPixel2.val[0] = media; //B
            bgrPixel2.val[1] = media; //G
            bgrPixel2.val[2] = media; //R

            bgrPixel3.val[0] = mediaPond; //B
            bgrPixel3.val[1] = mediaPond; //G
            bgrPixel3.val[2] = mediaPond; //R
        }
    }

    imshow("Colorida", img);
    imshow("Grayscale Media Aritmetica", img2);
    imshow("Grayscale Media Ponderada", img3);
    waitKey(0);
    
    return 0;
}

void drawText(Mat& image)
{
    putText(image, "Hello OpenCV",
        Point(20, 50),
        FONT_HERSHEY_COMPLEX, 1, // font face and scale
        Scalar(255, 255, 255), // white
        1, LINE_AA); // line thickness and type
}
