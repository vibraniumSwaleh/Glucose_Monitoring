#ifndef _MENU_
#define _MENU_

#include <iostream>
#include <string>
#include "OLED_1in3_c.h"
#include "ImageData.h"
#include "GUI_Paint.h"

class Welcome_Msg_0
{
private:
    std::string welcome_0_1;
    std::string welcome_0_2;
    std::string welcome_0_3;
public:
    Welcome_Msg_0(const std::string &msg0_1, const std::string &msg0_2, const std::string &msg0_3);
    void Display_Message();
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
    void Display_Message();
    ~Welcome_Msg_1();
};

class Welcome_Msg_2 
{
private:
    std::string welcome_2_1;
    uint8_t *BImage_2_1;
public:
    Welcome_Msg_2(const std::string &msg2_1, uint8_t *BI_2_1);
    void Display_Message();
    ~Welcome_Msg_2();
};

class Menu_0
{
private:
    std::string menu_0_1;
    std::string menu_0_2;
    std::string menu_0_3;
    const unsigned char	*Graphicx_0[2];
    
public:
    Menu_0(const std::string &menu0_1, const std::string &menu0_2, const std::string &menu0_3, const unsigned char *Graphicx_Array_0[2]);
    void Display_Menu();
    ~Menu_0();
};

#endif