#include <core/logger.h>
#include <core/asserts.h>

int main(void) 
{
    BFATAL("This is a fatal error: %f", 3.14f);
    BERROR("This is an error: %f", 3.14f);
    BWARNING("This is a warning: %f", 3.14f);
    BINFO("This is an info: %f", 3.14f);
    BDEBUG("This is a debug: %f", 3.14f);
    BTRACE("This is a trace: %f", 3.14f);

    BASSERT(1 == 0);

    return 0;
}