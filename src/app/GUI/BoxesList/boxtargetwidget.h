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

#ifndef BOXTARGETWIDGET_H
#define BOXTARGETWIDGET_H

#include <QWidget>
class BoundingBox;
class BoxTargetProperty;
#include "smartPointers/ememory.h"
#include "conncontextptr.h"

class BoxTargetWidget : public QWidget {
public:
    explicit BoxTargetWidget(QWidget *parent = nullptr);

    void setTargetProperty(BoxTargetProperty *property);
protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void paintEvent(QPaintEvent *);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
private:
    bool mDragging = false;
    ConnContextQPtr<BoxTargetProperty> mProperty;
};

#endif // BOXTARGETWIDGET_H
