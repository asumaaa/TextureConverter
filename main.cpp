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

	SetConsoleOutputCP(65001);

	//コマンドライン引数指定なし
	if (argc < NumArgument) {
		//使い方を表示する
		TextureConverter::OutputUsage();
		return 0;
	}

	//COMライブラリの初期化
	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//テクスチャコンバーター
	TextureConverter converter;

	//オプションの数
	int numOptions = argc - NumArgument;
	//オプション配列
	char** options = argv + NumArgument;

	//テクスチャ変換
	converter.ConvertTextureWICoDDS(argv[kFilePath], numOptions, options);

	//COMライブラリの終了
	CoUninitialize();

	/*system("pause");*/
	return 0;
}