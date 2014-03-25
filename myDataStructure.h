#include <iostream>
#include <fstream>
#include "myString.h"		// 스트링 관련 헤더

using namespace std;

//////// 클래스 구현 /////////////////////////////////////////////////////////

// 상품 노드
class Product
{
	// friend class로 지정해 접근 용이하게 함
	friend class List;
	friend class Title;
private:
	char Pname[40];		// 상품 이름
	int Pprice;			// 상품 단가
	int Pstock;			// 상품 재고
	int Pnum;			// 상품 판매 수량
	int U1num;			// Usr1 구매 수량
	int U2num;			// Usr2 구매 수량
	int U3num;			// Usr3 구매 수량
	bool U1Gpur;		// Usr1 공동구매 여부
	bool U2Gpur;		// Usr2 공동구매 여부
	bool U3Gpur;		// Usr3 공동구매 여부
	char PLoc[20];		// 상품 지역
	char PCat[20];		// 상품 카테고리
	Product *Clink;		// 상품 카테고리별 링크
	Product *Llink;		// 상품 위치별 링크
	Product *U1link;	// 유저1 링크
	Product *U2link;	// 유저2 링크
	Product *U3link;	// 유저3 링크
public:
	Product();			// 생성자
};

// product 생성자
Product::Product()
{
	// 모든 링크 널로 초기화
	Clink=NULL;Llink=NULL;U1link=NULL;U2link=NULL;U3link=NULL;
	// 모든 int형 데이터 0으로 초기화
	Pnum=0;U1num=0;U2num=0;U3num=0;
	// 모든 bool형 데이터 false로 초기화
	U1Gpur=false;U2Gpur=false;U3Gpur=false;
}

// 상품들을 리스트로 만들 타이틀
class Title
{
	friend class List;
private:
	char Tname[20];		// 타이틀 이름
	Title *Tlink;		// 타이틀 링크
	Product *Plink;		// 상품 링크
public:
	Title() {Tlink=NULL;Plink=NULL;};	// 생성자
};

// 기본 리스트
class List
{
private:
	Title *Lhead;	// 지역 헤드
	Title *Chead;	// 카테고리 헤드
	Title *Uhead;	// 유저 헤드
public:
	List();			// 생성자
	~List();		// 소멸자
	void Insert(char _name[40],int _price,int _stock,char _cat[20],char _loc[20]);	// 리스트에 상품 입력하는 함수
	void Update(int _usr,char _pername[40],int _pernum,int _gpur);					// 리스트에 판매정보 업데이트하는 함수
	bool Pur(int _usr,char _pername[40],int _pernum,int _gpur);						// 구매 함수
	void AddUsrList(int _usr,Product *pro);											// 유저 리스트에 구매한 상품 추가하는 함수
	bool Ref(int _usr,char _refname[40]);											// 환불 함수
	void DelUsrList(int _usr,Product *pro);											// 환불한 상품 유저리스트에서 제거하는 함수
	void Print(int n);																// 리스트 출력하는 함수(n=1:지역별 출력,n=2:카테고리별 출력)
	void Print(ofstream &product);													// 리스트의 상품 정보를 파일에 출력하는 함수
	void PrintUsr(int _usr);														// 유저 구매 리스트 출력 함수
	void PrintUsr(int _usr,ofstream &sales);										// 유저 구매 리스트를 파일로 출력하는 함수
	void FPrintSales(ofstream &sales);												// 판매 정보를 파일로 출력하는 함수
};

// List 생성자
List::List()
{
	// 모든 링크 널로 초기화
	Lhead=NULL;Chead=NULL;;

	// 유저 리스트 초기화
	Title *nTitle1=new Title;
	myStrcpy(nTitle1->Tname,1);
	Uhead=nTitle1;
	Title *nTitle2=new Title;
	myStrcpy(nTitle2->Tname,2);
	nTitle1->Tlink=nTitle2;
	Title *nTitle3=new Title;
	myStrcpy(nTitle3->Tname,3);
	nTitle2->Tlink=nTitle3;
}

// List 소멸자
List::~List()
{
	Title *Tpre, *Tcur;		// 타이틀 탐색용
	Product *Ppre, *Pcur;	// 상품 탐색용

	// 지역별 링크를 기준으로 삭제함
	if(Lhead!=NULL)	// 지역 헤더가 널이 아니면
	{
		Tcur=Lhead;	// 타이틀 초기 세팅
		while(Tcur->Tlink!=NULL)			// 타이틀이 널일때까지 탐색
		{
			Pcur=Tcur->Plink;			// 상품 탐색 초기 세팅
			while(Pcur->Llink!=NULL)		// 상품 끝까지 탐색
			{
				// 다음상품으로 이동후 이전 상품 삭제
				Ppre=Pcur;
				Pcur=Pcur->Llink;
				delete Ppre;
			}
			delete Pcur;	// 마지막 남은 상품 삭제

			// 다음 타이틀로 이동후 이전 타이틀 삭제
			Tpre=Tcur;
			Tcur=Tcur->Tlink;
			delete Tpre;
		}
		delete Tcur;	// 마지막 타이틀 삭제
	}
}

// 리스트에 상품 입력하는 함수
void List::Insert(char _name[40],int _price,int _stock,char _cat[20],char _loc[20])
{
	// 새 상품 생성 및 상품 정보 입력
	Product *nPro= new Product;
	myStrcpy(nPro->Pname,_name);
	myStrcpy(nPro->PCat,_cat);
	myStrcpy(nPro->PLoc,_loc);
	nPro->Pprice=_price;
	nPro->Pstock=_stock;

	// 지역 리스트
	if(Lhead==NULL)	// 지역 헤더가 널이면
	{
		// 새 지역 추가 후 새 지역에 새 상품 추가
		Title *nTitle=new Title;
		myStrcpy(nTitle->Tname,nPro->PLoc);
		Lhead=nTitle;
		nTitle->Plink=nPro;
	}
	else			// 지역 헤더가 널이 아니면
	{
		Title *Tcur;
		Product *Pcur;

		for(Tcur=Lhead;Tcur!=NULL;Tcur=Tcur->Tlink)	// 타이틀의 링크가 널일때까지
		{
			if(myStrcmp(Tcur->Tname,nPro->PLoc))		// 현재 지역의 이름이 새상품의 지역 이름과 같다면
			{
				// 현재 지역의 맨끝에 상품 추가
				Pcur=Tcur->Plink;
				for(Pcur=Tcur->Plink;Pcur->Llink!=NULL;Pcur=Pcur->Llink);
				Pcur->Llink=nPro;
				break;
			}
			else
			{
				if(Tcur->Tlink==NULL)				// 마지막 지역일 경우
				{
					// 새 지역 추가 후 새지역에 새 상품 추가
					Title *nTitle=new Title;
					myStrcpy(nTitle->Tname,nPro->PLoc);
					Tcur->Tlink=nTitle;
					nTitle->Plink=nPro;
					break;
				}
			}
		}
	}

	// 카테고리 리스트
	if(Chead==NULL)	// 지역 헤더가 널이면
	{
		// 새 카테고리 추가 후 새카테고리에 새 상품 추가
		Title *nTitle=new Title;
		myStrcpy(nTitle->Tname,nPro->PCat);
		Chead=nTitle;
		nTitle->Plink=nPro;
	}
	else			// 지역 헤더가 널이 아니면
	{
		Title *Tcur;
		Product *Pcur;

		for(Tcur=Chead;Tcur!=NULL;Tcur=Tcur->Tlink)	// 카테고리의 링크가 널일때까지
		{
			if(myStrcmp(Tcur->Tname,nPro->PCat))		// 현재 카테고리의 이름이 새상품의 지역 이름과 같다면
			{
				// 현재 카테고리의 맨끝에 상품 추가
				Pcur=Tcur->Plink;
				for(Pcur=Tcur->Plink;Pcur->Clink!=NULL;Pcur=Pcur->Clink);
				Pcur->Clink=nPro;
				break;
			}
			else
			{
				if(Tcur->Tlink==NULL)				// 마지막 카테고리일 경우
				{
					// 새 카테고리 추가 후 새카테고리에 새 상품 추가
					Title *nTitle=new Title;
					myStrcpy(nTitle->Tname,nPro->PCat);
					Tcur->Tlink=nTitle;
					nTitle->Plink=nPro;
					break;
				}
			}
		}
	}
}

// 리스트에 판매정보 업데이트하는 함수
void List::Update(int _usr,char _pername[40],int _pernum,int _gpur)
{
	// 지역 기준으로 업데이트함
	if(Lhead!=NULL)	// 지역 헤더가 널이 아니면
	{
		// 지역 초기 세팅
		Title *Tcur=Lhead;
		Product *Pcur;
		while(Tcur!=NULL)	// 지역이 널이 아닐때까지
		{
			Pcur=Tcur->Plink;	// 상품 초기 세팅
			while(Pcur!=NULL)	// 상품이 널이 아닐때까지
			{
				if(myStrcmp(Pcur->Pname,_pername))	// 현재 상품의 이름과 업데이트할 상품의 이름이 같으면
				{
					Pcur->Pnum+=_pernum;				// 현재 상품의 판매 개수에 업데이트할 개수를 더한다
					switch(_usr)					// 유저에 따라 정보 업데이트(유저 구매개수, 공동구매여부)
					{
					case 1:
						Pcur->U1num+=_pernum;
						if(_gpur) Pcur->U1Gpur=true;
						break;
					case 2: 
						Pcur->U2num+=_pernum;
						if(_gpur) Pcur->U2Gpur=true;
						break;
					case 3: 
						Pcur->U3num+=_pernum;
						if(_gpur) Pcur->U3Gpur=true;
						break;
					}
					AddUsrList(_usr,Pcur);	// 유저리스트에 추가
					return;
				}
				else
					Pcur=Pcur->Llink;	// 다음 상품으로
			}
			Tcur=Tcur->Tlink;			// 다음 지역으로
		}
	}
}

// 구매 함수
bool List::Pur(int _usr,char _pername[40],int _pernum,int _gpur)
{
	// 지역 기준으로
	if(Lhead!=NULL)		// 지역헤더가 널이 아니면
	{
		// 초기 세팅
		Title *Tcur=Lhead;
		Product *Pcur;
		while(Tcur!=NULL)		// 끝까지
		{
			Pcur=Tcur->Plink;	// 초기 세팅
			while(Pcur!=NULL)	// 상품 끝까지
			{
				if(myStrcmp(Pcur->Pname,_pername))	// 현재 상품의 이름과 구매할 상품의 이름이 같으면
				{
					if(!(Pcur->Pstock<_pernum))		// 재고가 구매수량보다 많으면
					{
						Pcur->Pstock-=_pernum;		// 재고 감소
						Pcur->Pnum+=_pernum;			// 구매수량 증가
						switch(_usr)				// 유저에 따라 정보 업데이트(유저 구매수량, 공동구매 여부)
						{
						case 1: 
							Pcur->U1num+=_pernum;
							if(_gpur) Pcur->U1Gpur=true;
							break;
						case 2: 
							Pcur->U2num+=_pernum;
							if(_gpur) Pcur->U2Gpur=true;
							break;
						case 3: 
							Pcur->U3num+=_pernum;
							if(_gpur) Pcur->U3Gpur=true;
							break;
						}
						AddUsrList(_usr,Pcur);	// 유저 리스트에 추가
						return true;
					}
					else		// 재고가 부족하면 메세지 출력
					{
						cout<<endl<<setw(50)<<right<<"=== 재고가 부족합니다 ==="<<endl<<endl;
						return false;
					}
				}
				else
					Pcur=Pcur->Llink;		// 다음 상품으로
			}
			Tcur=Tcur->Tlink;				// 다음 지역으로
		}
	}

	// 검색 실패시 메세지 출력
	cout<<endl<<setw(55)<<right<<"=== 해당 상품이 없습니다 ==="<<endl<<endl;
	return false;
}

// 유저 리스트에 구매 상품 추가하는 함수
void List::AddUsrList(int _usr,Product *pro)
{
	Title *Tcur;
	Product *Pcur;

	for(Tcur=Uhead;Tcur!=NULL;Tcur=Tcur->Tlink)	// 타이틀의 링크가 널일때까지
	{
		if(myStrcmp(Tcur->Tname,_usr))		// 현재 타이틀의 이름이 새상품의 사용자 이름과 같다면
		{
			// 현재 타이틀의 맨끝에 상품 추가
			Pcur=Tcur->Plink;
			switch(_usr)
			{
			case 1:
				if(Pcur==NULL)			// 상품이 없을경우
					Tcur->Plink=pro;		// 맨 처음으로 추가
				else
				{
					for(;Pcur->U1link!=NULL;Pcur=Pcur->U1link)	// 맨뒤까지
					{
						if(myStrcmp(Pcur->Pname,pro->Pname))		// 이미 리스트에 상품이 있으면 탈출
							return;
					}
					if(myStrcmp(Pcur->Pname,pro->Pname))		// 이미 리스트에 상품이 있으면 탈출
							return;
					Pcur->U1link=pro;
				}
				break;
			case 2:
				if(Pcur==NULL)
					Tcur->Plink=pro;
				else
				{
					for(;Pcur->U2link!=NULL;Pcur=Pcur->U2link)
					{
						if(myStrcmp(Pcur->Pname,pro->Pname))		// 이미 리스트에 상품이 있으면 탈출
							return;
					}
					if(myStrcmp(Pcur->Pname,pro->Pname))		// 이미 리스트에 상품이 있으면 탈출
							return;
					Pcur->U2link=pro;
				}
				break;
			case 3:
				if(Pcur==NULL)
					Tcur->Plink=pro;
				else
				{
					for(;Pcur->U3link!=NULL;Pcur=Pcur->U3link)
					{
						if(myStrcmp(Pcur->Pname,pro->Pname))		// 이미 리스트에 상품이 있으면 탈출
							return;
					}
					if(myStrcmp(Pcur->Pname,pro->Pname))		// 이미 리스트에 상품이 있으면 탈출
							return;
					Pcur->U3link=pro;
				}
				break;
			}
			break;		// 상품 추가후 탈출
		}
	}

}

// 환불 함수
bool List::Ref(int _usr,char _refname[40])
{
	Title *Tcur;
	Product *Pcur;

	// 지역 기준으로
	if(Lhead!=NULL)
	{
		Tcur=Lhead;	// 초기 세팅
		while(Tcur!=NULL)	// 지역 끝까지
		{
			Pcur=Tcur->Plink;	// 상품 초기 세팅
			while(Pcur!=NULL)	// 상품 끝까지
			{
				if(myStrcmp(Pcur->Pname,_refname))	// 환불할 상품이름과 현재 상품이름이 같으면
				{
					switch(_usr)					// 사용자에 따라 처리
					{
					case 1:
						Pcur->Pstock+=Pcur->U1num;	// 재고에 환불 수량 증가
						Pcur->Pnum-=Pcur->U1num;		// 상품 판매수량 감소
						Pcur->U1num=0;				// 유저 구매수량 감소
						break;
					case 2: 
						Pcur->Pstock+=Pcur->U2num;
						Pcur->Pnum-=Pcur->U2num;
						Pcur->U2num=0;
						break;
					case 3: 
						Pcur->Pstock+=Pcur->U3num;
						Pcur->Pnum-=Pcur->U3num;
						Pcur->U3num=0;
						break;
					}
					DelUsrList(_usr,Pcur);		// 유저리스트에서 상품 삭제

					return true;
				}
				else
					Pcur=Pcur->Llink;		// 다음 상품으로
			}
			Tcur=Tcur->Tlink;				// 다음 지역으로
		}
	}

	return false;
}

// 유저 구매 리스트에서 상품 삭제하는 함수
void List::DelUsrList(int _usr,Product *pro)
{
	// 초기 세팅
	Title *Tcur=Uhead;
	Product *Ppre=NULL,*Pcur;

	while(Tcur!=NULL)	// 유저 끝까지
	{
		if(myStrcmp(Tcur->Tname,_usr))	// 현재 유저와 입력받은 유저가 같으면 탈출
			break;
		Tcur=Tcur->Tlink;				// 다음 유저로
	}

	// 유저에 따라 처리 (유저의 고유 링크 사용)
	switch(_usr)
	{
	case 1:
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U1link)	// 유저 링크 끝까지
		{
			if(myStrcmp(Pcur->Pname,pro->Pname))				// 삭제할 상품이름과 현재 상품이름이 같으면
			{
				if(Ppre==NULL)								// 이전 상품이 없으면
				{
					Tcur->Plink=Pcur->U1link;				// 유저 타이틀의 상품 링크를 다음상품으로
					Pcur->U1link=NULL;						// 현재 상품의 링크 널로 초기화
				}
				else
				{
					Ppre->U1link=Pcur->U1link;				// 이전 상품의 유저 링크를 다음상품으로
					Pcur->U1link=NULL;						// 현재 상품의 유저 링크 널로 초기화
				}
				break;	// 탈출
			}
			Ppre=Pcur;	// 이전 상품 세팅
		}
		break;
	case 2:
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U2link)
		{
			if(myStrcmp(Pcur->Pname,pro->Pname))
			{
				if(Ppre==NULL)
				{
					Tcur->Plink=Pcur->U2link;
					Pcur->U2link=NULL;
				}
				else
				{
					Ppre->U2link=Pcur->U2link;
					Pcur->U2link=NULL;
				}
				break;
			}
			Ppre=Pcur;
		}
		break;
	case 3:
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U3link)
		{
			if(myStrcmp(Pcur->Pname,pro->Pname))
			{
				if(Ppre==NULL)
				{
					Tcur->Plink=Pcur->U3link;
					Pcur->U3link=NULL;
				}
				else
				{
					Ppre->U3link=Pcur->U3link;
					Pcur->U3link=NULL;
				}
				break;
			}
			Ppre=Pcur;
		}
		break;
	}

}

// 상품 리스트 출력하는 함수
void List::Print(int n)
{
	// n=1 이면 지역별 상품 출력
	// n=2 이면 카테고리별 상품 출력

	Title *Tcur;
	Product *Pcur;

	switch(n)
	{
	case 1: // 지역별 상품 출력
		for(Tcur=Lhead;Tcur!=NULL;Tcur=Tcur->Tlink)
		{
			cout<<"\t▶ "<<Tcur->Tname<<endl;
			cout<<"\t   "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(3)<<" "<<"재 고"<<endl;
			for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->Llink)
				cout<<"\t   "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(10)<<right<<Pcur->Pstock<<endl;
			cout<<endl;
		}
		break;
	case 2: // 카테고리별 상품 출력
		for(Tcur=Chead;Tcur!=NULL;Tcur=Tcur->Tlink)
		{
			cout<<"\t▶ "<<Tcur->Tname<<endl;
			cout<<"\t   "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(3)<<" "<<"재 고"<<endl;
			for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->Clink)
				cout<<"\t   "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(10)<<right<<Pcur->Pstock<<endl;
			cout<<endl;
		}
		break;
	}

}

// 파일에 상품 정보 기록하는 함수
void List::Print(ofstream &product)
{
	Title *Tcur;
	Product *Pcur;

	// 지역 기준으로 출력
	for(Tcur=Lhead;Tcur!=NULL;Tcur=Tcur->Tlink)	// 지역 끝까지
	{
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->Llink)	// 상품 끝까지 상품이름, 가격, 재고, 카테고리, 지역 파일로 출력
			product<<setw(30)<<left<<Pcur->Pname<<setw(10)<<left<<Pcur->Pprice<<setw(10)<<left<<Pcur->Pstock<<setw(10)<<left<<Pcur->PCat<<setw(10)<<Pcur->PLoc<<"\n";
	}
}

// 유저 구매 리스트 출력하는 함수
void List::PrintUsr(int _usr)
{
	// 초기 세팅
	Title *Tcur=Uhead;
	Product *Pcur;

	while(Tcur!=NULL)	// 유저 끝까지
	{
		if(myStrcmp(Tcur->Tname,_usr))	// 현재 유저와 입력받은 유저가 같으면 탈출
			break;
		Tcur=Tcur->Tlink;				// 다음 유저로
	}

	// 유저별로 처리
	switch(_usr)
	{
	case 1:
		cout<<endl<<"      ▶ 구매 상품 리스트"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U1link)	// 유저 링크 끝까지
		{
			if(!(Pcur->U1Gpur&&Pcur->Pnum<10))				// 일반구매이거나 공동구매가 성립된 상품만 출력
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U1num;
				if(Pcur->U1Gpur&&Pcur->Pnum>9)	// 공동구매가 성립된 상품 출력
					cout<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U1num*0.9<<endl;
				else							// 일반구매 출력
					cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U1num<<endl;
			}
		}

		cout<<endl<<"      ▶ 공동구매 진행 상품 리스트"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U1link)	// 유저링크 끝까지
		{
			if(Pcur->U1Gpur&&Pcur->Pnum<10)		// 공동구매가 진행중인 상품 출력
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U1num;
				cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U1num<<endl;
			}
		}
		cout<<endl;
		break;
	case 2:
		cout<<endl<<"      ▶ 구매 상품 리스트"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U2link)
		{
			if(!(Pcur->U2Gpur&&Pcur->Pnum<10))
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U2num;
				if(Pcur->U2Gpur&&Pcur->Pnum>9)
					cout<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U2num*0.9<<endl;
				else
					cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U2num<<endl;
			}
		}

		cout<<endl<<"      ▶ 공동구매 진행 상품 리스트"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U2link)
		{
			if(Pcur->U2Gpur&&Pcur->Pnum<10)
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U2num;
				cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U2num<<endl;
			}
		}
		cout<<endl;
		break;
	case 3:
		cout<<endl<<"      ▶ 구매 상품 리스트"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U3link)
		{
			if(!(Pcur->U3Gpur&&Pcur->Pnum<10))
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U3num;
				if(Pcur->U3Gpur&&Pcur->Pnum>9)
					cout<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U3num*0.9<<endl;
				else
					cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U3num<<endl;
			}
		}

		cout<<endl<<"      ▶ 공동구매 진행 상품 리스트"<<endl;
		cout<<"      "<<"----------------------------------------------------------------"<<endl;
		cout<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<endl;
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U3link)
		{
			if(Pcur->U3Gpur&&Pcur->Pnum<10)
			{
				cout<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U3num;
				cout<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U3num<<endl;
			}
		}
		cout<<endl;
		break;
	}
}

// 유저 구매 리스트를 파일로 출력하는 함수
void List::PrintUsr(int _usr,ofstream &sales)
{
	// 초기 세팅
	Title *Tcur=Uhead;
	Product *Pcur;

	while(Tcur!=NULL)	// 유저 끝까지
	{
		if(myStrcmp(Tcur->Tname,_usr))	// 현재 유저와 입력받은 유저가 같으면 탈출
			break;
		Tcur=Tcur->Tlink;				// 다음 유저로
	}

	// 유저에 따라 출력
	switch(_usr)
	{
	case 1:
		sales<<"\n"<<"      ▶ 구매 상품 리스트"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U1link)	// 유저 링크 끝까지
		{
			if(!(Pcur->U1Gpur&&Pcur->Pnum<10))				// 일반구매이거나 공동구매가 성립된 상품만 출력
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U1num;
				if(Pcur->U1Gpur&&Pcur->Pnum>9)	// 공동구매가 성립된 상품 출력
					sales<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U1num*0.9<<"\n";
				else							// 일반구매 출력
					sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U1num<<"\n";
			}
		}

		sales<<"\n"<<"      ▶ 공동구매 진행 상품 리스트"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U1link)	// 유저링크 끝까지
		{
			if(Pcur->U1Gpur&&Pcur->Pnum<10)					// 공동구매가 진행중인 상품 출력
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U1num;
				sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U1num<<"\n";
			}
		}
		sales<<"\n";
		break;
	case 2:
		sales<<"\n"<<"      ▶ 구매 상품 리스트"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U2link)
		{
			if(!(Pcur->U2Gpur&&Pcur->Pnum<10))
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U2num;
				if(Pcur->U2Gpur&&Pcur->Pnum>9)
					sales<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U2num*0.9<<"\n";
				else
					sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U2num<<"\n";
			}
		}

		sales<<"\n"<<"      ▶ 공동구매 진행 상품 리스트"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U2link)
		{
			if(Pcur->U2Gpur&&Pcur->Pnum<10)
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U2num;
				sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U2num<<"\n";
			}
		}
		sales<<"\n";
		break;
	case 3:
		sales<<"\n"<<"      ▶ 구매 상품 리스트"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U3link)
		{
			if(!(Pcur->U3Gpur&&Pcur->Pnum<10))
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U3num;
				if(Pcur->U3Gpur&&Pcur->Pnum>9)
					sales<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->U3num*0.9<<"\n";
				else
					sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U3num<<"\n";
			}
		}

		sales<<"\n"<<"      ▶ 공동구매 진행 상품 리스트"<<"\n";
		sales<<"      "<<"----------------------------------------------------------------"<<"\n";
		sales<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액"<<"\n";
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->U3link)
		{
			if(Pcur->U3Gpur&&Pcur->Pnum<10)
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->U3num;
				sales<<"     -     "<<setw(7)<<Pcur->Pprice*Pcur->U3num<<"\n";
			}
		}
		sales<<"\n";
		break;
	}
}

// 파일에 판매 정보 기록하는 함수
void List::FPrintSales(ofstream &sales)
{
	// 초기 세팅
	Title *Tcur=Uhead;
	Product *Pcur;
	int TOTAL=0;	// 총 판매금액

	sales<<" ▶ 판매 목록\n";
	sales<<"-----------------------------------------------------------------------------\n";
	// 판매목록 지역 기준으로 출력
	sales<<"      "<<setw(11)<<" "<<"품    목"<<setw(11)<<" "<<setw(2)<<" "<<"단  가"<<setw(2)<<" "<<setw(2)<<" "<<"수량"<<setw(2)<<" "<<"할  인"<<setw(4)<<" "<<"금  액\n";
	for(Tcur=Lhead;Tcur!=NULL;Tcur=Tcur->Tlink)	// 지역 끝까지
	{
		for(Pcur=Tcur->Plink;Pcur!=NULL;Pcur=Pcur->Llink)	// 상품 끝까지
		{
			if(Pcur->Pnum>0)		// 상품 판매 수량이 0보다 크면 출력
			{
				sales<<"      "<<setw(30)<<left<<Pcur->Pname<<setw(8)<<right<<Pcur->Pprice<<setw(8)<<right<<Pcur->Pnum;
				if((Pcur->U1Gpur||Pcur->U2Gpur||Pcur->U3Gpur)&&Pcur->Pnum>9)			// 공동구매 상품이면서 구매 수량이 10이상이면
				{
					// 10%DC
					sales<<"   10%DC   "<<setw(7)<<Pcur->Pprice*Pcur->Pnum*0.9<<"\n";
					TOTAL+=Pcur->Pprice*Pcur->Pnum*0.9;
				}
				else
				{
					sales<<"     -     "<<setw(7)<<right<<Pcur->Pprice*Pcur->Pnum<<"\n";
					TOTAL+=Pcur->Pprice*Pcur->Pnum;
				}
			}
		}
	}
	sales<<"-----------------------------------------------------------------------------\n";
	sales<<"  >> 매출 총액\t"<<TOTAL<<"\n\n\n";

	sales<<" ▶ 고객 목록"<<"\n";

	// 유저 리스트 파일로 출력
	for(int i=1;i<4;i++)
	{
		sales<<"  >> "<<i<<"-th user"<<"\n";
		PrintUsr(i,sales);
	}
}


//////////////////////////////////////////////////////////////////////////////////