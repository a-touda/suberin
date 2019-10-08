#include	"GameApp.h"
#include	"Gameselect.h"
#include	"GameDefine.h"

//変更するシーン（外部参照、実体はGameApp.cpp）
extern int		gChangeScene;

extern int		SelectStage;

CFont			gFont;
/**
 * コンストラクタ
 *
 */
CGameselect::CGameselect() {
}

/**
 * デストラクタ
 *
 */
CGameselect::~CGameselect() {
}

/**
*	読み込み
*	利用するテクスチャを読み込む
*/
bool CGameselect::Load(void) {
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
void CGameselect::Initialize(void) {
	m_bEnd = false;

	//文字の大きさ設定
	gFont.Create(40, "");
}

/**
 * 更新
 *
 */
void CGameselect::Update(void) {
	//Enterキーで選択したゲーム画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAME;
	}

	//SPACEキーでタイトル画面に戻る
	if (g_pInput->IsKeyPush(MOFKEY_SPACE))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_TITLE;
	}

	//左右キーでステージを選択
	if (g_pInput->IsKeyPush(MOFKEY_LEFT))
	{
		SelectStage -= 1;
		if (SelectStage < 0)
		{
			SelectStage = 0;
		}

	}
	else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
	{
		SelectStage += 1;
		if (SelectStage > 2)
		{
			SelectStage = 2;
		}
	}
	
}

/**
 * 描画
 *
 */
void CGameselect::Render(void) {
	CGraphicsUtilities::RenderString(10, 10, "ステージ選択画面");
	CGraphicsUtilities::RenderString(10, 40, "上下キーでステージ選択");
	CGraphicsUtilities::RenderString(950, 680, "SPACEキーでタイトルに戻る");

	if (SelectStage == 0)
	{
		gFont.RenderString(120, 200, MOF_COLOR_RED, "ステージ１");
	}
	else
	{
		gFont.RenderString(120, 200, MOF_COLOR_WHITE, "ステージ１");
	}

	if (SelectStage == 1)
	{
		gFont.RenderString(520, 200, MOF_COLOR_RED, "ステージ２");
	}
	else
	{
		gFont.RenderString(520, 200, MOF_COLOR_WHITE, "ステージ２");
	}

	if (SelectStage == 2)
	{
		gFont.RenderString(920, 200, MOF_COLOR_RED, "ステージ３");
	}
	else
	{
		gFont.RenderString(920, 200, MOF_COLOR_WHITE, "ステージ３");
	}

}

/**
*	解放
*/
void CGameselect::Release(void) {
	//テクスチャの解放
	m_Texture.Release();

	//フォントの解放
	gFont.Release();
}