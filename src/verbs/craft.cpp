#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/recipe.h"

void Handling::craft(MainWindow *mainWindow, QString target)
{
  auto targetRecipe =
      recipeBookObj.searchRecipeBook(player.getRecipeBook(), target);

  if (targetRecipe)
  {
    const auto &ingredients = targetRecipe->getIngredients();
    std::vector<int> ingredientIndices;
    bool canCraftTarget = true;

    for (const auto &ingredient : ingredients)
    {
      int ingredientIndex =
          inventoryObj.searchInventory(player.getInventory(), ingredient);
      if (ingredientIndex == -1)
      {
        canCraftTarget = false;
        break;
      }
      ingredientIndices.push_back(ingredientIndex);
    }
    if (canCraftTarget)
    {
      sfxPlayer.play("qrc:/audio/sfx/craft.mp3", sfxPlayer.getdefSfxVol(), 0);
      mainWindow->setDescription(QString("I crafted %1 %2.")
                                     .arg(handle.getArticle(target))
                                     .arg(target.toLower()));

      int recipeIndex = inventoryObj.searchInventory(
          player.getInventory(), targetRecipe->getRecipeName());
      inventoryObj.addItem(player.getInventory(), targetRecipe->getOutputItem(),
                           recipeIndex);

      for (int index : ingredientIndices)
      {
        inventoryObj.removeItem(player.getInventory(), index);
      }
    }
    else
    {
      mainWindow->setDescription(
          QString("I didn't have the resources to make %1 %2.")
              .arg(getArticle(target))
              .arg(target.toLower()));
    }
  }
  else
  {
    mainWindow->setDescription(QString("I didn't know how to make %1 %2.")
                                   .arg(getArticle(target))
                                   .arg(target.toLower()));
  }
}
