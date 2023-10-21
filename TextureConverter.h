/**
 * @file TextureConverter.h
 * @brief テクスチャのコンバーター
 * @author Asuma Syota
 * @date 2023/10/22
 */

#pragma once
#include "string"
#include "DirectXTex.h"

//テクスチャコンバーター
class TextureConverter
{
public:	//メンバ関数

	/// <sammary>
	/// テクスチャをWICからDDSに変換する
	///	<sammary>
	/// <param name="filePath">ファイルパス</param>
	void ConvertTextureWICoDDS(const std::string& filePath);

private: //メンバ関数

	/// <sammary>
	/// テクスチャファイル読み込み
	///	<sammary>
	/// <param name="filePath">ファイルパス</param>
	void LoadWICTextureFromFile(const std::string& filePath);

	/// <sammary>
	/// マルチバイト文字列をワイド文字列に変換
	///	<sammary>
	/// <param name="mString">マルチバイト文字列</param>
	/// <returns>ワイド文字列</returns>
	static std::wstring ConvertMutiByteStringToWideString(const std::string& mString);

	/// <sammary>
	/// フォルダパスとファイル名を分解する
	///	<sammary>
	/// <param name="filePath">ファイルパス</param>
	void SeparateFilePath(const std::wstring& filePath);

	/// <sammary>
	/// DDSテクスチャとしてファイル書き出し
	///	<sammary>
	void SaveDDSTextureToFile();

private: //メンバ変数
	//画像の情報
	DirectX::TexMetadata metadata_;
	//画像イメージのコンテナ
	DirectX::ScratchImage scratchImage_;
	//ディレクトリパス
	std::wstring directoryPath_;
	//ファイル名
	std::wstring fileName_;
	//ファイル拡張子
	std::wstring fileExt_;
};

