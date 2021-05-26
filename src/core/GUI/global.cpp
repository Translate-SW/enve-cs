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

#include "global.h"

#include <QWidget>
#include <QApplication>

SizeSetter eSizesUI::font;
SizeSetter eSizesUI::widget;
SizeSetter eSizesUI::button;

QFont OS_FONT;
int KEY_RECT_SIZE;

QPixmap* ALPHA_MESH_PIX;

QString gSingleLineTooltip(const QString &text) {
    return "<p style='white-space:pre'>" + text + "</p>";
}

QString gSingleLineTooltip(const QString &text, const QString &shortcut) {
    return "<p style='white-space:pre'>" + text +
            " <font color='grey'>" + shortcut + "</font></p>";
}

void connectAppFont(QWidget* const widget) {
    QObject::connect(&eSizesUI::font, &SizeSetter::sizeChanged,
                     widget, [widget]() {
        widget->setFont(QApplication::font());
    });
}
