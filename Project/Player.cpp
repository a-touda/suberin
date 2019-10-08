#include	"Player.h"

/**
 * コンストラクタ
 *
 */
CPlayer::CPlayer() :
m_Texture() ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bMove(false) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bJump(false) ,
m_bReverse(false) ,
m_SrcRect(),
m_ShotTexture(),
m_ShotArray(),
m_ShotWait(),
m_bHidarimuki(false),
m_bMigimuki(false),
m_bUemuki(false),
m_bSitamuki(false){
}

/**
 * デストラクタ
 *
 */
CPlayer::~CPlayer(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CPlayer::Load(void){
	//テクスチャの読み込み
	if(!m_Texture.Load("player.png"))
	{
		return false;
	}
	//弾のテクスチャ(読み込みは一つですべての弾にポインタを設定)
	if (!m_ShotTexture.Load("P_missile.png"))
	{
		return false;
	}
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].SetTexture(&m_ShotTexture);
	}
	//アニメーションを作成
	SpriteAnimationCreate anim[] = {
		//待機
		{
			"待機",
			0,0,
			60,64,
			TRUE,{{5,0,0}} 
		},
		//移動
		{
			"移動",
			64,0,
			64,64,
			TRUE,{{5,0,0}} 
		},
		//ジャンプ
		{
			"ジャンプ開始",
			128,0,
			64,64,
			FALSE,{{5,0,0}} 
		},
		{
			"ジャンプ終了",
			240,140,
			64,64,
			FALSE,{{2,0,0},{2,1,0}} 
		},
		//攻撃
		{
			"攻撃",
			0,350,
			90,64,
			FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}} 
		},
	};
	m_Motion.Create(anim,MOTION_COUNT);
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * プレイヤーの位置など状態を初期化したいときに実行する。
 */
void CPlayer::Initialize(void){
	m_PosX = 64;
	m_PosY = 64;
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_bJump = false;
	m_bHidarimuki = false;
	m_bMigimuki = false;
	m_bUemuki = false;
	m_bSitamuki = false;
	m_Motion.ChangeMotion(MOTION_WAIT);
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
}

/**
 * 更新
 *
 */
void CPlayer::Update(void){
	//移動フラグ、このフレームでの移動があったかを保存
	//m_bMove = false;
	//攻撃中、着地の場合の動作
	if(m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_JUMPEND)
	{
		//終了で待機に戻す
		if(m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else
	{
		UpdateKey();
	}
	//移動更新
	UpdateMove();
	//実際に座標を移動させる
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;

	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

/**
 * キー入力による動作更新
 *
 */
void CPlayer::UpdateKey(void){
	//キーボードでの移動
	//入力で直接座標を動かすのではなく、速度を変化させる。
	//攻撃中は移動できないようにする
	if (m_bMove == false)
	{
		
		//移動
		if (m_bHidarimuki == true) 
		{
			if (g_pInput->IsKeyPush(MOFKEY_LEFT))
			{
				m_MoveX = -PLAYER_SPEED;
				m_bMove = true;
			}
		}
		if (m_bMigimuki == true)
		{
			if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
			{
				m_MoveX = PLAYER_SPEED;
				m_bMove = true;
			}
		}
		if (m_bUemuki == true)
		{
			if (g_pInput->IsKeyPush(MOFKEY_UP))
			{
				m_MoveY = -PLAYER_SPEED;
				m_bMove = true;
			}
		}
		if (m_bSitamuki == true)
		{
			if (g_pInput->IsKeyPush(MOFKEY_DOWN))
			{
				m_MoveY = PLAYER_SPEED;
				m_bMove = true;
			}
		}
	}
	//向きを変える
	if (g_pInput->IsKeyPush(MOFKEY_LEFT))
	{
		m_bHidarimuki = true;
		m_bMigimuki = false;
		m_bUemuki = false;
		m_bSitamuki = false;
		m_bReverse = true;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_RIGHT))
	{
		m_bHidarimuki = false;
		m_bMigimuki = true;
		m_bUemuki = false;
		m_bSitamuki = false;
		m_bReverse = false;
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
	//弾の発射
	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyHold(MOFKEY_A))
		{
			for (int i = 0; i < PLAYERSHOT_COUNT; i++)
			{
				if (m_ShotArray[i].GetShow())
				{
					continue;
				}
				m_ShotWait = PLAYERSHOT_WAIT;
				m_ShotArray[i].Fire(m_PosX + m_Texture.GetWidth() * 0.05f, m_PosY + m_Texture.GetHeight() * 0.05f);
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}
	//弾の更新
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}
	
}

/**
 * 移動更新
 *
 */
void CPlayer::UpdateMove(void){
	
}

/**
 * ステージとの当たり
 *
 * 引数
 * [in]			ox					X埋まり量
 * [in]			oy					Y埋まり量
 */
void CPlayer::CollisionStage(float ox, float oy) {
	m_PosX += ox;
	m_PosY += oy;
	if (m_bMove == true)
	{
		//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
		if (oy < 0 && m_MoveY > 0)
		{
			m_MoveY = 0;
			m_bMove = false;
		}
		else if (oy > 0 && m_MoveY < 0)
		{
			m_MoveY = 0;
			m_bMove = false;
		}
		//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
		if (ox < 0 && m_MoveX > 0)
		{
			m_MoveX = 0;
			m_bMove = false;
		}
		else if (ox > 0 && m_MoveX < 0)
		{
			m_MoveX = 0;
			m_bMove = false;
		}
	}
}
/**
 * 描画
 *
 */
void CPlayer::Render(float wx,float wy){
	//描画矩形
	CRectangle dr = m_SrcRect;
	//描画位置
	float px = m_PosX - wx;
	float py = m_PosY - wy;
	//反転フラグがONの場合描画矩形を反転させる
	if(m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
		if(m_Motion.GetMotionNo() == MOTION_ATTACK)
		{
			px -= PLAYER_ATTACKWIDTH;
		}
	}
	//テクスチャの描画
	m_Texture.Render(px,py,dr);

	//弾の描画
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].Render();
	}

		
}

/**
 * デバッグ描画
 *
 */
void CPlayer::RenderDebug(float wx,float wy){
	//位置の描画
	CGraphicsUtilities::RenderString(10,70,"プレイヤー位置 X : %.0f , Y : %.0f",m_PosX,m_PosY);
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx,hr.Top -wy,hr.Right - wx,hr.Bottom - wy,MOF_XRGB(0,255,0));
	//攻撃の当たり判定表示
	if(IsAttack())
	{
		CRectangle hr = GetAttackRect();
		CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255,0,0));
	}
	//弾の描画
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_ShotArray[i].RenderDebug();
	}
}

/**
 * 解放
 *
 */
void CPlayer::Release(void){
	m_Texture.Release();
	m_Motion.Release();
	m_ShotTexture.Release();
}
