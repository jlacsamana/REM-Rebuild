#include "GameScene.h"
#include "editor-support/cocostudio/CocosStudioExtension.h"

USING_NS_CC;


Scene* GameScene::createScene()
{
    return GameScene::create();
}



bool GameScene::init()
{
    if (!Scene::init())

    {

        return false;

    }




    return true;

}