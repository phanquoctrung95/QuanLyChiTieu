#include "stdafx.h"
#include"QuanLyChiTieu.h"
#include"ComboBox.h"


HWND CreateComboBox(HWND hwndParent){
	RECT rect;
	GetClientRect(hwndParent, &rect);
	// Create the Combobox
	//
	// Uses the CreateWindow function to create a child window of 
	// the application window. The WC_COMBOBOX window style specifies  
	// that it is a combobox.

	int xpos = 50;            // Horizontal position of the window.
	int ypos = 50;            // Vertical position of the window.
	int nwidth = 200;          // Width of the window
	int nheight = 200;         // Height of the window


	HWND hWndComboBox = CreateWindow(WC_COMBOBOX, TEXT(""),
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
		rect.left + 100,
		rect.top + 40,
		200,
		rect.bottom - rect.top - 400,
		hwndParent, NULL, HINST_THISCOMPONENT,
		NULL);
	InitItemComboBox(hWndComboBox);
	return hWndComboBox;
}
BOOL InitItemComboBox(HWND hWndComboBox){
	int size = 6;
	TCHAR itemlistCBB[6][100] = { TEXT("Ăn uống"), TEXT("Di chuyển "),
		TEXT("Nhà cửa "), TEXT("Xe cộ "),
		TEXT("Nhu yếu phẩm "), TEXT("Dịch vụ")
	};
	TCHAR A[16];
	int  k = 0;

	memset(&A, 0, sizeof(A));
	for (k = 0; k <= 5; k += 1)
	{
		wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)itemlistCBB[k]);

		// Add string to combobox.
		SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
	}

	// Send the CB_SETCURSEL message to display an initial item 
	//  in the selection field  
	SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);
	return true;
}
