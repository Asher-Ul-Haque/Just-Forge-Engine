#include "../../TheMachine/Management/Assets.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

void Assets::loadFromFile(const std::string& PATH)
{
    //Open the file
    std::ifstream assetsFile(PATH);
    if (!assetsFile.is_open())
    {
        std::cerr << "Could not open file: " << PATH << std::endl;
        return;
    }
    std::string line;
    while (std::getline(assetsFile, line))
    {
        std::istringstream iss(line);
        std::string assetType;
        iss >> assetType;
        switch (assetType[0])
        {
            case 'T':
            {
                TextureAsset tAsset;
                iss >> tAsset.tName >> tAsset.tPath;
                assets.tAsset[tAsset.tName] = tAsset;
                break;
            }
            case 'F':
            {
                FontAsset fAsset;
                iss >> fAsset.fName >> fAsset.fPath;
                assets.fAsset[fAsset.fName] = fAsset;
                break;
            }
            case 'S':
            {
                SoundAsset soundAsset;
                iss >> soundAsset.soundName >> soundAsset.soundPath;
                assets.soundAsset.insert(std::pair<std::string, SoundAsset>(soundAsset.soundName, soundAsset));
                break;
            }
            case 'M':
            {
                MusicAsset musicAsset;
                iss >> musicAsset.musicName >> musicAsset.musicPath;
                assets.musicAsset.insert(std::pair<std::string, MusicAsset>(musicAsset.musicName, musicAsset));
                break;
            }
            case 'A':
            {
                AnimationAsset aAsset;
                iss >> aAsset.aName >> aAsset.aSpriteSheetPath >> aAsset.aFrameCount >> aAsset.aSpeed;
                assets.aAsset.insert(std::pair<std::string, AnimationAsset>(aAsset.aName, aAsset));
                break;
            }
            default:
                break;
            }
    }
}


