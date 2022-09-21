#include "qlog.hpp"

int main()
{
    qlog::set_prefix("[SOME PREFIX]");

    QLOG("hello", ' ', "world!", 42);
    int somevar = 3;
    double anothervar = 42.0;
    QVAR(somevar, anothervar);

    QLOGTAG("SHOWTHIS", "The SHOWTHIS tag is set");

    char const * onlyshowthis = "Only show this";
    QVARTAG("SHOWTHIS", onlyshowthis);
}
