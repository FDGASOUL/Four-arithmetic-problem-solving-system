#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
#include<string.h>
#include <iostream>
#include <stack>
using namespace std;
struct test {
	char texts[50];
	int result;
	int wrong;
}sql[50];
typedef struct S1				//����S1ջ 
{
	char Char[200];
	int top;
}S1;
typedef struct S2				//����S2ջ 
{
	double num[200];
	int top;
}S2;
class Stack {
private:
	char s2[200];
public:
	Stack(char* s1, int m) {
		Suffix(s1, s2);
		Calculate(s2, m);
	}
	char* GetS2() {
		return s2;
	}
	int Yxj(char);				                    //����Ԫ�����ȼ� 
	int TopYxj(char);				                //����ջ��Ԫ�����ȼ� 
	void cshS1(S1*);				                //��S1ջ��ʼ��
	void cshS2(S2*);				                //��S2ջ��ʼ��
	int FirstS1(S1*, char);			                //��S1ջ����ѹջ 
	int FirstS2(S2*, double);	                    //��S2����ѹջ
	char TotopS1(S1*);				                //����ջ��Ԫ�� 
	char OutS1(S1*);				                //S1��ջ 
	double OutS2(S2*);				                //S2��ջ 
	void Suffix(char* s1, char* s2);		        //��׺���ʽת��Ϊ��׺���ʽ 
	void Calculate(char* s2, int m); 	                    //�Ժ�׺���ʽ����������ֵ 
};
void Stack::cshS1(S1* a)
{
	a->top = -1;
}
void Stack::cshS2(S2* a)
{
	a->top = -1;
}
int Stack::FirstS1(S1* a, char b)
{
	if (a->top < 200)
	{
		a->Char[++a->top] = b;
		return 1;
	}
	else return 0;
}
int Stack::FirstS2(S2* a, double b)
{
	if (a->top < 200)
	{
		a->num[++a->top] = b;
		return 1;
	}
	else return 0;
}
char Stack::TotopS1(S1* a)
{
	return a->Char[a->top];
}
char Stack::OutS1(S1* a)
{
	return a->Char[a->top--];
}
double Stack::OutS2(S2* a)
{
	return a->num[a->top--];
}
int Stack::Yxj(char a)
{
	switch (a)
	{
	case '(': return 6;
	case '*': return 4;
	case '/': return 4;
	case '+': return 2;
	case '-': return 2;
	}
}
int Stack::TopYxj(char a)
{
	switch (a)
	{
	case '(': return 1;
	case '+': return 3;
	case '-': return 3;
	case '*': return 5;
	case '/': return 5;
	}
}
void Stack::Suffix(char* s1, char* s2)
{
	int i = 0, j = 0, F = -1, f = -1;
	S1 B;
	cshS1(&B);
	for (; s1[i] != '\0'; i++)
	{
		if (s1[0] == '-')
		{
			j = strlen(s1);
			for (; j > 0; j--)
			{
				s1[j + 5] = s1[j];
			}
			s1[j++] = '(';
			s1[j++] = '0';
			s1[j++] = '-';
			s1[j++] = '1';
			s1[j++] = ')';
			s1[j] = '*';
		}
		if (s1[i] == '(' && s1[i + 1] == '-')
		{
			j = strlen(s1);
			for (; j > i + 1; j--)
			{
				s1[j + 5] = s1[j];
			}
			s1[j++] = '(';
			s1[j++] = '0';
			s1[j++] = '-';
			s1[j++] = '1';
			s1[j++] = ')';
			s1[j] = '*';
			i = i + 5;
		}
	}
	i = 0;
	j = 0;
	for (; s1[i] != '\0'; i++)
	{
		if (F == 0 && f == 1)
		{
			s2[j++] = ' ';
			F = 1;
		}
		if (s1[i] >= '0' && s1[i] <= '9' || s1[i] == '.')
		{
			s2[j++] = s1[i];
			f = 0;
			F = 0;
		}
		else if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/' || s1[i] == '(')
		{
			f = 1;
			if (B.top<0 || Yxj(s1[i])>TopYxj(TotopS1(&B)))
			{
				FirstS1(&B, s1[i]);
			}
			else
			{
				for (; B.top >= 0 && Yxj(s1[i]) < TopYxj(TotopS1(&B));)
				{
					s2[j++] = OutS1(&B);
					F = 1;
				}
				if (B.top<0 || Yxj(s1[i])>TopYxj(TotopS1(&B)))
				{
					FirstS1(&B, s1[i]);
				}

			}
		}
		else if (s1[i] == ')')
		{
			f = 1;
			if (TotopS1(&B) != '(')
			{
				F = 1;
			}
			while (TotopS1(&B) != '(')
			{
				s2[j++] = OutS1(&B);
			}
			OutS1(&B);
		}
	}
	for (; B.top >= 0;)
	{
		s2[j++] = OutS1(&B);
	}
	s2[j] = '\0';
}
void Stack::Calculate(char* s1, int m)
{
	int i = 0, f;
	double a, b, sum;
	S2 A;
	cshS2(&A);
	for (; s1[i] != '\0'; i++)
	{
		if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/')
		{
			a = OutS2(&A);
			b = OutS2(&A);
			if (s1[i] == '+') FirstS2(&A, a + b);
			else if (s1[i] == '-') FirstS2(&A, b - a);
			else if (s1[i] == '*') FirstS2(&A, b * a);
			else if (s1[i] == '/') FirstS2(&A, b / a);
		}
		else
		{
			f = 0;
			sum = 0;
			double divider = 1;
			for (; s1[i] != ' ' && s1[i] != '+' && s1[i] != '-' && s1[i] != '*' && s1[i] != '/'; i++)
			{
				if (s1[i] == '.')
				{
					f = 1;
					i++;
					continue;
				}
				if (f == 0)
				{
					sum = sum * 10 + (double)(s1[i] - '0');
				}
				else
				{
					divider = divider * 10;
					sum = sum + ((double)(s1[i] - '0')) / divider;
				}
			}
			if (s1[i] == '+' || s1[i] == '-' || s1[i] == '*' || s1[i] == '/') i--;
			FirstS2(&A, sum);
		}
	}
	sql[m].result = OutS2(&A);
}
void readPra(int num)
{
	int i = 0;
	FILE* fp = NULL;
	fp = fopen("problem.txt", "r");
	while (i < num)
	{
		fscanf(fp, "%s", sql[i].texts);
		i++;
	}
}
char* Num(int n)
{
	int num;
	num = rand() % n;
	char str[128] = { 0 };
	sprintf_s(str, "%d", num);
	return str;
}
char* Sign1()
{
	int num;
	char i[128];
	num = rand() % 11;
	for (; num > 1;)
	{
		num = rand() % 11;
	}
	if (num == 0)
	{
		strcpy(i, "+");
		return i;
	}
	else if (num == 1)
	{
		strcpy(i, "-");
		return i;
	}
}
char* Sign2()
{

	int num;
	char i[128];
	num = rand() % 11;
	for (; num > 1;)
	{
		num = rand() % 11;
	}
	if (num == 0)
	{
		strcpy(i, "*");
		return i;
	}
	else if (num == 1)
	{
		strcpy(i, "/");
		return i;
	}
}
char* Sign()
{
	int num;
	char i[128];
	num = rand() % 11;
	for (; num > 3;)
	{
		num = rand() % 11;
	}
	if (num == 0)
	{
		strcpy(i, "*");
		return i;
	}
	else if (num == 1)
	{
		strcpy(i, "/");
		return i;
	}
	else if (num == 2)
	{
		strcpy(i, "+");
		return i;
	}
	else if (num == 3)
	{
		strcpy(i, "-");
		return i;
	}
}
int op()		//�������
{
	int num;
	num = rand() % 11;
	for (; num > 8;)
	{
		num = rand() % 11;
	}
	return num;
}
int op1()
{
	int num;
	num = rand() % 3;
	return num;
}
void Random(int n, int nums,int diffic)
{
	int num, i = 0;
	char str[128];
	srand(time(NULL));
	switch (diffic)
	{
		char e0[128], e1[128], e2[128], e3[128], e4[128], e5[128], e6[128], e7[128], e8[128], e9[128];
		int j, flag;
	case 1://�ӷ�
		for (i = 0; i < nums; i++)
		{
			num = op1();
			switch (num)
			{
			case 0:
				strcpy(e0, Num(n));
				strcpy(e1, "+");
				strcpy(e2, Num(n));
				strcpy(e3, "+");
				strcpy(e4, Num(n));
				strcpy(e5, "=");
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			case 1:
				strcpy(e0, Num(n));
				strcpy(e1, "+");
				strcpy(e2, Num(n));
				strcpy(e3, "+");
				strcpy(e4, Num(n));
				strcpy(e5, "+");
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, "+");
				strcpy(e2, Num(n));
				strcpy(e3, "=");
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			}
		}
		break;
	case 2://����
		for (i = 0; i < nums; i++)
		{
			num = op1();
			switch (num)
			{
			case 0:
				strcpy(e0, Num(n));
				strcpy(e1, "-");
				strcpy(e2, Num(n));
				strcpy(e3, "-");
				strcpy(e4, Num(n));
				strcpy(e5, "=");
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			case 1:
				strcpy(e0, Num(n));
				strcpy(e1, "-");
				strcpy(e2, Num(n));
				strcpy(e3, "-");
				strcpy(e4, Num(n));
				strcpy(e5, "-");
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, "-");
				strcpy(e2, Num(n));
				strcpy(e3, "=");
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			}
		}
		break;
	case 3://�˷�
		for (i = 0; i < nums; i++)
		{
			num = op1();
			switch (num)
			{
			case 0:
				strcpy(e0, Num(n));
				strcpy(e1, "*");
				strcpy(e2, Num(n));
				strcpy(e3, "*");
				strcpy(e4, Num(n));
				strcpy(e5, "=");
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			case 1:
				strcpy(e0, Num(n));
				strcpy(e1, "*");
				strcpy(e2, Num(n));
				strcpy(e3, "*");
				strcpy(e4, Num(n));
				strcpy(e5, "*");
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, "*");
				strcpy(e2, Num(n));
				strcpy(e3, "=");
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			}
		}
		break;
	case 4://����
		for (i = 0; i < nums; i++)
		{
			num = op1();
			switch (num)
			{
			case 0:
				strcpy(e0, Num(n));
				strcpy(e1, "/");
				strcpy(e2, Num(n));
				strcpy(e3, "/");
				strcpy(e4, Num(n));
				strcpy(e5, "=");
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 1:
				strcpy(e0, Num(n));
				strcpy(e1, "/");
				strcpy(e2, Num(n));
				strcpy(e3, "=");
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, "/");
				strcpy(e2, Num(n));
				strcpy(e3, "=");
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			}
		}
		break;
	case 5://�Ӽ����
		for (i = 0; i < nums; i++)
		{
			num = op1();
			switch (num)
			{
			case 0:
				strcpy(e0, Num(n));
				strcpy(e1, Sign1());
				strcpy(e2, Num(n));
				strcpy(e3, Sign1());
				strcpy(e4, Num(n));
				strcpy(e5, "=");
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			case 1:
				strcpy(e0, Num(n));
				strcpy(e1, Sign1());
				strcpy(e2, Num(n));
				strcpy(e3, Sign1());
				strcpy(e4, Num(n));
				strcpy(e5, Sign1());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, Sign1());
				strcpy(e2, Num(n));
				strcpy(e3, Sign1());
				strcpy(e4, Num(n));
				strcpy(e5, Sign1());
				strcpy(e6, Num(n));
				strcpy(e7, Sign1());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				strcpy(sql[i].texts, e0);
				continue;
			}
		}
		break;
	case 6://�˳����
		for (i = 0; i < nums; i++)
		{
			num = op1();
			switch (num)
			{
			case 0:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, Num(n));
				strcpy(e5, "=");
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 1:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, Num(n));
				strcpy(e5, Sign2());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, Num(n));
				strcpy(e5, Sign2());
				strcpy(e6, Num(n));
				strcpy(e7, Sign2());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			}
		}
		break;
	case 7://��������
		for (i = 0; i < nums; i++)
		{
			num = op1();
			switch (num)
			{
			case 0:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, Num(n));
				strcpy(e3, Sign());
				strcpy(e4, Num(n));
				strcpy(e5, "=");
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 1:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, Num(n));
				strcpy(e3, Sign());
				strcpy(e4, Num(n));
				strcpy(e5, Sign());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, Num(n));
				strcpy(e3, Sign());
				strcpy(e4, Num(n));
				strcpy(e5, Sign());
				strcpy(e6, Num(n));
				strcpy(e7, Sign());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			}
		}
		break;
	case 8://����������
		for (i = 0; i < nums; i++)
		{
			num = op();
			switch (num)
			{
			case 0:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign1());
				strcpy(e3, Num(n));
				strcpy(e4, ")");
				strcpy(e5, Sign2());
				strcpy(e6, Num(n));
				strcpy(e7, Sign());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 1:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign1());
				strcpy(e3, Num(n));
				strcpy(e4, ")");
				strcpy(e5, Sign());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, "(");
				strcpy(e3, Num(n));
				strcpy(e4, Sign1());
				strcpy(e5, Num(n));
				strcpy(e6, ")");
				strcpy(e7, Sign());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 3:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, "(");
				strcpy(e3, Num(n));
				strcpy(e4, Sign1());
				strcpy(e5, Num(n));
				strcpy(e6, ")");
				strcpy(e7, Sign());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 4:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, "(");
				strcpy(e5, Num(n));
				strcpy(e6, Sign1());
				strcpy(e7, Num(n));
				strcpy(e8, ")");
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 5:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, "(");
				strcpy(e5, Num(n));
				strcpy(e6, Sign1());
				strcpy(e7, Num(n));
				strcpy(e8, ")");
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 6:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, "(");
				strcpy(e3, Num(n));
				strcpy(e4, Sign());
				strcpy(e5, Num(n));
				strcpy(e6, Sign());
				strcpy(e7, Num(n));
				strcpy(e8, ")");
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 7:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign());
				strcpy(e3, Num(n));
				strcpy(e4, Sign());
				strcpy(e5, Num(n));
				strcpy(e6, ")");
				strcpy(e7, Sign2());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 8:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, "(");
				strcpy(e3, Num(n));
				strcpy(e4, Sign());
				strcpy(e5, Num(n));
				strcpy(e6, Sign());
				strcpy(e7, Num(n));
				strcpy(e8, ")");
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			}
		}
		break;
	case 9://��С������
		for (i = 0; i < nums; i++)
		{
			num = op();
			switch (num)
			{
			case 0:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign1());
				strcpy(e3, Num(n));
				strcpy(e4, ")");
				strcpy(e5, Sign2());
				strcpy(e6, Num(n));
				strcpy(e7, Sign());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 1:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign1());
				strcpy(e3, Num(n));
				strcpy(e4, ")");
				strcpy(e5, Sign());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, "(");
				strcpy(e3, Num(n));
				strcpy(e4, Sign1());
				strcpy(e5, Num(n));
				strcpy(e6, ")");
				strcpy(e7, Sign());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 3:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, Num(n));
				strcpy(e3, Sign1());
				strcpy(e4, Num(n));
				strcpy(e5, Sign2());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 4:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, "(");
				strcpy(e5, Num(n));
				strcpy(e6, Sign1());
				strcpy(e7, Num(n));
				strcpy(e8, ")");
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 5:
				strcpy(e0, Num(n));
				strcpy(e1, Sign1());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, Num(n));
				strcpy(e5, Sign1());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 6:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, "(");
				strcpy(e3, Num(n));
				strcpy(e4, Sign());
				strcpy(e5, Num(n));
				strcpy(e6, Sign());
				strcpy(e7, Num(n));
				strcpy(e8, ")");
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 7:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign());
				strcpy(e3, Num(n));
				strcpy(e4, Sign());
				strcpy(e5, Num(n));
				strcpy(e6, ")");
				strcpy(e7, Sign2());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 8:
				strcpy(e0, Num(n));
				strcpy(e1, Sign1());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, Num(n));
				strcpy(e5, "=");
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			}
		}
		break;
	case 10://�������
		for (i = 0; i < nums; i++)
		{
			num = op();
			switch (num)
			{
			case 0:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign1());
				strcpy(e3, Num(n));
				strcpy(e4, ")");
				strcpy(e5, Sign2());
				strcpy(e6, Num(n));
				strcpy(e7, Sign());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 1:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign1());
				strcpy(e3, Num(n));
				strcpy(e4, ")");
				strcpy(e5, Sign());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 2:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, "(");
				strcpy(e3, Num(n));
				strcpy(e4, Sign1());
				strcpy(e5, Num(n));
				strcpy(e6, ")");
				strcpy(e7, Sign());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 3:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, Num(n));
				strcpy(e3, Sign1());
				strcpy(e4, Num(n));
				strcpy(e5, Sign2());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 4:
				strcpy(e0, Num(n));
				strcpy(e1, Sign());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, "(");
				strcpy(e5, Num(n));
				strcpy(e6, Sign1());
				strcpy(e7, Num(n));
				strcpy(e8, ")");
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 5:
				strcpy(e0, Num(n));
				strcpy(e1, Sign1());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, Num(n));
				strcpy(e5, Sign1());
				strcpy(e6, Num(n));
				strcpy(e7, "=");
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 6:
				strcpy(e0, Num(n));
				strcpy(e1, Sign2());
				strcpy(e2, "(");
				strcpy(e3, Num(n));
				strcpy(e4, Sign());
				strcpy(e5, Num(n));
				strcpy(e6, Sign());
				strcpy(e7, Num(n));
				strcpy(e8, ")");
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 7:
				strcpy(e0, "(");
				strcpy(e1, Num(n));
				strcpy(e2, Sign());
				strcpy(e3, Num(n));
				strcpy(e4, Sign());
				strcpy(e5, Num(n));
				strcpy(e6, ")");
				strcpy(e7, Sign2());
				strcpy(e8, Num(n));
				strcpy(e9, "=");
				strcat(e8, e9);
				strcat(e7, e8);
				strcat(e6, e7);
				strcat(e5, e6);
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			case 8:
				strcpy(e0, Num(n));
				strcpy(e1, Sign1());
				strcpy(e2, Num(n));
				strcpy(e3, Sign2());
				strcpy(e4, Num(n));
				strcpy(e5, "=");
				strcat(e4, e5);
				strcat(e3, e4);
				strcat(e2, e3);
				strcat(e1, e2);
				strcat(e0, e1);
				j = 0;
				flag = 0;
				for (j = 0; e0[j + 1] != '\0'; j++)
				{
					if (e0[j] == '/' && e0[j + 1] == '0')flag = 1;
				}
				if (flag == 1)
				{
					i--;
					continue;
				}
				strcpy(sql[i].texts, e0);
				continue;
			}
		}
		break;
	}
	
}
void Practice(int n)
{
	int num, i = 0, m = 0, p, f,diffic;
	char str[128];
	srand(time(NULL));
	printf("��ѡ��������\n");
	printf("---------------------\n");
	printf("1.�ӷ�����\n");
	printf("---------------------\n");
	printf("2.��������\n");
	printf("---------------------\n");
	printf("3.�˷�����\n");
	printf("---------------------\n");
	printf("4.��������\n");
	printf("---------------------\n");
	printf("5.�Ӽ��������\n");
	printf("---------------------\n");
	printf("6.�˳��������\n");
	printf("---------------------\n");
	printf("7.����������\n");
	printf("---------------------\n");
	printf("8.�����ŵ�����������\n");
	printf("---------------------\n");
	printf("9.��С��������������\n");
	printf("---------------------\n");
	scanf("%d", &diffic);
	system("cls");
	for (; m == 0;)
	{
		Random(n, 1, diffic);
		printf("%s", sql[i].texts);
		Stack A(sql[i].texts, i);
		scanf("%d", &f);
		if (sql[i].result == f)
		{
			printf("����ȷ\n");
		}
		else
		{
			printf("�𰸴���\n");
			printf("��ȷ��Ϊ��%d\n", sql[i].result);
		}

		printf("�Ƿ������ϰ\n");
		printf("----------------\n");
		printf("1.��\n2.��\n");
		printf("----------------\n");
		scanf("%d", &p);
		system("cls");
		while (p != 1 && p != 2)
		{
			printf("ѡ�����������ѡ��");
			scanf("%d", &p);
		}
		system("cls");
		if (p == 2)
		{
			m = 1;
		}
	}
}
void Answer(int num)
{
	int m;

	for (m = 0; m < num; m++)
	{
		Stack A(sql[m].texts, m);
	}
}
int userAnswer(int num)
{
	int i, j, m,txt;
	FILE* fp;
	double p, q, trueNum = 0;
	q = num;
	int result;
	for (i = 0; i < 50; i++)
	{
		sql[i].wrong = 0;
	}
	for (i = 0; i < num; i++)
	{
		printf("��%i����Ŀ��%s", i + 1, sql[i].texts);
		scanf("%d", &result);
		if (result == sql[i].result)
			trueNum++;
		else
		{
			sql[i].wrong = 1;
		}
	}
	p = trueNum / q * 100;
	printf("��һ�������%.0lf����Ŀ����ȷ��Ϊ%.0lf%%\n", trueNum, p);
	fp = fopen("�ϴγɼ�.txt", "r");
	fscanf(fp, "%d", &m);
	fclose(fp);
	fp = fopen("�滻.txt", "w+");
	fclose(fp);
	remove("�ϴγɼ�.txt");
	rename("�滻.txt", "�ϴγɼ�.txt");
	fp = fopen("�ϴγɼ�.txt", "a");
	fprintf(fp, "%.0lf", p);
	fclose(fp);
	fp = fopen("��ʷ�ɼ�.txt", "a");
	fprintf(fp, "%.0lf\n", trueNum);
	fclose(fp);
	if (m < p)
	{
		printf("----------------\n");
		printf("���ϴβ�����ȷ��Ϊ%d%%\n", m);
		printf("��ϲ������ˣ�\n");
		printf("----------------\n");
	}
	else if (m > p)
	{
		printf("----------------\n");
		printf("���ϴβ�����ȷ��Ϊ%d%%\n", m);
		printf("�˲���Ŷ�������Ŭ����\n");
		printf("----------------\n");
	}
	else
	{
		printf("----------------\n");
		printf("���ϴβ�����ȷ��Ϊ%d%%\n", m);
		printf("���ϴ�ȡ����һ���ĳɼ��ء�\n");
		printf("----------------\n");
	}
	for (i = 0; i < num; i++)
	{
		if (sql[i].wrong == 1)
		{
			fp = fopen("���Ȿ.txt", "a");
			fprintf(fp, "%s%d\n", sql[i].texts, sql[i].result);
			fclose(fp);
		}
	}
	printf("������Ŀ�Ѿ����浽���Ȿ��\n");
	printf("�Ƿ�鿴���⣿\n");
	printf("----------------\n");
	printf("1.��\n2.��\n");
	printf("----------------\n");
	scanf("%d", &j);
	while (j != 1 && j != 2)
	{
		printf("ѡ�����������ѡ��");
		scanf("%d", &j);
	}
	if (j == 1)
	{
		printf("����Ϊ������Ŀ\n");
		for (i = 0; i < 50; i++)
		{
			if (sql[i].wrong == 1)
			{
				printf("%s%d\n", sql[i].texts, sql[i].result);
			}
		}
		system("pause");
	}
	system("cls");
	printf("�Ƿ񽫲��Խ����ӡ��.txt�ļ���\n");
	printf("----------------\n");
	printf("1.��\n2.��\n");
	printf("----------------\n");
	scanf("%d", &txt);
	while (txt != 1 && txt != 2)
	{
		printf("ѡ�����������ѡ��");
		scanf("%d", &txt);
	}
	if (txt == 1)
	{
		for (i = 0; i < num; i++)
		{
			if (sql[i].wrong == 1|| sql[i].wrong == 0)
			{
				fp = fopen("���Խ��.txt", "a");
				fprintf(fp, "%s%d\n", sql[i].texts, sql[i].result);
				fclose(fp);
			}
		}

		fp = fopen("���Խ��.txt", "a");
		fprintf(fp, "%s\n","--------------------------");
		fclose(fp);
		system("cls");
		printf("�ѽ����β��Խ������������Խ��.txt���ļ�����������ʱ�鿴");
		printf("----------------\n");
		printf("1.ȷ��\n");
		printf("----------------\n");
		scanf("%d", &txt);
	}
	return 0;
}
int main()
{
	int s = 0, t, i, His, num,diffic;
	FILE* fp;
	char Wro[100];
	for (; s == 0;)
	{
		printf("��ӭʹ��Сѧ������������ϰ������ϵͳ\n");
		printf("��ѡ����Ŀ�Ѷȣ�\n");
		printf("----------------\n");
		printf("1.10����\n2.100����\n3.1000����\n");
		printf("----------------\n");
		int a, b, c, m, n;
		scanf("%d", &a);
		system("cls");
		while (a != 1 && a != 2 && a != 3)
		{
			printf("ѡ�����������ѡ��");
			scanf("%d", &a);
		}
		system("cls");
		if (a == 1)
		{
			n = 11;
			printf("��ѡ���Ի���ϰ��\n");
			printf("----------------\n");
			printf("1.����\n2.������ϰ\n3.���Ȿ\n4.��ʷ�ɼ�\n");
			printf("----------------\n");
			scanf("%d", &b);
			system("cls");
			while (b != 1 && b != 2 && b != 3 && b != 4)
			{
				printf("ѡ�����������ѡ��");
				scanf("%d", &b);
			}
			system("cls");
			if (b == 1)
			{
				printf("��ѡ���Է�ʽ��\n");
				printf("----------------\n");
				printf("1.ϵͳ�������\n2.������Ŀ\n");
				printf("----------------\n");
				scanf("%d", &c);
				system("cls");
				while (c != 1 && c != 2)
				{
					printf("ѡ�����������ѡ��");
					scanf("%d", &c);
				}
				system("cls");
				if (c == 1)
				{
					printf("��ѡ������Ŀ������\n");
					scanf("%d", &num);
					system("cls");
					printf("��ѡ��������\n");
					printf("---------------------\n");
					printf("1.�ӷ�����\n");
					printf("---------------------\n");
					printf("2.��������\n");
					printf("---------------------\n");
					printf("3.�˷�����\n");
					printf("---------------------\n");
					printf("4.��������\n");
					printf("---------------------\n");
					printf("5.�Ӽ��������\n");
					printf("---------------------\n");
					printf("6.�˳��������\n");
					printf("---------------------\n");
					printf("7.����������\n");
					printf("---------------------\n");
					printf("8.�����ŵ�����������\n");
					printf("---------------------\n");
					printf("9.��С��������������\n");
					printf("---------------------\n");
					printf("10.��ѡ�ˣ�������\n");
					printf("---------------------\n");
					scanf("%d", &diffic);
					system("cls");
					Random(n, num,diffic);
					Answer(num);
					userAnswer(num);
				}
				else if (c == 2)
				{
					printf("��ѡ������Ŀ������\n");
					scanf("%d", &num);
					readPra(num);
					Answer(num);
					userAnswer(num);
				}
			}
			else if (b == 2)
			{
				Practice(n);
			}
			else if (b == 3)
			{
				printf("����Ϊ�������������Ŀ��\n");
				fp = fopen("���Ȿ.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%s", &Wro);
					printf("%s", Wro);
					printf("\n");
				}
				fclose(fp);
				system("pause");
			}
			else if (b == 4)
			{
				fp = fopen("��ʷ�ɼ�.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%d", &His);
					printf("������%d����\n", His);
					printf("----------------\n");
				}
				fclose(fp);
				system("pause");
			}
		}
		else if (a == 2)
		{
			n = 101;
			printf("��ѡ���Ի���ϰ��\n");
			printf("----------------\n");
			printf("1.����\n2.������ϰ\n3.���Ȿ\n4.��ʷ�ɼ�\n");
			printf("----------------\n");
			scanf("%d", &b);
			system("cls");
			while (b != 1 && b != 2 && b != 3 && b != 4)
			{
				printf("ѡ�����������ѡ��");
				scanf("%d", &b);
			}
			system("cls");
			if (b == 1)
			{
				printf("��ѡ���Է�ʽ��\n");
				printf("----------------\n");
				printf("1.ϵͳ�������\n2.������Ŀ\n");
				printf("----------------\n");
				scanf("%d", &c);
				system("cls");
				while (c != 1 && c != 2)
				{
					printf("ѡ�����������ѡ��");
					scanf("%d", &c);
				}
				system("cls");
				if (c == 1)
				{
					printf("��ѡ������Ŀ������\n");
					scanf("%d", &num);
					system("cls");
					printf("��ѡ��������\n");
					printf("---------------------\n");
					printf("1.�ӷ�����\n");
					printf("---------------------\n");
					printf("2.��������\n");
					printf("---------------------\n");
					printf("3.�˷�����\n");
					printf("---------------------\n");
					printf("4.��������\n");
					printf("---------------------\n");
					printf("5.�Ӽ��������\n");
					printf("---------------------\n");
					printf("6.�˳��������\n");
					printf("---------------------\n");
					printf("7.����������\n");
					printf("---------------------\n");
					printf("8.�����ŵ�����������\n");
					printf("---------------------\n");
					printf("9.��С��������������\n");
					printf("---------------------\n");
					printf("10.��ѡ�ˣ�������\n");
					printf("---------------------\n");
					scanf("%d", &diffic);
					system("cls");
					Random(n, num, diffic);
					Answer(num);
					userAnswer(num);
				}
				else if (c == 2)
				{
					printf("��ѡ������Ŀ������\n");
					scanf("%d", &num);
					readPra(num);
					Answer(num);
					userAnswer(num);
				}
			}
			else if (b == 2)
			{
				Practice(n);
			}
			else if (b == 3)
			{
				printf("����Ϊ�������������Ŀ��\n");
				fp = fopen("���Ȿ.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%s", &Wro);
					printf("%s", Wro);
					printf("\n");
				}
				fclose(fp);
				system("pause");
			}
			else if (b == 4)
			{
				fp = fopen("��ʷ�ɼ�.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%d", &His);
					printf("������%d����\n", His);
					printf("----------------\n");
				}
				fclose(fp);
				system("pause");
			}
		}
		else if (a == 3)
		{
			n = 1001;
			printf("��ѡ���Ի���ϰ��\n");
			printf("----------------\n");
			printf("1.����\n2.������ϰ\n3.���Ȿ\n4.��ʷ�ɼ�\n");
			printf("----------------\n");
			scanf("%d", &b);
			system("cls");
			while (b != 1 && b != 2 && b != 3 && b != 4)
			{
				printf("ѡ�����������ѡ��");
				scanf("%d", &b);
			}
			system("cls");
			if (b == 1)
			{
				printf("��ѡ���Է�ʽ��\n");
				printf("----------------\n");
				printf("1.ϵͳ�������\n2.������Ŀ\n");
				printf("----------------\n");
				scanf("%d", &c);
				system("cls");
				while (c != 1 && c != 2)
				{
					printf("ѡ�����������ѡ��");
					scanf("%d", &c);
				}
				system("cls");
				if (c == 1)
				{
					printf("��ѡ������Ŀ������\n");
					scanf("%d", &num);
					system("cls");
					printf("��ѡ��������\n");
					printf("---------------------\n");
					printf("1.�ӷ�����\n");
					printf("---------------------\n");
					printf("2.��������\n");
					printf("---------------------\n");
					printf("3.�˷�����\n");
					printf("---------------------\n");
					printf("4.��������\n");
					printf("---------------------\n");
					printf("5.�Ӽ��������\n");
					printf("---------------------\n");
					printf("6.�˳��������\n");
					printf("---------------------\n");
					printf("7.����������\n");
					printf("---------------------\n");
					printf("8.�����ŵ�����������\n");
					printf("---------------------\n");
					printf("9.��С��������������\n");
					printf("---------------------\n");
					printf("10.��ѡ�ˣ�������\n");
					printf("---------------------\n");
					scanf("%d", &diffic);
					system("cls");
					Random(n, num, diffic);
					Answer(num);
					userAnswer(num);
				}
				else if (c == 2)
				{
					printf("��ѡ������Ŀ������\n");
					scanf("%d", &num);
					readPra(num);
					Answer(num);
					userAnswer(num);
				}
			}
			else if (b == 2)
			{
				Practice(n);
			}
			else if (b == 3)
			{
				printf("����Ϊ�������������Ŀ��\n");
				fp = fopen("���Ȿ.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%s", &Wro);
					printf("%s", Wro);
					printf("\n");
				}
				fclose(fp);
				system("pause");
			}
			else if (b == 4)
			{
				fp = fopen("��ʷ�ɼ�.txt", "r");
				while (!feof(fp))
				{
					fscanf(fp, "%d", &His);
					printf("������%d����\n", His);
					printf("----------------\n");
				}
				fclose(fp);
				system("pause");
			}
		}
		system("cls");
		printf("�Ƿ����ʹ��\n");
		printf("----------------\n");
		printf("1.��    2.��\n");
		printf("----------------\n");
		scanf("%d", &t);
		system("cls");
		while (t != 1 && t != 2)
		{
			printf("ѡ�����������ѡ��");
			scanf("%d", &t);
		}
		if (t == 2)
			s = 1;
	}
}