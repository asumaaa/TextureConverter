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
}

// テクスチャファイル読み込み
void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	//ファイルパスをワイド文字列に変換する
	std::wstring wfilePath = ConvertMutiByteStringToWideString(filePath);

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
