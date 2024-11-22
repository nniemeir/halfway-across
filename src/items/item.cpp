#include "../../include/items/item.h"

QString Item::getName() const { return name; }

int Item::getAmount() const { return amount; }

bool Item::getActive() const { return active; }

int Item::getEffect() const { return effect; }

int Item::getWeight() const { return weight; }

QString Item::getType() const { return type; }

QString Item::getPayload() const { return payload; }

QString Item::getDescription() const { return description; }

void Item::setEffect(int value) { effect = value; }

void Item::setActive(bool value) { active = value; }

void Item::setQuantity(int value) { amount = value; }
