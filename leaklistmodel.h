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

#ifndef LEAKLISTMODEL_H
#define LEAKLISTMODEL_H

#include <QAbstractListModel>

class LeakListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LeakListModel(QObject *parent = 0);
    explicit LeakListModel(const QStringList &strings, QObject *parent = 0);
    void setStringList(const QStringList &strings);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool insertRows(int position, int rows,
                    const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows,
                    const QModelIndex &index = QModelIndex());

private:
    QStringList LeakList;
};

#endif // LEAKLISTMODEL_H
