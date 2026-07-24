/// <summary>
/// SceneManagerから呼び出されてSceneを作成するクラス
/// SceneManagerを触らなくていいように、作成部分をここに分離しておく
/// 作るシーンは、enumで指定してもらうようにした
/// </summary>
/// <author>H.suginuma</author>
#include "SceneFactory.h"
#include <windows.h>
#include <assert.h>
#include"BootScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include"QuestionnaireScene.h"
#include"InputScene.h"

SceneBase* SceneFactory::Create(SCENE_NAME sceneName)
{
	switch (sceneName)
	{
	case SCENE_NAME::BOOT:
		return new BootScene();
		break;
	case SCENE_NAME::TITLE:
		return new TitleScene();
		break;
	case SCENE_NAME::INPUT:
		return new InputScene();
		break;
	case SCENE_NAME::PLAY:
		return new PlayScene();
		break;
	case SCENE_NAME::RESULT:
		return new ResultScene();
		break;
	case SCENE_NAME::QUESTIONNAIRE:
		return new QuestionnaireScene();
		break;
	}
	MessageBox(NULL, ("次のシーンはありません\n"), "SceneFactory", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
