#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include    "PlayerShot.h"

//�ړ����x
#define		PLAYER_SPEED			10.0f

//�ړ��ő呬�x
#define		PLAYER_MAXSPEED			10.0f

//�W�����v����
#define		PLAYER_JUMP				-10.0f

//�U����
#define		PLAYER_ATTACKWIDTH		30

//�����蔻�茸����
#define		PLAYER_RECTDECREASE		12

//�e�̔��ˌ��E��
#define     PLAYERSHOT_COUNT        1

//�e�̔��ˊ��o
#define     PLAYERSHOT_WAIT         1



class CPlayer {
private:
	CTexture				m_Texture;
	CSpriteMotionController	m_Motion;
	float					m_PosX;
	float					m_PosY;
	bool					m_bMove;
	bool					m_bUemuki;
	bool					m_bSitamuki;
	bool					m_bMigimuki;
	bool					m_bHidarimuki;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bJump;
	bool					m_bReverse;
	CRectangle				m_SrcRect;
	CTexture                m_ShotTexture;
	CPlayerShot             m_ShotArray[PLAYERSHOT_COUNT];
	int                     m_ShotWait;

	//���[�V������ޒ�`
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMPSTART,
		MOTION_JUMPEND,
		MOTION_ATTACK,

		MOTION_COUNT,
	};
public:
	CPlayer();
	~CPlayer();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void UpdateKey(void);
	void UpdateMove(void);
	void CollisionStage(float ox, float oy);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	bool IsAttack(){ return m_Motion.GetMotionNo() == MOTION_ATTACK; }
	CRectangle GetRect(){
		if(IsAttack())
		{
			return CRectangle(m_PosX + PLAYER_RECTDECREASE,m_PosY + PLAYER_RECTDECREASE,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,m_PosY + m_SrcRect.GetHeight());
		}
		return CRectangle(m_PosX + PLAYER_RECTDECREASE,m_PosY + PLAYER_RECTDECREASE,m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
	}
	CRectangle GetAttackRect(){
		//���]��
		if(m_bReverse)
		{
			return CRectangle(m_PosX - PLAYER_ATTACKWIDTH,m_PosY,m_PosX + PLAYER_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
		}
		return CRectangle(m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,m_PosY,m_PosX + m_SrcRect.GetWidth(),m_PosY + m_SrcRect.GetHeight());
	}
};