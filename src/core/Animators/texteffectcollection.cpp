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

#include "texteffectcollection.h"

TextEffectCollection::TextEffectCollection() :
    DynamicComplexAnimator<TextEffect>("text effects") {}

void TextEffectCollection::addEffects(
        QList<TextEffect*> &list) const {
    const auto& children = ca_getChildren();
    for(const auto& effect : children) {
        const auto pEffect = static_cast<TextEffect*>(effect.get());
        if(!pEffect->isVisible()) continue;
        list << pEffect;
    }
}

#include "typemenu.h"
void TextEffectCollection::prp_setupTreeViewMenu(PropertyMenu * const menu) {
    if(menu->hasActionsForType<TextEffectCollection>()) return;
    menu->addedActionsForType<TextEffectCollection>();
    const PropertyMenu::PlainSelectedOp<TextEffectCollection> aOp =
    [](TextEffectCollection * coll) {
        coll->addChild(enve::make_shared<TextEffect>());
    };
    menu->addPlainAction("Add Effect", aOp);
    menu->addSeparator();
    DynamicComplexAnimator<TextEffect>::prp_setupTreeViewMenu(menu);
}
