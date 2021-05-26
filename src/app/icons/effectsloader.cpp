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

#include "effectsloader.h"
#include "GUI/ColorWidgets/colorwidgetshaders.h"
#include "RasterEffects/rastereffect.h"
#include <QFileSystemWatcher>
#include <QFileSystemModel>
#include <iostream>
#include "ShaderEffects/shadereffectcreator.h"
#include "Private/esettings.h"

EffectsLoader::EffectsLoader() {}

EffectsLoader::~EffectsLoader() {
    makeCurrent();
    glDeleteBuffers(1, &GL_PLAIN_SQUARE_VBO);
    glDeleteVertexArrays(1, &mPlainSquareVAO);
    glDeleteBuffers(1, &GL_TEXTURED_SQUARE_VBO);
    glDeleteVertexArrays(1, &mTexturedSquareVAO);

    glUseProgram(0);

    glDeleteProgram(HUE_PROGRAM.fID);
    glDeleteProgram(HSV_SATURATION_PROGRAM.fID);
    glDeleteProgram(VALUE_PROGRAM.fID);

    glDeleteProgram(HSL_SATURATION_PROGRAM.fID);
    glDeleteProgram(LIGHTNESS_PROGRAM.fID);

    glDeleteProgram(RED_PROGRAM.fID);
    glDeleteProgram(GREEN_PROGRAM.fID);
    glDeleteProgram(BLUE_PROGRAM.fID);

    glDeleteProgram(ALPHA_PROGRAM.fID);

    glDeleteProgram(PLAIN_PROGRAM.fID);

    glDeleteProgram(GRADIENT_PROGRAM.fID);

    glDeleteProgram(BORDER_PROGRAM.fID);
    glDeleteProgram(DOUBLE_BORDER_PROGRAM.fID);

    for(const auto& shaderEffect : ShaderEffectCreator::sEffectCreators)
        glDeleteProgram(shaderEffect->fProgram->fId);

    doneCurrent();
}

void EffectsLoader::initializeGpu() {
    std::cout << "Entered initializeGpu" << std::endl;

    OffscreenQGL33c::initialize();
    std::cout << "OffscreenQGL33c initialized" << std::endl;
    makeCurrent();
    std::cout << "Make OffscreenQGL33c current" << std::endl;

    iniPlainVShaderVBO(this);
    std::cout << "iniPlainVShaderVBO" << std::endl;
    iniPlainVShaderVAO(this, mPlainSquareVAO);
    std::cout << "iniPlainVShaderVAO" << std::endl;
    iniTexturedVShaderVBO(this);
    std::cout << "iniTexturedVShaderVBO" << std::endl;
    iniTexturedVShaderVAO(this, mTexturedSquareVAO);
    std::cout << "iniTexturedVShaderVAO" << std::endl;
    iniColorPrograms(this);
    std::cout << "iniColorPrograms" << std::endl;

    doneCurrent();
    std::cout << "Done OffscreenQGL33c current" << std::endl;
}

#include "Boxes/ecustombox.h"
#include "Boxes/customboxcreator.h"
void iniCustomBox(const QString& path) {
    try {
        CustomBoxCreator::sLoadCustom(path);
    } catch(...) {
        RuntimeThrow("Error while loading Box from '" + path + "'");
    }
}

void iniIfCustomBox(const QString& path) {
    const QFileInfo fileInfo(path);
    if(!fileInfo.isFile()) return;
    if(!fileInfo.completeSuffix().contains("so")) return;
    try {
        iniCustomBox(path);
    } catch(const std::exception& e) {
        gPrintExceptionCritical(e);
    }
}

void EffectsLoader::iniCustomBoxes() {
    QDir(eSettings::sSettingsDir()).mkdir("Boxes");
    const QString dirPath = eSettings::sSettingsDir() + "/Boxes";
    QDirIterator dirIt(dirPath, QDirIterator::NoIteratorFlags);
    while(dirIt.hasNext()) iniIfCustomBox(dirIt.next());

    const auto newFileWatcher = QSharedPointer<QFileSystemModel>(
                new QFileSystemModel);
    newFileWatcher->setRootPath(dirPath);
    connect(newFileWatcher.get(), &QFileSystemModel::directoryLoaded,
            this, [this, newFileWatcher]() {
        disconnect(newFileWatcher.get(), &QFileSystemModel::directoryLoaded,
                   this, nullptr);
        connect(newFileWatcher.get(), &QFileSystemModel::rowsInserted, this,
        [newFileWatcher](const QModelIndex &parent, int first, int last) {
            for(int row = first; row <= last; row++) {
                const auto rowIndex = newFileWatcher->index(row, 0, parent);
                const QString path = newFileWatcher->filePath(rowIndex);
                iniIfCustomBox(path);
            }
        });
    });
}

#include "PathEffects/custompatheffect.h"
#include "PathEffects/custompatheffectcreator.h"
void iniCustomPathEffect(const QString& path) {
    try {
        CustomPathEffectCreator::sLoadCustom(path);
    } catch(...) {
        RuntimeThrow("Error while loading PathEffect from '" + path + "'");
    }
}

void iniIfCustomPathEffect(const QString& path) {
    const QFileInfo fileInfo(path);
    if(!fileInfo.isFile()) return;
    if(!fileInfo.completeSuffix().contains("so")) return;
    try {
        iniCustomPathEffect(path);
    } catch(const std::exception& e) {
        gPrintExceptionCritical(e);
    }
}

void EffectsLoader::iniCustomPathEffects() {
    QDir(eSettings::sSettingsDir()).mkdir("PathEffects");
    const QString dirPath = eSettings::sSettingsDir() + "/PathEffects";
    QDirIterator dirIt(dirPath, QDirIterator::NoIteratorFlags);
    while(dirIt.hasNext()) iniIfCustomPathEffect(dirIt.next());

    const auto newFileWatcher = QSharedPointer<QFileSystemModel>(
                new QFileSystemModel);
    newFileWatcher->setRootPath(dirPath);
    connect(newFileWatcher.get(), &QFileSystemModel::directoryLoaded,
            this, [this, newFileWatcher]() {
        disconnect(newFileWatcher.get(), &QFileSystemModel::directoryLoaded,
                   this, nullptr);
        connect(newFileWatcher.get(), &QFileSystemModel::rowsInserted, this,
        [newFileWatcher](const QModelIndex &parent, int first, int last) {
            for(int row = first; row <= last; row++) {
                const auto rowIndex = newFileWatcher->index(row, 0, parent);
                const QString path = newFileWatcher->filePath(rowIndex);
                iniIfCustomPathEffect(path);
            }
        });
    });
}

#include "RasterEffects/customrastereffect.h"
#include "RasterEffects/customrastereffectcreator.h"
void EffectsLoader::iniCustomRasterEffect(const QString& soPath) {
    try {
        CustomRasterEffectCreator::sLoadCustom(soPath);
    } catch(...) {
        RuntimeThrow("Error while loading RasterEffect from '" + soPath + "'");
    }
}

void EffectsLoader::iniIfCustomRasterEffect(const QString& path) {
    const QFileInfo fileInfo(path);
    if(!fileInfo.isFile()) return;
    if(!fileInfo.completeSuffix().contains("so")) return;
    try {
        iniCustomRasterEffect(path);
    } catch(const std::exception& e) {
        gPrintExceptionCritical(e);
    }
}

void EffectsLoader::iniCustomRasterEffects() {
    QDir(eSettings::sSettingsDir()).mkdir("RasterEffects");
    const QString dirPath = eSettings::sSettingsDir() + "/RasterEffects";
    QDirIterator dirIt(dirPath, QDirIterator::NoIteratorFlags);
    while(dirIt.hasNext()) iniIfCustomRasterEffect(dirIt.next());

    const auto newFileWatcher = QSharedPointer<QFileSystemModel>(new QFileSystemModel);
    newFileWatcher->setRootPath(dirPath);
    connect(newFileWatcher.get(), &QFileSystemModel::directoryLoaded,
            this, [this, newFileWatcher]() {
        disconnect(newFileWatcher.get(), &QFileSystemModel::directoryLoaded,
                   this, nullptr);
        connect(newFileWatcher.get(), &QFileSystemModel::rowsInserted, this,
        [this, newFileWatcher](const QModelIndex &parent, int first, int last) {
            for(int row = first; row <= last; row++) {
                const auto rowIndex = newFileWatcher->index(row, 0, parent);
                const QString path = newFileWatcher->filePath(rowIndex);
                iniIfCustomRasterEffect(path);
            }
        });
    });
}

void EffectsLoader::reloadProgram(ShaderEffectCreator* const loaded,
                                  const QString &fragPath) {
    try {
        makeCurrent();
        loaded->reloadProgram(this, fragPath);
        emit programChanged(&*loaded->fProgram);
        doneCurrent();
    } catch(const std::exception& e) {
        doneCurrent();
        gPrintExceptionCritical(e);
    }
}

void EffectsLoader::iniShaderEffects() {
    makeCurrent();
    QDir(eSettings::sSettingsDir()).mkdir("ShaderEffects");
    const QString dirPath = eSettings::sSettingsDir() + "/ShaderEffects";
    QDirIterator dirIt(dirPath, QDirIterator::NoIteratorFlags);

    while(dirIt.hasNext()) {
        const QString path = dirIt.next();
        const QFileInfo fileInfo(path);
        if(!fileInfo.isFile()) continue;
        if(fileInfo.suffix() != "gre") continue;
        try {
            iniShaderEffectProgramExec(path);
        } catch(const std::exception& e) {
            gPrintExceptionCritical(e);
        }
    }

    const auto newFileWatcher = QSharedPointer<QFileSystemModel>(
                new QFileSystemModel);
    newFileWatcher->setRootPath(dirPath);
    connect(newFileWatcher.get(), &QFileSystemModel::directoryLoaded,
            this, [this, newFileWatcher]() {
        disconnect(newFileWatcher.get(), &QFileSystemModel::directoryLoaded,
                   this, nullptr);
        connect(newFileWatcher.get(), &QFileSystemModel::rowsInserted, this,
        [this, newFileWatcher](const QModelIndex &parent, int first, int last) {
            for(int row = first; row <= last; row++) {
                const auto rowIndex = newFileWatcher->index(row, 0, parent);
                const QString path = newFileWatcher->filePath(rowIndex);
                const QFileInfo fileInfo(path);
                if(!fileInfo.isFile()) return;
                const QString suffix = fileInfo.suffix();
                QString grePath;
                QString fragPath;
                if(suffix == "gre") {
                    fragPath = fileInfo.path() + "/" +
                            fileInfo.completeBaseName() + ".frag";
                    if(!QFile(fragPath).exists()) continue;
                    grePath = path;
                } else if(suffix == "frag") {
                    grePath = fileInfo.path() + "/" +
                            fileInfo.completeBaseName() + ".gre";
                    fragPath = path;
                    if(!QFile(grePath).exists()) continue;
                } else continue;
                if(mLoadedGREPaths.contains(grePath)) continue;
                iniSingleRasterEffectProgram(grePath);
            }
        });
    });
    doneCurrent();
}

void EffectsLoader::iniSingleRasterEffectProgram(const QString& grePath) {
    try {
        makeCurrent();
        iniShaderEffectProgramExec(grePath);
        doneCurrent();
    } catch(const std::exception& e) {
        doneCurrent();
        gPrintExceptionCritical(e);
    }
}

void EffectsLoader::iniShaderEffectProgramExec(const QString& grePath) {
    if(!QFile(grePath).exists()) return;
    const QFileInfo fileInfo(grePath);
    const QString fragPath = fileInfo.path() + "/" +
            fileInfo.completeBaseName() + ".frag";
    if(!QFile(fragPath).exists()) return;
    try {
        const auto loaded = ShaderEffectCreator::sLoadFromFile(this, grePath).get();
        mLoadedGREPaths << grePath;

        const auto newFileWatcher = QSharedPointer<QFileSystemWatcher>(
                    new QFileSystemWatcher);
        newFileWatcher->addPath(fragPath);
        connect(newFileWatcher.get(), &QFileSystemWatcher::fileChanged,
                this, [this, loaded, fragPath, newFileWatcher]() {
            reloadProgram(loaded, fragPath);
        });
    } catch(...) {
        const auto newFileWatcher = QSharedPointer<QFileSystemWatcher>(
                    new QFileSystemWatcher);
        newFileWatcher->addPath(grePath);
        newFileWatcher->addPath(fragPath);
        connect(newFileWatcher.get(), &QFileSystemWatcher::fileChanged,
                this, [this, grePath]() {
            iniSingleRasterEffectProgram(grePath);
        });
        RuntimeThrow("Error while loading ShaderEffect from '" + grePath + "'");
    }
}
