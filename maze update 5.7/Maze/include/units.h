#ifndef UNITS_H
#define UNITS_H
#include <string>
#include <iostream>

using namespace std;


class units
{
    public:
        int x, y;
        char type;
        units();
        void set_unit (int x1, int y1, char type1) {
        x = x1; y = y1; type = type1;
        }

        char print_unit(){//for debugging purposes
            return type;
        }
};

#endif // UNITS_H
