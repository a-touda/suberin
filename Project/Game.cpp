#include	"GameDefine.h"
#include	"Game.h"
#include	"Player.h"
#include	"Enemy.h"
#include	"Stage.h"
#include	"GameDefine.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
extern int		gChangeScene;

int			SelectStage;
/**
 * �R���X�g���N�^
 *
 */
CGame::CGame(){
}

/**
 * �f�X�g���N�^
 *
 */
CGame::~CGame(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGame::Load(void){

	//�v���C���[�̑f�ޓǂݍ���
	m_Player.Load();

	//�G�������m��
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];

	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGame::Initialize(void){
	//�}�b�v�̐錾
	char* m_Map[] =
	{
		"Stage2.txt",
		"Stage3.txt",
		"Stage4.txt",
	};

	//�I�񂾃X�e�[�W�̑f�ނ̓ǂݍ���
	m_Stage.Load(m_Map[SelectStage]);

	//�v���C���[�̏�ԏ�����
	m_Player.Initialize();
	m_Stage.Initialize(m_EnemyArray);


	m_bEnd = false;
}

/**
 * �X�V
 *
 */
void CGame::Update(void){
	//�v���C���[�̍X�V
	m_Player.Update();

	//�X�e�[�W�ƃv���C���[�̓����蔻��
	float ox = 0, oy = 0;
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}
	m_Stage.Update(m_Player);

	//�G�̍X�V
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
	}

	//F2�L�[�ŃQ�[���N���A��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAMECLEAR;
	}

	//F3�L�[�ŃQ�[���I�[�o�[��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAMEOVER;
	}
}

/**
 * �`��
 *
 */
void CGame::Render(void){
	//�X�e�[�W�̕`��
	m_Stage.Render();

	//�v���C���[�̕`��
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	//�G�̕`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	//�I�΂ꂽ�X�e�[�W�ŕ\�����ύX
	switch (SelectStage)
	{
	case 0:		CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "�Q�[�����(�P)");		break;
	case 1:		CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "�Q�[�����(�Q)");		break;
	case 2:		CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "�Q�[�����(�R)");		break;
	}
	CGraphicsUtilities::RenderString(10, 40, MOF_COLOR_BLACK, "F2�L�[�ŃQ�[���N���A�AF3�L�[�ŃQ�[���I�[�o�[");
}

/**
 * �f�o�b�O�`��
 *
 */
void CGame::RenderDebug(void){
	//�v���C���[�̃f�o�b�O�`��
	m_Player.RenderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());

	m_Stage.RenderDebug();
}

/**
 * ���
 *
 */
void CGame::Release(void){
	//�X�e�[�W�̉��
	m_Stage.Release();

	//�v���C���[�̉��
	m_Player.Release();

	//�G�̉��
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
}