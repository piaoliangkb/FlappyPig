
#include "stdafx.h"
#include "stdlib.h"
#include "time.h"



HINSTANCE hInst;
HBITMAP bg,dark,pig1,pig1black,pipe_up1,pipe_up2,pipe_down1,pipe_down2;
HBITMAP startbutton,startbutton_black,startbutton_down,startbmp,startbmp_black
,title,title_black,gameover,gameover_black,score_panel,score_panel_black
,restartbutton,restartbutton_down,button_score,button_score_black,button_score_down;
HBITMAP number[10],number_black[10],snumber[10],snumber_black[10];
HBITMAP pigup[21],pigup_black[21],pigdownfly1[18],pigdownfly1_black[18],pigdownfly2[18],pigdownfly2_black[18],pigdownfly3[18],pigdownfly3_black[18];
HBITMAP pigdown,pigdown_black,pigdown1,pigdown_black1,medals[3],medals_black,pigdowndown,pigdowndown_black;
HBITMAP flower,flowerclose,flower_black,flowerclose_black,cherry,cherry_black,leaf,leaf_black;
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow,pipecountPre,pipecountNow;

POINT point;//鼠标位置

int		x=0,pigy=200,pigypre=270,inix=400,iniy=10;
int     tempx=0,tempsecx=0;
int     uppipelength,downpipelength,uppipelength1,downpipelength1;
int     ifsig=0,upflag=0;
int		startflag=0,overflag=0,scoreflag=0,restartflag=0,cycleindex=0;
int		pipecount=0;
const int xspeed=5;
int		num=0,flydownimage=0;

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);
void				CollisionJudgment();
void				RandOfPipe1();
void				RandOfPipe2();

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

    srand((unsigned)time(NULL));

	RandOfPipe1();
	RandOfPipe2();
	
	//随机定义管子长度


	MSG msg;

	MyRegisterClass(hInstance);


	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}


    while( msg.message!=WM_QUIT )
    {
        if( PeekMessage( &msg, NULL, 0,0 ,PM_REMOVE) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
		else
		{
			tNow = GetTickCount();

			if(tNow-tPre >= 20)
			{
			    MyPaint(hdc);
			}
					
		}
    }

	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "canvas";
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
	hInst = hInstance;

	hWnd = CreateWindow("canvas", "Window" , WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	MoveWindow(hWnd,inix,iniy,400,630,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);

	bmp = CreateCompatibleBitmap(hdc,400,600);
	SelectObject(mdc,bmp);

	bg = (HBITMAP)LoadImage(NULL,"timg.bmp",IMAGE_BITMAP,400,600,LR_LOADFROMFILE);
	dark=(HBITMAP)LoadImage(NULL,"dark.bmp",IMAGE_BITMAP,400,600,LR_LOADFROMFILE);
	
	pig1=(HBITMAP)LoadImage(NULL,"pig1.bmp",IMAGE_BITMAP,32,24,LR_LOADFROMFILE);
	pig1black=(HBITMAP)LoadImage(NULL,"pig1black.bmp",IMAGE_BITMAP,32,24,LR_LOADFROMFILE);

	pipe_up1=(HBITMAP)LoadImage(NULL,"pipe_up1.bmp",IMAGE_BITMAP,52,320,LR_LOADFROMFILE);
	pipe_up2=(HBITMAP)LoadImage(NULL,"pipe_up2.bmp",IMAGE_BITMAP,52,320,LR_LOADFROMFILE);

	pipe_down1=(HBITMAP)LoadImage(NULL,"pipe_down1.bmp",IMAGE_BITMAP,52,320,LR_LOADFROMFILE);
	pipe_down2=(HBITMAP)LoadImage(NULL,"pipe_down2.bmp",IMAGE_BITMAP,52,320,LR_LOADFROMFILE);

	startbutton=(HBITMAP)LoadImage(NULL,"startbutton.bmp",IMAGE_BITMAP,116,70,LR_LOADFROMFILE);
	startbutton_black=(HBITMAP)LoadImage(NULL,"startbutton_black.bmp",IMAGE_BITMAP,116,70,LR_LOADFROMFILE);
	startbutton_down=(HBITMAP)LoadImage(NULL,"startbutton_down.bmp",IMAGE_BITMAP,116,70,LR_LOADFROMFILE);

	startbmp=(HBITMAP)LoadImage(NULL,"startbmp.bmp",IMAGE_BITMAP,114,98,LR_LOADFROMFILE);
	startbmp_black=(HBITMAP)LoadImage(NULL,"startbmp_black.bmp",IMAGE_BITMAP,114,98,LR_LOADFROMFILE);

	gameover=(HBITMAP)LoadImage(NULL,"gameover.bmp",IMAGE_BITMAP,204,54,LR_LOADFROMFILE);
	gameover_black=(HBITMAP)LoadImage(NULL,"gameover_black.bmp",IMAGE_BITMAP,204,54,LR_LOADFROMFILE);

	title=(HBITMAP)LoadImage(NULL,"title.bmp",IMAGE_BITMAP,178,48,LR_LOADFROMFILE);
	title_black=(HBITMAP)LoadImage(NULL,"title_black.bmp",IMAGE_BITMAP,178,48,LR_LOADFROMFILE);


	number[0]=(HBITMAP)LoadImage(NULL,"number[0].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);
	number_black[0]=(HBITMAP)LoadImage(NULL,"number_black[0].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);

	number[1]=(HBITMAP)LoadImage(NULL,"number[1].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);
	number_black[1]=(HBITMAP)LoadImage(NULL,"number_black[1].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);

	number[2]=(HBITMAP)LoadImage(NULL,"number[2].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);
	number_black[2]=(HBITMAP)LoadImage(NULL,"number_black[2].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);

	number[3]=(HBITMAP)LoadImage(NULL,"number[3].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);
	number_black[3]=(HBITMAP)LoadImage(NULL,"number_black[3].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);

	number[4]=(HBITMAP)LoadImage(NULL,"number[4].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);
	number_black[4]=(HBITMAP)LoadImage(NULL,"number_black[4].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);

	number[5]=(HBITMAP)LoadImage(NULL,"number[5].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);
	number_black[5]=(HBITMAP)LoadImage(NULL,"number_black[5].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);

	number[6]=(HBITMAP)LoadImage(NULL,"number[6].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);
	number_black[6]=(HBITMAP)LoadImage(NULL,"number_black[6].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);

	number[7]=(HBITMAP)LoadImage(NULL,"number[7].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);
	number_black[7]=(HBITMAP)LoadImage(NULL,"number_black[7].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);

	number[8]=(HBITMAP)LoadImage(NULL,"number[8].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);
	number_black[8]=(HBITMAP)LoadImage(NULL,"number_black[8].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);

	number[9]=(HBITMAP)LoadImage(NULL,"number[9].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);
	number_black[9]=(HBITMAP)LoadImage(NULL,"number_black[9].bmp",IMAGE_BITMAP,24,44,LR_LOADFROMFILE);

	
	snumber[0]=(HBITMAP)LoadImage(NULL,"snumber[0].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);
	snumber_black[0]=(HBITMAP)LoadImage(NULL,"snumber_black[0].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);

	snumber[1]=(HBITMAP)LoadImage(NULL,"snumber[1].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);
	snumber_black[1]=(HBITMAP)LoadImage(NULL,"snumber_black[1].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);

	snumber[2]=(HBITMAP)LoadImage(NULL,"snumber[2].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);
	snumber_black[2]=(HBITMAP)LoadImage(NULL,"snumber_black[2].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);

	snumber[3]=(HBITMAP)LoadImage(NULL,"snumber[3].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);
	snumber_black[3]=(HBITMAP)LoadImage(NULL,"snumber_black[3].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);

	snumber[4]=(HBITMAP)LoadImage(NULL,"snumber[4].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);
	snumber_black[4]=(HBITMAP)LoadImage(NULL,"snumber_black[4].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);

	snumber[5]=(HBITMAP)LoadImage(NULL,"snumber[5].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);
	snumber_black[5]=(HBITMAP)LoadImage(NULL,"snumber_black[5].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);

	snumber[6]=(HBITMAP)LoadImage(NULL,"snumber[6].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);
	snumber_black[6]=(HBITMAP)LoadImage(NULL,"snumber_black[6].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);

	snumber[7]=(HBITMAP)LoadImage(NULL,"snumber[7].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);
	snumber_black[7]=(HBITMAP)LoadImage(NULL,"snumber_black[7].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);

	snumber[8]=(HBITMAP)LoadImage(NULL,"snumber[8].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);
	snumber_black[8]=(HBITMAP)LoadImage(NULL,"snumber_black[8].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);

	snumber[9]=(HBITMAP)LoadImage(NULL,"snumber[9].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);
	snumber_black[9]=(HBITMAP)LoadImage(NULL,"snumber_black[9].bmp",IMAGE_BITMAP,12,22,LR_LOADFROMFILE);

	for(int upi=0;upi<7;upi++)
	{
	pigup[upi]=(HBITMAP)LoadImage(NULL,"pigup[0].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigup_black[upi]=(HBITMAP)LoadImage(NULL,"pigup_black[0].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	}
	for(upi;upi<14;upi++)
	{
	pigup[upi]=(HBITMAP)LoadImage(NULL,"pigup[1].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigup_black[upi]=(HBITMAP)LoadImage(NULL,"pigup_black[1].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	}
	for(upi;upi<21;upi++)
	{
	pigup[upi]=(HBITMAP)LoadImage(NULL,"pigup[2].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigup_black[upi]=(HBITMAP)LoadImage(NULL,"pigup_black[2].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	}

	pigdown=(HBITMAP)LoadImage(NULL,"pigdown.bmp",IMAGE_BITMAP,24,34,LR_LOADFROMFILE);
	pigdown_black=(HBITMAP)LoadImage(NULL,"pigdown_black.bmp",IMAGE_BITMAP,24,34,LR_LOADFROMFILE);

	pigdowndown=(HBITMAP)LoadImage(NULL,"pigdowndown.bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdowndown_black=(HBITMAP)LoadImage(NULL,"pigdowndown_black.bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdown1=(HBITMAP)LoadImage(NULL,"pigdown[0].bmp",IMAGE_BITMAP,28,32,LR_LOADFROMFILE);
	pigdown_black1=(HBITMAP)LoadImage(NULL,"pigdown_black[0].bmp",IMAGE_BITMAP,28,32,LR_LOADFROMFILE);

	score_panel=(HBITMAP)LoadImage(NULL,"score_panel.bmp",IMAGE_BITMAP,238,126,LR_LOADFROMFILE);
	score_panel_black=(HBITMAP)LoadImage(NULL,"score_panel_black.bmp",IMAGE_BITMAP,238,126,LR_LOADFROMFILE);


	medals[1]=(HBITMAP)LoadImage(NULL,"medals[1].bmp",IMAGE_BITMAP,44,44,LR_LOADFROMFILE);
	medals[2]=(HBITMAP)LoadImage(NULL,"medals[2].bmp",IMAGE_BITMAP,44,44,LR_LOADFROMFILE);
	medals[3]=(HBITMAP)LoadImage(NULL,"medals[3].bmp",IMAGE_BITMAP,44,44,LR_LOADFROMFILE);
	medals_black=(HBITMAP)LoadImage(NULL,"medals_black.bmp",IMAGE_BITMAP,44,44,LR_LOADFROMFILE);

	flower=(HBITMAP)LoadImage(NULL,"flower.bmp",IMAGE_BITMAP,28,49,LR_LOADFROMFILE);
	flower_black=(HBITMAP)LoadImage(NULL,"flower.bmp",IMAGE_BITMAP,28,49,LR_LOADFROMFILE);

	flowerclose=(HBITMAP)LoadImage(NULL,"flowerclose.bmp",IMAGE_BITMAP,25,52,LR_LOADFROMFILE);
	flowerclose_black=(HBITMAP)LoadImage(NULL,"flowerclose_black.bmp",IMAGE_BITMAP,25,52,LR_LOADFROMFILE);

	leaf=(HBITMAP)LoadImage(NULL,"leaf.bmp",IMAGE_BITMAP,28,43,LR_LOADFROMFILE);
	leaf=(HBITMAP)LoadImage(NULL,"leaf_black.bmp",IMAGE_BITMAP,28,43,LR_LOADFROMFILE);

	cherry=(HBITMAP)LoadImage(NULL,"cherry.bmp",IMAGE_BITMAP,35,38,LR_LOADFROMFILE);
	cherry_black=(HBITMAP)LoadImage(NULL,"cherry_black.bmp",IMAGE_BITMAP,35,38,LR_LOADFROMFILE);

	pigdownfly1[0]=(HBITMAP)LoadImage(NULL,"pigdownfly1[0].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[0]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[0].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[1]=(HBITMAP)LoadImage(NULL,"pigdownfly1[1].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[1]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[1].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[2]=(HBITMAP)LoadImage(NULL,"pigdownfly1[2].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[2]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[2].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[3]=(HBITMAP)LoadImage(NULL,"pigdownfly1[3].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[3]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[3].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[4]=(HBITMAP)LoadImage(NULL,"pigdownfly1[4].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[4]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[4].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[5]=(HBITMAP)LoadImage(NULL,"pigdownfly1[5].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[5]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[5].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[6]=(HBITMAP)LoadImage(NULL,"pigdownfly1[6].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[6]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[6].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[7]=(HBITMAP)LoadImage(NULL,"pigdownfly1[7].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[7]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[7].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[8]=(HBITMAP)LoadImage(NULL,"pigdownfly1[8].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[8]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[8].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[9]=(HBITMAP)LoadImage(NULL,"pigdownfly1[9].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[9]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[9].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[10]=(HBITMAP)LoadImage(NULL,"pigdownfly1[10].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[10]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[10].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[11]=(HBITMAP)LoadImage(NULL,"pigdownfly1[11].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[11]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[11].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[12]=(HBITMAP)LoadImage(NULL,"pigdownfly1[12].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[12]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[12].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[13]=(HBITMAP)LoadImage(NULL,"pigdownfly1[13].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[13]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[13].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[14]=(HBITMAP)LoadImage(NULL,"pigdownfly1[14].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[14]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[14].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[15]=(HBITMAP)LoadImage(NULL,"pigdownfly1[15].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[15]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[15].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[16]=(HBITMAP)LoadImage(NULL,"pigdownfly1[16].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[16]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[16].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly1[17]=(HBITMAP)LoadImage(NULL,"pigdownfly1[17].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly1_black[17]=(HBITMAP)LoadImage(NULL,"pigdownfly1_black[17].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);


	pigdownfly2[0]=(HBITMAP)LoadImage(NULL,"pigdownfly2[0].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[0]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[0].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[1]=(HBITMAP)LoadImage(NULL,"pigdownfly2[1].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[1]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[1].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[2]=(HBITMAP)LoadImage(NULL,"pigdownfly2[2].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[2]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[2].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[3]=(HBITMAP)LoadImage(NULL,"pigdownfly2[3].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[3]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[3].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[4]=(HBITMAP)LoadImage(NULL,"pigdownfly2[4].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[4]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[4].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[5]=(HBITMAP)LoadImage(NULL,"pigdownfly2[5].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[5]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[5].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[6]=(HBITMAP)LoadImage(NULL,"pigdownfly2[6].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[6]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[6].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[7]=(HBITMAP)LoadImage(NULL,"pigdownfly2[7].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[7]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[7].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[8]=(HBITMAP)LoadImage(NULL,"pigdownfly2[8].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[8]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[8].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[9]=(HBITMAP)LoadImage(NULL,"pigdownfly2[9].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[9]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[9].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[10]=(HBITMAP)LoadImage(NULL,"pigdownfly2[10].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[10]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[10].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[11]=(HBITMAP)LoadImage(NULL,"pigdownfly2[11].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[11]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[11].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[12]=(HBITMAP)LoadImage(NULL,"pigdownfly2[12].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[12]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[12].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[13]=(HBITMAP)LoadImage(NULL,"pigdownfly2[13].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[13]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[13].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[14]=(HBITMAP)LoadImage(NULL,"pigdownfly2[14].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[14]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[14].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[15]=(HBITMAP)LoadImage(NULL,"pigdownfly2[15].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[15]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[15].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[16]=(HBITMAP)LoadImage(NULL,"pigdownfly2[16].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[16]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[16].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly2[17]=(HBITMAP)LoadImage(NULL,"pigdownfly2[17].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly2_black[17]=(HBITMAP)LoadImage(NULL,"pigdownfly2_black[17].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[0]=(HBITMAP)LoadImage(NULL,"pigdownfly3[0].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[0]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[0].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[1]=(HBITMAP)LoadImage(NULL,"pigdownfly3[1].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[1]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[1].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[2]=(HBITMAP)LoadImage(NULL,"pigdownfly3[2].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[2]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[2].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[3]=(HBITMAP)LoadImage(NULL,"pigdownfly3[3].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[3]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[3].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[4]=(HBITMAP)LoadImage(NULL,"pigdownfly3[4].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[4]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[4].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[5]=(HBITMAP)LoadImage(NULL,"pigdownfly3[5].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[5]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[5].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[6]=(HBITMAP)LoadImage(NULL,"pigdownfly3[6].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[6]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[6].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[7]=(HBITMAP)LoadImage(NULL,"pigdownfly3[7].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[7]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[7].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[8]=(HBITMAP)LoadImage(NULL,"pigdownfly3[8].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[8]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[8].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[9]=(HBITMAP)LoadImage(NULL,"pigdownfly3[9].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[9]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[9].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[10]=(HBITMAP)LoadImage(NULL,"pigdownfly3[10].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[10]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[10].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[11]=(HBITMAP)LoadImage(NULL,"pigdownfly3[11].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[11]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[11].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[12]=(HBITMAP)LoadImage(NULL,"pigdownfly3[12].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[12]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[12].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[13]=(HBITMAP)LoadImage(NULL,"pigdownfly3[13].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[13]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[13].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[14]=(HBITMAP)LoadImage(NULL,"pigdownfly3[14].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[14]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[14].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[15]=(HBITMAP)LoadImage(NULL,"pigdownfly3[15].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[15]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[15].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[16]=(HBITMAP)LoadImage(NULL,"pigdownfly3[16].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[16]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[16].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	pigdownfly3[17]=(HBITMAP)LoadImage(NULL,"pigdownfly3[17].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);
	pigdownfly3_black[17]=(HBITMAP)LoadImage(NULL,"pigdownfly3_black[17].bmp",IMAGE_BITMAP,32,28,LR_LOADFROMFILE);

	restartbutton=(HBITMAP)LoadImage(NULL,"restartbutton.bmp",IMAGE_BITMAP,116,70,LR_LOADFROMFILE);
	restartbutton_down=(HBITMAP)LoadImage(NULL,"restartbutton_down.bmp",IMAGE_BITMAP,116,70,LR_LOADFROMFILE);

	button_score=(HBITMAP)LoadImage(NULL,"button_score.bmp",IMAGE_BITMAP,116,70,LR_LOADFROMFILE);
	button_score_black=(HBITMAP)LoadImage(NULL,"button_score_black.bmp",IMAGE_BITMAP,116,70,LR_LOADFROMFILE);
	button_score_down=(HBITMAP)LoadImage(NULL,"button_score_down.bmp",IMAGE_BITMAP,116,70,LR_LOADFROMFILE);


	MyPaint(hdc);
	

	return TRUE;
}


//自定义函数

void RandOfPipe1()
{
	uppipelength=(rand()%201)+120;
	downpipelength=450-uppipelength;
	if(downpipelength>320){
		downpipelength=320;
		uppipelength=130;
	}
}

void RandOfPipe2()
{
	uppipelength1=rand()%201+120;
	downpipelength1=450-uppipelength1;
	if(downpipelength1>320){
		downpipelength1=320;
		uppipelength1=130;
	}
}


void CollisionJudgment()
{
	if(pigy>600-28 )
	{
		overflag=1;
	}
	if( (tempx>=168) && (tempx<=252) )
	{
		if( (pigy<=downpipelength) || (pigy>=572-uppipelength) )
		{
			overflag=1;	
		}
	}
	if( (tempsecx>=168) && (tempsecx<=252) )
	{
		if( (pigy<=downpipelength1) || (pigy>=572-uppipelength1) )
		{
			overflag=1;	
		}
	}

}

void PrintOverPage()
{
	

	if(overflag==1)
	{
		SelectObject(bufdc,gameover_black);
		BitBlt(mdc,98,150,204,54,bufdc,0,0,SRCAND);
		SelectObject(bufdc,gameover);
		BitBlt(mdc,98,150,204,54,bufdc,0,0,SRCPAINT);//gameover标志

		SelectObject(bufdc,score_panel_black);
		BitBlt(mdc,81,230,238,126,bufdc,0,0,SRCAND);
		SelectObject(bufdc,score_panel);
		BitBlt(mdc,81,230,238,126,bufdc,0,0,SRCPAINT);//计分板

		if(pipecount<100)
		{
			if(pipecount<10)
			{
				SelectObject(bufdc,snumber_black[pipecount]);
				BitBlt(mdc,256,267,24,44,bufdc,0,0,SRCAND);
				SelectObject(bufdc,snumber[pipecount]);
				BitBlt(mdc,256,267,24,44,bufdc,0,0,SRCPAINT);
			}
			else 
			{
				SelectObject(bufdc,snumber_black[pipecount/10]);
				BitBlt(mdc,256,267,12,22,bufdc,0,0,SRCAND);
				SelectObject(bufdc,snumber[pipecount/10]);
				BitBlt(mdc,256,267,12,22,bufdc,0,0,SRCPAINT);

				SelectObject(bufdc,snumber_black[pipecount-(pipecount/10)*10]);
				BitBlt(mdc,268,267,12,22,bufdc,0,0,SRCAND);
				SelectObject(bufdc,snumber[pipecount-(pipecount/10)*10]);
				BitBlt(mdc,268,267,12,22,bufdc,0,0,SRCPAINT);
			
			}
		
		}//当前得分贴图

		if(pipecount>0 && pipecount<40)
		{
			SelectObject(bufdc,medals_black);
			BitBlt(mdc,112,274,44,44,bufdc,0,0,SRCAND);
			SelectObject(bufdc,medals[2]);
			BitBlt(mdc,112,274,44,44,bufdc,0,0,SRCPAINT);
		}
		else if(pipecount>=40 &&pipecount<60)
		{
			SelectObject(bufdc,medals_black);
			BitBlt(mdc,112,274,44,44,bufdc,0,0,SRCAND);
			SelectObject(bufdc,medals[1]);
			BitBlt(mdc,112,274,44,44,bufdc,0,0,SRCPAINT);
		}
		else if(pipecount>=60)
		{
			SelectObject(bufdc,medals_black);
			BitBlt(mdc,112,274,44,44,bufdc,0,0,SRCAND);
			SelectObject(bufdc,medals[1]);
			BitBlt(mdc,112,274,44,44,bufdc,0,0,SRCPAINT);
		}//奖牌贴图

		GetCursorPos(&point);
		SelectObject(bufdc,startbutton_black);
		BitBlt(mdc,74,382,116,70,bufdc,0,0,SRCAND);
		if(point.x>=79+inix && point.x<=184+inix && point.y>=442-30+iniy &&point.y<=512-28+iniy)
		{
			if(GetAsyncKeyState(VK_LBUTTON) & 0x8000){
			startflag=0;//贴出起始界面
			overflag=0;
			//数据初始化
			tempx=0;
			tempsecx=0;
			pipecount=0;
			pigy=200;
			ifsig=0;
			num=0;
			upflag=0;
			cycleindex++;
			}
			SelectObject(bufdc,restartbutton_down);
			BitBlt(mdc,74,382,116,70,bufdc,0,0,SRCPAINT);
		}
		else{
		SelectObject(bufdc,restartbutton);
		BitBlt(mdc,74,382,116,70,bufdc,0,0,SRCPAINT);
		}
		//重新开始按钮

		GetCursorPos(&point);
		SelectObject(bufdc,button_score_black);
		BitBlt(mdc,210,382,116,70,bufdc,0,0,SRCAND);
		if(point.x>=215+inix && point.x<=320+inix && point.y>=442-30+iniy && point.y<=512-28+iniy)
		{
			if(GetAsyncKeyState(VK_LBUTTON) & 0x8000){
			scoreflag=1;
			}//
			SelectObject(bufdc,button_score_down);
			BitBlt(mdc,210,382,116,70,bufdc,0,0,SRCPAINT);
		}
		else{
			SelectObject(bufdc,button_score);
			BitBlt(mdc,210,382,116,70,bufdc,0,0,SRCPAINT);
		}
		//排行榜按钮

		}
}

void PrintBG(HDC hdc)
{
	if(cycleindex%2==0)
		SelectObject(bufdc,bg);//游戏循环次数决定背景
	else if(cycleindex%2==1)
		SelectObject(bufdc,dark);
	BitBlt(mdc,400-x,0,x,600,bufdc,0,0,SRCCOPY);
	BitBlt(mdc,0,0,400-x,600,bufdc,x,0,SRCCOPY);//贴背景
}

void PrintStartPage()
{
	SelectObject(bufdc,title_black);
	BitBlt(mdc,120,50,178,48,bufdc,0,0,SRCAND);
	SelectObject(bufdc,title);
	BitBlt(mdc,120,50,178,48,bufdc,0,0,SRCPAINT);//题目

	SelectObject(bufdc,startbutton_black);
	BitBlt(mdc,142,350,116,70,bufdc,0,0,SRCAND);
	GetCursorPos(&point);
	if(point.x>=148+inix && point.x<=252+inix && point.y>=390+iniy && point.y<=452+iniy)
	{
		if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		{
			startflag=1;
		}
		SelectObject(bufdc,startbutton_down);
	}
	else
	{
		SelectObject(bufdc,startbutton);
	}
	BitBlt(mdc,142,350,116,70,bufdc,0,0,SRCPAINT);//开始按钮
	

	SelectObject(bufdc,startbmp_black);
	BitBlt(mdc,143,200,114,98,bufdc,0,0,SRCAND);
	SelectObject(bufdc,startbmp);
	BitBlt(mdc,143,200,114,98,bufdc,0,0,SRCPAINT);
}


void PrintPipe1()
{
	SelectObject(bufdc,pipe_down2);
	BitBlt(mdc,400-tempx,0,52,downpipelength,bufdc,0,320-downpipelength,SRCAND);
	SelectObject(bufdc,pipe_down1);
	BitBlt(mdc,400-tempx,0,52,downpipelength,bufdc,0,320-downpipelength,SRCPAINT);

	SelectObject(bufdc,pipe_up2);
	BitBlt(mdc,400-tempx,600-uppipelength,52,uppipelength,bufdc,0,0,SRCAND);
	SelectObject(bufdc,pipe_up1);
	BitBlt(mdc,400-tempx,600-uppipelength,52,uppipelength,bufdc,0,0,SRCPAINT);
}

void PrintPipe2()
{
	SelectObject(bufdc,pipe_down2);
	BitBlt(mdc,400-tempsecx,0,52,downpipelength1,bufdc,0,320-downpipelength1,SRCAND);
	SelectObject(bufdc,pipe_down1);
	BitBlt(mdc,400-tempsecx,0,52,downpipelength1,bufdc,0,320-downpipelength1,SRCPAINT);

	SelectObject(bufdc,pipe_up2);
	BitBlt(mdc,400-tempsecx,600-uppipelength1,52,uppipelength1,bufdc,0,0,SRCAND);
	SelectObject(bufdc,pipe_up1);
	BitBlt(mdc,400-tempsecx,600-uppipelength1,52,uppipelength1,bufdc,0,0,SRCPAINT);
}



void MyPaint(HDC hdc)
{
	PrintBG(hdc);//贴背景
	 if(startflag==0)
	{
		PrintStartPage();//开始界面
	}

	else
	{

	PrintPipe1();

	if(overflag==0)
	tempx += xspeed;
	
	if(pipecount<100)
	{
	if(pipecount<10)
			{
				SelectObject(bufdc,number_black[pipecount]);
				BitBlt(mdc,120,50,24,44,bufdc,0,0,SRCAND);
				SelectObject(bufdc,number[pipecount]);
				BitBlt(mdc,120,50,24,44,bufdc,0,0,SRCPAINT);
			}
			else 
			{
				SelectObject(bufdc,number_black[pipecount/10]);
				BitBlt(mdc,100,50,24,44,bufdc,0,0,SRCAND);
				SelectObject(bufdc,number[pipecount/10]);
				BitBlt(mdc,100,50,24,44,bufdc,0,0,SRCPAINT);

				SelectObject(bufdc,number_black[pipecount-(pipecount/10)*10]);
				BitBlt(mdc,124,50,24,44,bufdc,0,0,SRCAND);
				SelectObject(bufdc,number[pipecount-(pipecount/10)*10]);
				BitBlt(mdc,124,50,24,44,bufdc,0,0,SRCPAINT);
			}
	}
	//计分数字

	if(tempx==200)
	{
		ifsig=1;//第二根管子产生标志
	}
	if(tempx==250 && overflag==0)
	{
		pipecount++;//管子计数
	}

	if(ifsig==1)
	{
		PrintPipe2();

	if(overflag==0)
	tempsecx += xspeed;
	
	if(pipecount<100)
	{
			if(pipecount<10)
			{
				SelectObject(bufdc,number_black[pipecount]);
				BitBlt(mdc,120,50,24,44,bufdc,0,0,SRCAND);
				SelectObject(bufdc,number[pipecount]);
				BitBlt(mdc,120,50,24,44,bufdc,0,0,SRCPAINT);
			}
			else 
			{
				SelectObject(bufdc,number_black[pipecount/10]);
				BitBlt(mdc,100,50,24,44,bufdc,0,0,SRCAND);
				SelectObject(bufdc,number[pipecount/10]);
				BitBlt(mdc,100,50,24,44,bufdc,0,0,SRCPAINT);

				SelectObject(bufdc,number_black[pipecount-(pipecount/10)*10]);
				BitBlt(mdc,124,50,24,44,bufdc,0,0,SRCAND);
				SelectObject(bufdc,number[pipecount-(pipecount/10)*10]);
				BitBlt(mdc,124,50,24,44,bufdc,0,0,SRCPAINT);
			
			}
		
	}//计分数据


	
	if(tempsecx==250&&overflag==0)
		pipecount++;//管子计数

	if(tempsecx>=452){
		RandOfPipe2();
		tempsecx=0;
	}

	}
	

	if(tempx>=452){
		RandOfPipe1();
		tempx=0;
	}

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		upflag=1;
	}
	
	if(GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		upflag=1;
	}//无延迟上升操作

	if(upflag==0)
	{
		pigy += 8;
		pigypre=pigy;
	}
	else if(upflag==1)
	{
		pigy -= 10;
		if(pigypre-pigy>=60)
		{
			upflag=0;
		}
	}
	//飞猪上升下降操作


	if(overflag==0 && upflag==1)
	{
	SelectObject(bufdc,pigup_black[num]);
	BitBlt(mdc,200,pigy,32,28,bufdc,0,0,SRCAND);
	SelectObject(bufdc,pigup[num]);
	BitBlt(mdc,200,pigy,32,28,bufdc,0,0,SRCPAINT);

	flydownimage=0;

	num++;
	if(num==20) num=0;
	}

	else if(overflag==0 && upflag==0)
	{

	if(flydownimage!=17)
	{
	if(num>=0 && num<7)
	{
	SelectObject(bufdc,pigdownfly1_black[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCAND);
	SelectObject(bufdc,pigdownfly1[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCPAINT);
	if(flydownimage<17)
	flydownimage+=1;

	}
	else if(num>=7 && num<14)
	{
	SelectObject(bufdc,pigdownfly2_black[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCAND);
	SelectObject(bufdc,pigdownfly2[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCPAINT);
	if(flydownimage<17)
	flydownimage+=1;
	}
	else if(num>=14 && num<21)
	{
	SelectObject(bufdc,pigdownfly3_black[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCAND);
	SelectObject(bufdc,pigdownfly3[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCPAINT);
	if(flydownimage<17)
	flydownimage+=1;
	}

	num++;
	if(num==20) num=0;
	}

	else if(flydownimage==17)
	{
		if(num>=0 && num<7)
	{
	SelectObject(bufdc,pigdownfly1_black[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCAND);
	SelectObject(bufdc,pigdownfly1[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCPAINT);
	}
	else if(num>=7 && num<14)
	{
	SelectObject(bufdc,pigdownfly2_black[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCAND);
	SelectObject(bufdc,pigdownfly2[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCPAINT);
	}
	else if(num>=14 && num<21)
	{
	SelectObject(bufdc,pigdownfly3_black[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCAND);
	SelectObject(bufdc,pigdownfly3[flydownimage]);
	BitBlt(mdc,200,pigy-flydownimage/2,32,28,bufdc,0,0,SRCPAINT);
	}
	}
	}

	else if(overflag==1)
	{
		if(pigy>566)
		{
			pigy=566;
			SelectObject(bufdc,pig1black);
			BitBlt(mdc,200,576,34,24,bufdc,0,0,SRCAND);
			SelectObject(bufdc,pig1);
			BitBlt(mdc,200,576,34,24,bufdc,0,0,SRCPAINT);
		}//死亡后落地动作
		else
		{
		SelectObject(bufdc,pigdown_black);
		BitBlt(mdc,200,pigy,24,34,bufdc,0,0,SRCAND);
		SelectObject(bufdc,pigdown);
		BitBlt(mdc,200,pigy,24,34,bufdc,0,0,SRCPAINT);
		}
		pigy +=35;
//垂直下降动作
	}

	CollisionJudgment();//碰撞判断
	
	PrintOverPage();//结束界面
	
	}//else

	
	BitBlt(hdc,0,0,400,600,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();

	if(overflag==0)
	{
	x += xspeed;
	if(x>=400)
		x = 0;
	}

}




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:				
			DeleteDC(mdc);
			DeleteDC(bufdc);
			DeleteObject(bg);
			ReleaseDC(hWnd,hdc);
			PostQuitMessage(0);
			break;

/*		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_SPACE:
			if(startflag==1)
				upflag=1;
				break;
			
			default:break;
			}
		case WM_LBUTTONDOWN:
			switch(wParam)
			{
			case VK_LBUTTON:
			if(startflag==1)  
			upflag=1;
			break;

			default:break;
			}
	*/		
		default:							
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}





