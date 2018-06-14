#include <xboxrt/debug.h>
#include <pbkit/pbkit.h>
#include <hal/xbox.h>
#include "stdio.h"

void main(void)
{
    int i;

    if (pb_init()) {
        XSleep(2000);
        XReboot();
        return;
    }

    pb_show_debug_screen();
    debugPrint("Please insert an Xbox disc...\n");
    while(1) XSleep(1000);
    pb_kill();
    XReboot();
}
