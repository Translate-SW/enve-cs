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

#ifndef SAVEDCOLORBUTTON_H
#define SAVEDCOLORBUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include "colorhelpers.h"

class SavedColorButton : public QWidget {
    Q_OBJECT
public:
    explicit SavedColorButton(const QColor& colorT,
                              QWidget *parent = nullptr);
    const QColor& getColor() const
    { return mColor; }
    void setSelected(const bool selected);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void enterEvent(QEvent*) {
        mHovered = true;
        update();
    }
    void leaveEvent(QEvent*) {
        mHovered = false;
        update();
    }
private:
    bool mHovered = false;
    bool mSelected = false;
    QColor mColor;
signals:
    void selected(QColor);
};

#endif // SAVEDCOLORBUTTON_H
