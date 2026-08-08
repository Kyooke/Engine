#pragma once

#include <string>

class MTLLoader
{
public:

    // MTLファイルを読み込み、テクスチャファイル名を取得
    static bool Load(
        const char* fileName,
        std::string& textureFileName);
};