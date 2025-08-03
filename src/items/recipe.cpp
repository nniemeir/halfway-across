#include "items/recipe.h"

QString Recipe::getRecipeName() const { return name; }

QString Recipe::getDescription() const { return description; }

QStringList Recipe::getIngredients() const { return ingredients; }

Item Recipe::getOutputItem() const { return outputItem; }

std::optional<Recipe>
RecipeBook::searchRecipeBook(const std::vector<Recipe> &recipeBook,
                             const QString &itemName) const {
  auto it = std::find_if(recipeBook.begin(), recipeBook.end(),
                         [&itemName](const Recipe &recipe) {
                           return recipe.getRecipeName() == itemName;
                         });

  if (it != recipeBook.end()) {
    return *it;
  }
  return std::nullopt;
}

RecipeBook recipeBookObj;
