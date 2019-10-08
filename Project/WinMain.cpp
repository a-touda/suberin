#include	"GameApp.h"

#ifdef		UNICODE
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
#else
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
#endif
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	Mof::LPFramework pFrame = new Mof::CDX11GameFramework(); 
	Mof::WINDOWSGAMEFRAMEWORKINITIALIZEINFO Info;
	Info.pApplication = new CGameApp();
	//�N�����̉�ʃT�C�Y�w��
	Info.WindowCreateInfo.Width = 1280;
	Info.WindowCreateInfo.Height = 720;
	//M�L�[�Ńt���X�N���[��
/*	if (g_pInput->IsKeyPush(MOFKEY_M))
	{
		g_pGraphics->ChangeScreenMode();
	}*/
	pFrame->Initialize(&Info);
	pFrame->Run();
	MOF_SAFE_DELETE(pFrame);
	return 0;
}