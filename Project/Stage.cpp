#include	"Stage.h"

/**
 * コンストラクタ
 *
 */
CStage::CStage() :
m_ChipTexture() ,
m_BackTexture() ,
m_ChipSize(0) ,
m_XCount(0) ,
m_YCount(0) ,
m_pChipData(NULL) ,
m_ScrollX(0) ,
m_ScrollY(0) ,
m_EnemyTextureCount(0) ,
m_pEnemyTexture(NULL) ,
m_EnemyCount(0) {
}

/**
 * デストラクタ
 *
 */
CStage::~CStage(){
}

/**
 * 読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			pName				ステージファイルの名前
 */
bool CStage::Load(char* pName){
	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}

	//ファイルの全容を調べる
	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fsize + 1);
	//ファイルを全てバッファに読み込む
	fsize - fread(pBuffer, 1, fsize, fp);
	pBuffer[fsize] = '\0';
	char* pstr;

	//テクスチャの読み込み
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr))
	{
		return false;
	}
	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr))
	{
		return false;
	}

	//チップサイズ
	pstr = strtok(NULL, ",");
	m_ChipSize = atof(pstr);

	//マップのチップ数
	pstr = strtok(NULL, ",");
	m_XCount = atoi(pstr);
	pstr = strtok(NULL, ",");
	m_YCount = atoi(pstr);

	//マップのメモリ確保
	m_pChipData = (char*)malloc(m_XCount * m_YCount);

	//チップデータの読み込み
	for (int y = 0; y < m_YCount; y++)
	{
		for (int X = 0; X < m_XCount; X++)
		{
			pstr = strtok(NULL, ",");
			m_pChipData[y * m_XCount + X] = atoi(pstr);
		}
	}

	//敵のテクスチャの読み込み
	pstr = strtok(NULL, ",");
	m_EnemyTextureCount = atoi(pstr);
	m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
	for (int i = 0; i < m_EnemyTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pEnemyTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pEnemyData = (char*)malloc(m_XCount * m_YCount);
	m_EnemyCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			m_pEnemyData[y * m_XCount + x] = atoi(pstr);
			if (m_pEnemyData[y * m_XCount + x] > 0)
			{
				m_EnemyCount++;
			}
		}
	}

	//ファイルを閉じる
	fclose(fp);
	free(pBuffer);
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 */
void CStage::Initialize(CEnemy* pEnemy){
	m_ScrollX = 0;
	m_ScrollY = 0;

	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号０は配置しない
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on]);
			pEnemy[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
}

/**
 * 更新
 *
 * 引数
 * [in]			pl					プレイヤー、スクロールの判定に使用
 */
void CStage::Update(CPlayer& pl){
	//プレイヤーの矩形取得
	CRectangle prec = pl. GetRect();
	//スクリーンの幅
	float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	float sh = CGraphicsUtilities::GetGraphics()->GetTargetHeight();
	//ステージ全体の幅
	float stgw = m_ChipSize * m_XCount;
	float stgh = m_ChipSize * m_YCount;
	//横スクロール
	if (prec.Left - m_ScrollX < 200)
	{
		m_ScrollX -= 200 - (prec.Left - m_ScrollX);
		if (m_ScrollX <= 0)
		{
			m_ScrollX = 0;
		}
	}
	else if (prec.Right - m_ScrollX > sw - 200)
	{
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - 200);
		if (m_ScrollX >= stgw - sw)
		{
			m_ScrollX = stgw - sw;
		}
	}
	//縦スクロール
	if (prec.Bottom - m_ScrollY < 200)
	{
		m_ScrollY -= 200 - (prec.Bottom - m_ScrollY);
		if (m_ScrollY <= 0)
		{
			m_ScrollY = 0;
		}
	}
	else if (prec.Top - m_ScrollY > sh - 200)
	{
		m_ScrollY += (prec.Top - m_ScrollY) - (sh - 200);
		if (m_ScrollY >= stgh - sh)
		{
			m_ScrollY = stgh - sh;
		}
	}

}

/**
 * 当たり判定
 *
 * 引数
 * [in]			r					判定矩形
 * [out]		ox					X埋まり
 * [out]		oy					Y埋まり
 */
bool CStage::Collision(CRectangle r, float& ox, float& oy) {
	bool re = false;

	//当たり判定する矩形の左上と右下のチップ位置を求める
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;
	//ステージの範囲外にはならないようにする
	if (lc < 0)
	{
		lc = 0;
	}
	if (tc < 0)
	{
		tc = 0;
	}
	if (rc >= m_XCount)
	{
		rc = m_XCount - 1;
	}
	if (bc >= m_YCount)
	{
		bc = m_YCount - 1;
	}

	//当たり判定をする矩形の左上から右下の範囲のみ当たり判定をおこなう
	//それ以外の番号は当たることはないので判定が必要ない
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			//チップ番号０は当たり判定しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの矩形
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//当たり判定用のキャラクタ矩形
			//下で範囲を限定した専用の矩形を作成する。
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;	//下の矩形は上側を下と同じ値にする
			brec.Expansion(-11, 0);		//横の範囲を少し狭める
			//下と当たり判定
			if (cr.CollisionRect(brec))
			{
				re = true;
				//下の埋まりなのでチップの上端から矩形の下端の値を引いた値が埋まりの値になる
				oy += cr.Top - brec.Bottom;
				r.Top += cr.Top - brec.Bottom;
				r.Bottom += cr.Top - brec.Bottom;
			}
			//当たり判定用のキャラクタ矩形
			//左、右それぞれで範囲を限定した専用の矩形を作成する。
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;	//左の矩形は右側を左と同じ値にする
			lrec.Expansion(0, -11);		//縦の範囲を少し狭める
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;	//右の矩形は左側を右と同じ値にする
			rrec.Expansion(0, -11);		//縦の範囲を少し狭める
			//左と当たり判定
			if (cr.CollisionRect(lrec))
			{
				re = true;
				//左の埋まりなのでチップの右端から矩形の左端の値を引いた値が埋まりの値になる
				ox += cr.Right - lrec.Left;
				r.Left += cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//右と当たり判定
			else if (cr.CollisionRect(rrec))
			{
				re = true;
				//右の埋まりなのでチップの左端から矩形の右端の値を引いた値が埋まりの値になる
				ox += cr.Left - rrec.Right;
				r.Left += cr.Left - rrec.Right;
				r.Right += cr.Left - rrec.Right;
			}
			//当たり判定用のキャラクタ矩形
			//上で範囲を限定した専用の矩形を作成する。
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;	//上の矩形は下側を上と同じ値にする
			trec.Expansion(-11, 0);		//横の範囲を少し狭める
			//上と当たり判定
			if (cr.CollisionRect(trec))
			{
				re = true;
				//上の埋まりなのでチップの下端から矩形の上端の値を引いた値が埋まりの値になる
				oy += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}
		}
	}


	return re;
}

/**
 * 描画
 *
 */
void CStage::Render(void){
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-m_ScrollY % hn) - hn; y < sch; y += hn)
	{
		for (float X = ((int)-m_ScrollX % wn) - wn; X < scw; X += wn)
		{
			m_BackTexture.Render(X, y);
		}
	}

	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int X = 0; X < m_XCount; X++)
		{
			char cn = m_pChipData[y * m_XCount + X] - 1;
			if (cn < 0)
			{
				continue;
			}
			CRectangle cr(m_ChipSize * (cn%tcx), m_ChipSize * (cn / tcx), m_ChipSize * (cn%tcx + 1), m_ChipSize * (cn / tcx + 1));
			m_ChipTexture.Render(-m_ScrollX + X * m_ChipSize, -m_ScrollY + y * m_ChipSize, cr);
		}
	}
}

/**
 * デバッグ描画
 *
 */
void CStage::RenderDebug(void){
	//位置の描画
	CGraphicsUtilities::RenderString(10,100,"スクロール X : %.0f , Y : %.0f",m_ScrollX,m_ScrollY);
}

/**
 * 解放
 *
 */
void CStage::Release(void){
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}
	if (m_pEnemyData)
	{
		free(m_pEnemyData);
		m_pEnemyData = NULL;
	}
	if (m_pEnemyTexture)
	{
		delete[] m_pEnemyTexture;
		m_pEnemyTexture = NULL;
	}

}