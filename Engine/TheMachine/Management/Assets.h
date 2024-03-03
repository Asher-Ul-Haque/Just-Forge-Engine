#ifndef SUPERMARIO_ASSETS_H
#define SUPERMARIO_ASSETS_H
#include <string>
#include <vector>
#include <memory>
#include "Animation.h"
#include <map>
//---------------------------------

class Assets
{
    //Data
    friend class CTexture;
    friend class ScenePlay;
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
        Vector2D(aFrameSize);
    };
// - - - - - - - - - -
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
    //---------------------------------

    //Construction
    Assets(){}
    //---------------------------------

    //METHODS-
    void loadFromFile(const std::string& PATH);

    const std::string& getPath() const { return gPath; };

    void setPath(const std::string& PATH) { gPath = PATH; };

    //Make a template function to get assets of a certain type

    const std::shared_ptr<allAssets> getAssets()
    {
        return std::shared_ptr<allAssets>(&assets);
    };
};
//---------------------------------



#endif //SUPERMARIO_ASSETS_H