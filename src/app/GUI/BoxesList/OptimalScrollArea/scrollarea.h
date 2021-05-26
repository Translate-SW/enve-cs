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

#ifndef SCROLLAREA_H
#define SCROLLAREA_H
#include <QScrollArea>

class ScrollArea : public QScrollArea {
    Q_OBJECT
public:
    ScrollArea(QWidget * const parent = nullptr);

    void scrollBy(const int x, const int y);
    void callWheelEvent(QWheelEvent *event);
signals:
    void heightChanged(int);
    void widthChanged(int);
protected:
    void resizeEvent(QResizeEvent *e);
private:
    int mLastHeight = 0;
    int mLastWidth = 0;
};

#endif // SCROLLAREA_H
