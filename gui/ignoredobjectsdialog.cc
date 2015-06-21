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

#include "QSortFilterProxyModel"

#include "ignoredobjectsdialog.h"
#include "ui_ignoredobjectsdialog.h"

#include "ignoredobjectstablemodel.h"

IgnoredObjectsDialog::IgnoredObjectsDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::IgnoredObjectsDialog),
      tableModel(new IgnoredObjectsTableModel(parent)),
      proxyModel(new QSortFilterProxyModel(parent))
{
    ui->setupUi(this);
    proxyModel->setSourceModel(tableModel);
    ui->tableView->setModel(proxyModel);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(2, Qt::DescendingOrder);
}

void IgnoredObjectsDialog::setModel(const QMap<QString, int> &objects)
{
    tableModel->setModel(objects);
}

IgnoredObjectsDialog::~IgnoredObjectsDialog()
{
    delete ui;
    delete tableModel;
}

void IgnoredObjectsDialog::on_buttonBox_accepted()
{
    QSet<QString> ignoredObjects;

    ignoredObjects = this->tableModel->getIgnoredObjectsSet();

    emit ignoredObjectsSetChanged(ignoredObjects);
}

void IgnoredObjectsDialog::setIgnoredObjectsSet(QSet<QString> ignoredObjects)
{
    this->tableModel->setIgnoredObjectsSet(ignoredObjects);
}
