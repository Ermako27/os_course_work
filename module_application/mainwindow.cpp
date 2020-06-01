
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::connect_module(const std::string& str_write, const std::string& filename, std::vector<std::string>& answer)
{
    std::ofstream fw;
    fw.open(filename);
    if(fw.is_open())
    {
        fw << str_write;
        qDebug() << "Успешно записано " << QString(str_write.data()) << " в " << QString(filename.data());
        fw.close();
    }
    else
        return -1;

    std::ifstream fr(filename);
    if(fr.is_open())
    {
        std::string line;
        while (std::getline(fr, line))
        {
           qDebug() << QString(line.data());
           answer.push_back(line);
        }
        fr.close();
        return 0;
    }
    return -1;


}

void MainWindow::on_btn_tree_clicked()
{
    std::vector<std::string> answer;
    std::string filename("/proc/mod_proc_tree");
    std::string str_write("tree");

    int res = this->connect_module(str_write, filename, answer);

    if (res == 0)
    {
        ui->tb_tree->clear();
        for(std::string s : answer)
        {
            ui->tb_tree->append(QString(s.data()));
        }
    }
    else
    {
        QMessageBox::warning(this, "Модуль не доступен",
            "Невозможно обратиться к модулю.\nВозможно, он не загружен\nили используется другим процессом");
    }

}

void MainWindow::on_btn_files_clicked()
{

    std::vector<std::string> answer;
    std::string filename("/proc/mod_proc_files");
    std::string str_write(std::to_string(ui->spb_files->value()));

    int res = this->connect_module(str_write, filename, answer);

    if (res == 0)
    {
        ui->tb_files->clear();
        for(std::string s : answer)
        {
              ui->tb_files->append(QString(s.data()));
        }
    }
    else
    {
        QMessageBox::warning(this, "Модуль не доступен",
            "Невозможно обратиться к модулю.\nВозможно, он не загружен\nили используется другим процессом");
    }
}

void MainWindow::on_btn_mem_clicked()
{
    std::vector<std::string> answer;
    std::string filename("/proc/mod_proc_mem");
    std::string str_write(std::to_string(ui->spb_mem->value()));

    int res = this->connect_module(str_write, filename, answer);

    if (res == 0)
    {
        ui->tb_mem->clear();
        for(std::string s : answer)
        {
              ui->tb_mem->append(QString(s.data()));
        }
    }
    else
    {
        QMessageBox::warning(this, "Модуль не доступен",
            "Невозможно обратиться к модулю.\nВозможно, он не загружен\nили используется другим процессом");
    }
}
