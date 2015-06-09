/*
 * QSanitizer - Qt5 ui for *Sanitizer output
 * Copyright (C) 2015  Roman Lebedev
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qsanitizer.h"
#include "leaklistmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), sanitizer(new QSanitizer()),
      model(new LeakListModel(this))
{
    ui->setupUi(this);
    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete this->sanitizer;
    delete ui;
}

void MainWindow::openLog(const QString &logFile)
{
    QFileInfo fileInfo(logFile);
    if (!(fileInfo.exists() && fileInfo.isFile() && fileInfo.isReadable())) {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        return;
    }

    delete this->sanitizer;

    this->sanitizer = new QSanitizer(logFile);

    delete this->model;

    this->model = new LeakListModel(sanitizer->getLeaks(), this);

    ui->listView->setModel(this->model);
}

void MainWindow::on_action_Open_Log_triggered()
{
    QString fileName
        = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                       tr("Log Files (*.txt);;All Files (*)"));

    if (!fileName.isEmpty()) {
        this->openLog(fileName);
    }
}

void MainWindow::on_action_Quit_triggered() { this->close(); }
