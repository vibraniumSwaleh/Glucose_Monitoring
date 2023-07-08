#ifndef _MENU_
#define _MENU_

#include <iostream>
#include <string>
#include "OLED_1in3_c.h"
#include "ImageData.h"
#include "GUI_Paint.h"

extern const int NUM_MENU_ITEMS;
extern int selectedMenuItem;
extern int prevMenuItem;

void handleUpButton();
void handleDownButton();

class Welcome_Msg_0
{
private:
    std::string welcome_0_1;
    std::string welcome_0_2;
    std::string welcome_0_3;
public:
    Welcome_Msg_0(const std::string &msg0_1, const std::string &msg0_2, const std::string &msg0_3);
    void Display_Message(uint8_t *BImage_Msg_0);
    ~Welcome_Msg_0();
};

class Welcome_Msg_1
{
private:
    std::string welcome_1_1;
    std::string welcome_1_2;
    std::string welcome_1_3;
    std::string welcome_1_4;
    std::string welcome_1_5;
public:
    Welcome_Msg_1(const std::string &msg1_1, const std::string &msg1_2, const std::string &msg1_3, const std::string &msg1_4, const std::string &msg1_5);
    void Display_Message(uint8_t *BImage_Msg_1);
    ~Welcome_Msg_1();
};

class Welcome_Msg_2 
{
private:
    std::string welcome_2_1;
public:
    Welcome_Msg_2(const std::string &msg2_1);
    void Display_Message(uint8_t *BImage_Msg_2);
    ~Welcome_Msg_2();
};

class Menu_0
{
private:
    std::string menu_0_1;
    std::string menu_0_2;
    std::string menu_0_3;
    uint8_t *BImage_Menu_0;
    const unsigned char	*Graphicx_0[2];
    
public:
    Menu_0(const std::string &menu0_1, const std::string &menu0_2, const std::string &menu0_3, const unsigned char *Graphicx_Array_0[2]);
    void Display_Menu(uint8_t *BImage_Menu_0);
    ~Menu_0();
};

class BL_setup
{
private:
    bool No = true;
    bool Yes = true;
    std::string bl_setup_title;
    std::string on;
    std::string off;
public:
    BL_setup(const std::string &bl_setup_title, const std::string &on, const std::string &off);
    void Display_Menu(uint8_t *BImage_bl_setup);
    ~BL_setup();
};

void Main_Menu_Title();
void Pair_Bluetooth_Display();
void Dashboard_Display();

void Main_Menu_Display();

#endif