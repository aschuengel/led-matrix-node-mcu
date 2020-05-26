#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__

#include <MD_MAX72xx.h>

#define MAX_DEVICES 4
#define CS_PIN D1
#define DATA_PIN D2
#define CLCK_PIN D0

class Matrix {
    private:
        MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::FC16_HW, DATA_PIN, CLCK_PIN, CS_PIN, MAX_DEVICES);
    public:
        void scrollText(const char *p);
        void begin();
};
#endif