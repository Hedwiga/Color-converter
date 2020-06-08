/*
Filename: mainwindow.cpp
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "color.h"
#include <QStyle>
#include <QSpinBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Color colorTemp(0,0,0);
    QString colors[COLORS] = {"red", "green", "blue"};
    colorRGB = colorTemp;
    cyan = magenta = yellow = 0;
    black = 1;
    hue = saturation = value = 0;
    colorGray = colorInverted = colorBright = colorResult = color2 = color1 = colorTemp;
    for(int i = 0; i < COLORS; ++i)
    {
        for(int j = 0; j < COLORS; ++j)
        {
            QString boxName = colors[i] + QString::number(j);
            QSpinBox * box = findChild<QSpinBox *>(boxName);
            connect(box , QOverload<int>::of(&QSpinBox::valueChanged), this , &MainWindow::colorChanged);
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_CMYKtoRGB_clicked()
{
    ui->CMYKtoRGB->setEnabled(false);

    colorRGB.fromCMYK(cyan, magenta, yellow, black);
    showConverted();
}
void MainWindow::on_HSVtoRGB_clicked()
{
    ui->HSVtoRGB->setEnabled(false);

    colorRGB.fromHSV(hue, saturation, value);
    showConverted();
}
void MainWindow::on_sum_clicked()
{
    colorResult = color1 + color2;
    showResult();
}
void MainWindow::on_minus_clicked()
{
    colorResult = color1 - color2;
    showResult();
}
void MainWindow::colorChanged()
{
    QSpinBox * box = (QSpinBox *)sender();
    Color * temp = nullptr;
    QString boxName = box->objectName();
    int index = findIndex(boxName);

    switch(index)
    {
    case 0:
        initialiseConvertion();
        initialiseBrightness();

        temp = &colorRGB;
        ui->cyanValue << *temp;
        ui->magentaValue << *temp;
        ui->yellowValue << *temp;
        ui->blackValue << *temp;

        ui->hueValue << *temp;
        ui->saturationValue << *temp;
        ui->valueValue << *temp;
        break;
    case 1:
        initialiseOperations();
        temp = &color1;
        break;
    case 2:
        initialiseOperations();
        temp = &color2;
        break;
    }
    QString currentColor = defineColor(box);
    QLabel * level = findChild<QLabel *>(currentColor + "Level" + QString::number(index));
    QLabel * color = findChild<QLabel *>("color" + QString::number(index));
    box >> *temp;
    color << *temp;
    level << *temp;
}
QString MainWindow::defineColor(QWidget *widget)
{
    QString boxName = widget->objectName();
    if(boxName.contains("red"))
        return "red";
    else if(boxName.contains("green"))
        return "green";
    else if(boxName.contains("blue"))
        return "blue";
    return nullptr;
}
int MainWindow::findIndex(QString string)
{
    if(string.contains('0'))
        return 0;
    else if(string.contains('1'))
        return 1;
    else return 2;
}


void MainWindow::on_brightness0_valueChanged(double brightness)
{
    Color::DEGREE hueTemp = 0;
    Color::PERCENT satTemp = 0, valTemp = 0;
    colorBright = colorRGB * brightness;
    colorBright.toHSV(hueTemp, satTemp, valTemp);
    ui->brightness << colorBright;
}

void MainWindow::initialiseBrightness()
{
    Color::DEGREE hueTemp = 0;
    Color::PERCENT satTemp = 0, valTemp = 0;
    double maxScalar = 255;
    colorRGB.toHSV(hueTemp, satTemp, valTemp);

    ui->brightness0->setEnabled(true);
    ui->brightness0->setValue(1);
    // If current brightness is not too small,
    // Calculating maximum possible scale value
    if(valTemp > 0.0001)
        maxScalar = 1 / valTemp;
    ui->brightness0->setMaximum(maxScalar);
    ui->brightness << colorBright;
}
void MainWindow::initialiseConvertion()
{
    ui->toGray->setEnabled(true);
    ui->HSVtoRGB->setEnabled(true);
    ui->CMYKtoRGB->setEnabled(true);
    colorRGB.toCMYK(cyan, magenta, yellow, black);
    colorRGB.toHSV(hue, saturation, value);
}

void MainWindow::initialiseOperations()
{

    ui->equality->setStyle(ui->sum->style());
    ui->equality->setEnabled(true);
    ui->sum->setEnabled(true);
    ui->minus->setEnabled(true);
}

void MainWindow::on_invert_clicked()
{
    colorInverted  = !colorRGB;
    ui->inverted << colorInverted;
}

void MainWindow::showConverted()
{
    ui->redValue << colorRGB;
    ui->greenValue << colorRGB;
    ui->blueValue << colorRGB;
}

void MainWindow::showResult()
{
    ui->colorResult << colorResult;
    ui->redLevelResult << colorResult;
    ui->greenLevelResult << colorResult;
    ui->blueLevelResult << colorResult;
    ui->redResult << colorResult;
    ui->greenResult << colorResult;
    ui->blueResult << colorResult;
}

void MainWindow::on_equality_clicked()
{
    if(color1 == color2)
        ui->equality->setStyleSheet("font: 12pt \"Comic Sans MS\";"
                                  "background-color: rgb(170, 255, 127);");
    else
        ui->equality->setStyleSheet("font: 12pt \"Comic Sans MS\";"
                                  "background-color: rgb(255, 170, 127);");
    ui->equality->setEnabled(false);
}

void MainWindow::on_howMany_clicked()
{
    ui->amount->setText(QString::number(colorRGB.howManyColors()));
}

void MainWindow::on_toGray_clicked()
{
    Color::RGB_8bit grayScale = (Color::RGB_8bit)colorRGB;
    colorGray.setColor(grayScale, grayScale, grayScale);
    ui->gray << colorGray;
    ui->toGray->setEnabled(false);
}
