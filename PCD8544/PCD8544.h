/*

  ******************************************************************************
  * @file 			( фаил ):   PCD8544.h
  * @brief 		( описание ):  	
  ******************************************************************************
  * @attention 	( внимание ):	LCD_Nokia_5110_PCD8544_84x48
  ******************************************************************************
  
*/

#ifndef _PCD8544_H
#define _PCD8544_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------*/

// Обязательно нужен #include "main.h" 
// чтоб отдельно не подключать файлы связанные с МК и стандартными библиотеками
#include "main.h"

#include "fonts.h"

#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

/*
	подключение LCD_Nokia_5110_PCD8544_84x48:

	в CubeMX включаем SPI только на отправку скорость максимум 4 Мбит/с 
	оп даташиту написано что максимум 4 Мбит/с ( Serial interface maximum 4.0 Mbits/s )
	но я ставил 9 Мбит/с работало, на 18 Мбит/с уже не работало.

	( пины желательно называем как в коде если нет то в коде ставим нужные )

	GND	 ->   GND
	BL	 ->   +3.3V подсветка ( если нужно управлять подключаем к пину или шим )	
	VCC  ->   3.3V
	CIK	 ->   CLK SCK
	DIR	 ->	  MOSI
	DC	 ->   Выбор команда или данные
	CE	 ->   CS ( chip select )
	RST  ->   RST ( Reset )

*/

//##########  SETUP  ######################################################################################################################################
			
		// указываем порт SPI для HAL -------------------
		#define 	PCD8544_SPI_HAL 		hspi2
		//-----------------------------------------------
		
		//=== указываем порты ( если в кубе назвали их RES CS то тогда нечего указывать не нужно )
		
		#if defined (RST_GPIO_Port)
		#else
			#define RST_GPIO_Port   	GPIOA
			#define RST_Pin				GPIO_PIN_12
		#endif
		
		#if defined (DC_GPIO_Port)
		#else
			#define DC_GPIO_Port    GPIOA
			#define DC_Pin			GPIO_PIN_15
		#endif

		#if defined (CS_GPIO_Port)
		#else
			#define CS_GPIO_Port    GPIOA
			#define CS_Pin			GPIO_PIN_14
		#endif

		
		//=============================================================================
		
//##########################################################################################################################

enum PixelStatus{ PIX_OFF, PIX_ON };


#ifdef PCD8544_SPI_HAL
	extern SPI_HandleTypeDef PCD8544_SPI_HAL;
#endif



/** Screen width in pixels (tested with 84) */
#define SCREEN_WIDTH 	84
/** Screen height in pixels (tested with 48) */
#define SCREEN_HEIGHT 	48


/* Absolute value */
#define ABS(x)   ((x) > 0 ? (x) : -(x))
	

/* Functions prototypes ----------------------------------------------*/


//==============================================================================
// инициализация дисплея ( при другой инициализации можно поменять параметры внутри функции )
//==============================================================================
void PCD8544_Init( void );
//==============================================================================


//==============================================================================
// рисуем 1 пиксель, записываем его в буффер кадра но не выводим на дисплей
// параметры: координата Х (от 0 по 83) координата У (от 0 по 47)
//==============================================================================
void PCD8544_Draw_pixel(uint8_t x, uint8_t y);
//==============================================================================


//==============================================================================
// Функция удаления пикселя на экране
// параметры: координата Х (от 0 по 83) координата У (от 0 по 47)
//==============================================================================
void PCD8544_Clear_pixel(uint8_t x, uint8_t y);
//==============================================================================


//==============================================================================
// Функция ротации  дисплея
//	( параметры ):  координаты X(от 0 до 83) и Y(от 0 до 47)
//	( возвращает ):	0- поворот на 0 градусов ( по умолчанию ), 1- поворот на 180 градусов
//								вызвать перед формированием изображения ( если данные в массиве уже есть
//								то инверсии не будет, будет только то что было сформировано после вызова данной функции )
//==============================================================================
void PCD8544_rotation(uint8_t mode);
//==============================================================================


//==============================================================================
// Функция вывода буфера кадра на дисплей
// Вызывать каждый раз чтобы вывести на экран содержание буфера
//==============================================================================
void PCD8544_Update(void);
//==============================================================================


//==============================================================================
// Функция очистки буфера кадра ( само изображение на экране не удаляет )
//==============================================================================
void PCD8544_Clear_frame_buffer(void);
//==============================================================================


//==============================================================================
// Функция инверсии инвертируется дисплей
// ( 1-инвертируем  0-изображение по умолчанию )
//==============================================================================
void PCD8544_Inversion(uint8_t inv);
//==============================================================================


//==============================================================================
// Функция контрастности и цветовой температуры
// контрастность от 0 по 7
// цветовая температура от 0 по 3
//==============================================================================
void PCD8544_contrast(uint8_t contrast, uint8_t temp);
//==============================================================================


//==============================================================================
// Функция очистки дисплея вместе с буфером кадра
//==============================================================================
void PCD8544_Clear( void );
//==============================================================================


//==============================================================================
// Display ON OFF ( очищаем экран но не очищаем буфер кадра )
// 1-enable, 0-disable
//==============================================================================
void PCD8544_Display_On_Off(bool enable);
//==============================================================================


//==============================================================================
// функция рисует монохромныую картинку
// начальные координаты X Y, сама картинка, ширина и высота картинки и цвет ( PIX_ON PIX_OFF )
//==============================================================================
void PCD8544_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint8_t color);
//==============================================================================


//==============================================================================
// функция выводит 1 символ
// координаты X Y, символ, шрифт, множитель, цвет 1 или 0 ( PIX_ON PIX_OFF )
//==============================================================================
void PCD8544_DrawChar(int16_t x, int16_t y, unsigned char ch, FontDef_t* Font, uint8_t multiplier, uint8_t color);
//==============================================================================


//==============================================================================
// функция пишет строку
// координаты X Y, символ, шрифт, множитель, цвет 1 или 0 ( PIX_ON PIX_OFF )
//==============================================================================
void PCD8544_Print(int16_t x, int16_t y, char* str, FontDef_t* Font, uint8_t multiplier, uint8_t color);
//==============================================================================




/********************************РАБОТА С ГЕОМЕТРИЧЕСКИМИ ФИГУРАМИ**********************************/

void PCD8544_Draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint8_t color);

/*--------------------------------Вывести пустотелый прямоугольник---------------------------------*/
void PCD8544_Draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
/*--------------------------------Вывести пустотелый прямоугольник---------------------------------*/

/*-------------------------------Вывести закрашенный прямоугольник---------------------------------*/
void PCD8544_Draw_rectangle_filled(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
/*-------------------------------Вывести закрашенный прямоугольник---------------------------------*/

/*---------------------------------Вывести пустотелую окружность-----------------------------------*/
void PCD8544_Draw_circle(uint8_t x, uint8_t y, uint8_t radius, uint8_t color);
/*---------------------------------Вывести пустотелую окружность-----------------------------------*/

/*--------------------------------Вывести закрашенную окружность-----------------------------------*/
void PCD8544_Draw_circle_filled(int16_t x, int16_t y, int16_t radius, uint8_t color);
/*--------------------------------Вывести закрашенную окружность-----------------------------------*/

/*-----------------------------------Вывести пустотелый треугольник--------------------------------*/
void PCD8544_Draw_triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t color);
/*-----------------------------------Вывести пустотелый треугольник--------------------------------*/

/*----------------------------------Вывести закрашенный треугольник--------------------------------*/
void PCD8544_Draw_triangle_filled(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t color);
/*----------------------------------Вывести закрашенный треугольник--------------------------------*/

//==============================================================================
// Процедура рисования четверти окружности (закругление, дуга) ( ширина 1 пиксель)
//==============================================================================
void PCD8544_DrawCircleHelper(int16_t x0, int16_t y0, int16_t radius, int8_t quadrantMask, uint8_t color);
//==============================================================================


//==============================================================================
// Процедура рисования половины окружности ( правая или левая ) ( заполненый )
//==============================================================================
void PCD8544_DrawFillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint8_t color);
//==============================================================================


//==============================================================================
// Процедура рисования прямоугольник с закругленніми краями ( заполненый )
//==============================================================================
void PCD8544_DrawFillRoundRect(int16_t x, int16_t y, uint16_t width, uint16_t height, int16_t cornerRadius, uint8_t color);
//==============================================================================


//==============================================================================
// Процедура рисования прямоугольник с закругленніми краями ( пустотелый )
//==============================================================================
void PCD8544_DrawRoundRect(int16_t x, int16_t y, uint16_t width, uint16_t height, int16_t cornerRadius, uint8_t color);
//==============================================================================

/********************************РАБОТА С ГЕОМЕТРИЧЕСКИМИ ФИГУРАМИ**********************************/


#ifdef __cplusplus
}
#endif

#endif	/*	_PCD8544_H */

/************************ (C) COPYRIGHT GKP *****END OF FILE****/
