#include "../../include/audio.h"
#include "../../include/handling.h"
#include "../../include/player.h"
#include "../../include/recipe.h"

void Handling::craft(MainWindow *mainWindow, QString target) {
    auto targetRecipe = recipeBookObj.searchRecipeBook(player.getRecipeBook(), target);
    if (targetRecipe) {
    int ingredient1Index =
        inventoryObj.searchInventory(player.getInventory(), targetRecipe->getFirstIngredient());
    int ingredient2Index =
        inventoryObj.searchInventory(player.getInventory(), targetRecipe->getSecondIngredient());
    if (ingredient1Index != -1 && ingredient2Index != -1) {
        sfxPlayer.play("qrc:/audio/sfx/craft.mp3", sfxPlayer.getdefSfxVol(), 0);
        mainWindow->setDescription(QString("I crafted %1 %2.").arg(handle.getArticle(target)).arg(target.toLower()));
        int resultIndex = inventoryObj.searchInventory(player.getInventory(),
                                                       targetRecipe->getRecipeName());
        inventoryObj.addItem(
            player.getInventory(),
            targetRecipe->getOutputItem(), resultIndex);
        inventoryObj.removeItem(player.getInventory(), ingredient1Index);
        inventoryObj.removeItem(player.getInventory(), ingredient2Index);
    } else {
        mainWindow->setDescription(
            QString("I didn't have the resources to make %1 %2.").arg(getArticle(target)).arg(target));
    }
    } else {
        mainWindow->setDescription(
            QString("I didn't know how to make %1 %2.").arg(getArticle(target)).arg(target));
    }
}
