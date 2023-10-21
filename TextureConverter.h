/**
 * @file TextureConverter.h
 * @brief テクスチャのコンバーター
 * @author Asuma Syota
 * @date 2023/10/22
 */

#pragma once
#include "string"

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
};

