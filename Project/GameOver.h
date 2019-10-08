#pragma once

class CGameOver {
private:
	CTexture				m_BackImage;
	bool					m_bEnd;
	int						m_NextScene;

public:
	CGameOver();
	~CGameOver();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

	int	GetNextScene() { return m_NextScene; }
	bool IsEnd() { return m_bEnd; }
};