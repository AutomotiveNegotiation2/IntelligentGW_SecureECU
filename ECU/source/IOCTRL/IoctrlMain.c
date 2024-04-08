#include "Includes.h"

void IoctrlMain(void)
{
	SoftTimerSrv();
	IoctrlSrv();
}
