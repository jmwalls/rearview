#include <iostream>
#include <fstream>

#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;

const int RESIZE_BOX = 24;

class Classify
{
  public:
    Classify ()
        : _unlabeled ("unlabled_faces.txt")
    {}
    ~Classify () {}

    void identify (const Mat &im, const Rect &r)
    {
        Mat sub;
        resize (im (r), sub, Size (RESIZE_BOX, RESIZE_BOX)); 

        // should try to identify here

        write_unlabeled (sub);
    }

  private:
    ofstream _unlabeled;
    //ifstream _labeled;

    void write_unlabeled (Mat &im)
    {
        for (int i=0; i<im.rows; ++i)
            for (int j=0; j<im.cols; ++j) {
                _unlabeled << static_cast<int>(im.at<uchar> (i,j)) << "\t";
            }
        _unlabeled << endl;
    }
};

class Detector 
{
  public:
    Detector ()
        : _cascade ("../../data/haarcascade_frontalface_alt.xml")
    {}
    ~Detector () {}

    void find (Mat &im)
    {
        vector<Rect> rects;
        _cascade.detectMultiScale (im, rects, 1.2, 1, 0|CV_HAAR_SCALE_IMAGE, Size (100, 100));
        cout << "{Detector} detected " << rects.size () << " faces" << endl;
        for (auto &r : rects) {
            rectangle (im, r, CV_RGB (1,0,0), 2);
            _classifier.identify (im, r);
        }
    }

  private:
    CascadeClassifier _cascade;
    Classify _classifier;
};

int main (int argc, char *argv[])
{
    // camera
    VideoCapture capture (0);
    if (!capture.isOpened ()) {
        cerr << "{Capture} could not open video source" << endl;
        return EXIT_FAILURE;
    }
    cout << "{Capture} opened camera with fps : " << capture.get (CV_CAP_PROP_FPS) << endl
        << "                             resolution : " << capture.get (CV_CAP_PROP_FRAME_WIDTH) 
        << "x" << capture.get (CV_CAP_PROP_FRAME_HEIGHT) << endl;

    // detector
    Detector detect;

    cout << "{Capture} press any key to quit" << endl;
    Mat im;
    while (true) {
        capture >> im;
        //equalizeHist (im, imeq);

        detect.find (im);
        imshow ("Capture", im);

        int key = waitKey (30);
        if (key > 0) break;
    }

    return EXIT_SUCCESS;
}
