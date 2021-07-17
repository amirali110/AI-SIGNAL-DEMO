#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "symbols.h"
#include "stoch_calculator.h"
#include <QTimer>
#include <QFile>
#include <QDir>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QDateTime>
#include <QInputDialog>
#include <QMessageBox>
#include <QVector>
#include <vector>





auto K_PERIOD = 14;
auto D_PERIOD = 2;
auto SMOOTH = 5;
auto TIMEFRAME_MINUTE = 1;
auto STATIC_LOW_LINE = 20;






MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow) {


  ui->setupUi(this);


  bool OK_SETTINGS = false;
  bool ok = false;


  auto setk = new QInputDialog;

  ::K_PERIOD = setk->getInt(this, tr("تنظیمات دوره ها"), tr("لطفا دوره K را وارد کنید"), 5, 1, 200, 1, &ok);

  if (ok == true) {

    bool ok1 = false;
    auto setd = new QInputDialog;
    ::D_PERIOD = setd->getInt(this, tr("تنظیمات دوره ها"), tr("لطفا دوره D را وارد کنید"), 5, 1, 200, 1, &ok1);

    if (ok1 == true) {

      bool ok2 = false;
      auto smooth = new QInputDialog;
      ::SMOOTH = smooth->getInt(this, tr("تنظیمات دوره ها"), tr("لطفا مقدار هموار سازی را وارد کنید."), 5, 1, 200, 1, &ok2);

      if (ok2 == true) {

        bool ok3 = false;
        auto timef = new QInputDialog;
        ::TIMEFRAME_MINUTE = timef->getInt(this, tr("تنظیمات تایم فریم"), tr("تایم فریم مورد نظر را برحسب دقیقه وارد کنید."), 5, 1, 5000, 1, &ok3);

        if (ok3 == true) OK_SETTINGS = true;

      }

    }

  }



  if (OK_SETTINGS == true) {


    QVector <QVector<QString>> prof;


    int i = 0;


    QFile read_symbols(QDir::currentPath() + "/Symbols.txt");
    read_symbols.open(QFile::ReadOnly | QFile::Text);

    std::vector<QString> symbol;

    while (!read_symbols.atEnd()) {

      symbol.push_back(QString(read_symbols.readLine()).remove('\n'));
      i++;

    }

    this->num = i;


    auto table_widget = new QTableWidget;

    table_widget->setGeometry(400, 300, 700, 500);
    table_widget->show();



    auto* stoch = new Stoch_calculator[i];
    auto timer = new QTimer;


    auto CHECK_FOR_SIGNAL = new bool[i];
    auto OPEN_BUY_POSITION = new bool[i];


    int x = 0;


    while (x < i) {

      OPEN_BUY_POSITION[x] = false;
      x++;

    }


    /*
     * spot trading algorithm
     *
     */


    connect(timer, &QTimer::timeout, [ this, stoch, i, symbol, table_widget, CHECK_FOR_SIGNAL, OPEN_BUY_POSITION]() {



      int x = 0;


      while (x < i) {


        stoch[x].set_smoothing(::SMOOTH);
        stoch[x].set_k_period(::K_PERIOD);

        double K = stoch[x].Get_K_stochastic(::TIMEFRAME_MINUTE, symbol[x]);
        double D = stoch[x].Get_D_stochastic(::D_PERIOD);

        if (K < D) CHECK_FOR_SIGNAL[x] = true;

        if (OPEN_BUY_POSITION[x] == false && CHECK_FOR_SIGNAL[x] == true && K > D && D != NULL && K < 20 && D < 20) {    //open long position algortihm


          QVector<QString> inf;



          auto item_1 = new QTableWidgetItem(symbol[x]);
          auto item_2 = new QTableWidgetItem("BUY");

          QString last_price = QString::number(stoch[x].Get_last_close_price());

          auto item_3 = new QTableWidgetItem(last_price);
          auto item_4 = new QTableWidgetItem(QDateTime::currentDateTime().toString());
          auto item_5 = new QTableWidgetItem("OK");

          inf.push_back(symbol[x]);
          inf.push_back(last_price);

          this->PROFIT.push_back(inf);


          item_1->setTextAlignment(Qt::AlignCenter);
          item_2->setTextAlignment(Qt::AlignCenter);
          item_3->setTextAlignment(Qt::AlignCenter);
          item_4->setTextAlignment(Qt::AlignCenter);
          item_5->setTextAlignment(Qt::AlignCenter);


          table_widget->setColumnCount(5);


          table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);


          table_widget->setColumnWidth(0, 150);
          table_widget->setColumnWidth(1, 100);
          table_widget->setColumnWidth(2, 150);
          table_widget->setColumnWidth(3, 200);
          table_widget->setColumnWidth(4, 100);


          table_widget->insertRow(this->raw);


          table_widget->setItem(raw, 0, item_1);
          table_widget->setItem(raw, 1, item_2);
          table_widget->setItem(raw, 2, item_3);
          table_widget->setItem(raw, 3, item_4);
          table_widget->setItem(raw, 4, item_5);


          CHECK_FOR_SIGNAL[x] = false;
          OPEN_BUY_POSITION[x] = true;



          this->raw++;

        }

        if (OPEN_BUY_POSITION[x] == true && K < D && K != NULL && D != NULL) {     //close long position algortihm

          auto item_1 = new QTableWidgetItem(symbol[x]);
          auto item_2 = new QTableWidgetItem("SELL");
          QString close_price = QString::number(stoch[x].Get_last_close_price());
          auto item_3 = new QTableWidgetItem(close_price);
          auto item_4 = new QTableWidgetItem(QDateTime::currentDateTime().toString());


          item_1->setTextAlignment(Qt::AlignCenter);
          item_2->setTextAlignment(Qt::AlignCenter);
          item_3->setTextAlignment(Qt::AlignCenter);
          item_4->setTextAlignment(Qt::AlignCenter);


          table_widget->setColumnCount(5);


          table_widget->setEditTriggers(QAbstractItemView::NoEditTriggers);


          table_widget->setColumnWidth(0, 150);
          table_widget->setColumnWidth(1, 100);
          table_widget->setColumnWidth(2, 150);
          table_widget->setColumnWidth(3, 200);
          table_widget->setColumnWidth(4, 100);


          table_widget->insertRow(this->raw);


          table_widget->setItem(raw, 0, item_1);
          table_widget->setItem(raw, 1, item_2);
          table_widget->setItem(raw, 2, item_3);
          table_widget->setItem(raw, 3, item_4);

          int y = 0;

          while (1) {


            if (this->PROFIT[y][0] == symbol[x]) {


              double profit = (close_price.toDouble() / this->PROFIT[y][1].toDouble()) - 1;

              double real_profit = (profit * 100) - 0.15;


              this->sum_profits += real_profit;

              auto item_5 = new QTableWidgetItem(QString::number(real_profit));

              item_5->setTextAlignment(Qt::AlignCenter);

              table_widget->setItem(raw, 4, item_5);

              this->PROFIT.remove(y);

              ui->profit_window->clear();
              ui->profit_window->append(QString::number(this->sum_profits));

              break;
            }

            y++;

          }


          CHECK_FOR_SIGNAL[x] = true;
          OPEN_BUY_POSITION[x] = false;


          this->raw++;



        }


        ui->text->append(QString::number(K) + "---->" + symbol[x]);
        ui->text->append(QString::number(D) + "---->" + symbol[x]);

        x++;

        this->line += 2;


        if (this->line > 300) {

          ui->text->clear();
          this->line = 0;

        }


      }
    });


    timer->start(::TIMEFRAME_MINUTE * 60000);

  } else {
    auto error = new QMessageBox;
    error->setText("لطفا تنظیمات را به طور کامل وارد کنید.");
    error->show();
  }




}






MainWindow::~MainWindow() {
  delete ui;
}



void MainWindow::on_pushButton_clicked() {

  auto symbol_Setting_window = new Symbols;
  symbol_Setting_window->show();


}











