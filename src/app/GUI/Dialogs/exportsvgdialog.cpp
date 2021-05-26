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

#include "exportsvgdialog.h"

#include "Private/document.h"
#include "GUI/scenechooser.h"
#include "GUI/global.h"
#include "canvas.h"
#include "svgexporter.h"
#include "GUI/edialogs.h"
#include "GUI/twocolumnlayout.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMenuBar>
#include <QWebEngineView>

class SvgPreview : public QWebEngineView {
public:
    SvgPreview(QWidget* const parent = nullptr) : QWebEngineView(parent) {
        setSizePolicy(QSizePolicy::MinimumExpanding,
                      QSizePolicy::MinimumExpanding);
        setMinimumSize(10*eSizesUI::widget, 10*eSizesUI::widget);
    }
protected:
    void contextMenuEvent(QContextMenuEvent *e) {
        QMenu* menu = new QMenu(this);
        const auto action = menu->addAction("Restart");
        action->setIcon(QIcon::fromTheme(QStringLiteral("view-refresh")));
        connect(action, &QAction::triggered, this, &SvgPreview::reload);
        menu->popup(e->globalPos());
        connect(menu, &QMenu::aboutToHide, menu, &QObject::deleteLater);
    }
};

ExportSvgDialog::ExportSvgDialog(QWidget* const parent) :
    QDialog(parent) {

    setWindowTitle("Export SVG");

    const auto settingsLayout = new QVBoxLayout();

    const auto twoColLayout = new TwoColumnLayout();

    const auto document = Document::sInstance;
    mScene = new SceneChooser(*document, false, this);
    auto scene = *document->fActiveScene;
    if(!scene) {
        const auto& visScenes = document->fVisibleScenes;
        if(!visScenes.empty()) scene = visScenes.begin()->first;
        else {
            const auto& scenes = document->fScenes;
            if(!scenes.isEmpty()) scene = scenes.first().get();
        }
    }
    mScene->setCurrentScene(scene);

    const auto sceneButton = new QPushButton(mScene->title(), this);
    sceneButton->setMenu(mScene);

    mFirstFrame = new QSpinBox(this);
    mLastFrame = new QSpinBox(this);

    const int minFrame = scene ? scene->getMinFrame() : 0;
    const int maxFrame = scene ? scene->getMaxFrame() : 0;

    mFirstFrame->setRange(-99999, maxFrame);
    mFirstFrame->setValue(minFrame);
    mLastFrame->setRange(minFrame, 99999);
    mLastFrame->setValue(maxFrame);

    mBackground = new QCheckBox("Background", this);
    mBackground->setChecked(true);
    mFixedSize = new QCheckBox("Fixed Size", this);
    mFixedSize->setChecked(false);
    mLoop = new QCheckBox("Loop", this);
    mLoop->setChecked(true);

    twoColLayout->addPair(new QLabel("Scene:"), sceneButton);
    eSizesUI::widget.addSpacing(twoColLayout);
    twoColLayout->addPair(new QLabel("First Frame:"), mFirstFrame);
    twoColLayout->addPair(new QLabel("Last Frame:"), mLastFrame);

    settingsLayout->addLayout(twoColLayout);
    eSizesUI::widget.addSpacing(settingsLayout);
    settingsLayout->addWidget(mBackground);
    settingsLayout->addWidget(mFixedSize);
    settingsLayout->addWidget(mLoop);
    eSizesUI::widget.addSpacing(settingsLayout);

    connect(mFirstFrame, qOverload<int>(&QSpinBox::valueChanged),
            mLastFrame, &QSpinBox::setMinimum);
    connect(mLastFrame, qOverload<int>(&QSpinBox::valueChanged),
            mFirstFrame, &QSpinBox::setMaximum);

    const auto buttons = new QDialogButtonBox(QDialogButtonBox::Ok |
                                              QDialogButtonBox::Cancel);

    connect(mScene, &SceneChooser::currentChanged,
            this, [this, buttons, sceneButton](Canvas* const scene) {
        buttons->button(QDialogButtonBox::Ok)->setEnabled(scene);
        sceneButton->setText(mScene->title());
    });

    connect(buttons, &QDialogButtonBox::accepted, this, [this]() {
        const QString dir = Document::sInstance->projectDirectory();
        const QString fileType = tr("SVG Files %1", "ExportDialog_FileType");
        QString saveAs = eDialogs::saveFile("Export SVG", dir,
                                            fileType.arg("(*.svg)"));
        if(saveAs.isEmpty()) return;
        if(saveAs.right(4) != ".svg") saveAs += ".svg";
        const bool success = exportTo(saveAs);
        if(success) accept();
    });

    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    settingsLayout->addWidget(buttons, 0, Qt::AlignBottom);

    mPreview = new SvgPreview(this);
    mPreviewButton = new QPushButton("Preview", this);
    buttons->addButton(mPreviewButton, QDialogButtonBox::ActionRole);
    connect(mPreviewButton, &QPushButton::released, this, [this]() {
        if(!mPreviewFile) {
            const QString templ = QDir::tempPath() + "/enve_svg_preview_XXXXXX.svg";
            mPreviewFile = qsptr<QTemporaryFile>::create(templ);
            mPreviewFile->open();
            mPreviewFile->close();
        }
        const auto task = exportTo(mPreviewFile->fileName());
        if(!task) return;
        QPointer<ExportSvgDialog> ptr = this;
        task->addDependent(
        {[ptr]() {
            if(ptr) {
                const auto fileName = ptr->mPreviewFile->fileName();
                ptr->mPreview->load(QUrl::fromLocalFile(fileName));
            }
        }, nullptr});
    });

    const auto settingsWidget = new QWidget(this);
    settingsWidget->setLayout(settingsLayout);
    settingsWidget->setSizePolicy(QSizePolicy::Fixed,
                                  QSizePolicy::MinimumExpanding);

    const auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(mPreview);
    eSizesUI::widget.addHalfSpacing(mainLayout);
    mainLayout->addWidget(settingsWidget);
    setLayout(mainLayout);
}

ComplexTask* ExportSvgDialog::exportTo(const QString& file) {
    try {
        const auto scene = mScene->getCurrentScene();
        if(!scene) RuntimeThrow("No scene selected");
        const int firstFrame = mFirstFrame->value();
        const int lastFrame = mLastFrame->value();

        const bool background = mBackground->isChecked();
        const bool fixedSize = mFixedSize->isChecked();
        const bool loop = mLoop->isChecked();

        const FrameRange frameRange{firstFrame, lastFrame};
        const qreal fps = scene->getFps();

        const auto task = new SvgExporter(file, scene, frameRange, fps,
                                          background, fixedSize, loop);
        const auto taskSPtr = qsptr<SvgExporter>(task, &QObject::deleteLater);
        task->nextStep();
        TaskScheduler::instance()->addComplexTask(taskSPtr);
        return task;
    } catch(const std::exception& e) {
        gPrintExceptionCritical(e);
        return nullptr;
    }
}
