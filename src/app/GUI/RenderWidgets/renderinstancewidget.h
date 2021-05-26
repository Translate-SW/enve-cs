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

#ifndef RENDERINSTANCEWIDGET_H
#define RENDERINSTANCEWIDGET_H

#include "closablecontainer.h"
#include "renderinstancesettings.h"
#include "GUI/BoxesList/boxsinglewidget.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>
class OutputSettingsDisplayWidget;
class RenderSettingsDisplayWidget;

class RenderInstanceWidget;
class OutputProfilesListButton : public QPushButton {
    Q_OBJECT
public:
    OutputProfilesListButton(RenderInstanceWidget *parent);
signals:
    void profileSelected(OutputSettingsProfile *);
protected:
    void mousePressEvent(QMouseEvent *e);
    RenderInstanceWidget *mParentWidget;
};

class RenderInstanceWidget : public ClosableContainer {
    Q_OBJECT
public:
    RenderInstanceWidget(Canvas *canvas, QWidget *parent = nullptr);
    RenderInstanceWidget(const RenderInstanceSettings& canvas,
                         QWidget *parent);
    RenderInstanceSettings &getSettings();

    void write(eWriteStream &dst) const;
    void read(eReadStream &src);
protected:
    void mousePressEvent(QMouseEvent* e);
private:
    void iniGUI();

    ClosableContainer *mOutputSettings;
    RenderSettingsDisplayWidget *mRenderSettingsDisplayWidget;
    OutputSettingsDisplayWidget *mOutputSettingsDisplayWidget;

    QPushButton *mOutputDestinationButton;

    QPushButton* mRenderSettingsButton;

    OutputProfilesListButton *mOutputSettingsProfilesButton;
    QPushButton *mOutputSettingsButton;
    QLabel *mNameLabel;
    QVBoxLayout *mContentLayout = new QVBoxLayout();
    RenderInstanceSettings mSettings;
signals:
    void duplicate(RenderInstanceSettings&);
protected:
    void updateOutputDestinationFromCurrentFormat();
private:
    void updateFromSettings();

    void outputSettingsProfileSelected(OutputSettingsProfile *profile);

    void openOutputSettingsDialog();
    void openOutputDestinationDialog();
    void openRenderSettingsDialog();
};

#endif // RENDERINSTANCEWIDGET_H
