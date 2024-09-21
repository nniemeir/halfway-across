#include "../include/recipe.h"

Recipe::Recipe(const QString &name, const QStringList &ingredients,
               const QString &description, const Item &outputItem)
    : name(name), ingredients(ingredients), description(description),
      output(outputItem) {}

RecipeBook recipeBookObj;

QString Recipe::getRecipeName() const { return name; }
QStringList Recipe::getIngredients() const { return ingredients; }
QString Recipe::getDescription() const { return description; }

Item Recipe::getOutputItem() const { return output; }

std::optional<Recipe>
RecipeBook::searchRecipeBook(const std::vector<Recipe> &recipeBook,
                             const QString &itemName) const {
  auto it = std::find_if(recipeBook.begin(), recipeBook.end(),
                         [&itemName](const Recipe &recipe) {
                           return recipe.getRecipeName() == itemName;
                         });

  if (it != recipeBook.end()) {
    return *it;
  } else {
    return std::nullopt;
  }
}
