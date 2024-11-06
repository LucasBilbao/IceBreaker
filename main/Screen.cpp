#include "Screen.h"

Screen::Screen(int rs, int e, int d4, int d5, int d6, int d7)
  : LiquidCrystal(rs, e, d4, d5, d6, d7) {
  begin(16, 2);
}

void Screen::printScreen(String s) {
  clear();
  if (s.length() <= 16) {
    print(s);
  } else {
    String s1 = s.substring(0, 16);
    String s2 = s.substring(16);
    print(s1);
    setCursor(0, 1);
    print(s2);
  }
}
