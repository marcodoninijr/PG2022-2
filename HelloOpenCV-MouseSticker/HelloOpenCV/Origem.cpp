#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;

enum mouseEvents { NONE, LEFTBUTTON_DOWN };

int mouseEvent = LEFTBUTTON_DOWN;
int mousex, mousey;
Mat imgNariz, imgAlpha;

void drawText(Mat& image);

void overlayImage(Mat* src, Mat* overlay, const Point& location)
{
    for (int y = max(location.y, 0); y < src->rows; ++y)
    {
        int fY = y - location.y;

        if (fY >= overlay->rows)
            break;

        for (int x = max(location.x, 0); x < src->cols; ++x)
        {
            int fX = x - location.x;

            if (fX >= overlay->cols)
                break;

            double opacity = ((double)overlay->data[fY * overlay->step + fX * overlay->channels() + 3]) / 255;

            for (int c = 0; opacity > 0 && c < src->channels(); ++c)
            {
                unsigned char overlayPx = overlay->data[fY * overlay->step + fX * overlay->channels() + c];
                unsigned char srcPx = src->data[y * src->step + x * src->channels() + c];
                src->data[y * src->step + src->channels() * x + c] = srcPx * (1. - opacity) + overlayPx * opacity;
            }
        }
    }
}



static void mouseCallback(int event, int x, int y, int flags, void* userdata) { //function to track mouse movement and click//
    if (event == EVENT_LBUTTONDOWN) { //when left button clicked//
        cout << "Left click has been made, Position:(" << x << "," << y << ")" << endl;
        mouseEvent = LEFTBUTTON_DOWN;
        mousex = x;
        mousey = y;
        cout << "lalalalalallalalallala" << endl;
        overlayImage(&imgAlpha, &imgNariz, Point(mousex-imgNariz.cols/2, mousey-imgNariz.rows/2));
        imshow("MainWindow", imgAlpha);
    }
    else if (event == EVENT_RBUTTONDOWN) { //when right button clicked//
        cout << "Rightclick has been made, Position:(" << x << "," << y << ")" << endl;
    }
    else if (event == EVENT_MBUTTONDOWN) { //when middle button clicked//
        cout << "Middleclick has been made, Position:(" << x << "," << y << ")" << endl;
    }
    else if (event == EVENT_MOUSEMOVE) { //when mouse pointer moves//
        cout << "Current mouse position:(" << x << "," << y << ")" << endl;
    }
}

int main()
{
    cout << "Built with OpenCV " << CV_VERSION << endl;
    //Mat image;

    Mat imgOriginal;
    Mat imgCinza, imgBlur, imgCanny, imgBlurCanny, imgDilate, imgErode;
    Mat imgCrop, imgReSize, imgScale;

    

    imgOriginal = imread("pikachu.jpg");

    resize(imgOriginal, imgScale, Size(), 0.5, 0.5);
    cvtColor(imgScale, imgCinza, COLOR_BGR2GRAY);
    GaussianBlur(imgCinza, imgBlur, Size(5, 5), 5, 0);

    Mat grad_x, grad_y;
    Sobel(imgBlur, grad_x, CV_16S, 1, 0, 1, 1, 0, BORDER_DEFAULT);
    Sobel(imgBlur, grad_y, CV_16S, 0, 1, 1, 1, 0, BORDER_DEFAULT);

    Mat abs_grad_x, abs_grad_y, grad;

    // converting back to CV_8U
    convertScaleAbs(grad_x, abs_grad_x);
    convertScaleAbs(grad_y, abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    
    imshow("Sobel Result", grad);

    //Canny
    Canny(imgCinza, imgCanny, 25, 75);
    Canny(imgBlur, imgBlurCanny, 25, 75);

    Mat imgEqual;
    equalizeHist(imgBlur, imgEqual);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    
    dilate(imgBlurCanny, imgDilate, kernel);
    erode(imgDilate, imgErode, kernel);


   


    Rect areaCrop(100, 100, 50, 50); //a partir do ponto 100x100 recorto uma area de 200/200
    //novaIMG  img Base   area do crop
    imgCrop = imgOriginal(areaCrop);

    //imgCrop.copyTo(imgScale.rowRange(300, 350).colRange(300, 350));
    
    imgNariz = imread("nariz.png", IMREAD_UNCHANGED);
    resize(imgNariz, imgNariz, Size(), 0.2, 0.2);
   
    cvtColor(imgScale, imgAlpha, COLOR_BGR2BGRA); //converte para 4 canais

    namedWindow("MainWindow", WINDOW_AUTOSIZE);
    imshow("MainWindow", imgAlpha);
    setMouseCallback("MainWindow", mouseCallback, NULL);//Mouse callback function on define window//


    for (;;)
    {
        char c = (char)waitKey();

        if (c == 27)
            break;
     
        //imgNariz.copyTo(imgAlpha.rowRange(150, 150+185).colRange(150, 150 + 185));



        
        //imshow("Pikachu Grayscale", imgCinza);
        //imshow("Pikachu Borrado", imgBlur);
        //imshow("Pikachu Borda 1", imgCanny);
        //imshow("Pikachu Borda 2", imgBlurCanny);
        //imshow("Pikachu Equalizado", imgEqual);
        //imshow("Pikachu Dilatado", imgDilate);
        //imshow("Pikachu Erodido", imgErode);
        imshow("Pikachu cortado", imgCrop);
        
    }
    

   

    /*VideoCapture capture;
    capture.open(0);
    if (capture.isOpened())
    {
        cout << "Capture is opened" << endl;
        for (;;)
        {
            capture >> image;
            if (image.empty())
                break;
            drawText(image);
            imshow("Sample", image);
            if (waitKey(10) >= 0)
                break;
        }
    }
    else
    {
        cout << "No capture" << endl;
        image = Mat::zeros(480, 640, CV_8UC1);
        drawText(image);
        imshow("Sample", image);
        waitKey(0);
    }*/
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
