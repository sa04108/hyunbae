#pragma once
#include <iostream>
using namespace std;

class ScreenSize {
public:
	static int width_plus1; // plus1이 붙은 이유는 배열 사이사이에 엔터입력을 위한 \n이 들어가기 때문에, 처음부터 길이를 가로길이+1로 정한다.
	static int height;
	static int w_stored;
	static int h_stored;
};