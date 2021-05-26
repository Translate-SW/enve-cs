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

#ifndef ALIGNWIDGET_H
#define ALIGNWIDGET_H

#include <QWidget>
#include <QComboBox>
#include "canvas.h"

class AlignWidget : public QWidget {
    Q_OBJECT
public:
    explicit AlignWidget(QWidget* const parent = nullptr);

signals:
    void alignTriggered(const Qt::Alignment,
                        const AlignPivot,
                        const AlignRelativeTo);
private:
    void triggerAlign(const Qt::Alignment align);

    QComboBox* mAlignPivot = nullptr;
    QComboBox* mRelativeTo = nullptr;
};

#endif // ALIGNWIDGET_H
