#pragma once
#include <iostream>
using namespace std;

class ScreenSize {
public:
	static int width_plus1; // plus1�� ���� ������ �迭 ���̻��̿� �����Է��� ���� \n�� ���� ������, ó������ ���̸� ���α���+1�� ���Ѵ�.
	static int height;
	static int w_stored;
	static int h_stored;
};