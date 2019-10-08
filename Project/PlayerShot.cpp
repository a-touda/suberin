#include	"PlayerShot.h"

/**
 * コンストラクタ
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
 * デストラクタ
 *
 */
CPlayerShot::~CPlayerShot(){
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
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
 * 発射
 * 引数の座標に位置を設定して、表示フラグをtrueに変更する。
 *
 * 引数
 * [in]			px				発射Ｘ座標
 * [in]			py				発射Ｙ座標
 */
void CPlayerShot::Fire(float px,float py){
	m_PosX =px - m_pTexture->GetWidth();
	m_PosY =py-m_pTexture->GetHeight();
	m_bShow = true;
}

/**
 * 更新
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
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//上に移動
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
 * 描画
 *
 */
void CPlayerShot::Render(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//テクスチャの描画
	m_pTexture->Render(m_PosX,m_PosY);
}

/**
 * デバッグ描画
 *
 */
void CPlayerShot::RenderDebug(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CGraphicsUtilities::RenderRect(m_PosX,m_PosY,m_PosX + m_pTexture->GetWidth(),m_PosY + m_pTexture->GetHeight(),MOF_XRGB(0,255,0));
}