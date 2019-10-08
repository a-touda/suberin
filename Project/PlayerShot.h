#pragma once

#include	"Mof.h"

//ˆÚ“®‘¬“x
#define		PLAYERSHOT_SPEED		6

class CPlayerShot {
private:
	CTexture*				m_pTexture;
	float					m_PosX;
	float					m_PosY;
	bool					m_bShow;
	bool					m_bUemuki;
	bool					m_bSitamuki;
	bool					m_bMigimuki;
	bool					m_bHidarimuki;
	bool					m_bMove;

public:
	CPlayerShot();
	~CPlayerShot();
	void Initialize();
	void Fire(float px,float py);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight()); }
};