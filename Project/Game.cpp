#include	"GameDefine.h"
#include	"Game.h"
#include	"Player.h"
#include	"Enemy.h"
#include	"Stage.h"
#include	"GameDefine.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
extern int		gChangeScene;

int			SelectStage;
/**
 * コンストラクタ
 *
 */
CGame::CGame(){
}

/**
 * デストラクタ
 *
 */
CGame::~CGame(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGame::Load(void){

	//プレイヤーの素材読み込み
	m_Player.Load();

	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];

	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGame::Initialize(void){
	//マップの宣言
	char* m_Map[] =
	{
		"Stage2.txt",
		"Stage3.txt",
		"Stage4.txt",
	};

	//選んだステージの素材の読み込み
	m_Stage.Load(m_Map[SelectStage]);

	//プレイヤーの状態初期化
	m_Player.Initialize();
	m_Stage.Initialize(m_EnemyArray);


	m_bEnd = false;
}

/**
 * 更新
 *
 */
void CGame::Update(void){
	//プレイヤーの更新
	m_Player.Update();

	//ステージとプレイヤーの当たり判定
	float ox = 0, oy = 0;
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}
	m_Stage.Update(m_Player);

	//敵の更新
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);
		}
	}

	//F2キーでゲームクリア画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAMECLEAR;
	}

	//F3キーでゲームオーバー画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		m_bEnd = true;
		m_NextScene = SCENENO_GAMEOVER;
	}
}

/**
 * 描画
 *
 */
void CGame::Render(void){
	//ステージの描画
	m_Stage.Render();

	//プレイヤーの描画
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	//敵の描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	//選ばれたステージで表示文変更
	switch (SelectStage)
	{
	case 0:		CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "ゲーム画面(１)");		break;
	case 1:		CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "ゲーム画面(２)");		break;
	case 2:		CGraphicsUtilities::RenderString(10, 10, MOF_COLOR_BLACK, "ゲーム画面(３)");		break;
	}
	CGraphicsUtilities::RenderString(10, 40, MOF_COLOR_BLACK, "F2キーでゲームクリア、F3キーでゲームオーバー");
}

/**
 * デバッグ描画
 *
 */
void CGame::RenderDebug(void){
	//プレイヤーのデバッグ描画
	m_Player.RenderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());

	m_Stage.RenderDebug();
}

/**
 * 解放
 *
 */
void CGame::Release(void){
	//ステージの解放
	m_Stage.Release();

	//プレイヤーの解放
	m_Player.Release();

	//敵の解放
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
}