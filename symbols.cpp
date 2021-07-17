#include "symbols.h"
#include "ui_symbols.h"
#include <QFile>
#include <QInputDialog>
#include <QDir>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QAbstractItemView>




Symbols::Symbols(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::Symbols) {
  ui->setupUi(this);
}



Symbols::~Symbols() {
  delete ui;
}



void Symbols::on_pushButton_clicked() {

  bool ok = false;
  bool dublicate = false;

  auto Get_symbol = new QInputDialog;
  QString symbol = Get_symbol->getText(this, tr("ورود نماد جدید"), tr("نماد مورد نظر را با حروف بزرگ وارد کنید."), QLineEdit::EchoMode::Normal, tr("BTCUSDT"), &ok);



  if (ok == true) {

    QFile read_symbol(QDir::currentPath() + "/" + "Symbols.txt");
    read_symbol.open(QFile::ReadOnly | QFile::Text);


    while (!read_symbol.atEnd()) {

      if (QString(read_symbol.readLine()).remove('\n') == symbol) {

        dublicate = true;

        auto message = new QMessageBox;
        message->setText("نماد تکراری می باشد.");
        message->show();

        break;

      }


    }




    if (dublicate == false) {


      QFile write_symbol(QDir::currentPath() + "/" + "Symbols.txt");
      write_symbol.open(QFile::WriteOnly | QFile::Text | QFile::Append);


      QTextStream out(&write_symbol);

      out << symbol << Qt::endl;



      auto message = new QMessageBox;
      message->setText("نماد با موفقیت افزوده شد.");
      message->show();



    }

  }

}





void Symbols::on_pushButton_2_clicked() {



  auto table_widget = new QTableWidget;

  table_widget->setGeometry(400, 150, 500, 500);
  table_widget->setColumnCount(2);
  table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
  table_widget->setColumnWidth(0, 150);
  table_widget->setColumnWidth(1, 350);


  QFile read_symbols(QDir::currentPath() + "/Symbols.txt");
  read_symbols.open(QFile::ReadOnly | QFile::Text);


  int i = 0;


  while (!read_symbols.atEnd()) {


    auto item_1 = new QTableWidgetItem(tr("Symbol :"));
    auto item_2 = new QTableWidgetItem(QString(read_symbols.readLine()).remove('\n'));

    item_1->setTextAlignment(Qt::AlignCenter);
    item_2->setTextAlignment(Qt::AlignCenter);
    table_widget->insertRow(i);
    table_widget->setItem(i, 0, item_1);
    table_widget->setItem(i, 1, item_2);


    i++;


  }


  table_widget->show();


}




void Symbols::on_pushButton_3_clicked() {

  bool rem;

  rem = QFile::remove(QDir::currentPath() + "/Symbols.txt");

  if (rem == true) {

    auto message = new QMessageBox;
    message->setText(" لیست نماد ها با موفقیت حذف شد.");
    message->show();

  }

}











