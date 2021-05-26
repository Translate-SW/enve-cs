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

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

class eSettings;

class SettingsWidget : public QWidget {
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = nullptr);

    void add2HWidgets(QWidget* const widget1,
                      QWidget* const widget2);
    void addWidget(QWidget* const widget);
    void addLayout(QLayout* const layout);
    void addSeparator();

    virtual void applySettings() = 0;
    virtual void updateSettings() = 0;
protected:
    eSettings& mSett;
private:
    using QWidget::layout;
    QVBoxLayout* mMainLauout = nullptr;
};

#endif // SETTINGSWIDGET_H
