#include "settingsdialog.h"
#include "Private/esettings.h"
#include "hardwareinfo.h"
#include "exceptions.h"
#include "GUI/global.h"

#include "performancesettingswidget.h"
#include "interfacesettingswidget.h"
#include "canvassettingswidget.h"
#include "timelinesettingswidget.h"
#include "externalappssettingswidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QStatusBar>

SettingsDialog::SettingsDialog(QWidget * const parent) :
    QDialog(parent) {
    eSizesUI::widget.add(this, [this](const int size) {
        setMinimumWidth(20*size);
    });
    setWindowTitle("Settings");

    const auto mainLauout = new QVBoxLayout;
    setLayout(mainLauout);

    mTabWidget = new QTabWidget(this);
    eSizesUI::widget.add(this, [this](const int size) {
        mTabWidget->setContentsMargins(size, size, size, size);
    });

    const auto performance = new PerformanceSettingsWidget(this);
    addSettingsWidget(performance, "Provést");

    const auto ui = new InterfaceSettingsWidget(this);
    addSettingsWidget(ui, "Rozhraní");

    const auto canvas = new CanvasSettingsWidget(this);
    addSettingsWidget(canvas, "Promítání");

    const auto timeline = new TimelineSettingsWidget(this);
    addSettingsWidget(timeline, "Časová osa");

    const auto external = new ExternalAppsSettingsWidget(this);
    addSettingsWidget(external, "Externí aplikace");

    mainLauout->addWidget(mTabWidget);

    const auto buttonsLayout = new QHBoxLayout;

    const auto restoreButton = new QPushButton("Obnovit původní", this);
    const auto cancelButton = new QPushButton("Zrušit", this);
    const auto applyButton = new QPushButton("Použít", this);
    buttonsLayout->addWidget(restoreButton);
    eSizesUI::widget.addSpacing(buttonsLayout);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(cancelButton);
    buttonsLayout->addWidget(applyButton);

    eSizesUI::widget.addSpacing(mainLauout);
    mainLauout->addStretch();
    mainLauout->addLayout(buttonsLayout);
    const auto statusBar = new QStatusBar(this);
    mainLauout->addWidget(statusBar);

    connect(restoreButton, &QPushButton::released, this, [this]() {
        eSettings::sInstance->loadDefaults();
        updateSettings();
        eSizesUI::font.updateSize();
        eSizesUI::widget.updateSize();
    });

    connect(cancelButton, &QPushButton::released, this, &QDialog::close);

    connect(applyButton, &QPushButton::released,
            this, [this, statusBar]() {
        for(const auto widget : mSettingWidgets) {
            widget->applySettings();
        }
        emit eSettings::sInstance->settingsChanged();
        try {
            eSettings& sett = *eSettings::sInstance;
            sett.saveToFile();
        } catch(const std::exception& e) {
            gPrintExceptionCritical(e);
        }
        statusBar->showMessage("Nastavení bylo uloženo, můžete restartovat enve", 1500);
    });

    updateSettings();
}

void SettingsDialog::addSettingsWidget(SettingsWidget * const widget,
                                       const QString &name) {
    mTabWidget->addTab(widget, name);
    mSettingWidgets << widget;
}

void SettingsDialog::updateSettings() {
    for(const auto widget : mSettingWidgets) {
        widget->updateSettings();
    }
}
