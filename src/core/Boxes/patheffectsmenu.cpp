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

#include "patheffectsmenu.h"

template <typename T, typename U>
void addPathEffectActionToMenu(const QString& text, PropertyMenu * const menu,
                               void (U::*adder)(const qsptr<PathEffect>&)) {
    menu->addPlainAction<U>(text, [adder](U * obj) {
        (obj->*adder)(enve::make_shared<T>());
    });
}

#include "PathEffects/custompatheffectcreator.h"
template <typename U>
void addPathEffectsActionToMenu(PropertyMenu * const menu, const U &adder) {
    addPathEffectActionToMenu<DisplacePathEffect>(
                "Displace", menu, adder);
    addPathEffectActionToMenu<SpatialDisplacePathEffect>(
                "Spatial Displace", menu, adder);
    addPathEffectActionToMenu<DashPathEffect>(
                "Dash", menu, adder);
    addPathEffectActionToMenu<DuplicatePathEffect>(
                "Duplicate", menu, adder);
    addPathEffectActionToMenu<SubPathEffect>(
                "Sub-Path", menu, adder);
    addPathEffectActionToMenu<SolidifyPathEffect>(
                "Solidify", menu, adder);
    addPathEffectActionToMenu<SumPathEffect>(
                "Sum", menu, adder);
    addPathEffectActionToMenu<LinesPathEffect>(
                "Lines", menu, adder);
    addPathEffectActionToMenu<ZigZagPathEffect>(
                "ZigZag", menu, adder);
    addPathEffectActionToMenu<SubdividePathEffect>(
                "Subdivide", menu, adder);
    CustomPathEffectCreator::sAddToMenu(menu, adder);
}

void PathEffectsMenu::addPathEffectsToBoxActionMenu(PropertyMenu * const menu) {
    if(menu->hasSharedMenu("Path Effects")) return;
    menu->addSharedMenu("Path Effects");
    menu->addSection("Path Effects");

    const auto pathEffectsMenu = menu->addMenu("Path Effects");
    addPathEffectsActionToMenu(pathEffectsMenu,
                               &BoundingBox::addPathEffect);

    const auto fillPathEffectsMenu = menu->addMenu("Fill Effects");
    addPathEffectsActionToMenu(fillPathEffectsMenu,
                               &BoundingBox::addFillPathEffect);

    const auto outlineBasePathEffectsMenu = menu->addMenu("Outline Base Effects");
    addPathEffectsActionToMenu(outlineBasePathEffectsMenu,
                               &BoundingBox::addOutlineBasePathEffect);

    const auto outlinePathEffectsMenu = menu->addMenu("Outline Effects");
    addPathEffectsActionToMenu(outlinePathEffectsMenu,
                               &BoundingBox::addOutlinePathEffect);
}

#include "PathEffects/patheffectcollection.h"
void PathEffectsMenu::addPathEffectsToCollectionActionMenu(PropertyMenu * const menu) {
    const auto addEffectMenu = menu->addMenu("Add Effect");
    addPathEffectsActionToMenu(addEffectMenu, &PathEffectCollection::addChild);
}
