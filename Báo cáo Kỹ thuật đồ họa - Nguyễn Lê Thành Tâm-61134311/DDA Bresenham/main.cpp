#include<graphics.h>
#include<mylib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

#define Round(a)  int(a+0.5)

struct Point{
	int x, y;
};

int Color = YELLOW;
int GiaoDienChinh();
int Thoat();
void GiaoDienDDA1();
void GiaoDienDDA2();
void GiaoDienBres1();
void GiaoDienBres2();
void GiaoDienMid();
void DuongThangBres(Point, Point);
void DuongThangDDA(Point, Point);
void DuongTronBres(Point, int);
void DuongTronDDA(Point, int);
void DuongTronMid(Point, int);
void DoiXung(Point, Point);

//Giao dien chinh chuong trinh
int GiaoDienChinh()
{
	fflush(stdin);
	Sleep(200);
	XoaManHinh();	
	//Thanh phan cua menu
	string ChucNang[] = {
		"VE DUONG THANG THEO DDA",
		"VE DUONG THANG THEO BRES, MiD",
		"VE DUONG TRON THEO BRES",
		"VE DUONG TRON THEO MID",
		"THOAT (HOAC ESC)"	
	};
	
	int p=0, x=30, y=4, SoChucNang=5, exitFlag=0;
	int MauChuHien=14, MauChuMD=7;
	
	while(exitFlag!=1)
	{
		XoaManHinh();
		TextColor(MauChuMD);
		cout<<"\n___________________________ THUAT TOAN VE DUONG CO BAN _________________________";
				
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
					case 0: GiaoDienDDA1(); break;
					case 1: GiaoDienBres1(); break;
					//case 2: GiaoDienDDA2(); break;
					case 2: GiaoDienBres2(); break;
					case 3: GiaoDienMid(); break;
					case 4: exitFlag=Thoat(); break;
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
				m += 1;
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

//Goi ham ve duong thang theo thuat toan DDA
void GiaoDienDDA1()
{
	//int x1,x2,y1,y2;
	Point p1, p2;
	cout<<"\n\t\t\tVE DUONG THANG THEO THUAT TOAN DDA";
	while(1)
	{
		cout<<"\nNhap toa do DDA";
		cout<<"\nX1: ";	cin>>p1.x;
		cout<<"Y1: ";	cin>>p1.y;
		cout<<"X2: ";	cin>>p2.x;
		cout<<"Y2: ";	cin>>p2.y;
		//	Chuyen sang he toa do thuc
		p1.x = 320+p1.x;
		p1.y = 240-p1.y;
		p2.x = 320+p2.x;
		p2.y = 240-p2.y;
		//LineDDA(320+x1,240-y1,320+x2,240-y2);
		delay(0.01);
		DuongThangDDA(p1, p2);
	}
}

//Ve duong thang theo thuat toan DDA
void DuongThangDDA(Point p1, Point p2)
{
	fflush(stdin);
    Point p;
	float dx, dy, Step, xInc, yInc;

    dx = p1.x - p2.x;
    dy = p1.y - p2.y;

    if (fabs(dx) > fabs(dy))		Step = fabs(dx);
    else		Step = fabs(dy);

    xInc = dx/Step;
    yInc = dy/Step;

    p.x = p1.x;
    p.y = p1.y;

    for (int i=1; i<=Step; i++)
    {
        putpixel(p.x, Round(p.y), Color);
        p.x -= xInc;
        p.y -= yInc;
    }
}


//Goi ham ve duong thang theo thuat toan Bresenham
void GiaoDienBres1()
{
	fflush(stdin);
	//int x1,x2,y1,y2;
	Point p1, p2;
	cout<<"\n\t\t\tVE DUONG THANG THEO THUAT TOAN BRES";
	while(1)
	{
		cout<<"\nNhap toa do bresenham";
		cout<<"\nX1: ";	cin>>p1.x;
		cout<<"Y1: ";	cin>>p1.y;
		cout<<"X2: ";	cin>>p2.x;
		cout<<"Y2: ";	cin>>p2.y;
		//	Chuyen sang he toa do thuc
		p1.x = 320+p1.x;
		p1.y = 240-p1.y;
		p2.x = 320+p2.x;
		p2.y = 240-p2.y;
		DuongThangBres(p1, p2);
		delay(0.01);				
	}
}

//Ve duong thang theo thuat toan Bresenham
void DuongThangBres(Point p1, Point p2)
{
	Point p, pe;
	int dx, dy, dx1, dy1, s1, s2;
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	s1 = 2*dy1-dx1;
	s2 = 2*dx1-dy1;
	
	if(dy1 <= dx1)
	{
		if(dx >= 0)
		{
			p.x = p1.x;
			p.y = p1.y;
			pe.x = p2.x;
		}
		else
		{
			p.x = p2.x;
			p.y = p2.y;
			pe.x = p1.x;
		}
		putpixel(p.x, p.y, Color);
		for(int i=0; p.x < pe.x; i++)
		{
			p.x = p.x+1;
			if(s1 < 0)		s1 = s1+2*dy1;
			else
			{
				if( (dx<0 && dy<0) || (dx>0 && dy>0) )		p.y = p.y+1;
				else	p.y = p.y-1;
				s1 = s1 + 2*(dy1-dx1);
			}
			putpixel(p.x, p.y, Color);
		}
	}
	
	else
	{
		if(dy >= 0)
		{
			p.x = p1.x;
			p.y = p1.y;
			pe.y = p2.y;
			
		}
		else
		{
			p.x = p2.x;
			p.y = p2.y;
			pe.y = p1.y;
		}
		putpixel(p.x, p.y, Color);
		for(int i=0; p.y<pe.y; i++)
		{
			p.y = p.y+1;
			if(s2 <= 0)		s2 = s2 + 2*dx1;
			else
			{
				if( (dx<0 && dy<0) || (dx>0 && dy>0) )		p.x = p.x+1;
				else	p.x = p.x-1;
				s2 = s2 + 2*(dx1-dy1);
			}
			putpixel(p.x, p.y, Color);
		}
	}
}

//Nhap toa do tam, ban kinh va goi ham ve duong tron theo thuat toan Bresenham
void GiaoDienBres2()
{
	fflush(stdin);
	Point tam;
	int r;
	cout<<"\n\t\t\tVE DUONG TRON THEO THUAT TOAN BRES";
	while(1)
	{
		cout<<"\nNhap toa do tam duong tron bresenham";
		cout<<"\nX = ";	cin>>tam.x;
		cout<<"Y = ";	cin>>tam.y;
		cout<<"\Ban kinh duong tron R = ";	cin>>r;
		
		//Ve tam duong tron theo toa do thuc
		tam.x = 320+tam.x;
		tam.y = 240-tam.y; 
		putpixel(tam.x, tam.y, Color);		
		DuongTronBres(tam, r);
		delay(0.01);				
	}
}

void DoiXung(Point p1, Point p2)
{
	putpixel(p1.x+p2.x, p1.y+p2.y, BLUE);
	putpixel(p1.x-p2.x, p1.y+p2.y, BLUE);
	putpixel(p1.x+p2.x, p1.y-p2.y, BLUE);
	putpixel(p1.x-p2.x, p1.y-p2.y, BLUE);
	putpixel(p1.x+p2.y, p1.y+p2.x, BLUE);
	putpixel(p1.x-p2.y, p1.y+p2.x, BLUE);
	putpixel(p1.x+p2.y, p1.y-p2.x, BLUE);
	putpixel(p1.x-p2.y, p1.y-p2.x, BLUE);
}
//Ve duong tron bang thuat toan Bresenham
void DuongTronBres(Point tam, int r)
{
	Point p;
	p.x = 0;
	p.y = r;
	int b = 3-2*r;
	while(p.x < p.y)
	{
		DoiXung(tam, p);
		p.x++;
		if(b < 0)	b = b+4*p.x+6;
		else
		{
			p.y--;
			b = b+4*(p.x-p.y)+10;
		}
		DoiXung(tam, p);
	}
}

//	Ve duong tron theo thuat toan Midpoint
void GiaoDienMid()
{
	fflush(stdin);
	Point tam;
	int r;
	cout<<"\n\t\t\tVE DUONG TRON THEO THUAT TOAN MIDPOINT";
	while(1)
	{
		cout<<"\nNhap toa do tam duong tron Midpoint";
		cout<<"\nX = ";	cin>>tam.x;
		cout<<"Y = ";	cin>>tam.y;
		cout<<"\Ban kinh duong tron R = ";	cin>>r;
		
		//Ve tam duong tron theo toa do thuc
		tam.x = 320+tam.x;
		tam.y = 240-tam.y; 
		putpixel(tam.x, tam.y, Color);
		DuongTronMid(tam, r);
		delay(0.01);				
	}
}

//	Ve duong tron theo thuat toan Midpoint
void DuongTronMid(Point tam, int r)
{
	
	Point p;
	p.x = 0;
	p.y = r;
	float m = 5/4 - r;
	while (p.x < p.y)
	{
		DoiXung(tam, p);
		p.x++;
		if (m < 0)	m+= 2*p.x + 3;
		else
		{
			m+= 2*(p.x -p.y) + 5;
			p.y--;
		}		
		DoiXung(tam, p);
	}
}
 
//	Ve doi xung cho thuat toan ve duong tron
//void DoiXung(Point p1, Point p2)
//{
//	putpixel(p1.x+p2.x, p1.y+p2.y, BLUE);
//	putpixel(p1.x-p2.x, p1.y+p2.y, BLUE);
//	putpixel(p1.x+p2.x, p1.y-p2.y, BLUE);
//	putpixel(p1.x-p2.x, p1.y-p2.y, BLUE);
//	putpixel(p1.x+p2.y, p1.y+p2.x, BLUE);
//	putpixel(p1.x-p2.y, p1.y+p2.x, BLUE);
//	putpixel(p1.x+p2.y, p1.y-p2.x, BLUE);
//	putpixel(p1.x-p2.y, p1.y-p2.x, BLUE);
//}

//	Chuong trinh chinh
main()
{
	int gm=DETECT, gd;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	//Ve truc toa do thuc
	line(320,0,320,480);
    line(0,240,640,240);
		
	GiaoDienChinh();
	//getch();
	closegraph();
}

