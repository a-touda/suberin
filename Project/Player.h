#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include    "PlayerShot.h"

//移動速度
#define		PLAYER_SPEED			10.0f

//移動最大速度
#define		PLAYER_MAXSPEED			10.0f

//ジャンプ初速
#define		PLAYER_JUMP				-10.0f

//攻撃幅
#define		PLAYER_ATTACKWIDTH		30

//当たり判定減衰幅
#define		PLAYER_RECTDECREASE		12

//弾の発射限界数
#define     PLAYERSHOT_COUNT        1

//弾の発射感覚
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

	//モーション種類定義
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
		//反転中
		if(m_bReverse)
		{
			return CRectangle(m_PosX - PLAYER_ATTACKWIDTH,m_PosY,m_PosX + PLAYER_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
		}
		return CRectangle(m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE - PLAYER_ATTACKWIDTH,m_PosY,m_PosX + m_SrcRect.GetWidth(),m_PosY + m_SrcRect.GetHeight());
	}
};