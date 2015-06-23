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
#include <QSortFilterProxyModel>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ignoredobjectsdialog.h"

#include "qsanitizer.h"
#include "leaklistmodel.h"
#include "leaklistsortfilterproxymodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      ignoredObjectsDialog(new IgnoredObjectsDialog(this)),
      sanitizer(new QSanitizer()), model(new LeakListModel(this)),
      filterModel(new LeakListSortFilterProxyModel(this)),
      proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    ui->comboBox->addItem(tr("Regular expression"), QRegExp::RegExp);
    ui->comboBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    ui->comboBox->addItem(tr("Fixed string"), QRegExp::FixedString);

    this->model->setLeakList(&(this->leakList));
    this->filterModel->setLeakList(&(this->leakList));
    this->filterModel->setLeakList(&(this->leakList));
    this->filterModel->setIgnoredObjects(&(this->ignoredObjects));

    filterModel->setSourceModel(model);

    proxyModel->setSourceModel(filterModel);
    ui->listView->setModel(proxyModel);

    connect(ignoredObjectsDialog,
            SIGNAL(ignoredObjectsSetChanged(QSet<QString>)), this,
            SLOT(ignoredObjectsSetChanged(QSet<QString>)));
}

MainWindow::~MainWindow()
{
    delete this->proxyModel;
    delete this->filterModel;
    delete this->model;
    delete this->sanitizer;
    delete this->ignoredObjectsDialog;
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

    this->leakList = this->sanitizer->getLeaks();
    this->model->setLeakList(&(this->leakList));
    this->filterModel->setIgnoredObjects(&(this->ignoredObjects));
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

void MainWindow::on_lineEdit_textChanged()
{
    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(
        ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt());

    QRegExp regExp(ui->lineEdit->text(), Qt::CaseInsensitive, syntax);
    proxyModel->setFilterRegExp(regExp);
}

void MainWindow::on_comboBox_currentIndexChanged(int /* index */)
{
    this->on_lineEdit_textChanged();
}

void MainWindow::on_action_Objects_triggered()
{
    ignoredObjectsDialog->setModel(this->sanitizer->getLeaks().getObjectsMap());
    ignoredObjectsDialog->setIgnoredObjectsSet(this->ignoredObjects);
    ignoredObjectsDialog->show();
    ignoredObjectsDialog->raise();
    ignoredObjectsDialog->activateWindow();
}

void MainWindow::ignoredObjectsSetChanged(QSet<QString> objects)
{
    this->ignoredObjects = objects;
    this->filterModel->setIgnoredObjects(&(this->ignoredObjects));
}
