#include	"Player.h"

/**
 * �R���X�g���N�^
 *
 */
CPlayer::CPlayer() :
m_Texture() ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bMove(false) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bJump(false) ,
m_bReverse(false) ,
m_SrcRect(),
m_ShotTexture(),
m_ShotArray(),
m_ShotWait(),
m_bHidarimuki(false),
m_bMigimuki(false),
m_bUemuki(false),
m_bSitamuki(false){
}

/**
 * �f�X�g���N�^
 *
 */
CPlayer::~CPlayer(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CPlayer::Load(void){
	//�e�N�X�`���̓ǂݍ���
	if(!m_Texture.Load("player.png"))
	{
		return false;
	}
	//�e�̃e�N�X�`��(�ǂݍ��݂͈�ł��ׂĂ̒e�Ƀ|�C���^��ݒ�)
	if (!m_ShotTexture.Load("P_missile.png"))
	{
		return false;
	}
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].SetTexture(&m_ShotTexture);
	}
	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		//�ҋ@
		{
			"�ҋ@",
			0,0,
			60,64,
			TRUE,{{5,0,0}} 
		},
		//�ړ�
		{
			"�ړ�",
			64,0,
			64,64,
			TRUE,{{5,0,0}} 
		},
		//�W�����v
		{
			"�W�����v�J�n",
			128,0,
			64,64,
			FALSE,{{5,0,0}} 
		},
		{
			"�W�����v�I��",
			240,140,
			64,64,
			FALSE,{{2,0,0},{2,1,0}} 
		},
		//�U��
		{
			"�U��",
			0,350,
			90,64,
			FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}} 
		},
	};
	m_Motion.Create(anim,MOTION_COUNT);
	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * �v���C���[�̈ʒu�ȂǏ�Ԃ��������������Ƃ��Ɏ��s����B
 */
void CPlayer::Initialize(void){
	m_PosX = 64;
	m_PosY = 64;
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_bJump = false;
	m_bHidarimuki = false;
	m_bMigimuki = false;
	m_bUemuki = false;
	m_bSitamuki = false;
	m_Motion.ChangeMotion(MOTION_WAIT);
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
}

/**
 * �X�V
 *
 */
void CPlayer::Update(void){
	//�ړ��t���O�A���̃t���[���ł̈ړ�������������ۑ�
	//m_bMove = false;
	//�U�����A���n�̏ꍇ�̓���
	if(m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_JUMPEND)
	{
		//�I���őҋ@�ɖ߂�
		if(m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else
	{
		UpdateKey();
	}
	//�ړ��X�V
	UpdateMove();
	//���ۂɍ��W���ړ�������
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;

	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

/**
 * �L�[���͂ɂ�铮��X�V
 *
 */
void CPlayer::UpdateKey(void){
	//�L�[�{�[�h�ł̈ړ�
	//���͂Œ��ڍ��W�𓮂����̂ł͂Ȃ��A���x��ω�������B
	//�U�����͈ړ��ł��Ȃ��悤�ɂ���
	if (m_bMove == false)
	{
		
		//�ړ�
		if (m_bHidarimuki == true) 
		{
			if (g_pInput->IsKeyPush(MOFKEY_LEFT))
			{
				m_MoveX = -PLAYER_SPEED;
				m_bMove = true;
			}
		}
		if (m_bMigimuki == true)
		{
			if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
			{
				m_MoveX = PLAYER_SPEED;
				m_bMove = true;
			}
		}
		if (m_bUemuki == true)
		{
			if (g_pInput->IsKeyPush(MOFKEY_UP))
			{
				m_MoveY = -PLAYER_SPEED;
				m_bMove = true;
			}
		}
		if (m_bSitamuki == true)
		{
			if (g_pInput->IsKeyPush(MOFKEY_DOWN))
			{
				m_MoveY = PLAYER_SPEED;
				m_bMove = true;
			}
		}
	}
	//������ς���
	if (g_pInput->IsKeyPush(MOFKEY_LEFT))
	{
		m_bHidarimuki = true;
		m_bMigimuki = false;
		m_bUemuki = false;
		m_bSitamuki = false;
		m_bReverse = true;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
	{
		m_bHidarimuki = false;
		m_bMigimuki = true;
		m_bUemuki = false;
		m_bSitamuki = false;
		m_bReverse = false;
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
	//�e�̔���
	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyHold(MOFKEY_A))
		{
			for (int i = 0; i < PLAYERSHOT_COUNT; i++)
			{
				if (m_ShotArray[i].GetShow())
				{
					continue;
				}
				m_ShotWait = PLAYERSHOT_WAIT;
				m_ShotArray[i].Fire(m_PosX + m_Texture.GetWidth() * 0.05f, m_PosY + m_Texture.GetHeight() * 0.05f);
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}
	//�e�̍X�V
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}
	
}

/**
 * �ړ��X�V
 *
 */
void CPlayer::UpdateMove(void){
	
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CPlayer::CollisionStage(float ox, float oy) {
	m_PosX += ox;
	m_PosY += oy;
	if (m_bMove == true)
	{
		//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
		if (oy < 0 && m_MoveY > 0)
		{
			m_MoveY = 0;
			m_bMove = false;
		}
		else if (oy > 0 && m_MoveY < 0)
		{
			m_MoveY = 0;
			m_bMove = false;
		}
		//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
		if (ox < 0 && m_MoveX > 0)
		{
			m_MoveX = 0;
			m_bMove = false;
		}
		else if (ox > 0 && m_MoveX < 0)
		{
			m_MoveX = 0;
			m_bMove = false;
		}
	}
}
/**
 * �`��
 *
 */
void CPlayer::Render(float wx,float wy){
	//�`���`
	CRectangle dr = m_SrcRect;
	//�`��ʒu
	float px = m_PosX - wx;
	float py = m_PosY - wy;
	//���]�t���O��ON�̏ꍇ�`���`�𔽓]������
	if(m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
		if(m_Motion.GetMotionNo() == MOTION_ATTACK)
		{
			px -= PLAYER_ATTACKWIDTH;
		}
	}
	//�e�N�X�`���̕`��
	m_Texture.Render(px,py,dr);

	//�e�̕`��
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render();
	}

		
}

/**
 * �f�o�b�O�`��
 *
 */
void CPlayer::RenderDebug(float wx,float wy){
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10,70,"�v���C���[�ʒu X : %.0f , Y : %.0f",m_PosX,m_PosY);
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx,hr.Top -wy,hr.Right - wx,hr.Bottom - wy,MOF_XRGB(0,255,0));
	//�U���̓����蔻��\��
	if(IsAttack())
	{
		CRectangle hr = GetAttackRect();
		CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255,0,0));
	}
	//�e�̕`��
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].RenderDebug();
	}
}

/**
 * ���
 *
 */
void CPlayer::Release(void){
	m_Texture.Release();
	m_Motion.Release();
	m_ShotTexture.Release();
}
