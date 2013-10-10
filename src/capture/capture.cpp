#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

int main (int argc, char *argv[])
{
    VideoCapture capture (0);
    if (!capture.isOpened ()) {
        cerr << "{Capture} could not open video source" << endl;
        return EXIT_FAILURE;
    }
    //capture.set (CV_CAP_PROP_FPS, 10);

    Mat im;
    while (true) {
        capture >> im;
        imshow ("Capture", im);

        int key = waitKey (30);
        if (key > 0) break;
    }
    imwrite ("capture.png", im);

    return EXIT_SUCCESS;
}
