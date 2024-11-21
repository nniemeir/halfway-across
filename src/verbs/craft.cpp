#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/recipe.h"

void Handling::craft(MainWindow *mainWindow, QString target) {
  auto targetRecipe =
      recipeBookObj.searchRecipeBook(playerObj.getRecipeBook(), target);

  if (targetRecipe) {
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
    if (canCraftTarget) {
      sfxPlayer.play("qrc:/audio/sfx/craft.mp3", sfxPlayer.getdefSfxVol(),
                     false);
      mainWindow->setDescription(
          QString("I crafted %1 %2.")
              .arg(handlingObj.getArticle(target), target.toLower()));

      int recipeIndex = inventoryObj.searchInventory(
          playerObj.getInventory(), targetRecipe->getRecipeName());
      inventoryObj.addItem(playerObj.getInventory(),
                           targetRecipe->getOutputItem(), recipeIndex);

      for (int index : ingredientIndices) {
        inventoryObj.removeItem(playerObj.getInventory(), index);
      }
    } else {
      mainWindow->setDescription(
          QString("I didn't have the resources to make %1 %2.")
              .arg(getArticle(target), target.toLower()));
    }
  } else {
    mainWindow->setDescription(QString("I didn't know how to make %1 %2.")
                                   .arg(getArticle(target), target.toLower()));
  }
}
