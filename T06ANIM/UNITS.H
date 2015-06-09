/* FILENAME: UNITS.H
 * PROGRAMMER: MC6
 * PURPOSE: Animation units samples declaration module.
 * LAST UPDATE: 08.06.2015
 */

#ifndef __UNITS_H_
#define __UNITS_H_

#include "anim.h"


/* Функция создания объекта анимации "мяч".
 * АРГУМЕНТЫ: Нет.
 * ВОЗВРАЩАЕМОЕ ЗНАЧЕНИЕ:
 *   (mc6UNIT *) указатель на созданный объект анимации.
 */
mc6UNIT * MC6_UnitBallCreate( VOID );
mc6UNIT * MC6_UnitCowCreate( VOID );

#endif /* __UNITS_H_ */

/* END OF 'UNITS.H' FILE */
