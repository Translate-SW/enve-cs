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

#ifndef EXPRESSIONHIGHLIGHTER_H
#define EXPRESSIONHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include "Animators/qrealanimator.h"

class ExpressionEditor;

class ExpressionHighlighter : public QSyntaxHighlighter {
public:
    ExpressionHighlighter(QrealAnimator* const target,
                          ExpressionEditor* const editor,
                          QTextDocument *parent);

    void setCursor(const QTextCursor& cursor);

    void addVariable(const QString& name);
    void removeVariable(const QString& name);
protected:
    void highlightBlock(const QString &text) override;
private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    int mCursorPos = 0;
    QTextCursor mOldCursor;

    QTextCharFormat mAssignFormat;
    QTextCharFormat mPropPathFormat;
    QTextCharFormat mErrorFormat;

    QStringList mVariables;
    QVector<HighlightingRule> mHighlightingRules;
    QVector<HighlightingRule> mFuncRules;

    QRegularExpression mPropSetRegex;
    QRegularExpression mFrameValueSetRegex;

    QStringList mVariablesComplete;
    QStringList mBaseComplete;
    QStringList mBaseVarsComplete;

    QrealAnimator* const mTarget;
    ComplexAnimator* const mSearchCtxt;
    ExpressionEditor* const mEditor;
};

#endif // EXPRESSIONHIGHLIGHTER_H
