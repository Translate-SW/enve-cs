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

#ifndef EXPORTSVGDIALOG_H
#define EXPORTSVGDIALOG_H

#include <QDialog>

#include <QSpinBox>
#include <QCheckBox>
#include <QTemporaryFile>

class QWebEngineView;
class SceneChooser;
class ComplexTask;

class ExportSvgDialog : public QDialog {
public:
    ExportSvgDialog(QWidget* const parent = nullptr);

private:
    ComplexTask* exportTo(const QString& file);

    QSharedPointer<QTemporaryFile> mPreviewFile;
    QWebEngineView* mPreview;
    QPushButton* mPreviewButton;

    SceneChooser* mScene;

    QSpinBox* mFirstFrame;
    QSpinBox* mLastFrame;

    QCheckBox* mBackground;
    QCheckBox* mFixedSize;
    QCheckBox* mLoop;
};

#endif // EXPORTSVGDIALOG_H
