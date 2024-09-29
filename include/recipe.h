#ifndef RECIPE_H
#define RECIPE_H
#include "item.h"
#include <QStringList>
class Recipe
{
public:
  Recipe() {};
  Recipe(const QString &name, const QStringList &ingredients,
         const QString &description, const Item &outputItem);

  QString getRecipeName() const;
  QStringList getIngredients() const;
  QString getDescription() const;
  Item getOutputItem() const;

private:
  QString name;
  QStringList ingredients;
  QString description;
  Item output;
};

class RecipeBook
{
public:
  RecipeBook() {}
  RecipeBook(std::vector<Recipe> &recipeBook);
  std::optional<Recipe> searchRecipeBook(const std::vector<Recipe> &recipeBook,
                                         const QString &itemName) const;
};

extern RecipeBook recipeBookObj;
#endif
