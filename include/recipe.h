#ifndef RECIPE_H
#define RECIPE_H
#include "item.h"

class Recipe {
public:
    Recipe(){};
    Recipe(const QString &name, const QString &firstIngredient,
             const QString &secondIngrdient, const Item &outputItem);

    QString getRecipeName() const;
    QString getFirstIngredient() const;
    QString getSecondIngredient() const;
    Item getOutputItem() const;

private:
    QString name;
    QString firstIngredient;
    QString secondIngredient;
    Item output;
};

class RecipeBook {
public:
    RecipeBook(){}
    RecipeBook(std::vector<Recipe> &recipeBook);
    std::optional<Recipe> searchRecipeBook(const std::vector<Recipe> &recipeBook, const QString &itemName) const;
};

extern RecipeBook recipeBookObj;
#endif



