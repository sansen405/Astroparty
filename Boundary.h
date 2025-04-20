#ifndef BOUNDARY_H
#define BOUNDARY_H

#include <stdint.h>

class boundary {
private:
    int x;
    int y;
    int len;
    int wid;

public:
    boundary(int x, int y, int len, int wid);
    bool draw();
};

#endif
