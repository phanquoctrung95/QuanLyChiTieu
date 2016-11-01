#include"Lib.h"
#define MAX_ITEMLEN 256
HWND CreateListView(HWND hwndParent);
VOID SetView(HWND hWndListView, DWORD dwView);
BOOL InitListViewColumns(HWND list);
BOOL InsertListViewItems(HWND hWndListView, int cItems);
BOOL InsertListViewItemsArray(HWND hWndListView, int cItems);