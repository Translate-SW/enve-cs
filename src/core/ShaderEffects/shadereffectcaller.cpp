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

#include "shadereffectcaller.h"

#include "shadereffectprogram.h"

ShaderEffectCaller::ShaderEffectCaller(std::unique_ptr<ShaderEffectJS>&& engine,
                                       const ShaderEffectProgram &program) :
    RasterEffectCaller(HardwareSupport::gpuOnly, false, QMargins()),
    mEngine(std::move(engine)), mProgramId(program.fId), mProgram(program) {
    Q_ASSERT(mEngine.get());
}

ShaderEffectCaller::~ShaderEffectCaller() {
    mProgram.fEngines.push_back(std::move(mEngine));
}

void ShaderEffectCaller::processGpu(QGL33 * const gl,
                                    GpuRenderTools &renderTools) {

    renderTools.switchToOpenGL(gl);

    renderTools.requestTargetFbo().bind(gl);
    gl->glClear(GL_COLOR_BUFFER_BIT);

    setupProgram(gl);

    gl->glActiveTexture(GL_TEXTURE0);
    renderTools.getSrcTexture().bind(gl);

    gl->glBindVertexArray(renderTools.getSquareVAO());
    gl->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    renderTools.swapTextures();
}

QMargins ShaderEffectCaller::getMargin(const SkIRect &srcRect) {
    mEngine->setSceneRect(srcRect);
    mEngine->evaluate();
    const auto jsVal = mEngine->getMarginValue();
    if(jsVal.isNumber()) {
        return QMargins() + qCeil(jsVal.toNumber());
    } else if(jsVal.isArray()) {
        const int len = jsVal.property("length").toInt();
        if(len == 2) {
            const int valX = qCeil(jsVal.property(0).toNumber());
            const int valY = qCeil(jsVal.property(1).toNumber());

            return QMargins(valX, valY, valX, valY);
        } else if(len == 4) {
            const int valLeft = qCeil(jsVal.property(0).toNumber());
            const int valTop = qCeil(jsVal.property(1).toNumber());
            const int valRight = qCeil(jsVal.property(2).toNumber());
            const int valBottom = qCeil(jsVal.property(3).toNumber());

            return QMargins(valLeft, valTop, valRight, valBottom);
        } else {
            RuntimeThrow("Invalid Margin script");
        }
    } else RuntimeThrow("Invalid Margin script result type");
    return QMargins();
}

void ShaderEffectCaller::setupProgram(QGL33 * const gl) {
    gl->glUseProgram(mProgramId);
    for(const auto& uni : mUniformSpecifiers) uni(gl);
}
