#ifndef ITEM_H
#define ITEM_H
#include <qstring.h>

struct item {
  QString name;
  int amount;
  int active;
  int effects;
  QString type;
  QString payload;
  item()
      : name(""), amount(0), active(0), effects(0), type(""), payload("NONE") {}

  item(const QString &n, int a, int act, int eff, const QString &t,
       const QString &p)
      : name(n), amount(a), active(act), effects(eff), type(t), payload(p) {}

  item cookMeat(item raw) const {
    return item("COOKED " + raw.name, 1, 0, raw.effects, "FOOD", "NONE");
  }
};

struct recipe {
  QString name;
  QString firstIngredient;
  QString secondIngredient;
  item output;

  recipe() : name(""), firstIngredient(""), secondIngredient(""), output({}) {}

  recipe(const QString &n, const QString &f, const QString &s, const item &o)
      : name(n), firstIngredient(f), secondIngredient(s), output(o) {}
};

#endif // ITEM_H
