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

#include "labeledslider.h"

#include <QLabel>

LabeledSlider::LabeledSlider(const QString& suffix, QWidget *parent) :
    QHBoxLayout(parent) {
    mSlider = new QSlider(Qt::Horizontal, parent);
    const auto label = new QLabel;
    addWidget(mSlider);
    addWidget(label);
    connect(mSlider, &QSlider::valueChanged,
            label, [label, suffix](const int value) {
        label->setText(QString::number(value) + " " + suffix);
    });
}
