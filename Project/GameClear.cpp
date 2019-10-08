#include	"GameDefine.h"
#include	"GameClear.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int		gChangeScene;

CFont			gFont2;
/**
 * コンストラクタ
 *
 */
CGameClear::CGameClear() :
	m_BackImage() {
}

/**
 * デストラクタ
 *
 */
CGameClear::~CGameClear() {
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGameClear::Load(void) {
	//テクスチャの読込み
	if (!m_BackImage.Load(""))
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
void CGameClear::Initialize(void) {
	m_bEnd = false;

	gFont2.Create(80, "");
}

/**
 * 更新
 *
 */
void CGameClear::Update(void) {

	//Enterキーでステージ選択画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		gChangeScene = SCENENO_GAMESELECT;
	}
}

/**
 * 描画
 *
 */
void CGameClear::Render(void) {
	m_BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(10, 10, "ゲームクリア画面");
	gFont2.RenderString(430, 100, "GameClear!");
	CGraphicsUtilities::RenderString(520, 300, MOF_COLOR_WHITE, "Press Enter Key");
}

/**
 * デバッグ描画
 *
 */
void CGameClear::RenderDebug(void) {
}

/**
 * 解放
 *
 */
void CGameClear::Release(void) {

	//テクスチャの解放
	m_BackImage.Release();

	//フォントの解放
	gFont2.Release();
}