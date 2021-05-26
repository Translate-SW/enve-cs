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

#include "coloranimatorbutton.h"
#include "Animators/coloranimator.h"
#include "colorsetting.h"
#include "GUI/ewidgets.h"
#include <QVBoxLayout>
#include <QDialog>

ColorAnimatorButton::ColorAnimatorButton(QWidget * const parent) :
    BoxesListActionButton(parent) {
    connect(this, &BoxesListActionButton::pressed,
            this, &ColorAnimatorButton::openColorSettingsDialog);
}

ColorAnimatorButton::ColorAnimatorButton(ColorAnimator * const colorTarget,
                                         QWidget * const parent) :
    ColorAnimatorButton(parent) {
    setColorTarget(colorTarget);
}

ColorAnimatorButton::ColorAnimatorButton(const QColor &color,
                                         QWidget * const parent) :
    ColorAnimatorButton(parent) {
    mColor = color;
}

void ColorAnimatorButton::setColorTarget(ColorAnimator * const target) {
    mColorTarget.assign(target);
    if(target) {
        mColorTarget << connect(target->getVal1Animator(),
                                &QrealAnimator::effectiveValueChanged,
                                this, qOverload<>(&ColorAnimatorButton::update));
        mColorTarget << connect(target->getVal2Animator(),
                                &QrealAnimator::effectiveValueChanged,
                                this, qOverload<>(&ColorAnimatorButton::update));
        mColorTarget << connect(target->getVal3Animator(),
                                &QrealAnimator::effectiveValueChanged,
                                this, qOverload<>(&ColorAnimatorButton::update));
    }
}

void ColorAnimatorButton::paintEvent(QPaintEvent *) {
    const QColor color = mColorTarget ?
                mColorTarget->getColor() : mColor;
    QPainter p(this);
    if(mHover) p.setPen(Qt::red);
    else p.setPen(Qt::white);
    p.setBrush(color);
    p.drawRect(0, 0, width() - 1, height() - 1);
}

void ColorAnimatorButton::openColorSettingsDialog() {
    const auto dialog = new QDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setLayout(new QVBoxLayout(dialog));
    QWidget* colorWidget = nullptr;

    if(mColorTarget) {
        colorWidget = eWidgets::sColorWidget(dialog, mColorTarget);
    } else {
        const auto colOp = [this](const ColorSetting& setting) {
            mColor = setting.getColor();
            update();
        };
        colorWidget = eWidgets::sColorWidget(dialog, mColor, this, colOp);
    }
    dialog->layout()->addWidget(colorWidget);

    dialog->raise();
    dialog->show();
}

void ColorAnimatorButton::setColor(const QColor &color) {
    mColor = color;
    update();
}

QColor ColorAnimatorButton::color() const {
    if(mColorTarget) return mColorTarget->getColor();
    return mColor;
}
