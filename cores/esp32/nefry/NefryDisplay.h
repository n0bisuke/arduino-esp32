#ifndef NefryDisplay_h
#define NefryDisplay_h
#include <Arduino.h>
#include "inc\ssd1306\SSD1306.h"


class Nefry_Display
{
public:
	
	bool 
		begin(),
		//シンプルなログ表示用
		print(String s);
	// ディスプレイで使用しているメモリを解放する
	void end();

	//指定された場所に最大幅の文字列を描画します。
	//指定されたStringが指定された幅よりも広い場合
	//テキストはスペースまたはダッシュで次の行に折り返されます
	//TODO:長ければスクロールする機能の実装
	void drawString(int16_t x, int16_t y, String text, int16_t maxLineWidth = 0);

	// 表示に必要な幅を計算します。
	uint16_t getStringWidth(const char* text, uint16_t length);

	// 表示に必要な幅を計算します。
	uint16_t getStringWidth(String text);

	// 文字列配置位置指定(左揃え、中央揃え、右揃え、)
	// TEXT_ALIGN_LEFT, TEXT_ALIGN_CENTER, TEXT_ALIGN_RIGHT, TEXT_ALIGN_CENTER_BOTH
	void setTextAlignment(OLEDDISPLAY_TEXT_ALIGNMENT textAlignment);

	// フォントセット
	// フォント作成ツール http://oleddisplay.squix.ch
	void setFont(const char* fontData);

	/**
	* ピクセル製図モード
	*/

	// Draw a pixel at given position
	void setPixel(int16_t x, int16_t y);

	// Draw a line from position 0 to position 1
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);

	// Draw the border of a rectangle at the given location
	void drawRect(int16_t x, int16_t y, int16_t width, int16_t height);

	// Fill the rectangle
	void fillRect(int16_t x, int16_t y, int16_t width, int16_t height);

	// Draw the border of a circle
	void drawCircle(int16_t x, int16_t y, int16_t radius);

	// Fill circle
	void fillCircle(int16_t x, int16_t y, int16_t radius);

	// Draw a line horizontally
	void drawHorizontalLine(int16_t x, int16_t y, int16_t length);

	// Draw a lin vertically
	void drawVerticalLine(int16_t x, int16_t y, int16_t length);

	// プログレスバー
	// Progress 0 and 100
	void drawProgressBar(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t progress);

	// 作画イラストモード
	//イラスト変換サイト
	//https://www.online-utility.org/image/convert/to/XBM
	void drawXbm(int16_t x, int16_t y, int16_t width, int16_t height, const char* xbm);

	/**
	* ディスプレイ制御モード
	*/

	// 表示メモリクリア
	void clear(void);

	// ディスプレイに表示
	void display(void);

	// 反転ディスプレイモード
	void invertDisplay(void);

	// ノーマルディスプレイモード
	void normalDisplay(void);

	//ディスプレイコントラストを設定する
	void setContrast(char contrast);

	// 上下反転
	void flipScreenVertically();

};
extern Nefry_Display NefryDisplay;
#endif