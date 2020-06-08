/*
Filename: color.h
*/
#ifndef COLOR_H
#define COLOR_H
#define MIN(a,b) ((a) < (b)  ? (a) : (b) )
#define MIN3(a,b,c) MIN(MIN(a,b),(c))
#define MAX(a,b) ((a) > (b)  ? (a) : (b) )
#define MAX3(a,b,c) MAX(MAX(a,b),(c))
#define CHECK_INTERVAL(x) if((x < 0) || (x > 1)) { x = 0; }
#define COLORS 3
#include <cmath>
#include <QLabel>
#include <QSpinBox>

class Color
{
public:
    typedef unsigned char RGB_8bit;
    typedef unsigned int DEGREE;
    typedef double PERCENT;
    enum Colors{Red, Green, Blue};
    Color();
    Color(RGB_8bit red, RGB_8bit green, RGB_8bit blue);
    Color(PERCENT cyan, PERCENT magenta, PERCENT yellow, PERCENT black);
    virtual ~Color() {amountOfColors--;}

    Color add(Color summand1, Color summand2);
    Color subtract(Color minuend, Color subtrahend);

    void toHSV(DEGREE & hue, PERCENT & saturation, PERCENT & value) const;
    void fromHSV(DEGREE hue, PERCENT saturation, PERCENT value);
    void toCMYK(PERCENT & cyan, PERCENT & magenta, PERCENT & yellow, PERCENT & black) const;
    void fromCMYK(PERCENT cyan, PERCENT magenta, PERCENT yellow, PERCENT black);

    void getColor(RGB_8bit & red, RGB_8bit & green, RGB_8bit & blue) const;
    void setColor(RGB_8bit red, RGB_8bit green, RGB_8bit blue);
    void setRed(RGB_8bit red);
    void setGreen(RGB_8bit green);
    void setBlue(RGB_8bit blue);

    void readColor(const QSpinBox * box);
    void showColor(QLabel * label) const;
    void showRed(QLabel * label) const;
    void showGreen(QLabel * label) const;
    void showBlue(QLabel * label) const;
    void refreshColor(QLabel * labelColor) const;

    void showCMYK(QLabel * cyan, QLabel * magenta, QLabel * yellow, QLabel * black) const;
    void showCMYK(QLabel * label) const;

    void showHSV(QLabel * hueLabel, QLabel * saturationLabel, QLabel * valueLabel) const;
    void showHSV(QLabel * label) const;

    void showConvertedRGB(QLabel * redLabel, QLabel * greenLabel, QLabel * blueLabel) const;
    void showResultProperties(QLabel * redLabel, QLabel * greenLabel, QLabel * blueLabel) const;
    void showResult(QLabel * redLabel, QLabel * greenLabel, QLabel * blueLabel) const;

    void showProperties(QLabel * label) const;

    QString defineLabel(QWidget * widget);
    Color operator+(const Color &summand) const;
    Color operator-(const Color &subtrahend) const;
    Color operator*(double scalar) const;
    Color operator!() const;
    RGB_8bit &operator[](int index);
    RGB_8bit operator[](int index) const;
    explicit operator RGB_8bit() const;

    friend bool operator==(const Color & color1, const Color & color2);
    friend QLabel * operator<<(QLabel * label, const Color & color);
    friend QSpinBox *operator>>(QSpinBox * box, Color & color);


    static int amountOfColors;
    static int howManyColors() { return amountOfColors; }
private:
    RGB_8bit red, green, blue;
};

bool isChannel(const QWidget * widgetName);
bool isValue(const QWidget * widgetName);
bool isHSV(const QWidget * widgetName);
bool isCMYK(const QWidget * widgetName);
bool isResult(const QWidget * widgetName);
bool isColor(const QWidget * widgetName);
bool isLevel(const QWidget * widgetName);


#endif // COLOR_H
