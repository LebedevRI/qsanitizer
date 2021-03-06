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

#ifndef IGNOREDOBJECTSDIALOG_H
#define IGNOREDOBJECTSDIALOG_H

#include <QDialog>
#include <QSortFilterProxyModel>

#include "ignoredobjectstablemodel.h"

namespace Ui
{
class IgnoredObjectsDialog;
}

class IgnoredObjectsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IgnoredObjectsDialog(QWidget *parent = 0);
    void setModel(const QMap<QString, int> &objects);
    void setIgnoredObjectsSet(QSet<QString> ignoredObjects);
    ~IgnoredObjectsDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void ignoredObjectsSetChanged(QSet<QString> ignoredObjects);

private:
    Ui::IgnoredObjectsDialog *ui;
    IgnoredObjectsTableModel *tableModel;
    QSortFilterProxyModel *proxyModel;
};

#endif // IGNOREDOBJECTSDIALOG_H
