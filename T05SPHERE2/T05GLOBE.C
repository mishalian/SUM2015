/*T05SPHERE
*MC6 spr11
*05.06.2015
*Build a sphere in a three-dimentional space.
*/
#include "globe.h"

#define WND_CLASS_NAME "My window class"


LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg,
<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
	WPARAM wParam, LPARAM lParam); /* Ð¤ÑƒÐ½ÐºÑ†Ð¸Ñ Ð¾Ð±Ñ€Ð°Ð±Ð¾Ñ‚ÐºÐ¸. */

/* Ð“Ð»Ð°Ð²Ð½Ð°Ñ Ñ„ÑƒÐ½ÐºÑ†Ð¸Ñ Ð¿Ñ€Ð¾Ð³Ñ€Ð°Ð¼Ð¼Ñ‹.
*   - Ð´ÐµÑÐºÑ€Ð¸Ð¿Ñ‚Ð¾Ñ€ ÑÐºÐ·ÐµÐ¼Ð¿Ð»ÑÑ€Ð° Ð¿Ñ€Ð¸Ð»Ð¾Ð¶ÐµÐ½Ð¸Ñ:
*       HINSTANCE hInstance;
*   - Ð´ÐµÑÐºÑ€Ð¸Ð¿Ñ‚Ð¾Ñ€ Ð¿Ñ€ÐµÐ´Ñ‹Ð´ÑƒÑ‰ÐµÐ³Ð¾ ÑÐºÐ·ÐµÐ¼Ð¿Ð»ÑÑ€Ð° Ð¿Ñ€Ð¸Ð»Ð¾Ð¶ÐµÐ½Ð¸Ñ
*     (Ð½Ðµ Ð¸ÑÐ¿Ð¾Ð»ÑŒÐ·ÑƒÐµÑ‚ÑÑ Ð¸ Ð´Ð¾Ð»Ð¶Ð½Ð¾ Ð±Ñ‹Ñ‚ÑŒ NULL):
*       HINSTANCE hPrevInstance;
*   - ÐºÐ¾Ð¼Ð°Ð½Ð´Ð½Ð°Ñ ÑÑ‚Ñ€Ð¾ÐºÐ°:
*       CHAR *CmdLine;
* Ð’ÐžÐ—Ð’Ð ÐÐ©ÐÐ•ÐœÐžÐ• Ð—ÐÐÐ§Ð•ÐÐ˜Ð•:
*   (INT) ÐºÐ¾Ð´ Ð²Ð¾Ð·Ð²Ñ€Ð°Ñ‚Ð° Ð² Ð¾Ð¿ÐµÑ€Ð°Ñ†Ð¸Ð¾Ð½Ð½ÑƒÑŽ ÑÐ¸ÑÑ‚ÐµÐ¼Ñƒ.
*   0 - Ð¿Ñ€Ð¸ ÑƒÑÐ¿ÐµÑ…Ðµ.
=======
	WPARAM wParam, LPARAM lParam); /* Ôóíêöèÿ îáðàáîòêè. */

/* Ãëàâíàÿ ôóíêöèÿ ïðîãðàììû.
*   - äåñêðèïòîð ýêçåìïëÿðà ïðèëîæåíèÿ:
*       HINSTANCE hInstance;
*   - äåñêðèïòîð ïðåäûäóùåãî ýêçåìïëÿðà ïðèëîæåíèÿ
*     (íå èñïîëüçóåòñÿ è äîëæíî áûòü NULL):
*       HINSTANCE hPrevInstance;
*   - êîìàíäíàÿ ñòðîêà:
*       CHAR *CmdLine;
* ÂÎÇÂÐÀÙÀÅÌÎÅ ÇÍÀ×ÅÍÈÅ:
*   (INT) êîä âîçâðàòà â îïåðàöèîííóþ ñèñòåìó.
*   0 - ïðè óñïåõå.
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
*/
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	CHAR *CmdLine, INT ShowCmd)
{
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;

<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
	wc.style = CS_VREDRAW | CS_HREDRAW; /* Ð¡Ñ‚Ð¸Ð»ÑŒ Ð¾ÐºÐ½Ð° */
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = LoadCursor(NULL, IDC_HAND); /* Ð—Ð°Ð³Ñ€ÑƒÐ·ÐºÐ° ÐºÑƒÑ€ÑÐ¾Ñ€Ð° (ÑÐ¸ÑÑ‚ÐµÐ¼Ð½Ð¾Ð³Ð¾) */
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK); /* Ð—Ð°Ð³Ñ€ÑƒÐ·ÐºÐ° Ð¿Ð¸ÐºÑ‚Ð¾Ð³Ñ€Ð°Ð¼Ð¼Ñ‹ (ÑÐ¸ÑÑ‚ÐµÐ¼Ð½Ð¾Ð¹) */
	wc.hInstance = hInstance; /* Ð”ÐµÑÐºÑ€Ð¸Ð¿Ñ‚Ð¾Ñ€ Ð¿Ñ€Ð¸Ð»Ð¾Ð¶ÐµÐ½Ð¸Ñ, Ñ€ÐµÐ³Ð¸ÑÑ‚Ñ€Ð¸Ñ€ÑƒÑŽÑ‰ÐµÐ³Ð¾ ÐºÐ»Ð°ÑÑ */
	wc.lpszMenuName = NULL; /* Ð˜Ð¼Ñ Ñ€ÐµÑÑƒÑ€ÑÐ° Ð¼ÐµÐ½ÑŽ */
	wc.lpfnWndProc = MyWindowFunc; /* Ð£ÐºÐ°Ð·Ð°Ñ‚ÐµÐ»ÑŒ Ð½Ð° Ñ„ÑƒÐ½ÐºÑ†Ð¸ÑŽ Ð¾Ð±Ñ€Ð°Ð±Ð¾Ñ‚ÐºÐ¸ */
	wc.lpszClassName = WND_CLASS_NAME;


	/* Ð ÐµÐ³Ð¸ÑÑ‚Ñ€Ð°Ñ†Ð¸Ñ ÐºÐ»Ð°ÑÑÐ° Ð² ÑÐ¸ÑÑ‚ÐµÐ¼Ðµ */
=======
	wc.style = CS_VREDRAW | CS_HREDRAW; /* Ñòèëü îêíà */
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = LoadCursor(NULL, IDC_HAND); /* Çàãðóçêà êóðñîðà (ñèñòåìíîãî) */
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK); /* Çàãðóçêà ïèêòîãðàììû (ñèñòåìíîé) */
	wc.hInstance = hInstance; /* Äåñêðèïòîð ïðèëîæåíèÿ, ðåãèñòðèðóþùåãî êëàññ */
	wc.lpszMenuName = NULL; /* Èìÿ ðåñóðñà ìåíþ */
	wc.lpfnWndProc = MyWindowFunc; /* Óêàçàòåëü íà ôóíêöèþ îáðàáîòêè */
	wc.lpszClassName = WND_CLASS_NAME;


	/* Ðåãèñòðàöèÿ êëàññà â ñèñòåìå */
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
		return 0;
	}

<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
	/* Ð¡Ð¾Ð·Ð´Ð°Ð½Ð¸Ðµ Ð¾ÐºÐ½Ð° */
	hWnd =
		CreateWindow(WND_CLASS_NAME,    /* Ð˜Ð¼Ñ ÐºÐ»Ð°ÑÑÐ° Ð¾ÐºÐ½Ð° */
		"3D Sphere",                      /* Ð—Ð°Ð³Ð¾Ð»Ð¾Ð²Ð¾Ðº Ð¾ÐºÐ½Ð° */
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,          /* Ð¡Ñ‚Ð¸Ð»Ð¸ Ð¾ÐºÐ½Ð° - Ð¾ÐºÐ½Ð¾ Ð¾Ð±Ñ‰ÐµÐ³Ð¾ Ð²Ð¸Ð´Ð° */
		689 - 350, 370 - 350, /* ÐŸÐ¾Ð·Ð¸Ñ†Ð¸Ñ Ð¾ÐºÐ½Ð° (x, y) - Ð¿Ð¾ ÑƒÐ¼Ð¾Ð»Ñ‡Ð°Ð½Ð¸ÑŽ */
		700, 700, /* Ð Ð°Ð·Ð¼ÐµÑ€Ñ‹ Ð¾ÐºÐ½Ð° (w, h) - Ð¿Ð¾ ÑƒÐ¼Ð¾Ð»Ñ‡Ð°Ð½Ð¸ÑŽ */
		NULL,                         /* Ð”ÐµÑÐºÑ€Ð¸Ð¿Ñ‚Ð¾Ñ€ Ñ€Ð¾Ð´Ð¸Ñ‚ÐµÐ»ÑŒÑÐºÐ¾Ð³Ð¾ Ð¾ÐºÐ½Ð° */
		NULL,                         /* Ð”ÐµÑÐºÑ€Ð¸Ð¿Ñ‚Ð¾Ñ€ Ð·Ð°Ð³Ñ€ÑƒÐ¶ÐµÐ½Ð½Ð¾Ð³Ð¾ Ð¼ÐµÐ½ÑŽ */
		hInstance,                    /* Ð”ÐµÑÐºÑ€Ð¸Ð¿Ñ‚Ð¾Ñ€ Ð¿Ñ€Ð¸Ð»Ð¾Ð¶ÐµÐ½Ð¸Ñ */
		NULL);                        /* Ð£ÐºÐ°Ð·Ð°Ñ‚ÐµÐ»ÑŒ Ð½Ð° Ð´Ð¾Ð¿Ð¾Ð»Ð½Ð¸Ñ‚ÐµÐ»ÑŒÐ½Ñ‹Ðµ Ð¿Ð°Ñ€Ð°Ð¼ÐµÑ‚Ñ€Ñ‹ */
=======
	/* Ñîçäàíèå îêíà */
	hWnd =
		CreateWindow(WND_CLASS_NAME,    /* Èìÿ êëàññà îêíà */
		"3D Sphere",                      /* Çàãîëîâîê îêíà */
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,          /* Ñòèëè îêíà - îêíî îáùåãî âèäà */
		689 - 350, 370 - 350, /* Ïîçèöèÿ îêíà (x, y) - ïî óìîë÷àíèþ */
		700, 700, /* Ðàçìåðû îêíà (w, h) - ïî óìîë÷àíèþ */
		NULL,                         /* Äåñêðèïòîð ðîäèòåëüñêîãî îêíà */
		NULL,                         /* Äåñêðèïòîð çàãðóæåííîãî ìåíþ */
		hInstance,                    /* Äåñêðèïòîð ïðèëîæåíèÿ */
		NULL);                        /* Óêàçàòåëü íà äîïîëíèòåëüíûå ïàðàìåòðû */
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b

	ShowWindow(hWnd, ShowCmd);
	UpdateWindow(hWnd);

<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
	/* Ð—Ð°Ð¿ÑƒÑÐº Ñ†Ð¸ÐºÐ»Ð° ÑÐ¾Ð¾Ð±Ñ‰ÐµÐ½Ð¸Ð¹ Ð¾ÐºÐ½Ð° */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		/* ÐžÐ±Ñ€Ð°Ð±Ð¾Ñ‚ÐºÐ° ÑÐ¾Ð¾Ð±Ñ‰ÐµÐ½Ð¸Ð¹ Ð¾Ñ‚ ÐºÐ»Ð°Ð²Ð¸Ð°Ñ‚ÑƒÑ€Ñ‹ */
		TranslateMessage(&msg);
		/* ÐŸÐµÑ€ÐµÐ´Ð°Ñ‡Ð° ÑÐ¾Ð¾Ð±Ñ‰ÐµÐ½Ð¸Ð¹ Ð² Ñ„ÑƒÐ½ÐºÑ†Ð¸ÑŽ Ð¾ÐºÐ½Ð° */
=======
	/* Çàïóñê öèêëà ñîîáùåíèé îêíà */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		/* Îáðàáîòêà ñîîáùåíèé îò êëàâèàòóðû */
		TranslateMessage(&msg);
		/* Ïåðåäà÷à ñîîáùåíèé â ôóíêöèþ îêíà */
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
/* Ð¤ÑƒÐ½ÐºÑ†Ð¸Ñ Ð¾Ð±Ñ€Ð°Ð±Ð¾Ñ‚ÐºÐ¸ ÑÐ¾Ð¾Ð±Ñ‰ÐµÐ½Ð¸Ñ Ð¾ÐºÐ½Ð°.
* ÐÐ Ð“Ð£ÐœÐ•ÐÐ¢Ð«:
*   - Ð´ÐµÑÐºÑ€Ð¸Ð¿Ñ‚Ð¾Ñ€ Ð¾ÐºÐ½Ð°:
*       HWND hWnd;
*   - Ð½Ð¾Ð¼ÐµÑ€ ÑÐ¾Ð¾Ð±Ñ‰ÐµÐ½Ð¸Ñ (ÑÐ¼. WM_***):
*       UINT Msg;
*   - Ð¿Ð°Ñ€Ð°Ð¼ÐµÑ‚Ñ€ ÑÐ¾Ð¾Ð±ÑˆÐµÐ½Ð¸Ñ ('word parameter'):
*       WPARAM wParam;
*   - Ð¿Ð°Ñ€Ð°Ð¼ÐµÑ‚Ñ€ ÑÐ¾Ð¾Ð±ÑˆÐµÐ½Ð¸Ñ ('long parameter'):
*       LPARAM lParam;
* Ð’ÐžÐ—Ð’Ð ÐÐ©ÐÐ•ÐœÐžÐ• Ð—ÐÐÐ§Ð•ÐÐ˜Ð•:
*   (LRESULT) - Ð² Ð·Ð°Ð²Ð¸ÑÐ¸Ð¼Ð¾ÑÑ‚Ð¸ Ð¾Ñ‚ ÑÐ¾Ð¾Ð±Ñ‰ÐµÐ½Ð¸Ñ.
=======
/* Ôóíêöèÿ îáðàáîòêè ñîîáùåíèÿ îêíà.
* ÀÐÃÓÌÅÍÒÛ:
*   - äåñêðèïòîð îêíà:
*       HWND hWnd;
*   - íîìåð ñîîáùåíèÿ (ñì. WM_***):
*       UINT Msg;
*   - ïàðàìåòð ñîîáøåíèÿ ('word parameter'):
*       WPARAM wParam;
*   - ïàðàìåòð ñîîáøåíèÿ ('long parameter'):
*       LPARAM lParam;
* ÂÎÇÂÐÀÙÀÅÌÎÅ ÇÍÀ×ÅÍÈÅ:
*   (LRESULT) - â çàâèñèìîñòè îò ñîîáùåíèÿ.
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
*/
LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	CREATESTRUCT *cs;
	POINT pt;
	SYSTEMTIME st;
	HPEN hPen;
	static HDC hDC, hMemDC;
	static HBITMAP hBm;
	static INT w, h;


	switch (Msg)
	{
	case WM_CREATE:
		cs = (CREATESTRUCT *)lParam;
		SetTimer(hWnd, 111, 50, NULL);

		hDC = GetDC(hWnd);
<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
		/* ÑÐ¾Ð·Ð´Ð°ÐµÐ¼ ÐºÐ¾Ð½Ñ‚ÐµÐºÑÑ‚ Ð² Ð¿Ð°Ð¼ÑÑ‚Ð¸ */
=======
		/* ñîçäàåì êîíòåêñò â ïàìÿòè */
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
		hMemDC = CreateCompatibleDC(hDC);
		hBm = CreateCompatibleBitmap(hDC, w, h);
		ReleaseDC(hWnd, hDC);

		return 0;

	case WM_SIZE:
		w = LOWORD(lParam);
		h = HIWORD(lParam);

		if (hBm != NULL)
			DeleteObject(hBm);

		hDC = GetDC(hWnd);
		hBm = CreateCompatibleBitmap(hDC, w, h);
		ReleaseDC(hWnd, hDC);

		SelectObject(hMemDC, hBm);

		SendMessage(hWnd, WM_TIMER, 111, 0);
		return 0;

	case WM_TIMER:
		/* Clear Background */
		SelectObject(hMemDC, GetStockObject(NULL_PEN));
		SelectObject(hMemDC, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hMemDC, RGB(255, 255, 150));
		Rectangle(hMemDC, 0, 0, w + 1, h + 1);

		DrawGlobe(hMemDC, w, h);
		SelectObject(hMemDC, hBm);
		BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;

	case WM_CLOSE:
		break;

	case WM_ERASEBKGND:
		BitBlt(hDC, 0, 0, w, h, hMemDC, 0, 0, SRCCOPY);
		return 0;

	case WM_DESTROY:
		DeleteDC(hMemDC);
		KillTimer(hWnd, 111);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, Msg, wParam, lParam);
<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
} /* End of 'MyWindowFunc' function */
=======
} /* End of 'MyWindowFunc' function */
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
