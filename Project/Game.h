#pragma once

#include	"Player.h"
#include	"Stage.h"
#include    "PlayerShot.h"
#include	"Enemy.h"

class CGame {
private:
	//ÉvÉåÉCÉÑÅ[
	CPlayer					m_Player;
	CStage					m_Stage;
	CPlayerShot				m_PlayerShot;
	bool					m_bEnd;
	int						m_NextScene;
	CTexture				m_Texture;

	//ìG
	CEnemy*					m_EnemyArray;

public:
	CGame();
	~CGame();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

	int	GetNextScene() { return m_NextScene; }
	bool IsEnd() { return m_bEnd; }
};