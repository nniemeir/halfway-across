#include "items/item.h"

QString Item::getName() const { return name; }

QString Item::getDescription() const { return description; }

QString Item::getType() const { return type; }

QString Item::getPayload() const { return payload; }

int Item::getAmount() const { return amount; }

bool Item::getActive() const { return active; }

int Item::getEffect() const { return effect; }

int Item::getWeight() const { return weight; }

void Item::setAmount(int value) { amount = value; }

void Item::setActive(bool value) { active = value; }

void Item::setEffect(int value) { effect = value; }