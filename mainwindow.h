/*
Filename: mainwindow.h
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "color.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void colorChanged();
private slots:
    void on_CMYKtoRGB_clicked();
    void on_HSVtoRGB_clicked();
    void on_sum_clicked();
    void on_minus_clicked();
    QString defineColor(QWidget * widget);
    int findIndex(QString string);
    void on_brightness0_valueChanged(double arg1);
    void initialiseBrightness();
    void on_invert_clicked();
    void showConverted();
    void showResult();
    void initialiseConvertion();
    void initialiseOperations();

    void on_equality_clicked();

    void on_howMany_clicked();

    void on_toGray_clicked();

private:
    Ui::MainWindow *ui;
    Color colorGray;
    Color colorInverted;
    Color colorBright;
    Color colorRGB;
    Color color1, color2, colorResult;
    Color::PERCENT cyan, magenta, yellow, black;
    Color::PERCENT saturation, value;
    Color::DEGREE hue;
};
#endif // MAINWINDOW_H
