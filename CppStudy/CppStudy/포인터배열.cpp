#include <stdio.h>

int main()
{
	const char *nameArr[4] = { "NewYork", "Sanfransisco", "Washington", "California" }; // 상수지시포인터배열, 배열안의 값을 바꿀 수 없다. 각 인덱스들은 문자열상수이고 포인터배열은 그 상수들의 주소값을 가진 포인터들로 이루어져있다.

	for (int i = 0; i < 4; i++)
	{
		printf("1. nameArr[%d] 의 값 : %p => %s 가 저장되어있는 메모리의 주소\n2. &nameArr[%d] 의 값 : %p\n3. *(nameArr + %d) 의 값 : %s\n4. nameArr + %d 의 값 : %p\n\n", i, nameArr[i], *(nameArr + i), i, &nameArr[i], i, *(nameArr + i), i, nameArr + i);
	}

	return 0;
}