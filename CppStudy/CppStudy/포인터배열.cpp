#include <stdio.h>

int main()
{
	const char *nameArr[4] = { "NewYork", "Sanfransisco", "Washington", "California" }; // ������������͹迭, �迭���� ���� �ٲ� �� ����. �� �ε������� ���ڿ�����̰� �����͹迭�� �� ������� �ּҰ��� ���� �����͵�� �̷�����ִ�.

	for (int i = 0; i < 4; i++)
	{
		printf("1. nameArr[%d] �� �� : %p => %s �� ����Ǿ��ִ� �޸��� �ּ�\n2. &nameArr[%d] �� �� : %p\n3. *(nameArr + %d) �� �� : %s\n4. nameArr + %d �� �� : %p\n\n", i, nameArr[i], *(nameArr + i), i, &nameArr[i], i, *(nameArr + i), i, nameArr + i);
	}

	return 0;
}