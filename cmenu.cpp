#include "cmenu.h"

CMenu::CMenu(QWidget *parent) : QMenu{parent}
{
    setStyleSheet("QMenu {"
                  "background-color: rgb(57, 65, 69);"
                  "color: rgb(255,255,255);"
                  "border: 1px solid rgb(172, 172, 172);"
                  "border-radius: 3px; }"
                  "QMenu::item {"
                  "background-color: transparent;"
                  "border-bottom: 1px solid rgb(172, 172, 172);"
                  "padding:5px 10px;"
                  "margin:0px 0px; }"
                  "QMenu::item:selected {"
                  "background-color: rgb(76, 71, 169); }");
}
