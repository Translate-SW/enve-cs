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

#include "colorlabel.h"
#include "colorhelpers.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWidget>
#include <QMenu>
#include "Private/document.h"
#include "colorwidgetshaders.h"

ColorLabel::ColorLabel(QWidget *parent) : ColorWidget(parent) {
    //setMinimumSize(80, 20);
    //setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void ColorLabel::mousePressEvent(QMouseEvent *e) {
    QMenu menu(this);
    menu.addAction("Bookmark");
    const auto act = menu.exec(e->globalPos());
    if(act) {
        if(act->text() == "Bookmark") {
            const QColor col = QColor::fromHsvF(qreal(mHue),
                                                qreal(mSaturation),
                                                qreal(mValue),
                                                mAlpha);
            Document::sInstance->addBookmarkColor(col);
        }
    }
}

void ColorLabel::setAlpha(const qreal alpha_t) {
    mAlpha = alpha_t;
    update();
}

void ColorLabel::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(PLAIN_PROGRAM.fID);
    float r = mHue;
    float g = mSaturation;
    float b = mValue;
    hsv_to_rgb_float(r, g, b);

    int halfWidth = width()/2;
    glViewport(0, 0, halfWidth, height());
    glUniform4f(PLAIN_PROGRAM.fRGBAColorLoc, r, g, b,
                static_cast<float>(mAlpha));
    glUniform2f(PLAIN_PROGRAM.fMeshSizeLoc, height()/(1.5f*width()), 1.f/3);
    glBindVertexArray(mPlainSquareVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


    glViewport(halfWidth, 0, width() - halfWidth, height());
    glUniform4f(PLAIN_PROGRAM.fRGBAColorLoc, r, g, b, 1.f);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
