#pragma once

class CTitle {
private:
	bool	m_bEnd;
	int		m_NextScene;
	CTexture				m_Texture;

public:
	CTitle();
	~CTitle();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void Release(void);

	int	GetNextScene() { return m_NextScene; }
	bool IsEnd() { return m_bEnd; }
};