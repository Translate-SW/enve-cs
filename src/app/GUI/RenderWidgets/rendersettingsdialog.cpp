#include "rendersettingsdialog.h"
#include <QPushButton>
#include "GUI/global.h"
#include "Private/document.h"
#include "canvas.h"

RenderSettingsDialog::RenderSettingsDialog(
        const RenderInstanceSettings &settings,
        QWidget *parent) :
    QDialog(parent),
    mInitialScene(settings.getTargetCanvas()),
    mCurrentScene(mInitialScene),
    mInitialSettings(settings.getRenderSettings()) {
    setWindowTitle("Render Settings");

    const auto mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    const auto sceneLay = new QHBoxLayout;
    mSceneLabel = new QLabel("Scene: ");
    mSceneCombo = new QComboBox();
    for(const auto& canvas : Document::sInstance->fScenes) {
        mSceneCombo->addItem(canvas->prp_getName());
    }
    if(mCurrentScene) mSceneCombo->setCurrentText(mCurrentScene->prp_getName());
    connect(mSceneCombo, qOverload<int>(&QComboBox::currentIndexChanged),
            this, [this](const int id) {
        const auto newScene = Document::sInstance->fScenes.at(id).get();
        if(newScene) {
            const auto frameRange = newScene->getFrameRange();
            mMinFrameSpin->setValue(frameRange.fMin);
            mMaxFrameSpin->setValue(frameRange.fMax);
        }
        mCurrentScene = newScene;
        updateValuesFromRes();
    });
    sceneLay->addWidget(mSceneLabel);
    sceneLay->addWidget(mSceneCombo);
    mainLayout->addLayout(sceneLay);

    const auto resolutionLay = new QHBoxLayout;
    mResolutionLabel = new QLabel("Resolution: ");
    mResolutionSpin = new QDoubleSpinBox(this);
    mResolutionSpin->setDecimals(2);
    mResolutionSpin->setSuffix(" %");
    mResolutionSpin->setRange(1, 999.99);
    mResolutionSpin->setValue(mInitialSettings.fResolution*100);
    resolutionLay->addWidget(mResolutionLabel);
    resolutionLay->addWidget(mResolutionSpin);
    mainLayout->addLayout(resolutionLay);

    const auto dimLay = new QHBoxLayout;
    mWidthLabel = new QLabel("Width: ");
    mWidthSpin = new QSpinBox(this);
    mWidthSpin->setRange(1, 9999);
    mWidthSpin->setValue(mInitialSettings.fVideoWidth);
    dimLay->addWidget(mWidthLabel);
    dimLay->addWidget(mWidthSpin);

    eSizesUI::widget.addSpacing(dimLay);

    mHeightLabel = new QLabel("Height: ");
    mHeightSpin = new QSpinBox(this);
    mHeightSpin->setRange(1, 9999);
    mHeightSpin->setValue(mInitialSettings.fVideoHeight);
    dimLay->addWidget(mHeightLabel);
    dimLay->addWidget(mHeightSpin);

    connectDims();

    mainLayout->addLayout(dimLay);
    addSeparator();

    const auto rangeLay = new QHBoxLayout;
    mFrameRangeLabel = new QLabel("Frame range: ", this);
    mMinFrameSpin = new QSpinBox(this);
    mMinFrameSpin->setRange(-999999, 999999);
    mMaxFrameSpin = new QSpinBox(this);
    mMaxFrameSpin->setRange(-999999, 999999);

    connect(mMinFrameSpin, qOverload<int>(&QSpinBox::valueChanged),
            mMaxFrameSpin, &QSpinBox::setMinimum);
    connect(mMaxFrameSpin, qOverload<int>(&QSpinBox::valueChanged),
            mMinFrameSpin, &QSpinBox::setMaximum);
    mMinFrameSpin->setValue(mInitialSettings.fMinFrame);
    mMaxFrameSpin->setValue(mInitialSettings.fMaxFrame);

    rangeLay->addWidget(mFrameRangeLabel);
    rangeLay->addWidget(mMinFrameSpin);
    rangeLay->addWidget(new QLabel(" - "));
    rangeLay->addWidget(mMaxFrameSpin);

    mainLayout->addLayout(rangeLay);

//    addSeparator();

//    const auto fpsLay = new QHBoxLayout;
//    mFpsLabel = new QLabel("Fps: ", this);
//    mFpsSpin = new QDoubleSpinBox(this);
//    mFpsSpin->setRange(1, 999.99);
//    mFpsSpin->setValue(settings.fFps);
//    fpsLay->addWidget(mFpsLabel);
//    fpsLay->addWidget(mFpsSpin);

//    mainLayout->addLayout(fpsLay);

    eSizesUI::widget.addSpacing(mainLayout);
    mainLayout->addStretch();

    mButtonsLayout = new QHBoxLayout();
    mOkButton = new QPushButton("Ok", this);
    mCancelButton = new QPushButton("Cancel", this);
    mResetButton = new QPushButton("Reset", this);
    connect(mOkButton, &QPushButton::released,
            this, &RenderSettingsDialog::accept);
    connect(mCancelButton, &QPushButton::released,
            this, &RenderSettingsDialog::reject);
    connect(mResetButton, &QPushButton::released,
            this, &RenderSettingsDialog::restoreInitialSettings);
    mButtonsLayout->addWidget(mResetButton, Qt::AlignLeft);
    mButtonsLayout->addWidget(mCancelButton, Qt::AlignLeft);
    mButtonsLayout->addWidget(mOkButton, Qt::AlignRight);

    mainLayout->addLayout(mButtonsLayout);
}

RenderSettings RenderSettingsDialog::getSettings() const {
    RenderSettings sett = mInitialSettings;
    sett.fResolution = mResolutionSpin->value()/100;
    sett.fVideoWidth = mWidthSpin->value();
    sett.fVideoHeight = mHeightSpin->value();
    sett.fMinFrame = mMinFrameSpin->value();
    sett.fMaxFrame = mMaxFrameSpin->value();
    sett.fBaseFps = mCurrentScene ? mCurrentScene->getFps() :
                                    mInitialSettings.fFps;
    sett.fFps = sett.fBaseFps;
//    sett.fFps = mFpsSpin->value();
    return sett;
}

void RenderSettingsDialog::connectDims() {
    connect(mResolutionSpin,
            qOverload<qreal>(&QDoubleSpinBox::valueChanged),
            this, &RenderSettingsDialog::updateValuesFromRes);
    connect(mWidthSpin, qOverload<int>(&QSpinBox::valueChanged),
            this, &RenderSettingsDialog::updateValuesFromWidth);
    connect(mHeightSpin, qOverload<int>(&QSpinBox::valueChanged),
            this, &RenderSettingsDialog::updateValuesFromHeight);
}

void RenderSettingsDialog::disconnectDims() {
    disconnect(mResolutionSpin,
               qOverload<qreal>(&QDoubleSpinBox::valueChanged),
               this, &RenderSettingsDialog::updateValuesFromRes);
    disconnect(mWidthSpin, qOverload<int>(&QSpinBox::valueChanged),
               this, &RenderSettingsDialog::updateValuesFromWidth);
    disconnect(mHeightSpin, qOverload<int>(&QSpinBox::valueChanged),
               this, &RenderSettingsDialog::updateValuesFromHeight);
}

void RenderSettingsDialog::updateValuesFromRes() {
    disconnectDims();
    const qreal res = mResolutionSpin->value()/100;
    if(mCurrentScene) {
        mWidthSpin->setValue(qRound(mCurrentScene->getCanvasWidth()*res));
        mHeightSpin->setValue(qRound(mCurrentScene->getCanvasHeight()*res));
    } else {
        mWidthSpin->setValue(qRound(mInitialSettings.fBaseWidth*res));
        mHeightSpin->setValue(qRound(mInitialSettings.fBaseHeight*res));
    }
    connectDims();
}

void RenderSettingsDialog::updateValuesFromWidth() {
    disconnectDims();
    qreal res;
    if(mCurrentScene) {
        res = qreal(mWidthSpin->value())/
                    mCurrentScene->getCanvasWidth();
    } else {
        res = qreal(mWidthSpin->value())/
                    mInitialSettings.fBaseWidth;
    }
    mResolutionSpin->setValue(res*100);
    mHeightSpin->setValue(qRound(mInitialSettings.fBaseHeight*res));
    connectDims();
}

void RenderSettingsDialog::updateValuesFromHeight() {
    disconnectDims();
    qreal res;
    if(mCurrentScene) {
        res = qreal(mHeightSpin->value())/
                    mCurrentScene->getCanvasHeight();
    } else {
        res = qreal(mHeightSpin->value())/
                    mInitialSettings.fBaseHeight;
    }
    mResolutionSpin->setValue(res*100);
    mWidthSpin->setValue(qRound(mInitialSettings.fBaseWidth*res));
    connectDims();
}

void RenderSettingsDialog::restoreInitialSettings() {
    if(mInitialScene) {
        mSceneCombo->setCurrentText(mInitialScene->prp_getName());
    }
    mResolutionSpin->setValue(mInitialSettings.fResolution*100);
    mMinFrameSpin->setValue(mInitialSettings.fMinFrame);
    mMaxFrameSpin->setValue(mInitialSettings.fMaxFrame);
//    mFpsSpin->setValue(mInitialSettings.fFps);
}

void RenderSettingsDialog::addSeparator() {
    const auto line = new QFrame;
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout()->addWidget(line);
}
