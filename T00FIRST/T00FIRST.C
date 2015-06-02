#include <stdio.h>
#include <windows.h>

void main( void )
{
  if (MessageBox(NULL, "Choose YES or NO", "To be or not to be?", MB_YESNO | MB_ICONQUESTION) == IDYES)
    printf("You chose to be\n");
  else
    printf("You chose not to be\n");
}