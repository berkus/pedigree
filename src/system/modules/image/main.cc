#include <Module.h>

void init()
{
}

void destroy()
{
}

MODULE_NAME("image");
MODULE_ENTRY(&init);
MODULE_EXIT(&destroy);
MODULE_DEPENDS("VFS");
