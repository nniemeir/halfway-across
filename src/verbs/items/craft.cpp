#include "core/handling/inputhandler.h"
#include "core/handling/verbhandler.h"
#include "entities/player.h"
#include "items/recipe.h"

void VerbHandler::craft(MainWindow *mainWindow, QString target) {
  auto targetRecipe =
      recipeBookObj.searchRecipeBook(playerObj.getRecipeBook(), target);
  if (!targetRecipe) {
    mainWindow->setDescription(
        QString("I didn't know how to make %1 %2.")
            .arg(inputHandlerObj.getArticle(target), target.toLower()));
    return;
  }

  const auto &ingredients = targetRecipe->getIngredients();
  std::vector<int> ingredientIndices;
  bool canCraftTarget = true;

  for (const auto &ingredient : ingredients) {
    int ingredientIndex =
        inventoryObj.searchInventory(playerObj.getInventory(), ingredient);
    if (ingredientIndex == ITEM_NOT_FOUND) {
      canCraftTarget = false;
      break;
    }
    ingredientIndices.push_back(ingredientIndex);
  }

  if (!canCraftTarget) {
    mainWindow->setDescription(
        QString("I didn't have the resources to make %1 %2.")
            .arg(inputHandlerObj.getArticle(target), target.toLower()));
    return;
  }

  int recipeIndex = inventoryObj.searchInventory(playerObj.getInventory(),
                                                 targetRecipe->getRecipeName());
  inventoryObj.addItem(playerObj.getInventory(), targetRecipe->getOutputItem(),
                       recipeIndex);

  for (int index : ingredientIndices) {
    inventoryObj.removeItem(playerObj.getInventory(), index);
  }

  mainWindow->playSfx("qrc:/audio/sfx/craft.mp3");
  mainWindow->setDescription(
      QString("I crafted %1 %2.")
          .arg(inputHandlerObj.getArticle(target), target.toLower()));
}
