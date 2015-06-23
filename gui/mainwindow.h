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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QSortFilterProxyModel>

#include "ignoredobjectsdialog.h"
#include "qsanitizer.h"
#include "leaklistmodel.h"
#include "leaklistsortfilterproxymodel.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void openLog(const QString &logFile);

private slots:
    void on_action_Open_Log_triggered();
    void on_action_Quit_triggered();

    void on_lineEdit_textChanged();

    void on_comboBox_currentIndexChanged(int index);

    void on_action_Objects_triggered();
    void ignoredObjectsSetChanged(QSet<QString> ignoredObjects);

private:
    Ui::MainWindow *ui;
    IgnoredObjectsDialog *ignoredObjectsDialog;
    QSanitizer *sanitizer;
    LeakList leakList;
    LeakListModel *model;
    LeakListSortFilterProxyModel *filterModel;
    QSortFilterProxyModel *proxyModel;
    QSet<QString> ignoredObjects;
};

#endif // MAINWINDOW_H
