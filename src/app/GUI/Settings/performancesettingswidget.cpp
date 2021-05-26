#include "performancesettingswidget.h"
#include "Private/esettings.h"
#include "exceptions.h"
#include "hardwareinfo.h"
#include "GUI/global.h"

PerformanceSettingsWidget::PerformanceSettingsWidget(QWidget *parent) :
    SettingsWidget(parent) {
    QHBoxLayout* cpuCapSett = new QHBoxLayout;

    mCpuThreadsCapCheck = new QCheckBox("CPU threads cap", this);
    mCpuThreadsCapLabel = new QLabel(this);
    mCpuThreadsCapSlider = new QSlider(Qt::Horizontal);
    mCpuThreadsCapSlider->setRange(1, HardwareInfo::sCpuThreads());
    connect(mCpuThreadsCapCheck, &QCheckBox::toggled,
            mCpuThreadsCapSlider, &QWidget::setEnabled);
    connect(mCpuThreadsCapCheck, &QCheckBox::toggled,
            mCpuThreadsCapLabel, &QWidget::setEnabled);
    mCpuThreadsCapSlider->setEnabled(false);
    mCpuThreadsCapLabel->setEnabled(false);
    connect(mCpuThreadsCapSlider, &QSlider::valueChanged,
            this, [this](const int val) {
        const int nTot = HardwareInfo::sCpuThreads();
        mCpuThreadsCapLabel->setText(QString("%1 / %2").arg(val).arg(nTot));
    });

    addWidget(mCpuThreadsCapCheck);
    cpuCapSett->addWidget(mCpuThreadsCapLabel);
    cpuCapSett->addWidget(mCpuThreadsCapSlider);
    addLayout(cpuCapSett);

    addSeparator();

    QHBoxLayout* ramCapSett = new QHBoxLayout;

    mRamMBCapCheck = new QCheckBox("RAM cap", this);
    mRamMBCapSpin = new QSpinBox(this);
    mRamMBCapSpin->setRange(250, intMB(HardwareInfo::sRamKB()).fValue);
    mRamMBCapSpin->setSuffix(" MB");
    mRamMBCapSpin->setEnabled(false);

    mRamMBCapSlider = new QSlider(Qt::Horizontal);
    mRamMBCapSlider->setRange(250, intMB(HardwareInfo::sRamKB()).fValue);
    mRamMBCapSlider->setEnabled(false);

    connect(mRamMBCapCheck, &QCheckBox::toggled,
            mRamMBCapSpin, &QWidget::setEnabled);
    connect(mRamMBCapCheck, &QCheckBox::toggled,
            mRamMBCapSlider, &QWidget::setEnabled);

    connect(mRamMBCapSpin, qOverload<int>(&QSpinBox::valueChanged),
            mRamMBCapSlider, &QSlider::setValue);
    connect(mRamMBCapSlider, &QSlider::valueChanged,
            mRamMBCapSpin, &QSpinBox::setValue);

    ramCapSett->addWidget(mRamMBCapCheck);
    ramCapSett->addWidget(mRamMBCapSpin);
    addLayout(ramCapSett);
    addWidget(mRamMBCapSlider);

    addSeparator();

    mAccPreferenceLabel = new QLabel("Acceleration preference:");
    const auto sliderLayout = new QHBoxLayout;
    mAccPreferenceCpuLabel = new QLabel("CPU");
    mAccPreferenceSlider = new QSlider(Qt::Horizontal);
    mAccPreferenceSlider->setRange(0, 4);
    mAccPreferenceGpuLabel = new QLabel("GPU");
    sliderLayout->addWidget(mAccPreferenceCpuLabel);
    sliderLayout->addWidget(mAccPreferenceSlider);
    sliderLayout->addWidget(mAccPreferenceGpuLabel);
    mAccPreferenceDescLabel = new QLabel();
    mAccPreferenceDescLabel->setAlignment(Qt::AlignCenter);
    connect(mAccPreferenceSlider, &QSlider::valueChanged,
            this, &PerformanceSettingsWidget::updateAccPreferenceDesc);
    addWidget(mAccPreferenceLabel);
    addLayout(sliderLayout);
    addWidget(mAccPreferenceDescLabel);

    addSeparator();

    mPathGpuAccCheck = new QCheckBox("Path GPU acceleration", this);
    addWidget(mPathGpuAccCheck);

//    const auto line2 = new QFrame();
//    line2->setFrameShape(QFrame::HLine);
//    line2->setFrameShadow(QFrame::Sunken);
//    mainLauout->addWidget(line2);

//    mHddCacheCheck = new QCheckBox("HDD cache", this);
//    mainLauout->addWidget(mHddCacheCheck);

//    QWidget* hddCacheSett = new QWidget(this);
//    hddCacheSett->setContentsMargins(0, 0, 0, 0);
//    const auto hddCacheSettLay = new QHBoxLayout;
//    hddCacheSett->setLayout(hddCacheSettLay);
//    hddCacheSettLay->setContentsMargins(0, 0, 0, 0);

//    mHddCacheMBCapCheck = new QCheckBox("HDD cache MB cap", this);
//    mHddCacheMBCapSpin = new QSpinBox(this);
//    connect(mHddCacheMBCapCheck, &QCheckBox::toggled,
//            mHddCacheMBCapSpin, &QWidget::setEnabled);

//    hddCacheSettLay->addWidget(mHddCacheMBCapCheck);
//    hddCacheSettLay->addWidget(mHddCacheMBCapSpin);
//    connect(mHddCacheCheck, &QCheckBox::toggled,
//            hddCacheSett, &QWidget::setEnabled);

    //    mainLauout->addWidget(hddCacheSett);
}

void PerformanceSettingsWidget::applySettings() {
    mSett.fCpuThreadsCap = mCpuThreadsCapCheck->isChecked() ?
                mCpuThreadsCapSlider->value() : 0;
    mSett.fRamMBCap = intMB(mRamMBCapCheck->isChecked() ?
                mRamMBCapSpin->value() : 0);
    mSett.fAccPreference = static_cast<AccPreference>(
                mAccPreferenceSlider->value());
    mSett.fPathGpuAcc = mPathGpuAccCheck->isChecked();
//        sett.fHddCache = mHddCacheCheck->isChecked();
//        sett.fRamMBCap = mHddCacheMBCapCheck->isChecked() ?
//                    mHddCacheMBCapSpin->value() : 0;
}


void PerformanceSettingsWidget::updateSettings() {
    const bool capCpu = mSett.fCpuThreadsCap > 0;
    mCpuThreadsCapCheck->setChecked(capCpu);
    const int nThreads = capCpu ? mSett.fCpuThreadsCap :
                                  HardwareInfo::sCpuThreads();
    mCpuThreadsCapSlider->setValue(nThreads);

    const bool capRam = mSett.fRamMBCap.fValue > 250;
    mRamMBCapCheck->setChecked(capRam);
    const int nRamMB = capRam ? mSett.fRamMBCap.fValue :
                                intMB(HardwareInfo::sRamKB()).fValue;
    mRamMBCapSpin->setValue(nRamMB);

    mAccPreferenceSlider->setValue(static_cast<int>(mSett.fAccPreference));
    updateAccPreferenceDesc();
    mPathGpuAccCheck->setChecked(mSett.fPathGpuAcc);

//    mHddCacheCheck->setChecked(sett.fHddCache);

//    mHddCacheMBCapCheck->setChecked(sett.fHddCacheMBCap > 0);
//    mHddCacheMBCapSpin->setEnabled(sett.fHddCacheMBCap > 0);
//    mHddCacheMBCapSpin->setValue(sett.fHddCacheMBCap);
}

void PerformanceSettingsWidget::updateAccPreferenceDesc() {
    const int value = mAccPreferenceSlider->value();
    QString toolTip;
    if(value == 0) {
        mAccPreferenceDescLabel->setText("Strong CPU preference");
        toolTip = "Use the GPU only for tasks not supported by the CPU";
    } else if(value == 1) {
        mAccPreferenceDescLabel->setText("Soft CPU preference");
        toolTip = "Use the GPU only for tasks marked as preferred for the GPU";
    } else if(value == 2) {
        mAccPreferenceDescLabel->setText(" Hardware agnostic (recommended) ");
        toolTip = "Adhere to the default hardware preference";
    } else if(value == 3) {
        mAccPreferenceDescLabel->setText("Soft GPU preference");
        toolTip = "Use the CPU only for tasks marked as preferred for the CPU";
    } else if(value == 4) {
        mAccPreferenceDescLabel->setText("Strong GPU preference");
        toolTip = "Use the CPU only for tasks not supported by the GPU";
    }
    mAccPreferenceDescLabel->setToolTip(gSingleLineTooltip(toolTip));
    mAccPreferenceSlider->setToolTip(gSingleLineTooltip(toolTip));
}
