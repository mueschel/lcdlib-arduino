

#include <SPI.h>

extern "C" {
#include "lcd-color-graphic.h"
#include "font.h"
}


void setup() {
  
  lcd_init();
  lcd_set_background(0x00,0x00,0x04);
  lcd_set_area_xy(0,240,0,320);
  
  lcd_set_foreground(0x1f,0x3f,0x1f);
  lcd_moveto_xy(6,0);
  lcd_set_font(FONT_PROP_16,NORMAL | WRAP);
  lcd_putstr("Ein kleiner Beispieltext auf einem ILI9341 TFT");

  lcd_set_foreground(0x00,0x3f,0x00);
  lcd_moveto_xy(15,80);
  lcd_set_font(FONT_DIGITS_32,NORMAL);
  lcd_putstr("1:0");

  lcd_set_font(FONT_PROP_16,NORMAL | WRAP);
  lcd_moveto_xy(20,0);
  lcd_putstr("fuer dich!");


  lcd_set_foreground(0x1f,0x1f,0x00);
  lcd_moveto_xy(0,0);
  lcd_set_font(FONT_PROP_16,DOUBLE_SIZE | UNDERLINE);
  lcd_putstr("Arduino LcdLib");

}


void loop() {
  delay(5000);

}

