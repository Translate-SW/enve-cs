// enve - 2D animations software
// Copyright (C) 2016-2020 Maurycy Liebner

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef FAKEMENUBAR_H
#define FAKEMENUBAR_H

#include <QHBoxLayout>
#include <QMenu>

class FakeMenuBar : public QWidget {
public:
    explicit FakeMenuBar(QWidget* const parent = nullptr);

    void addSeparator();

    QMenu* addMenu(const QString& title);
    QMenu* addMenu(const QIcon& icon, const QString& title);
    void addMenu(QMenu * const menu);

    QAction* addAction(const QString& title);
    QAction* addAction(const QIcon& icon, const QString& title);
    void addAction(QAction * const action);
private:
    QHBoxLayout* mActsLayout;
};

#endif // FAKEMENUBAR_H
