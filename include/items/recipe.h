#ifndef RECIPE_H
#define RECIPE_H
#include "item.h"
#include <QStringList>

// Recipes allow the player to craft new items from those that they already possess
class Recipe {
public:
  Recipe(){};
  Recipe(const QString &n, const QString &d, const QStringList &i,
         const Item &o)
      : name(n), description(d), ingredients(i), outputItem(o) {}
  QString getRecipeName() const;
  QString getDescription() const;
  QStringList getIngredients() const;
  Item getOutputItem() const;

private:
  QString name;
  QString description;
  QStringList ingredients;
  Item outputItem;
};

class RecipeBook {
public:
  RecipeBook() {}
  RecipeBook(std::vector<Recipe> &recipeBook);
  std::optional<Recipe> searchRecipeBook(const std::vector<Recipe> &recipeBook,
                                         const QString &itemName) const;
};

extern RecipeBook recipeBookObj;

#endif
