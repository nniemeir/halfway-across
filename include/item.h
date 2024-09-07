#ifndef ITEM_H
#define ITEM_H
#include <qstring.h>

struct item {
  QString name;
  int amount;
  int active;
  int effects;
  QString type;
  item() : name(""), amount(0), active(0), effects(0), type("") {}

  // Parameterized constructor
  item(const QString& n, int a, int act, int eff, const QString& t)
      : name(n), amount(a), active(act), effects(eff), type(t) {}

  item makeCookedVersion(item raw) const {
      return item("COOKED " + raw.name, 1, 0, raw.effects, "FOOD");
  }

};

#endif // ITEM_H
