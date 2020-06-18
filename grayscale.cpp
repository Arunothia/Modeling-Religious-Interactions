#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <bits/stdc++.h>
#include "grayscale.hpp"

using namespace std;
using namespace cv;

// yellow - 0, green -1, pink -2, o.w -3
int val = 0;
int Matrix[5000][5000];

int maxIndex(Vec3b p){
	if(p[0]>p[1]){
		if(p[0]>p[2])
			return 0;
		else
			return 2;
	}
	else{
		if(p[1]>p[2])
			return 1;
		else
			return 2;
	}
}

int minIndex(Vec3b p){
        if(p[0]<p[1]){
                if(p[0]<p[2])
                        return 0;
                else
                        return 2;
        }
        else{
                if(p[1]<p[2])
                        return 1;
                else
                        return 2;
        }
}

Mat convertToGrayscale(Mat input)
{
	Mat output = Mat(input.size(), CV_8UC1);

	for(int i = 0; i < input.rows; i++)
	{
		for(int j = 0; j < input.cols; j++)
		{
			Vec3b pixel = input.at<Vec3b>(i, j);
			int sum = (int) (pixel[0] + pixel[1] + pixel[2])/3;
			cout<<sum<<" ";	
			output.at<uchar>(i, j) = (pixel[0] + pixel[1] + pixel[2])/3;
		}
		cout<<endl;
	}

	return output;
}
