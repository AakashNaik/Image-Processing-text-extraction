#include<iostream>
#include<stack>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

///////////////
 vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
RotatedRect minRect;
Scalar color(0,255,0);
//////////////
int main(int argc, char **argv){

    Mat img;
    img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat img1(img.rows, img.cols, CV_8UC3,Scalar(0,0,0));
    Mat img2(img.rows, img.cols, CV_8UC1, Scalar(0));
    Mat img3(img.rows, img.cols, CV_8UC1, Scalar(0));
    cvtColor(img, img1, CV_BGR2HSV);

    int i, j;
    for(i = 0; i < img.rows; i++)
      {
       for(j = 0; j < img.cols; j++)
            {
                if(img1.at<Vec3b>(i, j)[0] >2&&img1.at<Vec3b>(i,j)[0]<12)
                   {
                     img2.at<uchar>(i,j)=255;
                   }
                   else
                        {
                          img2.at<uchar>(i,j)=0;
                        }
            }
       }
          i=0;
     /*while(!contours.empty())
     {
       contours2[i]=contours[i];
       i++;
     }*/
    erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
     erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    findContours(img2, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    minRect = minAreaRect( Mat(contours) );

   Point2f rect_points[4];
   minRect.points( rect_points );
       for( int j = 0; j < 4; j++ )
	 {   line( img, rect_points[j], rect_points[(j+1)%4], color, 2, 8 );
		 }
       if(norm(rect_points[0]-rect_points[1])>norm(rect_points[1]-rect_points[2]))//Euclidean distance norm(point1-point2)
    line( img, rect_points[0], rect_points[1], color, 4, 8 );
  else
    line( img, rect_points[1], rect_points[2], color, 4, 8 );


    namedWindow("output", WINDOW_AUTOSIZE);
    imshow("output", img1);
//cout<<pnt1.x;
    waitKey(0);
    return 0;
}
