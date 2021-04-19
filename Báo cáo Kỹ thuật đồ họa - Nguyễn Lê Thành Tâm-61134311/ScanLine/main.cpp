#include <mylib.h>
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

struct Point {
  int x, y;
};
struct DoanThang {
	Point diemDau, diemCuoi;
};

queue<Point> myQueue;

#define soDinhToiDa 30		// So dinh toi da cua da giac = 30
#define SIZE 100000
int thuatToan=0, mauVe=15, mauTo = 9, mauNen = 0, dinhdg=3;

DoanThang canhDaGiac[soDinhToiDa];
//DoanThang *canhDaGiac = new DoanThang[dinhdg];
Point giaoDiem[SIZE];

int trangThai[soDinhToiDa], xmin, ymin, xmax, ymax;

void VeDaGiac();
int GiaoDienChinh();
void GiaoDienDongQuet();
void GiaoDienDauLoang();
int Thoat();

void SapXepCanhDaGiac(DoanThang canhDaGiac[], int soCanh);
void ThuatToanScanline(DoanThang canh[], int soCanh );
Point TimGiaoDiem(DoanThang d1, DoanThang d2);
bool CatCanhDaGiac(int y1, int y2, int y3);
bool ThuocDoanThang(Point p1, Point p2, Point p3);
void ToMauDauLoang(DoanThang canhDaGiac[], int soCanh);
void ThuatToanDauLoang(int x, int y, int nen, int mauMoi);
void DauLoang(Point , int , int);

//Giao dien chinh chuong trinh to mau da giac
int GiaoDienChinh()
{
	Sleep(200);
	XoaManHinh();
	fflush(stdin);
	//Thanh phan cua menu
	string ChucNang[] = {
		"TO MAU THEO DONG QUET",
		"TO MAU THEO VET DAU LOANG",
		"THOAT (HOAC ESC)"	
	};
	
	int p=0, x=30, y=4, SoChucNang=3, exitFlag=0;
	int MauChuHien=14, MauChuMD=7;
	
	while(exitFlag!=1)
	{
		XoaManHinh();
		TextColor(MauChuMD);
		cout<<"\n___________________________ THUAT TOAN TO MAU DA GIAC __________________________";
				
		//In menu va thiet lap mau sac chu
		for (int i = 0; i < SoChucNang; i++)
		{
			gotoxy(x,y+i);
			if (i == p)
			{
				TextColor(MauChuHien);
				cout << ChucNang[i];
			}			
			else
			{
				TextColor(MauChuMD);
				cout << ChucNang[i];
			}
		}
		TextColor(MauChuMD);
		
		//Thiet lap Up/Down/Enter/Escape
		while(1)
		{
			fflush(stdin);
			if (GetAsyncKeyState(VK_UP))	//Up
			{
				p -= 1;
				if (p == -1)
				{
					p = SoChucNang-1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN))	//Down
			{
				p += 1;
				if (p == SoChucNang)
				{
					p = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN))	//Enter
			{
				XoaManHinh();
				switch(p)
				{
					case 0: GiaoDienDongQuet(); break;
					case 1: GiaoDienDauLoang(); break;
					case 2: exitFlag = Thoat(); break;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_ESCAPE)) exitFlag=Thoat();	break;		//Escape				
		}
		Sleep(200);
	}
}

//Xu ly thoat chuong trinh
int Thoat()
{
	//fflush(stdin);
	Sleep(200);
	XoaManHinh();
	fflush(stdin);
	string chon[] = { " KHONG ", " CO "};
	int m=0 ;
	int MauChuHien=14, MauChuMD=7, x=20,y=4;
	
	while(1)
	{
		TextColor(MauChuMD);
		gotoxy(32,2); cout<<"BAN MUON THOAT?";
		
		//In menu va thiet lap mau sac
		gotoxy(33,4);
		for (int i = 0; i < 2; ++i)
		{	
			if (i == m)
			{				
				TextColor(MauChuHien);
				cout << chon[i] ;
			}
			else
			{				
				TextColor(MauChuMD);
				cout << chon[i] ;
			}
		}
		//Thiet lap mau ve mac dinh
		TextColor(MauChuMD);
		
		//Thiet lap Left/Right/Enter
		while(1)
		{
			fflush(stdin);
			if (GetAsyncKeyState(VK_LEFT))	//Left
			{
				m-= 1;
				if (m == -1)
				{
					m = 1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RIGHT))	//Right
			{
				m+= 1;
				if (m == 2)
				{
					m = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN))	//Enter
			{
				return m;
			}
			break;
			//cin.ignore(1);
		}
		Sleep(200);
	}
}


//	Giao dien to mau theo thuat toan scanline
void GiaoDienDongQuet()
{
	// Thuat toan
	cout<<"\n_______________________________Thuat toan scanline______________________________";
	thuatToan = 1;
	VeDaGiac();
}

//	Sap xep cac canh da giac (loai bo canh song song Ox, cac canh tang dan theo Oy)
void SapXepCanhDaGiac(DoanThang canhDaGiac[], int soCanh)
{	
	//	Loai bo cac canh da giac song song voi Ox	
	int soCanhConLai = soCanh, soCanhGiamDi = 0;
	
	DoanThang doanThangTam[soCanhConLai];
	
	for(int i=0; i<soCanh; i++)
	{
		if(canhDaGiac[i].diemDau.y != canhDaGiac[i].diemCuoi.y)
		{
			doanThangTam[i-soCanhGiamDi] = canhDaGiac[i];
		}
		else
		{
			soCanhConLai--;
			soCanhGiamDi++;
		}
	}
	
	//	Sap xep canh tang dan theo Oy
	int ymin_dt1, ymin_dt2;
	DoanThang tam;
	for(int i=0; i<soCanhConLai; i++)
	{
		ymin_dt1 = min( doanThangTam[i].diemDau.y, doanThangTam[i].diemCuoi.y ) ;
		for(int j=i+1; j<soCanhConLai; j++)
		{
			ymin_dt2 = min( doanThangTam[j].diemDau.y, doanThangTam[j].diemCuoi.y ) ;
			if( ymin_dt1 >= ymin_dt2 )
			{
				tam = doanThangTam[i];
				doanThangTam[i] = doanThangTam[j];
				doanThangTam[j] = tam;
			}
		}
	}
	
	//	Sao chep lai doan thang doanThangTam[] da sap xep vao mang canhDaGiac[]
	for(int i=0; i<soCanhConLai; i++)	
	{
		canhDaGiac[i] = doanThangTam[i];
		//	Trang thai canh da giac ban dau = 0 (chua kich hoat)
		trangThai[i] = 0;
		
	}
	
	//	Sau khi sap xep, ymin la min cua canh da giac dau tien, ymax la max cua canh da giac cuoi cung 
	ymin = min(canhDaGiac[0].diemDau.y, canhDaGiac[0].diemCuoi.y);
	ymax = max(canhDaGiac[soCanhConLai-1].diemDau.y, canhDaGiac[soCanhConLai-1].diemCuoi.y);
	
	//	Tim xmin, xmax cua da giac
	int xtamMin, xtamMax;
	for(int i=0; i<soCanhConLai-1; i++)
	{
		xmin = min(canhDaGiac[i].diemDau.x, canhDaGiac[i].diemCuoi.x);
		xmax = max(canhDaGiac[i].diemDau.x, canhDaGiac[i].diemCuoi.x);
		xtamMin = min(canhDaGiac[i+1].diemDau.x, canhDaGiac[i+1].diemCuoi.x);
		xtamMax = max(canhDaGiac[i+1].diemDau.x, canhDaGiac[i+1].diemCuoi.x);
		if(xtamMin<=xmin)	xmin = xtamMin;
		if(xtamMax>=xmax)	xmax = xtamMax;
	}
	
	//	Goi thuat toan to mau da chon
	if(thuatToan == 1)
	{
		//	Goi ThuatToanScanline de to mau theo dong quet
		ThuatToanScanline(canhDaGiac, soCanhConLai);
	}
	if(thuatToan == 2)
	{
		//	Goi ToMauDauLoang de to mau theo vet dau loang
		ToMauDauLoang(canhDaGiac, soCanh);
	}	
}

//	Thuat toan to mau theo dong quet
void ThuatToanScanline(DoanThang canh[], int soCanh)
{
	cout<<"\nThuat toan scanline...";
	//	Tao dong quet quet qua da giac
	DoanThang dongQuet;
	dongQuet.diemDau.x = xmin;
	dongQuet.diemCuoi.x = xmax;
	int dem=0;	//	So giao diem khi cat da giac
	for(int i=ymin; i<ymax; i++)
	{
		dongQuet.diemDau.y = i;
		dongQuet.diemCuoi.y = dongQuet.diemDau.y;
		for(int j=0; j<soCanh; j++)
		{
			if( CatCanhDaGiac(canh[j].diemDau.y, i, canh[j].diemCuoi.y) == true)
			{
				// Danh dau trang thai cua doan thang j kich hoat
				trangThai[j] = 1;				
			}
			else
			{
				//	Danh dau trang thai cua doan thang j khong con kich hoat
				trangThai[j] = 0;
			}
			if(trangThai[j]==1)
			{
				giaoDiem[dem] = TimGiaoDiem(canh[j], dongQuet);				
				dem++;
			}
		}
	}
	
	//	Sap xep giao diem tang dan theo x, gom nhom theo y
	int tamx;
	for(int i=0; i<dem; i++)
	{
		for(int j=i+1; j<dem; j++)
		{
			if(giaoDiem[i].x > giaoDiem[j].x && giaoDiem[i].y == giaoDiem[j].y)
			{
				tamx=giaoDiem[j].x;
				giaoDiem[j].x=giaoDiem[i].x;
				giaoDiem[i].x=tamx;
			}			
		}		
	}
	
	//To mau cho vung nam trong khoang cac giao diem
	int ydem = 0,vt;
	for(int i=0; i<dem-1; i++)
	{
		ydem = 1;
		for(int k=i+1; k<dem; k++)
		{
			if(giaoDiem[k].y == giaoDiem[i].y)
			{
				vt = k;
				ydem++;			 	
			}		
			else	break;
		}
		int imin, imax;
		if(ydem%2 == 0)
		{
			for(int m=i; m<i+ydem ;m++)
			{
			 	imin = giaoDiem[m].x;
				imax = giaoDiem[m+1].x;
				for(int j=imin; j<=imax; j++)
				{
					putpixel(j, giaoDiem[m].y, mauTo);
				}
				m++;	
			}		
			i+=ydem-1;
		}		
		else
		{
			for(int m=i; m<i+ydem ;m++)
			{
			 	imin = giaoDiem[m].x;
				imax = giaoDiem[m+2].x;
				for(int j=imin; j<=imax; j++)
				{
					putpixel(j, giaoDiem[m].y, mauTo);
				}					
				m++;
			}
			i+=ydem-1;			
		}
	}
	cout<<"\nSo giao diem: "<<dem<<"\nKet thuc thuat toan scanline";
	//getch();
	//delay(10000);
	//GiaoDienChinh();
}

//	Tim giao diem cua 2 doan thang
Point TimGiaoDiem(DoanThang d1, DoanThang d2)
{
	//	Phuong trinh doan thang di qua 2 diem A(xa,ya), B(xb,yb) có dang Y = Ax + B
	//	=> Y = X(ya-yb)/(xa-xb) + (ybxa - yaxb)/(xa-xb)
	
	//	Toa do diem A,B,C,D
	float xa,xb,xc,xd,ya,yb,yc,yd;
	xa = d1.diemDau.x;
	ya = d1.diemDau.y;
	xb = d1.diemCuoi.x;
	yb = d1.diemCuoi.y;
	xc = d2.diemDau.x;
	yc = d2.diemDau.y;
	xd = d2.diemCuoi.x;
	yd = d2.diemCuoi.y;
	
	//	Tim giao diem cua 2 doan thang y1 = Ax+B, y2 = Cx+D
	//	=> X = (D-B)/(A-C), Y = (A*D-B*C)/(A-C)
	double  a, b, c, d, x, y;
	a = (ya-yb) / (xa-xb);
	b = (yb*xa - ya*xb) / (xa-xb);
	c = (yc-yd) / (xc-xd);
	d = (yd*xc - yc*xd) / (xc-xd);
	x = (d-b) / (a-c);
	y = (a*d-b*c) / (a-c);
	
	Point giaoDiem2DT;
	giaoDiem2DT.x = x;
	giaoDiem2DT.y = y;
	return giaoDiem2DT;
}

//	Ham ve da giac voi n dinh
void VeDaGiac()
{
	cout<<"\n\n- Ve da giac can to mau bang chuot.\n- Double-click tai dinh cuoi cung de ket thuc.";
	
	int soDinhDaGiac = 0;
	Point p1, p2, daGiac[soDinhToiDa];
	while(1)
    {
    	clearmouseclick(WM_LBUTTONDOWN);
    	clearmouseclick(WM_LBUTTONDBLCLK);
		delay(0.001);
    	if( ismouseclick(WM_LBUTTONDBLCLK) )
		{
			getmouseclick(WM_LBUTTONDBLCLK,p2.x,p2.y);
			//	Double-click se có 2 click down -> sodinh-1
			daGiac[soDinhDaGiac-1] = p2;
    		cout<<"\nDouble-click:\tX: "<<p2.x<<"\tY: "<<p2.y;
    		putpixel(p2.x,p2.y,mauVe);
			break; 
		}
		if (ismouseclick(WM_LBUTTONDOWN))
    	{    		
    		getmouseclick(WM_LBUTTONDOWN, p1.x, p1.y);
			daGiac[soDinhDaGiac] = p1;
			putpixel(p1.x,p1.y,mauVe);
			soDinhDaGiac++;    		
    		cout<<"\nClick down:\tX: "<<p1.x<<"\tY: "<<p1.y;
			//cout<<"\nSo dinh: "	<<soDinhDaGiac;
		}       
	}
	
	//	Da giac n dinh co n+1 toa do dinh -> can (n+1)*2 phan tu luu toa do.
	int m = (soDinhDaGiac+1)*2;
	int toaDo[m], k=0;
	DoanThang dt[soDinhDaGiac];
	for(int i=0; i<m; i+=2)
	{
		if(k < soDinhDaGiac)
		{
			toaDo[i] = daGiac[k].x;
			toaDo[i+1] = daGiac[k].y;
			//	Tao doan thang (canh) cho da giac
			dt[k].diemDau = daGiac[k];
			//cout<<"\nDoan thang"<<k<<"\tDiem dau\tX: "<<dt[k].diemDau.x<<"\tY: "<<dt[k].diemDau.y;
			k++;
			dt[k-1].diemCuoi = daGiac[k];
			//cout<<"\nDoan thang"<<k-1<<"\tDiem cuoi\tX: "<<dt[k-1].diemCuoi.x<<"\tY: "<<dt[k-1].diemCuoi.y;
		}
	}
	
	//	Toa do diem dau tien va diem cuoi cung trung nhau
	toaDo[m-2] = daGiac[0].x;
	toaDo[m-1] = daGiac[0].y;
	//	Diem cuoi cua doan thang cuoi = diem dau cua doan thang dau
	dt[soDinhDaGiac-1].diemCuoi = dt[0].diemDau;
	
	//	Chep mang dt[][] vao mang canh da giac canhDaGiac[]
	for(int j=0; j<soDinhDaGiac; j++)
	{
		canhDaGiac[j] = dt[j];
	}
	
	//	Ve da giac theo so dinh va toa do da chon
	drawpoly(soDinhDaGiac+1, toaDo);
	
	//	Goi ham sap xep canh da giac
	SapXepCanhDaGiac(canhDaGiac, soDinhDaGiac);
	
	//getch();
}

//	Giao dien thuat toan dau loang
void GiaoDienDauLoang()
{
	cout<<"\n______________________________Thuat toan dau loang______________________________";
	thuatToan = 2;
	VeDaGiac();	
}

//	Xac dinh toa do diem p co nam trong da giac hay khong, neu co thi to mau da giac theo thuat toan dau loang
void ToMauDauLoang(DoanThang canhDaGiac[], int soCanh)
{
	nhay:
	cout<<"\nClick vao 1 diem trong da giac de to mau...";
	Point p;
	
	clearmouseclick(WM_LBUTTONDOWN);
	while(1)
	{
		delay(0.01);
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			//	Nhan toa do diem click p
			getmouseclick(WM_LBUTTONDOWN, p.x, p.y);
			cout<<"\nClick down...\tX: "<<p.x<<"\tY: "<<p.y;
			break;			
		}	
	}
	//	Neu diem p nam trong HCN nho nhat chua da giac thi p co kha nang nam trong da giac
	if( p.x<xmin || p.x>xmax || p.y<ymin || p.y>ymax )
	{
		cout<<"\nDiem P ban vua click khong nam trong da giac.";
		goto nhay;
		
	}
	else
	{
		//	Tao doan thang kiemTra quet qua diem p, gioi han kiemTra nam trong HCN nho nhat chua da giac
		DoanThang kiemTra;
		kiemTra.diemDau.x = xmin;
		kiemTra.diemCuoi.x = xmax;
		kiemTra.diemDau.y = p.y;
		kiemTra.diemCuoi.y = kiemTra.diemDau.y;
		
		int dem=0, n=100;
		Point giaoDiemKT[n];	
		
		for(int i=0; i<soCanh; i++)
		{
			//	Chi tim giao diem tren nhung canh cua da giac co kha nang cat doan thang kiemTra			
			if( CatCanhDaGiac(canhDaGiac[i].diemDau.y, p.y, canhDaGiac[i].diemCuoi.y) )
			{
				giaoDiemKT[dem]= TimGiaoDiem(canhDaGiac[i], kiemTra);
				dem++;			 				 	
			}			
		}
		//	Neu p nam giua 1 cap giao diem -> p thuoc da giac => to mau tu diem p		
		for(int j=0; j<dem; j+=2)
		{
			if(ThuocDoanThang(giaoDiemKT[j], p, giaoDiemKT[j+1]) == true )
			//ThuatToanDauLoang(p.x, p.y, mauNen, mauTo);			 	
			DauLoang(p, mauNen, mauTo);
		}					
	}
	//delay(10000);
	//getch();
	//GiaoDienChinh();
}

//	Thuat toan to mau theo dau loang khong de quy (dung queue)
void DauLoang(Point p, int chuaTo, int mauTo)
{
	//	Khai bao queue chua pixel chua duoc to mau
	queue<Point> myQueue;	
    
    Point	m, temp;
    m.x = p.x;
    m.y = p.y;
    putpixel(m.x, m.y, mauTo);
    //	Them 1 diem vao queue, queue size tang 1
    myQueue.push(m);
    
//    int mauHienTai;	
//    mauHienTai = getpixel(x,y);

	  //	Xet 4 diem xung quanh voi moi diem luu trong queue (neu queue con phan tu)
	while(myQueue.empty() != true)
	{
		//	Xoa 1 diem phia dau queue, queue size giam 1
		myQueue.pop();
		//	Xet cac diem lan can cua 1 diem (phai -> trai -> tren -> duoi)
		if(getpixel(m.x+1, m.y) == chuaTo)
		{
			putpixel(m.x+1, m.y, mauTo);
			temp.x = m.x+1;
			temp.y = m.y; 
			myQueue.push(temp);
		}  
		if(getpixel(m.x-1, m.y) == chuaTo)
		{
			putpixel(m.x-1, m.y, mauTo);
			temp.x = m.x-1;
			temp.y = m.y;
			myQueue.push(temp);
		}
		if(getpixel(m.x, m.y+1) == chuaTo)
		{
			putpixel(m.x, m.y+1, mauTo);
			temp.x = m.x;
			temp.y = m.y+1;
			myQueue.push(temp);
		}
		if(getpixel(m.x, m.y-1) == chuaTo)
		{
			putpixel(m.x, m.y-1, mauTo);
			temp.x = m.x;
			temp.y = m.y-1;
			myQueue.push(temp);
		}
		m = myQueue.front();
	}
}

//	Xac dinh dong quet co tung do = y di qua canh cua da giac hay khong?
bool CatCanhDaGiac(int y1, int y2, int y3)
{
	if (y2 <= max(y1, y3) && y2 >= min(y1, y3))
	   		 return true;
    else
			 return false;
}

//	Xac dinh 3 diem co thang hang hay khong (trong truong hop p1.y = p2.y = p3.y)
bool ThuocDoanThang(Point p1, Point p2, Point p3)
{
//	if( (p2.x<=max(p1.x,p3.x)) && (p2.x>=min(p1.x,p3.x)) && (p2.y<=max(p1.y,p3.y)) && ((p2.y>=min(p1.y,p3.y))))
	if( (p2.x<=max(p1.x,p3.x)) && (p2.x>=min(p1.x,p3.x)) )
		return true;
	else
		return false;
}

//	Chuong trinh chinh to mau theo thuat toan
main()
{	
	int gd,gm=DETECT;
	initgraph(&gd, &gm, "C:\\TC\\BGI");	
	cleardevice();
	fflush(stdin);
	GiaoDienChinh();
	
	closegraph();
}
