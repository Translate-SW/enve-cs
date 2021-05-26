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

#include "scrollarea.h"
#include <QResizeEvent>
#include <QScrollBar>

ScrollArea::ScrollArea(QWidget * const parent) : QScrollArea(parent) {
    setFocusPolicy(Qt::NoFocus);
    //verticalScrollBar()->setSingleStep(20);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setBackgroundRole(QPalette::Window);
    setFrameShadow(QFrame::Plain);
    setFrameShape(QFrame::NoFrame);
    setWidgetResizable(true);
}

void ScrollArea::scrollBy(const int x, const int y) {
    Q_UNUSED(x)
    verticalScrollBar()->setValue(verticalScrollBar()->value() + y);
}

void ScrollArea::resizeEvent(QResizeEvent *e) {
    int newHeight = e->size().height();
    if(newHeight != mLastHeight) {
        mLastHeight = newHeight;
        emit heightChanged(newHeight);
    }
    int newWidth = e->size().width();
    if(newWidth != mLastWidth) {
        mLastWidth = newWidth;
        emit widthChanged(newWidth);
    }
    QScrollArea::resizeEvent(e);
}
#include "GUI/global.h"
void ScrollArea::callWheelEvent(QWheelEvent *event) {
    if(event->delta() > 0) {
        scrollBy(0, -eSizesUI::widget);
    } else {
        scrollBy(0, eSizesUI::widget);
    }
//    verticalScrollBar()->triggerAction(
//                (event->delta() > 0) ?
//                    QAbstractSlider::SliderSingleStepSub :
//                    QAbstractSlider::SliderSingleStepAdd);
}
