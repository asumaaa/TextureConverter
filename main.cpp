#include "cstdio"
#include "cstdlib"
#include "TextureConverter.h"

//コマンドライン引数
enum Argument {
	kApplicationPath,	//アプリケーションのパス
	kFilePath,			//渡されたファイルのパス

	NumArgument
};

int main(int argc, char* argv[]) {


	/*assert(argc >= NumArgument);*/

	//COMライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//テクスチャコンバーター
	TextureConverter converter;

	//テクスチャ変換
	converter.ConvertTextureWICoDDS(argv[kFilePath]);

	//COMライブラリの終了
	CoUninitialize();

	////argcの数だけ繰り返す
	//for (int i = 0; i < argc; i++)
	//{
	//	//文字列argvのi番を取得
	//	printf(argv[i]);
	//	//改行
	//	printf("\n");
	//}

	system("pause");
	return 0;
}