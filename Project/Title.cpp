#include	"GameApp.h"
#include	"Title.h"
#include	"GameDefine.h"



/**
 * コンストラクタ
 *
 */
CTitle::CTitle() {
}

/**
 * デストラクタ
 *
 */
CTitle::~CTitle() {
}

/**
*	読み込み
*	利用するテクスチャを読み込む
*/
bool CTitle::Load(void) {
	//テクスチャの読み込み
	if (!m_Texture.Load(""))
	{
		return false;
	}

	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CTitle::Initialize(void) {
	m_bEnd = false;
}

/**
 * 更新
 *
 */
void CTitle::Update(void) {
	//Enterキーでゲーム選択画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAMESELECT;
	}
}

/**
 * 描画
 *
 */
void CTitle::Render(void) {
	CGraphicsUtilities::RenderString(10, 10, "タイトル画面");
	CGraphicsUtilities::RenderString(10, 40, "Enterキーで画面遷移");
}

/**
*	解放
*/
void CTitle::Release(void) {
}