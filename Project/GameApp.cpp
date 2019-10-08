/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"

#include	"GameDefine.h"
#include	"Title.h"
#include	"Game.h"
#include	"GameClear.h"
#include	"GameOver.h"
#include	"Gameselect.h"

//���݂̃V�[��
int						gScene = SCENENO_TITLE;
//�ύX����V�[��
int						gChangeScene = SCENENO_TITLE;

//�e�V�[���N���X
CTitle					gTitleScene;
CGame					gGameScene;
CGameselect             gGameselectScene;
CGameClear				gGameClearScene;
CGameOver				gGameOverScene;

//�f�o�b�O�\���t���O
bool					g_bDebug = false;

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");
	//�^�C�g����ʂ̑f�ނ̓ǂݍ���
	gTitleScene.Load();

	//�Q�[���I����ʂ̑f�ނ̓ǂݍ���
	gGameselectScene.Load();

	//�Q�[����ʂ̑f�ނ̓ǂݍ���
	gGameScene.Load();
	gGameClearScene.Load();
	gGameOverScene.Load();

	//�ŏ��Ɏ��s�����V�[���̏�����
	gTitleScene.Initialize();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();
	
	//�V�[���ԍ��ɂ���čX�V
	switch (gScene)
	{
	case SCENENO_TITLE:			gTitleScene.Update();			break;
	case SCENENO_GAME:			gGameScene.Update();			break;
	case SCENENO_GAMESELECT:	gGameselectScene.Update();		break;
	case SCENENO_GAMECLEAR:		gGameClearScene.Update();		break;
	case SCENENO_GAMEOVER:		gGameOverScene.Update();		break;
	}


	//�V�[�����I�����Ă���ꍇ�A���̃V�[���ԍ����X�V
	switch (gScene)
	{
	case SCENENO_TITLE:
		if (gTitleScene.IsEnd()) { gChangeScene = gTitleScene.GetNextScene(); }					break;
	case SCENENO_GAME:
		if (gGameScene.IsEnd()) { gChangeScene = gGameScene.GetNextScene(); }					break;
	case SCENENO_GAMESELECT:
		if (gGameselectScene.IsEnd()) { gChangeScene = gGameselectScene.GetNextScene(); }		break;
	case SCENENO_GAMECLEAR:
		if (gGameClearScene.IsEnd()) { gChangeScene = gGameClearScene.GetNextScene(); }			break;
	case SCENENO_GAMEOVER:
		if (gGameOverScene.IsEnd()) { gChangeScene = gGameOverScene.GetNextScene(); }			break;
	}


	//�V�[���ύX���������ꍇ�ύX��V�[���̏�����
	if (gChangeScene != gScene)
	{
		switch (gChangeScene)
		{
		case SCENENO_TITLE:			gTitleScene.Initialize();			break;
		case SCENENO_GAME:			gGameScene.Initialize();			break;
		case SCENENO_GAMESELECT:	gGameselectScene.Initialize();		break;
		case SCENENO_GAMECLEAR:		gGameClearScene.Initialize();		break;
		case SCENENO_GAMEOVER:		gGameOverScene.Initialize();		break;
		}
		gScene = gChangeScene;
	}

	//�f�o�b�O�\���̐؂�ւ�
	if(g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = ((g_bDebug) ? false : true);
	}
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);
	
	//�V�[���ԍ��ɂ���ĕ`��
	switch(gScene)
	{
		case SCENENO_TITLE:
			gTitleScene.Render();
			break;
		case SCENENO_GAME:
			gGameScene.Render();
			break;
		case SCENENO_GAMECLEAR:
			gGameClearScene.Render();
			break;
		case SCENENO_GAMEOVER:
			gGameOverScene.Render();
			break;
	}
	
	//�V�[���ԍ��ɂ���ĕ`��
	switch (gScene)
	{
	case SCENENO_TITLE:			gTitleScene.Render();		break;
	case SCENENO_GAME:			gGameScene.Render();		break;
	case SCENENO_GAMESELECT:	gGameselectScene.Render();	break;
	case SCENENO_GAMECLEAR:		gGameClearScene.Render();	break;
	case SCENENO_GAMEOVER:		gGameOverScene.Render();    break;
	}

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void){
	gTitleScene.Release();
	gGameScene.Release();
	gGameselectScene.Release();
	gGameClearScene.Release();
	gGameOverScene.Release();
	return TRUE;
}