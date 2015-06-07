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

#include <QApplication>
#include <QCommandLineParser>
#include <QFileInfo>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.addPositionalArgument(
        "log", QCoreApplication::translate("main", "Log file to parse."));
    parser.process(a);

    const QStringList args = parser.positionalArguments();

    MainWindow w;
    w.show();

    if (!args.empty()) {
        QFileInfo logFile(args.at(0));
        if (logFile.exists() && logFile.isFile() && logFile.isReadable()) {
            w.openLog(args.at(0));
        }
    }

    return a.exec();
}
