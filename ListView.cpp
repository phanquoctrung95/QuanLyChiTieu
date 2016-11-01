#include "stdafx.h"
#include"QuanLyChiTieu.h"
#include"ListView.h"
// global array of houses
struct HOUSEINFO {
	char *x;
	char *y;
	int z;
	int t;
	int m;
};
HOUSEINFO rgHouseInfo[] =
{
	{ "100 Main Street", "Redmond", 175000, 3, 2 },
	{ "523 Pine Lake Road", "Redmond", 125000, 4, 2 },
	{ "1212 112th Place SE", "Redmond", 200000, 4, 3 },
	{ "22 Lake Washington Blvd", "Bellevue", 2500000, 4, 4 },
	{ "33542 116th Ave. NE", "Bellevue", 180000, 3, 2 },
	{ "64134 Nicholas Lane", "Bellevue", 250000, 4, 3 },
	{ "33 Queen Anne Hill", "Seattle", 350000, 3, 2 },
	{ "555 SE Fifth St", "Seattle", 140000, 3, 2 },
	{ "446 Mariners Way", "Seattle", 225000, 4, 3 }
};

// CreateListView: Creates a list-view control in report view.
// Returns the handle to the new control
// TO DO:  The calling procedure should determine whether the handle is NULL, in case 
// of an error in creation.
//
// HINST hInst: The global handle to the applicadtion instance.
// HWND  hWndParent: The handle to the control's parent window. 
//

HWND CreateListView(HWND hwndParent)
{
	//INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	//icex.dwICC = ICC_LISTVIEW_CLASSES;
	//InitCommonControlsEx(&icex);
	InitCommonControls();
	RECT rect;                       // The parent window's client area.

	GetClientRect(hwndParent, &rect);
	// Create the list-view window in report view with label editing enabled.
	HWND list = CreateWindowExW(0, (LPCWSTR)WC_LISTVIEWW,NULL,
		// WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_SHOWSELALWAYS | LVS_REPORT|LVS_AUTOARRANGE|LVM_SCROLL,
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT |
		LVS_EDITLABELS | WS_EX_CLIENTEDGE,
		rect.left + 10,
		rect.top + 180,
		500,
		rect.bottom - rect.top - 190,
		hwndParent,
		NULL,
		NULL,
		NULL);
	
	// add colunms to list view
	InitListViewColumns(list);
	// 
	return (list);
}


// SetView: Sets a list-view's window style to change the view.
// hWndListView: A handle to the list-view control. 
// dwView:       A value specifying the new view style.
//
VOID SetView(HWND hWndListView, DWORD dwView)
{
	// Retrieve the current window style. 
	DWORD dwStyle = GetWindowLong(hWndListView, GWL_STYLE);

	// Set the window style only if the view bits changed.
	if ((dwStyle & LVS_TYPEMASK) != dwView)
	{
		SetWindowLong(hWndListView,
			GWL_STYLE,
			(dwStyle & ~LVS_TYPEMASK) | dwView);
	}               // Logical OR'ing of dwView with the result of 
}                   // a bitwise AND between dwStyle and 
// the Unary complenent of LVS_TYPEMASK.

// InitListViewColumns: Adds columns to a list-view control.
// hWndListView:        Handle to the list-view control. 
// Returns TRUE if successful, and FALSE otherwise. 
BOOL InitListViewColumns(HWND list)
{

	LVCOLUMN lvc2;
	lvc2.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc2.iSubItem = 0;
	lvc2.pszText = _T("Loại Chi Tiêu");
	lvc2.cx = 100;
	lvc2.fmt = LVCFMT_LEFT;
	ListView_InsertColumn(list, 0, &lvc2);

	LVCOLUMN lvc3;
	lvc3.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc3.iSubItem = 0;
	lvc3.pszText = _T("Nội dung chi tiêu");
	lvc3.cx = 200;
	lvc3.fmt = LVCFMT_LEFT;
	ListView_InsertColumn(list, 1, &lvc3);

	LVCOLUMN lvc1;
	lvc1.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc1.iSubItem = 0;
	lvc1.pszText = _T("Số tiền");
	lvc1.cx = 150;
	lvc1.fmt = LVCFMT_LEFT;
	ListView_InsertColumn(list, 2, &lvc1);
	return true;
}

// InsertListViewItems: Inserts items into a list view. 
// hWndListView:        Handle to the list-view control.
// cItems:              Number of items to insert.
// Returns TRUE if successful, and FALSE otherwise.
BOOL InsertListViewItems(HWND hWndListView, int pos)
{
	LVITEM lvI;
	// Initialize LVITEM members that are common to all items.
	lvI.pszText = LPSTR_TEXTCALLBACK; // Sends an LVN_GETDISPINFO message.
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvI.stateMask = 0;
	lvI.iSubItem = 0;
	lvI.state = 0;
	// Initialize LVITEM members that are different for each item.
	lvI.iItem = pos;
	lvI.iImage = pos;
	
	// Insert items into the list.
	if (ListView_InsertItem(hWndListView, &lvI) == -1)
		return FALSE;
	return TRUE;
}

BOOL InsertListViewItemsArray(HWND hWndListView, int cItems)
{
	LVITEM lvI;

	// Initialize LVITEM members that are common to all items.
	lvI.pszText = LPSTR_TEXTCALLBACK; // Sends an LVN_GETDISPINFO message.
	lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	lvI.stateMask = 0;
	lvI.iSubItem = 0;
	lvI.state = 0;

		// Initialize LVITEM members that are different for each item.
	for (int index = 0; index < cItems; index++)
	{
		
		lvI.iItem = index;
		lvI.iImage = index;

		// Insert items into the list.
		if (ListView_InsertItem(hWndListView, &lvI) == -1)
			return FALSE;
	}

	return TRUE;
}
