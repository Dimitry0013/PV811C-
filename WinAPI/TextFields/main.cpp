#include<Windows.h>
#include"resource.h"

HWND hEdit1;
HWND hEdit2;

CHAR str1[] = "Hello guys ;-)";
CHAR str2[] = { 0 };
CONST UINT MSG_SIZE = 256;
CONST CHAR sz_invitation[MSG_SIZE] = "Type your name";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
		hEdit2 = GetDlgItem(hwnd, IDC_EDIT2);

		//SendMessage(hEdit1, WM_SETTEXT, 0, (LPARAM)str1);
		SetWindowText(hEdit1, sz_invitation);

		SetFocus(GetDlgItem(hwnd, IDC_COPY));
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT1:
		{
			CHAR buffer[256] = {};
			GetDlgItemText(hwnd, IDC_EDIT1, buffer, 256);
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				if (strcmp(buffer, sz_invitation) == 0)SetDlgItemText(hwnd, IDC_EDIT1, "");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				if (strcmp(buffer, "") == 0)
				{
					SetDlgItemText(hwnd, IDC_EDIT1, sz_invitation);
				}
			}
		}
		break;
		case IDC_COPY:
			/*SendMessage(hEdit1, WM_GETTEXT, 255, (LPARAM)str2);
			SendMessage(hEdit2, WM_SETTEXT, 0, (LPARAM)str2);*/
			GetWindowText(hEdit1, str2, 255);
			SetWindowText(hEdit2, str2);
			break;
		case IDOK:
		{
			CHAR msg[MSG_SIZE] = "Hello ";
			CHAR buffer[MSG_SIZE]{};
			GetDlgItemText(hwnd, IDC_EDIT1, buffer, MSG_SIZE);
			strcat_s(msg, MSG_SIZE, buffer);
			strcat_s(msg, MSG_SIZE, "!");
			MessageBox(hwnd, msg, "Hi", MB_OK);
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}