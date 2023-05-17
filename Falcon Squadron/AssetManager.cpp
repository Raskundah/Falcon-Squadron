#include "AssetManager.h"

std::map<std::string, sf::Texture> AssetManager::textures;
std::map<std::string, sf::Font> AssetManager::fonts;
std::map<std::string, sf::SoundBuffer> AssetManager::soundBuffers;


sf::Texture& AssetManager::RequestTexture(std::string assetName)
{
    auto pairFound = textures.find(assetName); //using auto to iterate through textures to find the given asset name.

    if (pairFound != textures.end())
    {
        // We found an existing texture! Use it
        return pairFound->second; // the value in the key-value pair
    }
    else
    {
        sf::Texture& newTexture = textures[assetName]; //creates a new texture and string key value pair.
        newTexture.loadFromFile(assetName); //loads the item from storage.
        return newTexture;
    }


}

sf::Font& AssetManager::RequestFont(std::string assetName)
{
    auto pairFound = fonts.find(assetName);

    if (pairFound != fonts.end())
    {
        // We found an existing texture! Use it
        return pairFound->second; // the value in the key-value pair
    }
    else
    {
        sf::Font& newFont = fonts[assetName];
        newFont.loadFromFile(assetName);
        return newFont;
    }


}

sf::SoundBuffer& AssetManager::RequestSoundBuffer(std::string assetName)
{
    auto pairFound = soundBuffers.find(assetName);

    if (pairFound != soundBuffers.end())
    {
        // We found an existing texture! Use it
        return pairFound->second; // the value in the key-value pair
    }
    else
    {
        sf::SoundBuffer& newSoundBuffer = soundBuffers[assetName];
        newSoundBuffer.loadFromFile(assetName);
        return newSoundBuffer;
    }


}

void AssetManager::DestroyAllAssets()
{
    textures.clear();
    fonts.clear();
    soundBuffers.clear();

    //wipes the map clean for memory cleaning purposes.
}