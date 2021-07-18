#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <QWidget>

namespace Ui {
class Symbols;
}

class Symbols : public QWidget
{
    Q_OBJECT

public:
    explicit Symbols(QWidget *parent = nullptr);
    ~Symbols();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Symbols *ui;
};

#endif // SYMBOLS_H
