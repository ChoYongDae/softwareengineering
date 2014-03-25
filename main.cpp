#include <iostream>
#include <iomanip>
#include <fstream>
#include "myDataStructure.h"	// 클래스 구현
#include "myString.h"			// 스트링 관련 헤더 구현

using namespace std;

//////// define, 글로벌 변수 /////////////////////////////////////////////////////

int _sel=0;	// 사용자 메뉴 선택
int _usr=1;	// 유저 카운트
List LIST;	// 상품 리스트

// 데이터 파일에서 상품정보 파싱해 저장할 변수들
char tmp[200];
char _name[40], _loc[20], _cat[20], _dc[7];
int _price, _stock, _num;

////////////////////////////////////////////////////////////////////////////////

//////// 메뉴 관련 함수 ///////////////////////////////////////////////////////

void MainMenu();		// 메인 메뉴
void CatSearch();		// 카테고리 상품 검색
void LocSearch();		// 지역 상품 검색
void PurList();			// 구매 리스트
void NormPur();			// 일반구매
void GroupPur();		// 공동구매
void Refund();			// 환불

//////////////////////////////////////////////////////////////////////////////

void InitSales(ifstream &Isales,int _usr);	// 판매 정보파일 받아서 데이터 초기 세팅하는 함수

//////// 메인 구현 ///////////////////////////////////////////////////////////

int main()
{
	// input file들
	ifstream Iproduct,Isales;
	Iproduct.open("product_list.dat");	// 상품 정보 파일
	Isales.open("sales_list.dat");		// 판매 정보 파일

	// input 파일 open 에러시 메세지 출력
	if(Iproduct.fail()||Isales.fail())
	{
		cout<<"Data File Open Error!!"<<endl;
		return 0;
	}

	// 상품 정보파일 읽어서 LIST 초기 세팅
	while(!Iproduct.eof())
	{
		Iproduct.getline(tmp,200);
		if(tmp[0]==NULL)
			break;
		productInfo(tmp,_name,_price,_stock,_cat,_loc);
		LIST.Insert(_name,_price,_stock,_cat,_loc);
	}

	// 상품 판매 정보파일 읽어서 LIST 초기 세팅
	Isales.getline(tmp,200);
	if(myStrcmp(tmp," ▶ 판매 목록"))	// 상품 판매정보파일에 아무것도 없으면 수행 안함
	{
		// usr1-3 판매 정보 입력
		InitSales(Isales,1);
		InitSales(Isales,2);
		InitSales(Isales,3);
	}

	// input 파일 종료
	Iproduct.close();
	Isales.close();

	// usr1-3까지 반복
	while(_usr<4)
	{
		system("cls");	// 화면 초기화
		
		// 몇번째 유저인지 출력
		PrintLine;
		cout<<endl<<endl<<endl<<endl;
		cout<<setw(32)<<right<<_usr<<"-th user Login"<<endl;
		cout<<endl<<endl<<endl<<endl;
		PrintLine;
		
		system("pause");
		MainMenu();		// 메인메뉴 호출
		_usr++;			// 메인메뉴 종료 후 usr 증가시킴
	}

	system("cls");	// 화면 초기화

	// output 파일들
	ofstream Oproduct,Osales;
	Oproduct.open("product_list.dat");
	Osales.open("sales_list.dat");

	// LIST의 정보를 output파일에 기록
	LIST.Print(Oproduct);
	LIST.FPrintSales(Osales);

	// output 파일 종료
	Oproduct.close();
	Osales.close();

	return 0;
}

//////////////////////////////////////////////////////////////////////////////

//////// 메뉴 함수 구현 ///////////////////////////////////////////////////////

// 메인 메뉴
void MainMenu()
{
	while(1)
	{
		_sel=0;
		system("cls");		// 화면 초기화
		PrintTop;
		// 메뉴 출력
		cout<<"\t1. 카테고리 상품 검색"<<endl;
		cout<<"\t2. 지역 상품 검색"<<endl;
		cout<<"\t3. 구매 리스트"<<endl;
		cout<<"\t4. 종료"<<endl;
		cout<<"\t>> ";
		// 입력 버퍼 초기화
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin>>_sel;
		// 입력받은 메뉴 호출
		if(_sel==1)
			CatSearch();
		else if(_sel==2)
			LocSearch();
		else if(_sel==3)
			PurList();
		else if(_sel==4)
			break;
		else
			continue;
	}
}

// 카테고리 상품 검색
void CatSearch()
{
	while(1)
	{
		_sel=0;
		system("cls");		// 화면 초기화
		PrintTop;
		cout<<" 카테고리 상품 검색 결과"<<endl<<endl;
		LIST.Print(2);	// 카테고리별 상품 출력

		// 메뉴 출력
		PrintLine;
		cout<<setw(30)<<left<<"\t1. 일반 구매"<<"2. 공동 구매"<<endl<<setw(30)<<left<<"\t3. 구매 리스트"<<"4. 이전 메뉴"<<endl;
		cout<<"\t>> ";
		// 입력 버퍼 초기화
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin>>_sel;
		// 입력받은 메뉴 호출
		if(_sel==1)
			NormPur();
		else if(_sel==2)
			GroupPur();
		else if(_sel==3)
			PurList();
		else if(_sel==4)
			break;
		else
			continue;
	}
}

// 지역 상품 검색
void LocSearch()
{
	while(1)
	{
		_sel=0;
		system("cls");		// 화면 초기화
		PrintTop;
		cout<<" 지역 상품 검색 결과"<<endl<<endl;
		LIST.Print(1);	// 지역별 상품 출력
		
		// 메뉴 출력
		PrintLine;
		cout<<setw(30)<<left<<"\t1. 일반 구매"<<"2. 공동 구매"<<endl<<setw(30)<<left<<"\t3. 구매 리스트"<<"4. 이전 메뉴"<<endl;
		cout<<"\t>> ";
		// 입력 버퍼 초기화
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin>>_sel;
		// 입력받은 메뉴 호출
		if(_sel==1)
			NormPur();
		else if(_sel==2)
			GroupPur();
		else if(_sel==3)
			PurList();
		else if(_sel==4)
			break;
		else
			continue;
	}
}

// 구매 리스트
void PurList()
{
	while(1)
	{
		_sel=0;
		system("cls");		// 화면 초기화
		PrintTop;
		LIST.PrintUsr(_usr);	// 현재 유저의 구매리스트 출력

		PrintLine;
		cout<<setw(30)<<left<<"\t1. 환불"<<"2. 이전 메뉴"<<endl;
		cout<<"\t>> ";
		// 입력 버퍼 초기화
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail()); 
		cin>>_sel;
		if(_sel==1)
			Refund();
		else if(_sel==2)
			break;
		else
			continue;
	}
}

// 일반구매
void NormPur()
{
	char PerName[40];
	int PerNum;

	// 입력버퍼 초기화
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail()); 

	// 구매할 상품이름, 수량 입력
	cout<<endl<<"\t구매할 상품명을 입력해주십시오 : ";
	cin.getline(PerName,40);
	cout<<"\t구매할 수량을 입력해주십시오 : ";
	cin>>PerNum;

	// 입력받은 상품이름, 수량으로 Pur함수 호출
	if(LIST.Pur(_usr,PerName,PerNum,0))		// Pur함수의 마지막 매개변수는 일반구매, 공동구매를 의미함 (0:일반,1:공동)
		cout<<endl<<endl<<"\t"<<PerName<<" "<<PerNum<<"개 구매 완료되었습니다."<<endl<<endl;
	
	system("pause");	// 구매 완료 확인을 위해 일시 정지
}

// 공동구매
void GroupPur()
{
	char PerName[40];
	int PerNum;

	// 입력 버퍼 초기화
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail()); 

	// 공동구매할 상품명, 수량 입력
	cout<<endl<<"\t공동구매할 상품명을 입력해주십시오 : ";
	cin.getline(PerName,40);
	cout<<"\t공동구매할 수량을 입력해주십시오 : ";
	cin>>PerNum;

	// 입력받은 상품명, 수량으로 공동구매
	if(LIST.Pur(_usr,PerName,PerNum,1))	// Pur함수의 마지막 매개변수는 일반구매, 공동구매를 의미함 (0:일반,1:공동)
		cout<<endl<<endl<<"\t"<<PerName<<" "<<PerNum<<"개 구매 완료되었습니다."<<endl<<endl;
	
	system("pause");	// 구매완료 확인을 위해 일시 정지
}

// 환불
void Refund()
{
	char RefName[40];

	// 입력 버퍼 초기화
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail()); 

	// 환불할 상품명 입력
	cout<<endl<<"\t환불할 상품명을 입력해주십시오 : ";
	cin.getline(RefName,40);
	
	// 입력받은 상품명으로 환불
	if(LIST.Ref(_usr,RefName))	// 환불 성공시 메세지 출력
		cout<<endl<<endl<<"\t"<<RefName<<" 환불 완료되었습니다."<<endl<<endl;
	else						// 환불 실패시 메세지 출력
		cout<<endl<<setw(55)<<right<<"=== 해당 상품이 없습니다 ==="<<endl<<endl;

	system("pause");		// 환불 완료 확인을 위해 일시 정지
}

//////////////////////////////////////////////////////////////////////////////

// 초기 LIST 판매 정보 업데이트
void InitSales(ifstream &Isales,int _usr)
{
	// 유저1이면 한줄 먼저 읽음
	if(_usr==1)
		Isales.getline(tmp,200);

	// 몇번째 유저인지 확인하기 위한 변수 세팅
	char bfr[15]="  >> 0-th user";
	bfr[5]=(char)(_usr+48);

	while(!myStrcmp(tmp,bfr))		// 유저 이름 확인될때까지 다음줄 읽음
		Isales.getline(tmp,200);

	// 유저 이름 확인 후 다음줄에 바로 다음 유저 이름이 있으면 탈출
	Isales.getline(tmp,200);
	bfr[5]++;
	if(myStrcmp(tmp,bfr)||Isales.eof())
		return;

	// 일반구매 데이터 찾기위한 탐색
	while(!myStrcmp(tmp,"      ▶ 구매 상품 리스트"))
		Isales.getline(tmp,200);
	while(!myStrcmp(tmp,"                 품    목             단  가    수량  할  인    금  액"))
		Isales.getline(tmp,200);
	// 데이터 입력받아 파싱 후 LIST에 추가
	while(1)
	{
		Isales.getline(tmp,200);
		if(tmp[0]==NULL)
			break;
		salesInfo(tmp,_name,_num,_dc);		// 파싱 함수
		if(_dc[0]!=' ')						// dc의 첫번째 값이 공백이면
			LIST.Update(_usr,_name,_num,0);	// 일반구매로 처리
		else								// 공백이 아니면
			LIST.Update(_usr,_name,_num,1);	// 공동구매로 처리
	}

	// 일반구매 데이터 찾기위한 탐색
	while(!myStrcmp(tmp,"      ▶ 공동구매 진행 상품 리스트"))
		Isales.getline(tmp,200);
	while(!myStrcmp(tmp,"                 품    목             단  가    수량  할  인    금  액"))
		Isales.getline(tmp,200);
	// 데이터 입력받아 파싱 후 LIST에 추가
	while(1)
	{
		Isales.getline(tmp,200);
		if(tmp[0]==NULL)
			break;
		salesInfo(tmp,_name,_num,_dc);
		LIST.Update(_usr,_name,_num,1);	// 공동구매로 처리
	}
}