#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int main(int argc, const char* argv[]) {
  if(argc<3) {
    cout << "Use: ./jodelMatcher racoonSample.png captcha.png [output.png]" << endl;
    return -1;
  }

  const Mat input1 = imread(argv[1], IMREAD_GRAYSCALE);
  const Mat input2 = imread(argv[2], IMREAD_GRAYSCALE);

  Ptr<SIFT> detector = SIFT::create();
  std::vector<KeyPoint> kp1, kp2;
  Mat descr1, descr2;
  std::vector< std::vector<DMatch> > matches;
  std::vector<DMatch> good;
  BFMatcher matcher;

  detector->detectAndCompute(input1, noArray(), kp1, descr1);
  detector->detectAndCompute(input2, noArray(), kp2, descr2);

  matcher.knnMatch(descr1, descr2, matches, 9);

  int i;
  int pos[9] = {};
  const float ratio = 0.6;
  for(i=0; i<matches.size(); i++) {
    if (matches[i][0].distance < ratio * matches[i][1].distance) {
      good.push_back(matches[i][0]);
      float x = kp2[matches[i][0].trainIdx].pt.x/240;
      pos[(int)x] = 1;
    }
  }

  for(i=0; i<9; i++) {
    if(pos[i]==1) {cout << i << " ";}
  }
  cout << endl;

  if(argc>=4) {
    Mat output;
    drawMatches(input1, kp1, input2, kp2, good, output);
    imwrite(argv[3], output);
  }

  return 0;
}
