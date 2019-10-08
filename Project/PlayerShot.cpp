#include	"PlayerShot.h"

/**
 * �R���X�g���N�^
 *
 */
CPlayerShot::CPlayerShot() :
m_pTexture(NULL) ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bShow(false),
m_bHidarimuki(false),
m_bMigimuki(true),
m_bUemuki(false),
m_bSitamuki(false),
m_bMove(false){
}

/**
 * �f�X�g���N�^
 *
 */
CPlayerShot::~CPlayerShot(){
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 */
void CPlayerShot::Initialize(){
	m_PosX = 0;
	m_PosY = 0;
	m_bHidarimuki = false;
	m_bMigimuki = true;
	m_bUemuki = false;
	m_bSitamuki = false;
	m_bShow = false;
	m_bMove = false;
}
/**
 * ����
 * �����̍��W�Ɉʒu��ݒ肵�āA�\���t���O��true�ɕύX����B
 *
 * ����
 * [in]			px				���˂w���W
 * [in]			py				���˂x���W
 */
void CPlayerShot::Fire(float px,float py){
	m_PosX =px - m_pTexture->GetWidth();
	m_PosY =py-m_pTexture->GetHeight();
	m_bShow = true;
}

/**
 * �X�V
 *
 */
void CPlayerShot::Update(void){
	if (g_pInput->IsKeyPush(MOFKEY_A))
	{
		m_bMove = true;
	}
	if(m_bMove == false)
	{
		if (g_pInput->IsKeyPush(MOFKEY_LEFT))
		{
			m_bHidarimuki = true;
			m_bMigimuki = false;
			m_bUemuki = false;
			m_bSitamuki = false;
		}
		else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
		{
			m_bHidarimuki = false;
			m_bMigimuki = true;
			m_bUemuki = false;
			m_bSitamuki = false;
		}
		if (g_pInput->IsKeyPush(MOFKEY_UP))
		{
			m_bHidarimuki = false;
			m_bMigimuki = false;
			m_bUemuki = true;
			m_bSitamuki = false;
		}
		if (g_pInput->IsKeyPush(MOFKEY_DOWN))
		{
			m_bHidarimuki = false;
			m_bMigimuki = false;
			m_bUemuki = false;
			m_bSitamuki = true;
		}
	}
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//��Ɉړ�
	if (m_bHidarimuki == true)
	{
		m_PosX -= PLAYERSHOT_SPEED;
	}
	else if (m_bMigimuki == true)
	{
		m_PosX += PLAYERSHOT_SPEED;
	}
	if (m_bUemuki == true)
	{
		m_PosY -= PLAYERSHOT_SPEED;
	}
	if (m_bSitamuki == true)
	{
		m_PosY += PLAYERSHOT_SPEED;
	}
	
	if (m_PosX < 64)
	{
		m_bShow = false;
		m_bMove = false;
	}
	if (m_PosX > 64 * 50)
	{
		m_bShow = false;
		m_bMove = false;
	}
	if (m_PosY < 64)
	{
		m_bShow = false;
		m_bMove = false;
	}
	if (m_PosY > 64 * 25)
	{
		m_bShow = false;
		m_bMove = false;
	}
}

/**
 * �`��
 *
 */
void CPlayerShot::Render(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX,m_PosY);
}

/**
 * �f�o�b�O�`��
 *
 */
void CPlayerShot::RenderDebug(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CGraphicsUtilities::RenderRect(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight(),MOF_XRGB(0,255,0));
}