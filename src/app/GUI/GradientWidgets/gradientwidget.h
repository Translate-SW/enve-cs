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

#ifndef GRADIENTWIDGET_H
#define GRADIENTWIDGET_H
#include "GUI/fillstrokesettings.h"
#include <QComboBox>
#include <QScrollArea>
#include "GUI/GradientWidgets/gradientslistwidget.h"
#include "GUI/GradientWidgets/currentgradientwidget.h"

class GradientWidget : public QWidget {
    Q_OBJECT
public:
    GradientWidget(QWidget * const parent);

    void setCurrentGradient(Gradient *gradient);
    Gradient *getCurrentGradient();
    ColorAnimator *getColorAnimator();

    void clearAll();
signals:
    void selectionChanged(Gradient*);
    void selectedColorChanged(ColorAnimator*);
    void triggered(Gradient *gradient);
protected:
    void showEvent(QShowEvent *e);
private:
    QVBoxLayout *mMainLayout;
    GradientsListWidget *mGradientsListWidget;
    CurrentGradientWidget *mCurrentGradientWidget;

    bool mReordering = false;
    bool mFirstMove = false;

    int mNumberVisibleGradients = 6;
    int mHalfHeight = 64;
    int mQuorterHeight = 32;

    Gradient *mCurrentGradient = nullptr;
    ColorAnimator *mCurrentColor = nullptr;
    int mCurrentColorId = 0;
    int mCenterGradientId = 1;
};

#endif // GRADIENTWIDGET_H
