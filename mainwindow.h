#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fifo.h"
#include "tourniquet.h"
#include "priorite_sans_requisition.h"
#include "pcte.h"
#include "pcter.h"
#include "Priorite_avec_requisition.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Fifo f ;
    Pcte P ;
    Tourniquet T ;
    PrioriteSansRequisition Pr ;
    PrioriteAvecRequisition PrR ;
    Pcter PR ;



    // int tab1[5] = {2,3,1,1,2} ;
    // int tab2[6] = {1,1,2,2,1} ;
    // int tab3[4] = {3,3,2} ;
    // int tab4[3] = {1,2,2} ;

    int tab1[3] = {2, 3, 1};
    int tab2[3] = {4, 1, 2};
    int tab3[3] = {1, 1, 3};
    int tab4[2] = {2,2};

    Processus p1;
    Processus p2;
    Processus p3;
    Processus p4;

    bool soumissionAjout = false ;
    bool soumissionRetrait = true ;
    int quant ;

public:
    MainWindow(QWidget *parent = nullptr);
    void viderTables(QTableWidget *table1, QTableWidget *table2, QTableWidget *table3, QTableWidget *table4) ;
    void calculTemps() ;
    void tempsProcess( QTableWidget* tab ,  Processus **tabProcessus ,int col) ;


    void prepareFIFO() ;
    void preparePCTE() ;
    void preparePRIOITE() ;
    void prepareTOUNIQUET() ;
    void preparePRIORITEPREAMPTIVE();
     void preparePCTEPREAMPTIVE();

    ~MainWindow();


private slots:

    void on_textEdit_7_cursorPositionChanged();

    void on_pushButton_5_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_16_clicked();

    void on_label_linkActivated(const QString &link);

    void on_commandLinkButton_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_46_clicked();

    void on_actionajout_triggered();

    void on_actionretire_triggered();

    void on_action1_triggered();

    void on_action2_triggered();

    void on_action3_triggered();

    void on_action4_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
