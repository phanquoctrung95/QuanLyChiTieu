// QuanLyChiTieu.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lib.h"
#include"QuanLyChiTieu.h"
#include"ListView.h"
#include"ComboBox.h"
#include"ChiTieu.h"
#define MAX_LOADSTRING 100
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void OnDestroy(HWND hwnd);
void OnPaint(HWND hWnd);
void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
LRESULT HandleWM_NOTIFY(HWND hWnd, WPARAM wParam, NMHDR * lParam);
vector<ChiTieu> data;
WCHAR *bufferND = new WCHAR[256];
WCHAR *bufferST = new WCHAR[256];
WCHAR *bufferLoai=new WCHAR[256];
bool isAvailable = false;
void OnResizing(HWND hWnd);
bool isNumber(WCHAR* buffer, int len);// kiem tra co phai la so
int pos = 0;// vi tri dong tiep theo trong listview
HWND txtNoiDung;
HWND txtSoTien;
HWND hWndLV;
HWND hWndCBB;
void resetData();
// Write file in UTF-8
std::wofstream wof;

// Read file in UTF-8
std::wifstream wif;

// luu du lieu doc tu file
std::wstringstream wss;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_QUANLYCHITIEU, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QUANLYCHITIEU));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra = sizeof(LONG_PTR);
	wcex.hInstance = hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QUANLYCHITIEU));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_QUANLYCHITIEU);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 900, 500, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);		
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_NOTIFY, HandleWM_NOTIFY);
		//HANDLE_MSG(hWnd, WM_SIZING, OnResizing(hWnd));
	//case WM_NOTIFY:
	//	{
	//		HandleWM_NOTIFY(lParam);
	//	}
	//	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct){
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	RECT rect;
	GetClientRect(hWnd, &rect);
	
	// Lấy font hệ thống
	HFONT hFont = GetSystemFont();
	// tao listview
	hWndLV = CreateListView(hWnd);
	SendMessage(hWndLV, WM_SETFONT | WM_SIZE, WPARAM(hFont), TRUE);
	// tao group box
	HWND hControl = CreateWindowEx(NULL, L"BUTTON", L"Thêm mục chi tiêu",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_GROUPBOX ,
		rect.left + 10,
		rect.top + 10,
		500,
		rect.bottom - rect.top - 300,
		hWnd,
		(HMENU)(-1),
		0, NULL);
	SendMessage(hControl, WM_SETFONT, WPARAM(hFont), TRUE);
	HWND hwnd = CreateWindowEx(0, L"STATIC", L"Loại chi tiêu: ",
		WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER,
		rect.left + 15,
		rect.top + 40,
		80,
		20,
		hWnd, NULL,
		hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	// tao combo box
	hWndCBB = CreateComboBox(hWnd);
	SendMessage(hWndCBB, WM_SETFONT, WPARAM(hFont), TRUE);
	//tao text box
	hwnd = CreateWindowEx(0, L"STATIC", L"Nội dung: ", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER,
		rect.left + 15,
		rect.top + 70,
		80,
		20,
		hWnd,
		NULL,
		hInst,
		NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txtNoiDung = CreateWindowEx(0, L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | SS_LEFT|WS_BORDER,
		rect.left + 100,
		rect.top + 70,
		200,
		20,
		hWnd,
		NULL,
		hInst,
		NULL);
	SendMessage(txtNoiDung, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Số tiền: ", WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER,
		rect.left + 15,
		rect.top + 100,
		80,
		20,
		hWnd,
		HMENU(ID_TXT_NOIDUNG),
		hInst,
		NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txtSoTien = CreateWindowEx(0, L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER,
		rect.left + 100,
		rect.top + 100,
		200,
		20,
		hWnd,
		HMENU(ID_TXT_SOTIEN),
		hInst,
		NULL);
	SendMessage(txtSoTien, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"BUTTON", L"Thêm",
		WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER,
		rect.left + 330,
		rect.top + 40,
		150,
		80,
		hWnd,
		HMENU(ID_BTN_THEM),
		hInst,
		NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	wof.imbue(locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	wif.imbue(locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	// kiem tra file data 
	wif.open("data.txt");
	
	if (!wif.bad()){
		wss << wif.rdbuf();
		
		if (!wss.str().empty())
		{
			while (!wss.eof())
			{
				ChiTieu tmp2;
				isAvailable = true;
				WCHAR bffLCT[256];// Loai chi tieu
				WCHAR bffNDCT[256];// noi dung chi tieu
				WCHAR bffST[256];// so tien
				//
				wss.getline(bufferLoai, 255);
				wss.getline(bufferND, 255);
				wss.getline(bufferST, 255);
				//
				tmp2.setLoai(bufferLoai);
				tmp2.setNoiDung(bufferND);
				tmp2.setSoTien(bufferST);
				//
				data.push_back(tmp2);
				pos++;
			}
			InsertListViewItemsArray(hWndLV, pos);
		}
		//		
		isAvailable = false;
	}

	return true;
}

void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	int size;
	int tienLuong = 0;
	switch (id)
	{
	case ID_RESETDATA:
	{
						 wof.clear();
						 //data.clear();
						data.erase(data.begin(),data.end());
						pos = 0;
	}
		break;
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case ID_BTN_THEM:
	{
						 isAvailable = false;
						 int sizeNoiDung = 0;
						 int sizeSoTien = 0;
						 sizeNoiDung = GetWindowTextLength(txtNoiDung);
						 sizeSoTien = GetWindowTextLength(txtSoTien);
						 if (sizeNoiDung > 0 && sizeSoTien > 0)
						 {
							
							GetWindowText(txtNoiDung, bufferND, sizeNoiDung+1);
							GetWindowText(txtSoTien, bufferST, sizeSoTien+1);
							
							if (isNumber(bufferST, sizeSoTien)==true)
							{ 
								 ChiTieu tmp3;
								 int sotien = _wtoi(bufferST);
								 //
								 ComboBox_GetLBText(hWndCBB, ComboBox_GetCurSel(hWndCBB), bufferLoai);
								 tmp3.setLoai(bufferLoai);
								 tmp3.setNoiDung(bufferND);
								 tmp3.setSoTien(bufferST);
								 //
								 data.push_back(tmp3);
								 //
								 InsertListViewItems(hWndLV, pos);// insert item
								 pos++;
								 SetWindowText(txtNoiDung, L"");
								 SetWindowText(txtSoTien, L"");
							}
							else
							{								 
								 MessageBox(hWnd, L"Nhập lại số tiền!", L"Lỗi", 0);
								 SetWindowText(txtSoTien, L"");
							}
						
						 }
	}
		break;

	default:
		break;
	}

}

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rc;
	GetClientRect(hWnd, &rc);
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	wif.close();
	// Write file in UTF-8
	wof.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	wof.open(L"data.txt");
	int size = data.size();
	if (size > 0)
	{
		for (int i = 0; i <= size - 2; ++i)
		{
			wof << data[i].getLoai() << endl;
			wof << data[i].getNoiDung() << endl;
			wof << data[i].getSoTien() << endl;
		}
		wof << data[size - 1].getLoai() << endl;
		wof << data[size - 1].getNoiDung() << endl;
		wof << data[size - 1].getSoTien();
	}
	wof.close();
	PostQuitMessage(0);
}

HFONT GetSystemFont(){
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);
	return hFont;
}
/*
void OnResizing(HWND hWnd){
	RECT rect;
	GetClientRect(hWnd, &rect);
	SetWindowPos(hwndLV,
		0,
		0,
		0,
		rect.right,
		rect.bottom,
		SWP_NOZORDER | SWP_NOACTIVATE);
}
*/
bool isNumber(WCHAR* buffer, int len){
	for (int i = 0; i < len; ++i)
	{
		if (buffer[i] < 48 || buffer[i] > 57)
			return false;
	}	
	return true;
}

// HandleWM_NOTIFY - Handles the LVN_GETDISPINFO notification code that is 
//         sent in a WM_NOTIFY to the list view parent window. The function 
//        provides display strings for list view items and subitems.
//
// lParam - The LPARAM parameter passed with the WM_NOTIFY message.
// rgPetInfo - A global array of structures, defined as follows:


LRESULT HandleWM_NOTIFY(HWND hWnd, WPARAM wParam, NMHDR *lParam)
{
	
	NMLVDISPINFO* plvdi;
	switch (((LPNMHDR)lParam)->code)
	{
	case LVN_GETDISPINFO:
		plvdi = (NMLVDISPINFO*)lParam;
		switch (plvdi->item.iSubItem)
		{
		case 0:		
			plvdi->item.pszText = data[plvdi->item.iItem].ChiTieu::getLoai();
			break;
		case 1:
			plvdi->item.pszText = data[plvdi->item.iItem].ChiTieu::getNoiDung();
			break;
		case 2:
			plvdi->item.pszText = data[plvdi->item.iItem].ChiTieu::getSoTien();
			break;
		default:
			break;
		}

		break;

	}
	// NOTE: In addition to setting pszText to point to the item text, you could 
	// copy the item text into pszText using StringCchCopy. For example:
	//
	// StringCchCopy(plvdi->item.pszText, 
	//                         plvdi->item.cchTextMax, 
	//                         rgPetInfo[plvdi->item.iItem].szKind);

	return 0;
}

void resetData(){

}