#include "global.h"
#include "log/log_output.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
    Logging(true, "abc/def/ghi.html", -1, GET, CONSOLE_ONLY);
    return 0;
}
