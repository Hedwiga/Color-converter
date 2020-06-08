/*
Filename: color.cpp
*/
#include "color.h"
#include <QDebug>
Color::Color()
{
    amountOfColors++;
    red = green = blue = 0;

}
Color::Color(Color::RGB_8bit redNew, Color::RGB_8bit greenNew, Color::RGB_8bit blueNew)
{
    amountOfColors++;
    red = redNew;
    green = greenNew;
    blue = blueNew;
}
Color::Color(Color::PERCENT cyan, Color::PERCENT magenta, Color::PERCENT yellow, Color::PERCENT black)
{
    amountOfColors++;
    fromCMYK(cyan, magenta, yellow, black);
}
Color Color::add(Color summand1, Color summand2)
{
    RGB_8bit tempRed1 = 0, tempRed2 = 0, tempGreen1 = 0, tempGreen2 = 0, tempBlue1 = 0, tempBlue2 = 0;
    summand1.getColor(tempRed1, tempGreen1, tempBlue1);
    summand2.getColor(tempRed2, tempGreen2, tempBlue2);
    RGB_8bit * tempColors[6] = {&tempRed1, &tempRed2, &tempGreen1, &tempGreen2, &tempBlue1, &tempBlue2};
    for(int i = 0; i < 6; ++i)
    {
        if(*tempColors[i] == 0)
            *tempColors[i] = 1;
    }
    double redResult = sqrt(tempRed1 * tempRed2);
    double greenResult = sqrt(tempGreen1 * tempGreen2);
    double blueResult = sqrt(tempBlue1 * tempBlue2);
    red = (RGB_8bit)redResult;
    green = (RGB_8bit)greenResult;
    blue = (RGB_8bit)blueResult;
    return *this;
}
Color Color::subtract(Color minuend, Color subtrahend)
{
    red = minuend.red - subtrahend.red;
    green = minuend.green - subtrahend.green;
    blue = minuend.blue - subtrahend.blue;
    return *this;
}
void Color::toHSV(Color::DEGREE & hue, Color::PERCENT & saturation, Color::PERCENT & value) const
{
    PERCENT redPer = (red / 255.0);
    PERCENT greenPer = (green / 255.0);
    PERCENT bluePer = (blue / 255.0);
    PERCENT maxColor = MAX3(redPer, greenPer, bluePer);
    PERCENT minColor = MIN3(redPer, greenPer, bluePer);
    value = maxColor;
    PERCENT deltaMinMax = maxColor - minColor;
    if(deltaMinMax < 0.0001)
    {
        saturation = 0;
        hue = 0;
        return;
    }
    if(maxColor == 0)
    {
        saturation = 0;
        hue = 0;
        return;
    }
    PERCENT deltaHue = 0;
    DEGREE degree = 0;
    if(maxColor == redPer)
    {
        deltaHue = greenPer - bluePer;
        if(greenPer < bluePer)
            degree = 360;
        else
            degree = 0;
    }
    else if(maxColor == greenPer)
    {
        deltaHue = bluePer - redPer;
        degree = 120;
    }
    else if(maxColor == bluePer)
    {
        deltaHue = redPer - greenPer;
        degree = 240;
    }
    else if(maxColor == 0)
    {
        deltaHue = 0;
    }

    hue = (60 * (deltaHue / deltaMinMax)) + degree;
    saturation = 1 - (minColor/maxColor);
}
void Color::fromHSV(Color::DEGREE hue, Color::PERCENT saturation, Color::PERCENT value)
{
    PERCENT value1 = saturation * value;
    PERCENT value2 = value1 * (1 - fabs(fmod(hue / 60.0, 2) - 1));
    PERCENT delta = value - value1;
    PERCENT redTemp, greenTemp, blueTemp;
    if(hue < 60)
    {
        redTemp = value1;
        greenTemp = value2;
        blueTemp = 0;
    }
    else if(hue >= 60 && hue < 120)
    {
        redTemp = value2;
        greenTemp = value1;
        blueTemp = 0;
    }
    else if(hue >= 120 && hue < 180)
    {
        redTemp = 0;
        greenTemp = value1;
        blueTemp = value2;
    }
    else if(hue >= 180 && hue < 240)
    {
        redTemp = 0;
        greenTemp = value2;
        blueTemp = value1;
    }
    else if(hue >= 240 && hue < 300)
    {
        redTemp = value2;
        greenTemp = 0;
        blueTemp = value1;
    }
    else
    {
        redTemp = value1;
        greenTemp = 0;
        blueTemp = value2;
    }
    red = (redTemp + delta) * 255;
    green = (greenTemp + delta) * 255;
    blue= (blueTemp + delta) * 255;
}
void Color::toCMYK(Color::PERCENT &cyan, Color::PERCENT &magenta, Color::PERCENT &yellow, Color::PERCENT &black) const
{
    cyan = 1 - (red / 255.0);
    magenta = 1 - (green / 255.0);
    yellow = 1 - (blue / 255.0);
    black = MIN3(cyan, magenta, yellow);
    if(black == 1) black = 0;
    cyan = (cyan - black) / (1 - black);
    magenta = (magenta - black) / (1 - black);
    yellow = (yellow - black) / (1 - black);
}
void Color::fromCMYK(Color::PERCENT cyan, Color::PERCENT magenta, Color::PERCENT yellow, Color::PERCENT black)
{
    red = 255 * (1 - cyan) * (1 - black);
    green = 255 * (1 - magenta) * (1 - black);
    blue = 255 * (1 - yellow) * (1 - black);
}
void Color::setColor(Color::RGB_8bit redNew, Color::RGB_8bit greenNew, Color::RGB_8bit blueNew)
{
    red = redNew;
    green = greenNew;
    blue = blueNew;
}
void Color::setRed(Color::RGB_8bit redNew)
{
    red = redNew;
}
void Color::setGreen(Color::RGB_8bit greenNew)
{
    green = greenNew;
}
void Color::setBlue(Color::RGB_8bit blueNew)
{
    blue = blueNew;
}
void Color::readColor(const QSpinBox *box)
{
    QString boxName = box->objectName();
    if(boxName.contains("red"))
        red = box->value();
    else if(boxName.contains("green"))
        green = box->value();
    else if(boxName.contains("blue"))
        blue = box->value();

}
void Color::showColor(QLabel *label) const
{
    QString labelName = label->objectName();
    if(labelName.contains("red"))
        showRed(label);
    else if(labelName.contains("green"))
        showGreen(label);
    else if(labelName.contains("blue"))
        showBlue(label);
    else
        refreshColor(label);
}
void Color::getColor(Color::RGB_8bit & redCurrent, Color::RGB_8bit & greenCurrent, Color::RGB_8bit & blueCurrent) const
{
    redCurrent = red;
    greenCurrent = green;
    blueCurrent = blue;
}
void Color::showRed(QLabel *label) const
{
     label->setStyleSheet("background-color: rgb(" + QString::number(red) + ", 0, 0);");
}
void Color::showGreen(QLabel * label) const
{
     label->setStyleSheet("background-color: rgb(0, "+ QString::number(green) + ", 0);");
}
void Color::showBlue(QLabel *label) const
{
     label->setStyleSheet("background-color: rgb(0, 0, " + QString::number(blue) + ");");
}
void Color::refreshColor(QLabel * labelColor) const
{
    QString redValue = QString::number(red);
    QString greenValue = QString::number(green);
    QString blueValue = QString::number(blue);
    labelColor->setStyleSheet("background-color: rgb("
                                    + redValue  + ","
                                    + greenValue + ","
                                    + blueValue + ");");
}
void Color::showCMYK(QLabel * cyanLabel,QLabel * magentaLabel, QLabel *  yellowLabel, QLabel *  blackLabel) const
{
    PERCENT cyan, magenta, yellow, black;
    toCMYK(cyan, magenta,  yellow, black);
    cyanLabel->setText(QString::number(cyan));
    magentaLabel->setText(QString::number(magenta));
    yellowLabel->setText(QString::number(yellow));
    blackLabel->setText(QString::number(black));
}

void Color::showCMYK(QLabel *label) const
{
    PERCENT cyan, magenta, yellow, black;
    toCMYK(cyan, magenta,  yellow, black);
    QString labelName = label->objectName();
    if(labelName.contains("cyan"))
             label->setText(QString::number(cyan));
    else if(labelName.contains("magenta"))
             label->setText(QString::number(magenta));
    else if(labelName.contains("yellow"))
             label->setText(QString::number(yellow));
    else if(labelName.contains("black"))
             label->setText(QString::number(black));
}
void Color::showHSV(QLabel * hueLabel, QLabel * saturationLabel, QLabel * valueLabel) const
{
    DEGREE hue;
    PERCENT saturation, value;
    toHSV(hue, saturation, value);
    hueLabel->setText(QString::number(hue));
    saturationLabel->setText(QString::number(saturation));
    valueLabel->setText(QString::number(value));
}

void Color::showHSV(QLabel *label) const
{
    DEGREE hue;
    PERCENT saturation, value;
    toHSV(hue, saturation, value);
    QString labelName = label->objectName();
    if(labelName.contains("hue"))
        label->setText(QString::number(hue));
    else if(labelName.contains("saturation"))
        label->setText(QString::number(saturation));
    else if(labelName.contains("value"))
        label->setText(QString::number(value));


}
void Color::showConvertedRGB(QLabel * redLabel, QLabel * greenLabel, QLabel * blueLabel) const
{
    redLabel->setText(QString::number(red));
    greenLabel->setText(QString::number(green));
    blueLabel->setText(QString::number(blue));
}


void Color::showResultProperties(QLabel * redLabel, QLabel * greenLabel, QLabel * blueLabel) const
{
    redLabel->setText(QString::number(red));
    greenLabel->setText(QString::number(green));
    blueLabel->setText(QString::number(blue));
}


void Color::showResult(QLabel * redLabel, QLabel * greenLabel, QLabel * blueLabel) const
{
    redLabel->setStyleSheet("background-color: rgb(" + QString::number(red) + ", 0, 0);");
    greenLabel->setStyleSheet("background-color: rgb(0, " + QString::number(green) + ", 0);");
    blueLabel->setStyleSheet("background-color: rgb(0, 0, " + QString::number(blue) + ");");
}

void Color::showProperties(QLabel *label) const
{
    QString labelName = label->objectName();
    if(labelName.contains("red"))
       label->setText(QString::number(red));
    else if(labelName.contains("green"))
       label->setText(QString::number(green));
    else if(labelName.contains("blue"))
        label->setText(QString::number(blue));
}



Color Color::operator*(double scalar) const
{
    RGB_8bit redTemp = 1, greenTemp = 1, blueTemp = 1;
    if(red)
        redTemp = red;
    if(green)
        greenTemp = green;
    if(blue)
        blueTemp = blue;
    Color newColor(redTemp, greenTemp, blueTemp);
    DEGREE hue = 0;
    PERCENT sat = 0, val = 0;
    newColor.toHSV(hue, sat, val);
    val = val * scalar;
    if(val > 1)
        val = 1;
    newColor.fromHSV(hue, sat, val);
    return newColor;
}

Color Color::operator!() const
{
   PERCENT cyanTemp = 0, magentaTemp = 0, yellowTemp = 0, blackTemp = 0;
   RGB_8bit redNew = 0, greenNew = 0, blueNew = 0;
   this->toCMYK(cyanTemp, magentaTemp, yellowTemp, blackTemp);
   redNew = cyanTemp * 255;
   greenNew = magentaTemp * 255;
   blueNew = yellowTemp * 255;
   Color newColor(redNew, greenNew, blueNew);
   return newColor;
}

Color::RGB_8bit &Color::operator[](int index)
{
    switch(index)
    {
    case Red:
        return red;
    case Green:
        return green;
    case Blue:
        return blue;
    }
}

Color::RGB_8bit Color::operator[](int index) const
{
    switch(index)
    {
    case Red:
        return red;
    case Green:
        return green;
    case Blue:
        return blue;
    }
    return -1;
}

Color::operator RGB_8bit() const
{
    return RGB_8bit((red + green + blue)/COLORS);
}
Color Color::operator+(const Color &summand) const
{
    Color tempColor;
    return tempColor.add(*this,summand);
}

Color Color::operator-(const Color &subtrahend) const
{
    Color tempColor;
    return tempColor.subtract(*this, subtrahend);
}
QSpinBox *operator>>(QSpinBox *box, Color &color1)
{
    color1.readColor(box);
    return box;
}
QLabel *operator<<(QLabel *label, const Color &color)
{

    if(isColor(label))
        color.refreshColor(label);
    else if(isHSV(label))
        color.showHSV(label);
    else if(isCMYK(label))
        color.showCMYK(label);
    else if(isLevel(label) )
        color.showColor(label);
    else if(isChannel(label) || isResult(label))
        color.showProperties(label);

    return label;
}
bool operator==(const Color & color1, const Color & color2)
{

    for(int i = 0; i < COLORS; ++i)
    {
        if(color1[i] != color2[i])
            return false;
    }
    return true;


}

bool isChannel(const QWidget * label)
{
    QString widgetName = label->objectName();
    return widgetName.contains("red") ||
           widgetName.contains("green") ||
           widgetName.contains("blue");
}

bool isValue(const QWidget * label)
{
    QString widgetName = label->objectName();
    return widgetName.contains("Value");
}
bool isHSV(const QWidget * label)
{
    QString widgetName = label->objectName();
     return widgetName.contains("hue") ||
            widgetName.contains("saturation") ||
            widgetName.contains("value");
}

bool isCMYK(const QWidget * label)
{
    QString widgetName = label->objectName();
    return widgetName.contains("cyan") ||
           widgetName.contains("magenta") ||
           widgetName.contains("yellow") ||
            widgetName.contains("black");
}



bool isColor(const QWidget * label)
{
    QString widgetName = label->objectName();
    return widgetName.contains("color") ||
            widgetName.contains("brightness") ||
            widgetName.contains("inverted") ||
            widgetName.contains("gray");
}


bool isResult(const QWidget *label)
{
    QString widgetName = label->objectName();
    return widgetName.contains("Result");
}

bool isLevel(const QWidget *label)
{
    QString widgetName = label->objectName();
    return widgetName.contains("Level");
}
