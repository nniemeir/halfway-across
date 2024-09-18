#include "../include/recipe.h"

Recipe::Recipe(const QString &name, const QString &firstIngredient,
               const QString &secondIngredient, const Item &outputItem)
    : name(name), firstIngredient(firstIngredient), secondIngredient(secondIngredient), output(outputItem) {}

RecipeBook recipeBookObj;

QString Recipe::getRecipeName() const {
    return name;
}
QString Recipe::getFirstIngredient() const {
    return firstIngredient;
}
QString Recipe::getSecondIngredient() const {
    return secondIngredient;
}

Item Recipe::getOutputItem() const {
    return output;
}

std::optional<Recipe> RecipeBook::searchRecipeBook(const std::vector<Recipe> &recipeBook, const QString &itemName) const {
    auto it = std::find_if(recipeBook.begin(), recipeBook.end(),
                           [&itemName](const Recipe &recipe) { return recipe.getRecipeName() == itemName; });

    if (it != recipeBook.end()) {
        return *it;
    } else {
        return std::nullopt;
    }
}
