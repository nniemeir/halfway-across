#ifndef ITEM_H
#define ITEM_H
#include <qstring.h>

class Item {
public:
    // Constructors
    Item()
        : name(""), amount(0), active(0), effect(0), type(""), payload("NONE") {}
    Item(const QString &n, int a, int act, int eff, const QString &t, const QString &p)
        : name(n), amount(a), active(act), effect(eff), type(t), payload(p) {}

    Item cookMeat(const Item &raw) const {
        return Item("COOKED " + raw.name, 1, 0, raw.effect, "FOOD", "NONE");
    }

    QString getName() const;
    int getAmount() const;
    int getActive() const;
    int getEffect() const;
    QString getType() const;
    QString getPayload() const;
    void setEffect(int value);
    void setActive(int value);
    void setQuantity(int value);

private:
    QString name;
    int amount;
    int active;
    int effect;
    QString type;
    QString payload;
};

#endif // ITEM_H
