/*T05SPHERE
*MC6 spr11
*05.06.2015
*Build a sphere in a three-dimentional space.
*/
#include "globe.h"

#define WND_CLASS_NAME "My window class"


LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg,
<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
	WPARAM wParam, LPARAM lParam); /* Функция обработки. */

/* Главная функция программы.
*   - дескриптор экземпляра приложения:
*       HINSTANCE hInstance;
*   - дескриптор предыдущего экземпляра приложения
*     (не используется и должно быть NULL):
*       HINSTANCE hPrevInstance;
*   - командная строка:
*       CHAR *CmdLine;
* ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
*   (INT) код возврата в операционную систему.
*   0 - при успехе.
=======
	WPARAM wParam, LPARAM lParam); /* ������� ���������. */

/* ������� ������� ���������.
*   - ���������� ���������� ����������:
*       HINSTANCE hInstance;
*   - ���������� ����������� ���������� ����������
*     (�� ������������ � ������ ���� NULL):
*       HINSTANCE hPrevInstance;
*   - ��������� ������:
*       CHAR *CmdLine;
* ������������ ��������:
*   (INT) ��� �������� � ������������ �������.
*   0 - ��� ������.
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
*/
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	CHAR *CmdLine, INT ShowCmd)
{
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;

<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
	wc.style = CS_VREDRAW | CS_HREDRAW; /* Стиль окна */
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = LoadCursor(NULL, IDC_HAND); /* Загрузка курсора (системного) */
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK); /* Загрузка пиктограммы (системной) */
	wc.hInstance = hInstance; /* Дескриптор приложения, регистрирующего класс */
	wc.lpszMenuName = NULL; /* Имя ресурса меню */
	wc.lpfnWndProc = MyWindowFunc; /* Указатель на функцию обработки */
	wc.lpszClassName = WND_CLASS_NAME;


	/* Регистрация класса в системе */
=======
	wc.style = CS_VREDRAW | CS_HREDRAW; /* ����� ���� */
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.hCursor = LoadCursor(NULL, IDC_HAND); /* �������� ������� (����������) */
	wc.hIcon = LoadIcon(NULL, IDI_ASTERISK); /* �������� ����������� (���������) */
	wc.hInstance = hInstance; /* ���������� ����������, ��������������� ����� */
	wc.lpszMenuName = NULL; /* ��� ������� ���� */
	wc.lpfnWndProc = MyWindowFunc; /* ��������� �� ������� ��������� */
	wc.lpszClassName = WND_CLASS_NAME;


	/* ����������� ������ � ������� */
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
		return 0;
	}

<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
	/* Создание окна */
	hWnd =
		CreateWindow(WND_CLASS_NAME,    /* Имя класса окна */
		"3D Sphere",                      /* Заголовок окна */
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,          /* Стили окна - окно общего вида */
		689 - 350, 370 - 350, /* Позиция окна (x, y) - по умолчанию */
		700, 700, /* Размеры окна (w, h) - по умолчанию */
		NULL,                         /* Дескриптор родительского окна */
		NULL,                         /* Дескриптор загруженного меню */
		hInstance,                    /* Дескриптор приложения */
		NULL);                        /* Указатель на дополнительные параметры */
=======
	/* �������� ���� */
	hWnd =
		CreateWindow(WND_CLASS_NAME,    /* ��� ������ ���� */
		"3D Sphere",                      /* ��������� ���� */
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,          /* ����� ���� - ���� ������ ���� */
		689 - 350, 370 - 350, /* ������� ���� (x, y) - �� ��������� */
		700, 700, /* ������� ���� (w, h) - �� ��������� */
		NULL,                         /* ���������� ������������� ���� */
		NULL,                         /* ���������� ������������ ���� */
		hInstance,                    /* ���������� ���������� */
		NULL);                        /* ��������� �� �������������� ��������� */
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b

	ShowWindow(hWnd, ShowCmd);
	UpdateWindow(hWnd);

<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
	/* Запуск цикла сообщений окна */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		/* Обработка сообщений от клавиатуры */
		TranslateMessage(&msg);
		/* Передача сообщений в функцию окна */
=======
	/* ������ ����� ��������� ���� */
	while (GetMessage(&msg, NULL, 0, 0))
	{
		/* ��������� ��������� �� ���������� */
		TranslateMessage(&msg);
		/* �������� ��������� � ������� ���� */
>>>>>>> 977fc549a26382dff558fe32d092344f27deec0b
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


<<<<<<< 7657d15ee41ca1055590354e8fe077ff86efc760
/* Функция обработки сообщения окна.
* АРГУМЕНТЫ:
*   - дескриптор окна:
*       HWND hWnd;
*   - номер сообщения (см. WM_***):
*       UINT Msg;
*   - параметр сообшения ('word parameter'):
*       WPARAM wParam;
*   - параметр сообшения ('long parameter'):
*       LPARAM lParam;
* ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
*   (LRESULT) - в зависимости от сообщения.
=======
/* ������� ��������� ��������� ����.
* ���������:
*   - ���������� ����:
*       HWND hWnd;
*   - ����� ��������� (��. WM_***):
*       UINT Msg;
*   - �������� ��������� ('word parameter'):
*       WPARAM wParam;
*   - �������� ��������� ('long parameter'):
*       LPARAM lParam;
* ������������ ��������:
*   (LRESULT) - � ����������� �� ���������.
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
		/* создаем контекст в памяти */
=======
		/* ������� �������� � ������ */
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
