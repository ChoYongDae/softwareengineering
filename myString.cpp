#include <iostream>
#include "myString.h"

using namespace std;


//////// string 함수 구현 ////////////////////////////////////////////////////

// 입력받은 문자열 배열을 형식에 맞게 파싱하는 함수 (상품 정보)
void productInfo(char tmp[],char _name[], int &_price, int &_stock, char _cat[],char _loc[])
{
	char bfr[50];	// 임시 버퍼

	// tmp에서 해당 데이터 파싱해 저장
	myStrtok(tmp,' ',_name);
	myStrtok(tmp,' ',bfr);
	_price=cToi(bfr);
	myStrtok(tmp,' ',bfr);
	_stock=cToi(bfr);
	myStrtok(tmp,' ',_cat);
	myStrtok(tmp,' ',_loc);
}

// 입력받은 문자열 배열을 형식에 맞게 파싱하는 함수 (판매 정보)
void salesInfo(char tmp[],char _name[],int &_num,char _dc[])
{
	char bfr[50];	// 임시 버퍼

	// tmp에서 해당 데이터 파싱해 저장
	myStrtok(tmp,' ',_name);
	myStrtok(tmp,' ',bfr);
	myStrtok(tmp,' ',bfr);
	_num=cToi(bfr);
	myStrtok(tmp,' ',_dc);
}

// 문자열 배열을 다른배열에 복사하는 함수
void myStrcpy(char result[], char source[])
{
	int i;
	for(i=0;source[i]!=NULL;i++)	// source의 끝까지 result에 복사
		result[i]=source[i];
	result[i]=NULL;	// result 마지막에 NULL 저장
}

// 숫자를 문자열로 복사하는 함수
void myStrcpy(char result[], int source)
{
	result[0]=source;
	result[1]=NULL;
}

// 문자열을 정수형으로 변환하는 함수
int cToi(char ch[])
{
	int result=0;

	for(int i=0;ch[i]!=NULL;i++)	// ch끝까지
	{
		result*=10;			// 자리수 증가
		result+=ch[i]-48;	// 아스키코드 이용해 숫자 저장
	}

	return result;
}

// 두 문자열이 같은지 비교하는 함수
bool myStrcmp(char ch1[], char ch2[])
{
	int i;
	for(i=0;ch1[i]!=NULL;i++)	// ch1끝까지
	{
		if(ch1[i]==ch2[i])	// ch1과 ch2가 같으면 다음 비교
			continue;
		else				// 다르면 거짓 반환
			return false;
	}
	if(ch2[i]==NULL)		// for문 종료 후 ch2 마지막에 널값있으면 참반환
		return true;
	else
		return false;
}

// 두 문자열이 같은지 비교하는 함수 (숫자와 문자 비교)
bool myStrcmp(char ch1[], int n)
{
	if((int)ch1[0]==n)
		return true;
	else
		return false;
}

// strtok 구현
char *myStrtok(char token[],char del,char result[])
{
	int j=0;	// result 인덱스
	for(int i=0;token[i]!=NULL;i++)		// token의 끝까지
	{
		if(token[i]==del)		// token[i]가 del과 같으면 계속
			continue;
		else					// token[i]가 del과 다르면
		{
			// token[i]가 del과 같거나 널이 될때까지 token을 result에 저장
			while(!(token[i]==del||token[i]==NULL))
			{
				result[j]=token[i];
				token[i]=del;
				j++;i++;
			}
			result[j]=NULL;	// result 마지막에 널 저장
			return result;
		}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////