#include <Arduino.h>
#include "Matrix.hpp"

void Matrix::scrollText(const char *p)
{
  unsigned int charWidth;
  uint8_t cBuf[8]; // this should be ok for all built-in fonts
  int length;
  int k;
  char c;

  length = strlen(p);

  mx.clear(); 

  for (k = 0; k < length; k++)
  {
    c = p[k];
    charWidth = mx.getChar(c, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);

    for (unsigned int i = 0; i <= charWidth; i++) // allow space between characters
    {
      mx.transform(MD_MAX72XX::TSL);
      if (i < charWidth)
        mx.setColumn(0, cBuf[i]);
      delay(50);
    }
  }
}

void Matrix::begin() {
    mx.begin();
}