#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#include <inttypes.h>
#include <string.h>


/*****************************************************************************
 * BEGIN CONFIG BLOCK
 *****************************************************************************/
#define LCD_WIDTH   240
#define LCD_HEIGHT  320

//Should chip select (CS) be used?
#define LCD_USE_CHIPSELECT  1

//Define a function that waits until SPI interface is idle (not needed here)
#define spi_wait_for_idle() 

/*****************************************************************************
 * END CONFIG BLOCK
 *****************************************************************************/

//In case of an color LCD, this struct will keep the necessary information
//Color struct - no bit fields are used for better performance (i.e. bit shifts
//can be done while waiting for SPI, not while preparing to write the pixel)
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    } color_t;


/*****************************************************************************
 * Public Functions
 *****************************************************************************/
//initializes the display in standard settings
 void lcd_init(void);

//write data word or command to the LCD
 void lcd_data      (uint8_t data);
 void lcd_command   (uint8_t cmd);
 void lcd_command_1 (uint8_t cmd, uint8_t data);

//Set the drawing and background colors
 void lcd_set_foreground(uint8_t r, uint8_t g, uint8_t b);
 void lcd_set_background(uint8_t r, uint8_t g, uint8_t b);
  
//set display area for next write accesses
 void lcd_set_page(uint16_t start, uint16_t end);
 void lcd_set_column(uint16_t start, uint16_t end);

//write pixel data in 16 bit color mode. Display must be in write mode
 void lcd_send_pixel(color_t c);

//Set a pixel at a given location to the foreground color
 void lcd_set_pixel_xy(uint16_t column, uint16_t page); 
//Set an area to the background color
 void lcd_set_area_xy(uint16_t col0, uint16_t col1, uint16_t page0, uint16_t page1);

 
 
 
//Text functions are included in font.c / font.h
//These functions provide compatibility to the old font generator
 uint16_t lcd_inc_page(int16_t s);
 uint16_t lcd_inc_column(int16_t s);
 void lcd_moveto_xy(uint16_t page, uint16_t column);
 void lcd_move_xy(int16_t pages, int16_t columns);
//Function to read the current position
 extern uint16_t lcd_current_page;
 extern uint16_t lcd_current_column;
 static inline uint16_t lcd_get_position_page(void)   {return lcd_current_page;}
 static inline uint16_t lcd_get_position_column(void) {return lcd_current_column;}
 void lcd_write_font_byte(uint8_t b);


/*****************************************************************************
 * Command Codes
 *****************************************************************************/
  #define LCD_NOP               0x00
  #define LCD_SOFT_RESET        0x01
  #define LCD_SLEEP_ENTER       0x10
  #define LCD_SLEEP_OUT         0x11
  #define LCD_OFF               0x28
  #define LCD_ON                0x29
  #define LCD_SET_COLUMN        0x2A
  #define LCD_SET_PAGE          0x2B
  #define LCD_WRITE_MEM         0x2C
  #define LCD_MIRROR            0x36
  #define LCD_IDLE_MODE_OFF     0x38
  #define LCD_IDLE_MODE_ON      0x39
  #define LCD_COLOR_MODE        0x3A
  #define LCD_WRITE_CONTINUE    0x3C  
 

/*****************************************************************************
 * Commands  Arguments
 *****************************************************************************/
  #define LCD_16BIT             0x55
  #define LCD_18BIT             0x66

//Settings for LCD_MIRROR (0x36)
  #define LCD_MIRROR_Y          0x80
  #define LCD_MIRROR_X          0x40
  #define LCD_FLIP_XY           0x20
  #define LCD_BGR               0x08



 
/*****************************************************************************
 * Output pin controlling makros
 *****************************************************************************/

//Control A0 input of LCD
#define LCD_DATA()            digitalWrite(2, 1);
#define LCD_CMD()             digitalWrite(2, 0)
#define LCD_SET_OUTPUT_DC()   pinMode(2, OUTPUT)

//Control reset input of LCD
#define LCD_RESET_OFF()       
#define LCD_RESET_ON()        
#define LCD_SET_OUTPUT_RST()  


//Control pin for chip select
#if LCD_USE_CHIPSELECT == 1
  #define LCD_SET_OUTPUT_CS()  pinMode(15, OUTPUT)
  #define LCD_SELECT()         digitalWrite(15, 0)
  #define LCD_UNSELECT()       digitalWrite(15, 1)
#else
  #define LCD_SET_OUTPUT_CS()  
  #define LCD_SELECT()         
  #define LCD_UNSELECT()   
#endif

//combined direction selection for all pins
#define LCD_SET_PIN_DIRECTIONS()   LCD_SET_OUTPUT_DC(); \
                                   LCD_SET_OUTPUT_RST(); \
                                   LCD_SET_OUTPUT_CS()





#endif

