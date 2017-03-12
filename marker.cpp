#include<iostream>
#include"stdafx.h"
#include<stack>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


using namespace std;
using namespace cv;

///////////////
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

Scalar color(0, 255, 0);
//////////////
int main(){

	Mat img;
	img = imread("C:\\Users\\Aakash Naik\\Pictures\\Screenshots\\marker.png");
	Mat img1(img.rows, img.cols, CV_8UC3,Scalar(0,0, 0));
	Mat img2(img.rows, img.cols, 0);
	Mat img3(img.rows, img.cols,  0);
	cvtColor(img, img1, CV_BGR2HSV);

	int i, j;
	for (i = 0; i < img.rows; i++)
	{
		for (j = 0; j < img.cols; j++)
		{
			if (img1.at<Vec3b>(i, j)[0] >2 && img1.at<Vec3b>(i, j)[0]<12)
			{
				img2.at<uchar>(i, j) = 255;
			}
			else
			{
				img2.at<uchar>(i, j) = 0;
			}
		}
	}
	i = 0;
	
	erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(img2, img2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	findContours(img2, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<RotatedRect> minRect(contours.size());
	cout << contours.size()<<"size";
	for (int i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(Mat(contours[i]));
	}

	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(0, 255, 0);

		Point2f rect_points[4]; minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
		{
			line(img, rect_points[j], rect_points[(j + 1) % 4], color, 2, 8);
		}
		if (norm(rect_points[0] - rect_points[1])>norm(rect_points[1] - rect_points[2]))//Euclidean distance norm(point1-point2)
			line(img, rect_points[0], rect_points[1], Scalar(0, 0, 255), 4, 8);
		else
			line(img, rect_points[1], rect_points[2], Scalar(155, 255, 0), 4, 8);
	}


	namedWindow("output", WINDOW_AUTOSIZE);
	imshow("output", img);
	//cout<<pnt1.x;
	waitKey(0);
	return 0;
}