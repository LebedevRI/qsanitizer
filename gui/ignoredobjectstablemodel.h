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

#ifndef IGNOREDOBJECTSTABLEMODEL_H
#define IGNOREDOBJECTSTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>

#include "leaklist.h"

typedef struct {
    QString object;
    int occurences;
    bool ignored;
} IgnoredObjectsTableModelData;

Q_DECLARE_METATYPE(IgnoredObjectsTableModelData)

class IgnoredObjectsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    IgnoredObjectsTableModel(QObject *parent);
    void setModel(const QMap<QString, int> &objects);
    int rowCount(const QModelIndex &parent
                 = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent
                    = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    QList<IgnoredObjectsTableModelData> model;
};

#endif // IGNOREDOBJECTSTABLEMODEL_H
