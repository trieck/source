
#include "Common.h"
#include "Exception.h"
#include "Configuration.h"

/////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    try {
        Configuration c = Configuration("d:\\temp\\win.ini");

        string v = c.GetValue("Settings", "Left Delims");
        cout << "\"" << v << "\"" << endl;

        v = c.GetValueEx("Settings", "Left Delims");
        cout << "\"" << v << "\"" << endl;

    } catch (const Exception &e) {
        cerr << e.GetDescription() << endl;
        return 1;
    }

    return 0;
}