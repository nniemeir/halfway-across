#ifndef ITEM_H
#define ITEM_H
#include <QStringList>
#include <qstring.h>

class Item {
public:
  Item(){};
  Item(const QString &n, int a, bool act, int e, int w, const QString &t,
       const QString &p, const QString &d)
      : name(n), amount(a), active(act), effect(e), weight(w), type(t),
        payload(p), description(d) {}

  Item cookMeat(const Item &raw) const {
    return Item("COOKED " + raw.name, 1, false, raw.effect, raw.weight, "FOOD",
                "NONE", "I could eat it to ease my hunger.");
  }

  QString getName() const;
  int getAmount() const;
  bool getActive() const;
  int getEffect() const;
  int getWeight() const;
  QString getType() const;
  QString getPayload() const;
  QString getDescription() const;
  void setEffect(int value);
  void setActive(bool value);
  void setQuantity(int value);

private:
  QString name;
  int amount;
  bool active;
  int effect;
  int weight;
  QString type;
  QString payload;
  QString description;
};

#endif
