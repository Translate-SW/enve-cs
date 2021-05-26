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

#ifndef BUTTONBASE_H
#define BUTTONBASE_H

#include <QWidget>

class ButtonBase : public QWidget {
    Q_OBJECT
public:
    explicit ButtonBase(const QString &toolTip,
                        QWidget *parent = nullptr);
    void setCurrentIcon(const QImage &icon);
protected:
    void mouseReleaseEvent(QMouseEvent *) final;
    void mousePressEvent(QMouseEvent *) final;
    void enterEvent(QEvent *) final;
    void leaveEvent(QEvent *) final;

    void paintEvent(QPaintEvent *) final;

    virtual void toggle() {}
private:
    bool mHover = false;
    const QImage* mCurrentIcon = nullptr;
signals:
    void released();
    void pressed();
};
#endif // BUTTONBASE_H
