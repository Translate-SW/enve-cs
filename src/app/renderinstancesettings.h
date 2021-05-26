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

#ifndef RENDERINSTANCESETTINGS_H
#define RENDERINSTANCESETTINGS_H

#include "outputsettings.h"
#include "rendersettings.h"
#include "smartPointers/ememory.h"
#include "Private/esettings.h"
#include "conncontextptr.h"

class Canvas;

enum class RenderState {
    none,
    error,
    finished,
    rendering,
    paused,
    waiting
};

class RenderInstanceSettings : public QObject {
    Q_OBJECT
public:
    RenderInstanceSettings(Canvas* canvas);
    RenderInstanceSettings(const RenderInstanceSettings& src);

    QString getName();
    void setOutputDestination(const QString &outputDestination);
    const QString &getOutputDestination() const;
    void setTargetCanvas(Canvas *canvas, const bool copySceneSettings = true);
    Canvas *getTargetCanvas() const;
    void setCurrentRenderFrame(const int currentRenderFrame);
    int currentRenderFrame();
    const OutputSettings &getOutputRenderSettings() const;
    void setOutputRenderSettings(const OutputSettings &settings);
    const RenderSettings &getRenderSettings() const;
    void setRenderSettings(const RenderSettings &settings);
    void renderingAboutToStart();
    void setCurrentState(const RenderState &state,
                         const QString &text = "");
    const QString &getRenderError() const;
    RenderState getCurrentState() const;
    void setOutputSettingsProfile(OutputSettingsProfile *profile);
    OutputSettingsProfile *getOutputSettingsProfile();

    void write(eWriteStream& dst) const;
    void read(eReadStream& src);
signals:
    void stateChanged(const RenderState state);
    void renderFrameChanged(const int frame);
private:
    RenderState mState = RenderState::none;
    int mCurrentRenderFrame = 0;

    QString mOutputDestination;
    QString mRenderError;

    ConnContextQPtr<OutputSettingsProfile> mOutputSettingsProfile;

    ConnContextQPtr<Canvas> mTargetCanvas;

    RenderSettings mRenderSettings;
    OutputSettings mOutputSettings;
};

#endif // RENDERINSTANCESETTINGS_H
