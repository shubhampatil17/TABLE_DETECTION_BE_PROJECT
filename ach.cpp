#include <iostream>
#include "ach.h"

using namespace std;

int calculateACH(Mat img){

	Mat labels(img.rows,img.cols,img.type());

	Mat stats;
	Mat centroids;

	int totalLabels=connectedComponentsWithStats(img,labels,stats,centroids,8,CV_32S);

	cout<<"Total Number of Labels :"<<totalLabels<<"\n";

	int max=0;

	for(int i=0;i<totalLabels;i++){
		if(stats.at<int>(i,CC_STAT_HEIGHT)>max){
			max=stats.at<int>(i,CC_STAT_HEIGHT);
		}
	}

	cout<<"Max height :"<<max<<"\n";

	Mat Histogram= Mat::zeros(1,max,CV_32SC1);

	for(int i=0;i<totalLabels;i++){
		Histogram.at<int>((int)stats.at<int>(i,CC_STAT_HEIGHT)-1)++;
	}

	int avgchar=3;

	for(int i=4;i<Histogram.cols;i++){
		if(Histogram.at<int>(0,i)> Histogram.at<int>(0,avgchar)){

			avgchar=i;
		}
	}

	avgchar++;


	cout<<"Average Character Height :"<<avgchar<<"\n";


	return avgchar;
}
