/**
 * @file TextureConverter.cpp
 * @brief テクスチャのコンバーター
 * @author Asuma Syota
 * @date 2023/10/22
 */

#include "TextureConverter.h"
#include <windows.h>

// テクスチャをWICからDDSに変換する
void TextureConverter::ConvertTextureWICoDDS(const std::string& filePath)
{
	//テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);

	//DDS形式に変換して書き出す
	SaveDDSTextureToFile();
}

// テクスチャファイル読み込み
void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	HRESULT result;

	//ファイルパスをワイド文字列に変換する
	std::wstring wfilePath = ConvertMutiByteStringToWideString(filePath);

	//WICテクスチャのロード
	result = DirectX::LoadFromWICFile(wfilePath.c_str(), DirectX::WIC_FLAGS_NONE, &metadata_, scratchImage_);
	assert(SUCCEEDED(result));

	//フォルダパスとファイル名を分離する
	SeparateFilePath(wfilePath);
}

// マルチバイト文字列をワイド文字列に変換
std::wstring TextureConverter::ConvertMutiByteStringToWideString(const std::string& mString)
{
	//ワイド文字列に変換した際の文字数を計算
	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	//ワイド文字列
	std::wstring wString;
	wString.resize(filePathBufferSize);

	//ワイド文字列に変換
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;
}

// フォルダパスとファイル名を分解する
void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{
	size_t pos1;
	std::wstring exceptExt;

	//区切り喪に'.'が出てくる一番最後の部分を検索
	pos1 = filePath.rfind('.');
	//検索がヒットしたら
	if (pos1 != std::wstring::npos) {
		//区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//区切り文字の前まで抜き出す
		exceptExt = filePath.substr(0, pos1);
	}
	else {
		fileExt_ = L"";
		exceptExt = filePath;
	}

	//区切り文字'\\'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos) {
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//区切り文字'/'が出てくる一番最後の部分を検索
	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos) {
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイル名として保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//区切り文字がないのでファイル名飲みして扱う
	directoryPath_ = L"";
	fileName_ = exceptExt;
}

// DDSテクスチャとしてファイル書き出し
void TextureConverter::SaveDDSTextureToFile()
{
	HRESULT result;

	//読み込んだテクスチャをSRGBとして扱う
	metadata_.format = DirectX::MakeSRGB(metadata_.format);

	//出力ファイル名を設定する
	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	//DDSファイル書き出し
	result = DirectX::SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(),
		metadata_, DirectX::DDS_FLAGS_NONE, filePath.c_str());
	assert(SUCCEEDED(result));
}
