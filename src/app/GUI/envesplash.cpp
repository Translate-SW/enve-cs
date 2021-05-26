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

#include "envesplash.h"

#include <QPainter>

#include "Private/esettings.h"

EnveSplash::EnveSplash() {
    mText = "Vítejte v enve - Software pro 2D animace pro linux! .\n\n"
            "Budoucnost vývoje tohoto programu bude možná pouze s vaší dobrovolnou finanční podporou. "
            "Kliknutím na Podpořit enve nám vyjádříte podporu. .\n\n"
            "Vezměte prosím na vědomí, že hlavní verze nula 0.x.y je pro počáteční vývoj; "
            "proto lze čekávat drobné chybičky, a to se stává.";
    const auto splashPath = eSettings::sIconsDir() + "/splash1.png";
    const QPixmap pixmap(splashPath);
    const int x = qRound(0.03*pixmap.width());
    const int width = qRound(0.94*pixmap.width());
    mTextRect = QRect(x, qRound(0.16*pixmap.height()),
                      width, qRound(0.42*pixmap.height()));
    mMessageRect = QRect(x, qRound(0.65*pixmap.height()),
                         width, qRound(0.08*pixmap.height()));
    mSponsorsRect = QRect(x, qRound(0.72*pixmap.height()),
                        width, qRound(0.24*pixmap.height()));
    mBottomRect = QRect(x, qRound(0.91*pixmap.height()),
                        width, qRound(0.09*pixmap.height()));
    setPixmap(pixmap);
    setFixedSize(pixmap.width(), pixmap.height());
//    setWindowFlag(Qt::WindowStaysOnTopHint);
}

void EnveSplash::drawContents(QPainter * const p) {
    p->setPen(QColor(125, 125, 125));
    p->drawRect(mTextRect);
    p->drawRect(mMessageRect);

    p->setPen(Qt::white);

    QFont font = p->font();
    font.setPointSizeF(font.pointSizeF()*1.5);
    font.setFamily("FreeMono");
    p->setFont(font);
    const int w = width();
    const int marg = w/80;
    p->drawText(mTextRect.adjusted(marg, marg, -marg, -marg),
                Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap, mText);
    p->drawText(mMessageRect, Qt::AlignCenter, message());
    p->setPen(QColor(Qt::gray));
    p->drawText(mSponsorsRect, Qt::AlignVCenter, "Děkujeme za vaši podporu");
    p->drawText(mBottomRect, Qt::AlignVCenter | Qt::AlignLeft, "Maurycy Liebner - hlavní vývojář enve");
    QString rightTxt;
#if defined(LATEST_COMMIT_HASH) && defined(LATEST_COMMIT_DATE)
    const QString date(LATEST_COMMIT_DATE);
    rightTxt = QString(LATEST_COMMIT_HASH) + " " + date.split(" ").first();
#else
    rightTxt = ENVE_VERSION;
#endif
    p->drawText(mBottomRect, Qt::AlignVCenter | Qt::AlignRight, rightTxt);
}

void EnveSplash::mousePressEvent(QMouseEvent *) {
    if(parent()) deleteLater();
}
