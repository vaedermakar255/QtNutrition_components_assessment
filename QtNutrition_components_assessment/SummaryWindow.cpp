#include "SummaryWindow.h"
#include <QtWidgets/QApplication>
//#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtCharts/QChartView>
#include "donutbreakdownchart.h"

SummaryWindow::SummaryWindow(Summary& summary, QMainWindow& mainWindow, QWidget* parent)
    : QFrame{parent}, ui{new Ui_Frame}, summary{summary}//, mainWindow{mainWindow}
{
    ui->setupUi(this);

    connect(ui->pushButtonSave, SIGNAL(clicked()),
            this, SLOT(pushButtonSave_clicked())
            );
    connect(ui->pushButtonShowChart, SIGNAL(clicked()),
            this, SLOT(pushButtonShowChart_clicked())
            );

    QPixmap bkgnd("../Backgrounds/Background2.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //setMinimumSize(QSize(1183, 773))


    showResults();
    this->setEnabled(true);
    this->setMinimumWidth(570);

}
//======================================================================================================
void SummaryWindow::showResults()
{
    const uint8_t precision = 2;

    for (uint32_t i = 0; i < AMI; ++i)
    {
        if (i == 0)
            ui->textEdit->append("Валин:\n");
        if (i == 1)
            ui->textEdit->append("Гистидин:\n");
        if (i == 2)
            ui->textEdit->append("Изолейцин:\n");
        if (i == 3)
            ui->textEdit->append("Лейцин:\n");
        if (i == 4)
            ui->textEdit->append("Лизин:\n");
        if (i == 5)
            ui->textEdit->append("Метионин+Цистеин:\n");
        if (i == 6)
            ui->textEdit->append("Треонин:\n");
        if (i == 7)
            ui->textEdit->append("Триптофан:\n");
        if (i == 8)
            ui->textEdit->append("Фенилаланин+Тирозин:\n");

        if (summary.comp_num == 1)
            ui->textEdit->append(QString("Аминокислота на 100г белка = %1\n")
                                 .arg(summary.recount[i][0], 0, 'f', precision));
        if (summary.comp_num == 2)
        {
            ui->textEdit->append(QString("Аминокислота на 100г белка в 1 компоненте = %1\n")
                                 .arg(summary.recount[i][0], 0, 'f', precision));
            ui->textEdit->append(QString("Аминокислота на 100г белка в 2 компоненте = %1\n")
                                 .arg(summary.recount[i][1], 0, 'f', precision));
        }
        if (summary.comp_num == 3)
        {
            ui->textEdit->append(QString("Аминокислота на 100г белка в 1 компоненте = %1\n")
                                 .arg(summary.recount[i][0], 0, 'f', precision));
            ui->textEdit->append(QString("Аминокислота на 100г белка в 2 компоненте = %1\n")
                                 .arg(summary.recount[i][1], 0, 'f', precision));
            ui->textEdit->append(QString("Аминокислота на 100г белка в 3 компоненте = %1\n")
                                 .arg(summary.recount[i][2], 0, 'f', precision));
        }
        if (summary.comp_num == 4)
        {
            ui->textEdit->append(QString("Аминокислота на 100г белка в 1 компоненте = %1\n")
                                 .arg(summary.recount[i][0], 0, 'f', precision));
            ui->textEdit->append(QString("Аминокислота на 100г белка в 2 компоненте = %1\n")
                                 .arg(summary.recount[i][1], 0, 'f', precision));
            ui->textEdit->append(QString("Аминокислота на 100г белка в 3 компоненте = %1\n")
                                 .arg(summary.recount[i][2], 0, 'f', precision));
            ui->textEdit->append(QString("Аминокислота на 100г белка в 4 компоненте = %1\n")
                                 .arg(summary.recount[i][3], 0, 'f', precision));
        }
        if (summary.comp_num == 5)
        {
            ui->textEdit->append(QString("Аминокислота на 100г белка в 1 компоненте = %1\n")
                                 .arg(summary.recount[i][0], 0, 'f', precision));
            ui->textEdit->append(QString("Аминокислота на 100г белка в 2 компоненте = %1\n")
                                 .arg(summary.recount[i][1], 0, 'f', precision));
            ui->textEdit->append(QString("Аминокислота на 100г белка в 3 компоненте = %1\n")
                                 .arg(summary.recount[i][2], 0, 'f', precision));
            ui->textEdit->append(QString("Аминокислота на 100г белка в 4 компоненте = %1\n")
                                 .arg(summary.recount[i][3], 0, 'f', precision));
            ui->textEdit->append(QString("Аминокислота на 100г белка в 5 компоненте = %1\n")
                                 .arg(summary.recount[i][4], 0, 'f', precision));
        }

        ui->textEdit->append(QString("Аминокислота в продукте = %1\n")
                             .arg(summary.akp[i], 0, 'f', precision) +
                QString("Аминокислотный скор = %1\n")
                             .arg(summary.aminoacidskor[i], 0, 'f', precision) +
                QString("Коэффициент рациональности = %1\n")
                             .arg(summary.koef_ration[i], 0, 'f', precision)
                             );

        ui->textEdit->append(QString("Коэффициент сбалансированности = %1\n")
                             .arg(summary.fatty_acid_per_100g[i], 0, 'f', precision));
        ui->textEdit->append("=================================================");

    } // for

    ui->textEdit->append("==========ОЦЕНКА БЕЛКОВОЙ СОСТАВЛЯЮЩЕЙ:==========\n\n");
    ui->textEdit->append(QString("Коэффициент разбалансированности = %1\n")
                         .arg(summary.kras, 0, 'f', precision));
    ui->textEdit->append(QString("Биологическая ценность = %1\n")
                         .arg(summary.biological_value, 0, 'f', precision));
    ui->textEdit->append(QString("Коэффициент рациональности аминокислотного состава = %1\n")
                         .arg(summary.amino_acid_comp_ratio_coef, 0, 'f', precision));
    ui->textEdit->append(QString("Показатель сопоставимой избыточности = %1\n")
                         .arg(summary.comparable_redundancy_ratio, 0, 'f', precision));
    ui->textEdit->append(QString("Индекс сбалансированности = %1\n")
                         .arg(summary.balance_index, 0, 'f', precision));
    ui->textEdit->append(QString("Коэффициент сбалансированности белковой составляющей = %1\n")
                         .arg(summary.k_general, 0, 'f', precision));

    if (summary.k_general >= 0.0 && summary.k_general <= 0.2)
    {
        ui->textEdit->setTextColor(QColor(Qt::darkRed));
        printf("Шкала желательности Харрингтона - очень низкая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }

    if (summary.k_general > 0.2 && summary.k_general <= 0.37)
    {
        ui->textEdit->setTextColor(QColor(Qt::red));
        ui->textEdit->append("Шкала желательности Харрингтона - низкая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }

    if (summary.k_general > 0.37 && summary.k_general <= 0.64)
    {
        ui->textEdit->setTextColor(QColor(Qt::yellow));
        ui->textEdit->append("Шкала желательности Харрингтона - средняя\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }


    if (summary.k_general > 0.64 && summary.k_general <= 0.8)
    {
        ui->textEdit->setTextColor(QColor(Qt::green));
        ui->textEdit->append("Шкала желательности Харрингтона - высокая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }

    if (summary.k_general > 0.8 && summary.k_general <= 1.0)
    {
        ui->textEdit->setTextColor(QColor(Qt::green));
        ui->textEdit->append("Шкала желательности Харрингтона - очень высокая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }

    ui->textEdit->append("=================================================");

    /*ВЫВОД ЛИПИДОВ*/
    for (uint32_t i = 0; i < LIP_PROP; ++i)
    {
        if (summary.comp_num == 1 && i == 0)
            ui->textEdit->append(QString("Насыщенных жирных кислот = %1\n")
                                 .arg(summary.recount_lip[i][0], 0, 'f', precision));
        if (summary.comp_num == 1 && i == 1)
            ui->textEdit->append(QString("Мононенасыщенных жирных кислот = %1\n")
                                 .arg(summary.recount_lip[i][0], 0, 'f', precision));
        if (summary.comp_num == 1 && i == 2)
            ui->textEdit->append(QString("Полиненасыщенных жирных кислот = %1\n")
                                 .arg(summary.recount_lip[i][0], 0, 'f', precision));
        if (summary.comp_num == 1 && i == 3)
            ui->textEdit->append(QString("Омега-6 = %1\n")
                                 .arg(summary.recount_lip[i][0], 0, 'f', precision));
        if (summary.comp_num == 1 && i == 4)
            ui->textEdit->append(QString("Омега-3 = %1\n")
                                 .arg(summary.recount_lip[i][0], 0, 'f', precision));

        if (summary.comp_num == 2)
        {
            if (i == 0)
                ui->textEdit->append(QString("Насыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Насыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision));
            if (i == 1)
                ui->textEdit->append(QString("Мононенасыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Мононенасыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision));
            if (i == 2)
                ui->textEdit->append(QString("Полиненасыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Полиненасыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision));
            if (i == 3)
                ui->textEdit->append(QString("Омега-6 в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Омега-6 в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision));
            if (i == 4)
                ui->textEdit->append(QString("Омега-3 в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Омега-3 в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision));
        }
        if (summary.comp_num == 3)
        {
            if (i == 0)
                ui->textEdit->append(QString("Насыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Насыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Насыщенных жирных кислот в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision));
            if (i == 1)
                ui->textEdit->append(QString("Мононенасыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Мононенасыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Мононенасыщенных жирных кислот в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision));
            if (i == 2)
                ui->textEdit->append(QString("Полиненасыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Полиненасыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Полиненасыщенных жирных кислот в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision));
            if (i == 3)
                ui->textEdit->append(QString("Омега-6 в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Омега-6 в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Омега-6 в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision));
            if (i == 4)
                ui->textEdit->append(QString("Омега-3 в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Омега-3 в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Омега-3 в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision));
        }
        if (summary.comp_num == 4)
        {
            if (i == 0)
                ui->textEdit->append(QString("Насыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Насыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Насыщенных жирных кислот в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision) +
                        QString("Насыщенных жирных кислот в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][3], 0, 'f', precision));
            if (i == 1)
                ui->textEdit->append(QString("Мононенасыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Мононенасыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Мононенасыщенных жирных кислот в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision) +
                        QString("Мононенасыщенных жирных кислот в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][3], 0, 'f', precision));
            if (i == 2)
                ui->textEdit->append(QString("Полиненасыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Полиненасыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Полиненасыщенных жирных кислот в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision) +
                        QString("Полиненасыщенных жирных кислот в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][3], 0, 'f', precision));
            if (i == 3)
                ui->textEdit->append(QString("Омега-6 в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Омега-6 в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Омега-6 в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision) +
                        QString("Омега-6 в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][3], 0, 'f', precision));
            if (i == 4) // ПОЧЕМУ 5???
                ui->textEdit->append(QString("Омега-3 в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Омега-3 в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Омега-3 в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision) +
                        QString("Омега-3 в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][3], 0, 'f', precision));
        }
        if (summary.comp_num == 5)
        {
            if (i == 0)
                ui->textEdit->append(QString("Насыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Насыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Насыщенных жирных кислот в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision) +
                        QString("Насыщенных жирных кислот в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][3], 0, 'f', precision) +
                        QString("Насыщенных жирных кислот в 5 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][4], 0, 'f', precision));
            if (i == 1)
                ui->textEdit->append(QString("Мононенасыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Мононенасыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Мононенасыщенных жирных кислот в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision) +
                        QString("Мононенасыщенных жирных кислот в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][3], 0, 'f', precision) +
                        QString("Мононенасыщенных жирных кислот в 5 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][4], 0, 'f', precision));
            if (i == 2)
                ui->textEdit->append(QString("Полиненасыщенных жирных кислот в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Полиненасыщенных жирных кислот в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Полиненасыщенных жирных кислот в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision) +
                        QString("Полиненасыщенных жирных кислот в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][3], 0, 'f', precision) +
                        QString("Полиненасыщенных жирных кислот в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][4], 0, 'f', precision));
            if (i == 3)
                ui->textEdit->append(QString("Омега-6 в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Омега-6 в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Омега-6 в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision) +
                        QString("Омега-6 в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][3], 0, 'f', precision) +
                        QString("Омега-6 в 5 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][4], 0, 'f', precision));
            if (i == 4)
                ui->textEdit->append(QString("Омега-3 в 1 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][0], 0, 'f', precision) +
                        QString("Омега-3 в 2 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][1], 0, 'f', precision) +
                        QString("Омега-3 в 3 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][2], 0, 'f', precision) +
                        QString("Омега-3 в 4 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][3], 0, 'f', precision) +
                        QString("Омега-3 в 5 компоненте = %1\n")
                                     .arg(summary.recount_lip[i][4], 0, 'f', precision));
        }
        ui->textEdit->append(QString("Жирных кислот в 100г продукта = %1\n").arg(summary.ratio_calc[i], 0, 'f', precision));
        ui->textEdit->append("=================================================");
    } // for

    ui->textEdit->append("==========ОЦЕНКА ЛИПИДНОЙ СОСТАВЛЯЮЩЕЙ:==========\n");
    ui->textEdit->append(QString("Коэффициент жирнокислотного соответствия (при i=3) = %1\n").arg(summary.fattyAcidComplianceResult1));
    ui->textEdit->append(QString("Коэффициент жирнокислотного соответствия (при i=5) = %1\n").arg(summary.fattyAcidComplianceResult2));

    if (summary.fattyAcidComplianceResult1 >= 0.0 && summary.fattyAcidComplianceResult1 <= 0.2)
    {
        ui->textEdit->setTextColor(QColor(Qt::darkRed));
        printf("Шкала желательности Харрингтона (при i=3) - очень низкая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }

    if (summary.fattyAcidComplianceResult1 > 0.2 && summary.fattyAcidComplianceResult1 <= 0.37)
    {
        ui->textEdit->setTextColor(QColor(Qt::red));
        ui->textEdit->append("Шкала желательности Харрингтона (при i=3) - низкая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }

    if (summary.fattyAcidComplianceResult1 > 0.37 && summary.fattyAcidComplianceResult1 <= 0.64)
    {
        ui->textEdit->setTextColor(QColor(Qt::yellow));
        ui->textEdit->append("Шкала желательности Харрингтона (при i=3) - средняя\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }


    if (summary.fattyAcidComplianceResult1 > 0.64 && summary.fattyAcidComplianceResult1 <= 0.8)
    {
        ui->textEdit->setTextColor(QColor(Qt::green));
        ui->textEdit->append("Шкала желательности Харрингтона (при i=3) - высокая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }

    if (summary.fattyAcidComplianceResult1 > 0.8 && summary.fattyAcidComplianceResult1 <= 1.0)
    {
        ui->textEdit->setTextColor(QColor(Qt::green));
        ui->textEdit->append("Шкала желательности Харрингтона (при i=3) - очень высокая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }
    //-------------------------------------------------------------------------------------------------
    if (summary.fattyAcidComplianceResult2 >= 0.0 && summary.fattyAcidComplianceResult2 <= 0.2)
    {
        ui->textEdit->setTextColor(QColor(Qt::darkRed));
        printf("Шкала желательности Харрингтона (при i=3) - очень низкая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }

    if (summary.fattyAcidComplianceResult2 > 0.2 && summary.fattyAcidComplianceResult2 <= 0.37)
    {
        ui->textEdit->setTextColor(QColor(Qt::red));
        ui->textEdit->append("Шкала желательности Харрингтона (при i=3) - низкая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }

    if (summary.fattyAcidComplianceResult2 > 0.37 && summary.fattyAcidComplianceResult2<= 0.64)
    {
        ui->textEdit->setTextColor(QColor(Qt::yellow));
        ui->textEdit->append("Шкала желательности Харрингтона (при i=3) - средняя\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }


    if (summary.fattyAcidComplianceResult2 > 0.64 && summary.fattyAcidComplianceResult2 <= 0.8)
    {
        ui->textEdit->setTextColor(QColor(Qt::green));
        ui->textEdit->append("Шкала желательности Харрингтона (при i=3) - высокая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }

    if (summary.fattyAcidComplianceResult2 > 0.8 && summary.fattyAcidComplianceResult2 <= 1.0)
    {
        ui->textEdit->setTextColor(QColor(Qt::green));
        ui->textEdit->append("Шкала желательности Харрингтона (при i=3) - очень высокая\n");
        ui->textEdit->setTextColor(QColor(Qt::black));
    }


    ui->textEdit->append("=================================================");

}
//======================================================================================================
void SummaryWindow::closeEvent(QCloseEvent* event)
{
    Q_UNUSED(event);



}

//======================================================================================================
void SummaryWindow::pushButtonSave_clicked()
{

}
//======================================================================================================
void SummaryWindow::pushButtonShowChart_clicked()
{
    QVector<QPieSeries*> proteins_comps(summary.comp_num);
    QVector<QPieSeries*> lipids_comps(summary.comp_num);

    DonutBreakdownChart* donutBreakdownProteins = nullptr;
    DonutBreakdownChart* donutBreakdownLipids = nullptr;

    QVector<QColor> colors_comps(MAX_COMP);
    colors_comps << QColor(Qt::red)
                 << QColor(Qt::blue)
                 << QColor(Qt::green)
                 << QColor(Qt::cyan)
                 << QColor(Qt::darkMagenta);






    if (summary.comp_num == 1)
    {
        uint32_t allAKP = 0;
        for (const auto& current: summary.akp)
        {
            allAKP += current;
        }
        proteins_comps[0] = new QPieSeries(this);
        proteins_comps[0]->setName("Протеины");
        proteins_comps[0]->append("1 Компонент", allAKP);
        //-------------------------------------------------------------------------------------------------
        uint32_t allFatty_acid_per_100g = 0;
        for (const auto& current: summary.fatty_acid_per_100g)
        {
            allFatty_acid_per_100g += current;
        }
        lipids_comps[0] = new QPieSeries(this);
        lipids_comps[0]->setName("Липиды");
        lipids_comps[0]->append("1 Компонент", allFatty_acid_per_100g);
    }
    if (summary.comp_num == 2)
    {
        uint32_t allAKP1 = 0;
        uint32_t allAKP2 = 0;
        for (const auto& current: summary.akp)
        {
            allAKP1 += current;
        }

        proteins_comps[0] = new QPieSeries(this);
        proteins_comps[0]->setName("Протеины");
        //proteins_comps[0]->append("1 Компонент", allAKP);
        //-------------------------------------------------------------------------------------------------
        uint32_t allFatty_acid_per_100g = 0;
        for (const auto& current: summary.fatty_acid_per_100g)
        {
            allFatty_acid_per_100g += current;
        }
        lipids_comps[0] = new QPieSeries(this);
        lipids_comps[0]->setName("Липиды");
        lipids_comps[0]->append("1 Компонент", allFatty_acid_per_100g);
    }



    donutBreakdownProteins = new DonutBreakdownChart;
    donutBreakdownProteins->setParent(this);
    donutBreakdownProteins->setAnimationOptions(QChart::AllAnimations);
    donutBreakdownProteins->setTitle("Оценка белковой составляющей продукта");
    donutBreakdownProteins->legend()->setAlignment(Qt::AlignRight);

    donutBreakdownLipids = new DonutBreakdownChart;
    donutBreakdownLipids->setParent(this);
    donutBreakdownLipids->setAnimationOptions(QChart::AllAnimations);
    donutBreakdownLipids->setTitle("Оценка липидной составляющей продукта");
    donutBreakdownLipids->legend()->setAlignment(Qt::AlignRight);

    if (summary.comp_num == 1)
    {
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[0], colors_comps[0]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[0], colors_comps[0]);
    }
    if (summary.comp_num == 2)
    {
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[0], colors_comps[0]);
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[1], colors_comps[1]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[0], colors_comps[0]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[1], colors_comps[1]);
    }
    if (summary.comp_num == 3)
    {
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[0], colors_comps[0]);
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[1], colors_comps[1]);
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[2], colors_comps[2]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[0], colors_comps[0]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[1], colors_comps[1]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[2], colors_comps[2]);
    }
    if (summary.comp_num == 4)
    {
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[0], colors_comps[0]);
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[1], colors_comps[1]);
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[2], colors_comps[2]);
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[3], colors_comps[3]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[0], colors_comps[0]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[1], colors_comps[1]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[2], colors_comps[2]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[3], colors_comps[3]);
    }
    if (summary.comp_num == 5)
    {
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[0], colors_comps[0]);
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[1], colors_comps[1]);
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[2], colors_comps[2]);
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[3], colors_comps[3]);
        donutBreakdownProteins->addBreakdownSeries(proteins_comps[4], colors_comps[4]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[0], colors_comps[0]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[1], colors_comps[1]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[2], colors_comps[2]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[3], colors_comps[3]);
        donutBreakdownLipids->addBreakdownSeries(lipids_comps[4], colors_comps[4]);
    }








    QChartView *chartViewProteins = new QChartView;
    chartViewProteins->setChart(donutBreakdownProteins);
    chartViewProteins->setRenderHint(QPainter::Antialiasing);
    QPixmap bkgnd("../Backgrounds/Background3.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    //palette.setBrush(QPalette::Background, bkgnd);
    chartViewProteins->setBackgroundBrush(bkgnd);

    QChartView *chartViewLipids = new QChartView;
    chartViewLipids->setChart(donutBreakdownLipids);
    chartViewLipids->setRenderHint(QPainter::Antialiasing);
    //palette.setBrush(QPalette::Background, bkgnd);
    chartViewLipids->setBackgroundBrush(bkgnd);


    QRect rec = QApplication::desktop()->screenGeometry();
    uint32_t global_height = rec.height();
    uint32_t global_width = rec.width();

    chartViewProteins->setWindowTitle("Протеины");
    chartViewProteins->resize(800, 500);
    chartViewProteins->move(x()-500, y());
    chartViewProteins->show();

    chartViewLipids->setWindowTitle("Липиды");
    chartViewLipids->resize(800, 500);
    chartViewLipids->move(x()+300, y());
    chartViewLipids->show();
}
//======================================================================================================
SummaryWindow::~SummaryWindow()
{
    delete ui;
}