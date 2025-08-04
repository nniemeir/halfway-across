#ifndef ITEM_H
#define ITEM_H
#include <QStringList>
#include <qstring.h>

// Contains attributes unique to each item
class Item {
public:
  Item() {};
  Item(const QString &n, const QString &d, const QString &t, const QString &p,
       int a, bool act, int e, int w)
      : name(n), description(d), type(t), payload(p), amount(a), active(act),
        effect(e), weight(w) {}

  Item cookMeat(const Item &raw) const {
    return Item("COOKED " + raw.name, "I could eat it to ease my hunger.",
                "FOOD", "NONE", 1, false, raw.effect, raw.weight);
  }

  // Getters
  QString getName() const;
  QString getDescription() const;
  QString getType() const;
  QString getPayload() const;
  int getAmount() const;
  bool getActive() const;
  int getEffect() const;
  int getWeight() const;
  
  // Setters
  void setAmount(int value);
  void setActive(bool value);
  void setEffect(int value);

private:
  QString name;
  QString description;
  QString type;
  QString payload;
  int amount;
  bool active;
  int effect;
  int weight;
};

#endif
