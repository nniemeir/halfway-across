#include "../include/item.h"

QString Item::getName() const { return name; }

int Item::getAmount() const { return amount; }

int Item::getActive() const { return active; }

int Item::getEffect() const { return effect; }

QString Item::getType() const { return type; }

QString Item::getPayload() const { return payload; }

void Item::setEffect(int value) { effect = value; }

void Item::setActive(int value) { active = value; }

void Item::setQuantity(int value) { amount = value; }
