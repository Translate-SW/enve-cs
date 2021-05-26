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

#include "ecombobox.h"

#include <QWheelEvent>

void eComboBox::wheelEvent(QWheelEvent *e) {
    switch(mWheelMode) {
    case WheelMode::disabled:
        return QWidget::wheelEvent(e);
    case WheelMode::enabledWithCtrl: {
        const bool ctrlPressed = e->modifiers() & Qt::CTRL;
        if(ctrlPressed) return QComboBox::wheelEvent(e);
    } break;
    case WheelMode::enabled:
        return QComboBox::wheelEvent(e);
    }
}
