#include	"GameApp.h"
#include	"Gameselect.h"
#include	"GameDefine.h"

//�ύX����V�[���i�O���Q�ƁA���̂�GameApp.cpp�j
extern int		gChangeScene;

extern int		SelectStage;

CFont			gFont;
/**
 * �R���X�g���N�^
 *
 */
CGameselect::CGameselect() {
}

/**
 * �f�X�g���N�^
 *
 */
CGameselect::~CGameselect() {
}

/**
*	�ǂݍ���
*	���p����e�N�X�`����ǂݍ���
*/
bool CGameselect::Load(void) {
	//�e�N�X�`���̓ǂݍ���
	if (!m_Texture.Load(""))
	{
		return false;
	}

	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGameselect::Initialize(void) {
	m_bEnd = false;

	//�����̑傫���ݒ�
	gFont.Create(40, "");
}

/**
 * �X�V
 *
 */
void CGameselect::Update(void) {
	//Enter�L�[�őI�������Q�[����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAME;
	}

	//SPACE�L�[�Ń^�C�g����ʂɖ߂�
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_TITLE;
	}

	//���E�L�[�ŃX�e�[�W��I��
	if (g_pInput->IsKeyPush(MOFKEY_LEFT))
	{
		SelectStage -= 1;
		if (SelectStage < 0)
		{
			SelectStage = 0;
		}

	}
	else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
	{
		SelectStage += 1;
		if (SelectStage > 2)
		{
			SelectStage = 2;
		}
	}
	
}

/**
 * �`��
 *
 */
void CGameselect::Render(void) {
	CGraphicsUtilities::RenderString(10, 10, "�X�e�[�W�I�����");
	CGraphicsUtilities::RenderString(10, 40, "�㉺�L�[�ŃX�e�[�W�I��");
	CGraphicsUtilities::RenderString(950, 680, "SPACE�L�[�Ń^�C�g���ɖ߂�");

	if (SelectStage == 0)
	{
		gFont.RenderString(120, 200, MOF_COLOR_RED, "�X�e�[�W�P");
	}
	else
	{
		gFont.RenderString(120, 200, MOF_COLOR_WHITE, "�X�e�[�W�P");
	}

	if (SelectStage == 1)
	{
		gFont.RenderString(520, 200, MOF_COLOR_RED, "�X�e�[�W�Q");
	}
	else
	{
		gFont.RenderString(520, 200, MOF_COLOR_WHITE, "�X�e�[�W�Q");
	}

	if (SelectStage == 2)
	{
		gFont.RenderString(920, 200, MOF_COLOR_RED, "�X�e�[�W�R");
	}
	else
	{
		gFont.RenderString(920, 200, MOF_COLOR_WHITE, "�X�e�[�W�R");
	}

}

/**
*	���
*/
void CGameselect::Release(void) {
	//�e�N�X�`���̉��
	m_Texture.Release();

	//�t�H���g�̉��
	gFont.Release();
}