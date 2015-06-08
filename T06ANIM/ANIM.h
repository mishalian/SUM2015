/* FILENAME: ANIM.H
 * PROGRAMMER: MC6
 * PURPOSE: Animation system declaration module.
 * LAST UPDATE: 08.06.2015
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "def.h"
#include "vec.h"

#include <windows.h>
#include <stdlib.h>
#include <time.h>

/* Максимальное количество элементов анимации */
#define MC6_MAX_UNITS 3000

/* Объявление типа объектов анимации "вперед" */
typedef struct tagmc6UNIT mc6UNIT;

/* Структура хранения контекста анимации */
typedef struct
{
  HWND hWnd;          /* Окно вывода */
  INT W, H;           /* Размер окна вывода */
  HBITMAP hBmFrame;   /* Буфер кадра */
  HDC hDC;            /* Контекст вывода */
  BOOL IsPause; 
  DBL GlobalTime, GlobalDeltaTime, DeltaTime, Time, FPS;

  /* Массив элементов анимации и их количество */
  mc6UNIT *Units[MC6_MAX_UNITS]; 
  INT NumOfUnits;

} mc6ANIM;

/* Базовые поля объекта анимации:
 * - размер структуры для наследования
 *     INT Size;
 * - идентификатор объеткта:
 *     INT Id;
 * - указатель на функцию инициализации
 *     VOID (*Init)( mc6UNIT *Unit, mc6ANIM *Ani );
 * - указатель на функцию деинициализации
 *     VOID (*Close)( mc6UNIT *Unit, mc6ANIM *Ani );
 * - указатель на функцию обновления межкадровых параметров
 *     VOID (*Response)( mc6UNIT *Unit, mc6ANIM *Ani );
 * - указатель на функцию построения
 *     VOID (*Render)( mc6UNIT *Unit, mc6ANIM *Ani );
 */
#define MC6_UNIT_BASE_FIELDS \
  INT Size;                                          \
  VOID (*Init)( mc6UNIT *Unit, mc6ANIM *Ani );       \
  VOID (*Close)( mc6UNIT *Unit, mc6ANIM *Ani );      \
  VOID (*Response)( mc6UNIT *Unit, mc6ANIM *Ani );   \
  VOID (*Render)( mc6UNIT *Unit, mc6ANIM *Ani )

/* Базовый тип объекта анимации */
struct tagmc6UNIT
{
  MC6_UNIT_BASE_FIELDS;
};

/* Функция инициализации анимации.
 * АРГУМЕНТЫ:
 *   - дескриптор окна:
 *       HWND hWnd;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_AnimInit( HWND hWnd );

/* Функция деинициализации анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_AnimClose( VOID );

/* Функция обработки изменения размера области вывода.
 * АРГУМЕНТЫ:
 *   - новый размер области вывода:
 *       INT W, H;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_AnimResize( INT W, INT H );

/* Функция построения кадра анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_AnimRender( VOID );

/* Функция вывода кадра анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_AnimCopyFrame( VOID );

/* Функция добавления в систему объекта анимации.
 * АРГУМЕНТЫ:
 *   - добавляемый объект анимации:
 *       mc6UNIT *Unit;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_AnimAddUnit( mc6UNIT *Unit );

/* Функция переключения в/из полноэкранного режима
 * с учетом нескольких мониторов.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_AnimFlipFullScreen( VOID );

/* Функция создания объекта анимации.
 * АРГУМЕНТЫ:
 *   - размер структуры объекта анимации:
 *       INT Size;
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (mc6UNIT *) указатель на созданный объект анимации.
 */
mc6UNIT * MC6_AnimUnitCreate( INT Size );

/* Функция выхода из анимации.
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ: Нет.
 */
VOID MC6_AnimDoExit( VOID );

#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */
