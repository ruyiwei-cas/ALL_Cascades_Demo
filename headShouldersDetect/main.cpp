#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include<time.h>
using namespace std;
using namespace cv;

//#define SHOW_SCORE

string face_cascade_name = "Cascades/haarcascade_frontalface_default.xml";
string hs_cascade_name = "Cascades/haarcascade_mcs_upperbody.xml";
string image_test_path = "list.txt";
CascadeClassifier face_cascade;
CascadeClassifier hs_cascade;


int main(int argc, char* argv[])
{
	fstream image_file;
	string image_path;
	fstream face_result, lihs_result;
	face_result.open("face_result.txt");
	lihs_result.open("lihs_result.txt");
	face_result.clear();
	lihs_result.clear();
	image_file.open(image_test_path);
	Mat image;
	face_cascade.load(face_cascade_name);
	hs_cascade.load(hs_cascade_name);
	vector<Rect>faces, faces_hq;
	Mat image_real;
	int a, b, angle, cx, cy;
	double score;
	vector<int> reject_levels, reject_levels_hq;
	vector<double> level_weights, level_weights_hq;
	while (!image_file.eof())
	{
		image_file >> image_path;
		/*if (image_path.length() <= 30)
		{
		image_path.erase(image_path.length() - 4, image_path.length() - 1);
		image_path = image_path + ".bmp";
		}
		if (image_path[0] == 'f')
		continue;*/

		image_real = imread(image_path);
		//image_path.erase(0,15);
		cvtColor(image_real, image, CV_BGR2GRAY);

		//cout << image_path << endl;
		//equalizeHist(image, image);

#ifdef SHOW_SCORE

		face_cascade.detectMultiScale(image, faces, reject_levels, level_weights, 1.1, 3, CV_HAAR_SCALE_IMAGE, Size(50, 50), Size(500, 500), true);
		hs_cascade.detectMultiScale(image, faces_hq, reject_levels_hq, level_weights_hq, 1.1, 3, CV_HAAR_SCALE_IMAGE, Size(50, 50), Size(500, 500), true);
		cout << image_path << endl;

		face_result << image_path << endl;
		lihs_result << image_path << endl;
		face_result << faces.size() << endl;
		lihs_result << faces_hq.size() << endl;
		for (int i = 0; i < faces.size(); i++)
		{

			/*rectangle(image_real, faces[i], Scalar(255, 0, 0), 8);
			putText(image_real, std::to_string(level_weights[i]),
			Point(faces[i].x, faces[i].y), 1, 2, Scalar(255, 0, 0));*/
			a = faces[i].width*0.5;
			b = faces[i].height*0.5;
			angle = 0;
			cx = faces[i].x + faces[i].width*0.5;
			cy = faces[i].y + faces[i].height*0.5;
			score = level_weights[i];
			if (a <= b)
				swap(a, b);

			face_result << b << " " << a << "	" << 0 << "	" << cx << " "
				<< cy << " " << score << endl;
			/*ellipse(image_real, Point(cx, cy), Size(a, b), 0, 0, 360, Scalar(255, 0, 0), 2, 7, 0);*/

		}


		//cascade.detectMultiScale(img, objs, reject_levels, level_weights, scale_factor, min_neighbors, 0, Size(), Size(), true);

		for (int i = 0; i < faces_hq.size(); i++)
		{
			/*rectangle(image_real, faces_hq[i], Scalar(0, 0, 255), 8);
			putText(image_real, std::to_string(level_weights_hq[i]),
			Point(faces_hq[i].x, faces_hq[i].y), 1, 2, Scalar(0, 0, 255));*/
			a = faces_hq[i].width*0.5;
			b = faces_hq[i].height*0.5;
			angle = 0;
			cx = faces_hq[i].x + faces_hq[i].width*0.5;
			cy = faces_hq[i].y + faces_hq[i].height*0.5;
			score = level_weights_hq[i];
			if (a <= b)
				swap(a, b);
			b = (b * 28) / 34;
			a = (a * 42) / 50;
			lihs_result << b << " " << a << "	" << 0 << "	" << cx << " "
				<< cy << " " << score << endl;
			/*	ellipse(image_real, Point(cx, cy), Size(a, b), 0, 0, 360, Scalar(0, 255, 255), 2, 7, 0);*/

		}


		//imshow("image", image_real);
		//waitKey(1);

		/*	image_path.erase(0, 5);
		image_path = "E:/FDDB/Images/irsi_new/" + image_path;
		image_path.erase(image_path.length() - 4, 4);
		image_path = image_path+".jpg";
		imwrite(image_path,image);*/

#endif

#ifndef SHOW_SCORE
		/*clock_t t1, t2, t3;
		t1 = clock();*/
		face_cascade.detectMultiScale(image, faces, 1.1, 3, CV_HAAR_SCALE_IMAGE, Size(50, 50), Size(500, 500));
		/*t2 = clock();*/
		hs_cascade.detectMultiScale(image, faces_hq, 1.1, 3, CV_HAAR_SCALE_IMAGE, Size(50, 50), Size(500, 500));
		/*t3 = clock();*/
		/*cout << "-------------" << endl;
		if ((t3 - t2) != 0)
		cout << double(t2 - t1) / double(t3 - t2) << endl;*/

		for (int i = 0; i < faces.size(); i++)
		{

			rectangle(image_real, faces[i], Scalar(255, 0, 0), 8);
			Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
			ellipse(image_real, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 0), 2, 7, 0);
		}
		//cascade.detectMultiScale(img, objs, reject_levels, level_weights, scale_factor, min_neighbors, 0, Size(), Size(), true);

		for (int i = 0; i < faces_hq.size(); i++)
		{
			rectangle(image_real, faces_hq[i], Scalar(0, 0, 255), 8);
			Point center(faces_hq[i].x + faces_hq[i].width*0.5, faces_hq[i].y + faces_hq[i].height*0.5);
			ellipse(image_real, center, Size(faces_hq[i].width*0.5, faces_hq[i].height*0.5), 0, 0, 360, Scalar(0, 0, 255), 2, 7, 0);
		}
#endif
		/*image_path.erase(3, 17);
		image_path.insert(3, "DETECT_RESULT_v4/");
		imwrite(image_path, image_real);*/
		imshow("image", image_real);
		waitKey(0);

	}
	face_result.close();
	lihs_result.close();
	return 0;
}