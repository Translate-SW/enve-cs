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

#include "glwidget.h"
#include "colorhelpers.h"
#include "GUI/global.h"
#include "Animators/paintsettingsanimator.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) {
//    setFormat(QSurfaceFormat::defaultFormat());
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(eSizesUI::widget, eSizesUI::widget);
}

void GLWidget::initializeGL() {
    if(!initializeOpenGLFunctions())
        RuntimeThrow("Initializing OpenGL 3.3 functions failed. "
                     "Make sure your GPU supports OpenGL 3.3.");

    glClearColor(0, 0, 0, 1);
    //Set blending
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    iniPlainVShaderVAO(this, mPlainSquareVAO);
}
