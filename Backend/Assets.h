#ifndef SUPERMARIO_ASSETS_H
#define SUPERMARIO_ASSETS_H
#include <string>
#include <Vector>
#include <memory>
#include "Animation.h"
#include <map>

//THIS CLASS FINDS ALL THE ASSETS FROM THE PATH ACCORDING TO ASSETFILESPECIFICATION.TXT
class Assets
{
    friend class CTexture;
    std::string gPath;
    struct TextureAsset
    {
        std::string tName;
        std::string tPath;
    };

    struct FontAsset
    {
        std::string fName;
        std::string fPath;
    };

    struct SoundAsset
    {
        std::string soundName;
        std::string soundPath;
    };

    struct MusicAsset
    {
        std::string musicName;
        std::string musicPath;
    };

    struct AnimationAsset
    {
        std::string aName;
        std::string aSpriteSheetPath;
        size_t aFrameCount;
        size_t aSpeed;
    };
public:
    typedef struct allAssets
    {
        std::map<std::string, TextureAsset> tAsset;
        std::map<std::string, FontAsset> fAsset;
        std::map<std::string, SoundAsset> soundAsset;
        std::map<std::string, MusicAsset> musicAsset;
        std::map<std::string, AnimationAsset> aAsset;
    } allAssets;

    allAssets assets;

    Assets(){}

    void loadFromFile(const std::string& PATH);

    void setPath(const std::string& PATH) { gPath = PATH; };

    const std::shared_ptr<allAssets> getAssets()
    {
        return std::shared_ptr<allAssets>(&assets);
    };
};


#endif //SUPERMARIO_ASSETS_H
