#include "sound_manager.h"
#include<QUrl>
#include<QAudioOutput>
#include<QDebug>
Sound_manager* Sound_manager::manager=nullptr;
std::mutex Sound_manager::m_mutex;

Sound_manager *Sound_manager::instance()
{
    std::unique_lock<std::mutex>m_mutex;
    if(!manager){
        manager=new Sound_manager();
    }
    return manager;
}


struct Sound_ResInfo {
    std::string id;
    QString path;
};
static const QVector<Sound_ResInfo>background_music_info_list = {
    {"start","./sound/background_music/舒缓背景音.mp3"},
    {"select","./sound/background_music/False_King.mp3"},
    {"game","./sound/background_music/枪火战线游戏背景音乐.mp3"},
};

static const QVector<Sound_ResInfo>sound_eddect_info_list = {
    {"jump","./sound/sound_effect/跳跃.mp3"},
    {"roll","./sound/sound_effect/快速移动.mp3"},

    {"pirate_attack","./sound/sound_effect/打击音效.mp3"},
    {"pirate_skill","./sound/sound_effect/多重拳.mp3"},
    {"pirate_dead","./sound/sound_effect/男死亡.mp3"},

    {"queen_attack","./sound/sound_effect/踢腿打击.mp3"},
    {"queen_skill","./sound/sound_effect/飞吻音效.mp3"},
    {"queen_dead","./sound/sound_effect/女死亡.mp3"},
};

void Sound_manager::load()
{
    for(const auto info:background_music_info_list){
        QMediaPlayer* player=new QMediaPlayer;
        player->setSource(QUrl::fromLocalFile(info.path));
        QAudioOutput* audioOutput = new QAudioOutput(player);
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(20);
        player->setLoops(-1);

        if (player->error() != QMediaPlayer::NoError) {
            qDebug() << "Error:" << player->errorString();
        }
        background_music_list[info.id]=player;
    }
    for(const auto info:sound_eddect_info_list){
        QMediaPlayer* player=new QMediaPlayer;
        player->setSource(QUrl::fromLocalFile(info.path));
        QAudioOutput* audioOutput = new QAudioOutput(player);
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(100);
        player->setLoops(1);

        if (player->error() != QMediaPlayer::NoError) {
            qDebug() << "Error:" << player->errorString();
        }
        sound_effect_list[info.id]=player;
    }
}

QMediaPlayer *Sound_manager::find_background_music(std::string id)
{
    if(background_music_list[id]==nullptr){
        qDebug()<<"没有该音频";
    }

    return background_music_list[id];
}

QMediaPlayer *Sound_manager::find_sound_effect(std::string id)
{
    if(sound_effect_list[id]==nullptr){
        qDebug()<<"没有该音频";
    }

    return sound_effect_list[id];
}

Sound_manager::~Sound_manager()
{
    std::vector<std::string> keys_to_delete;

    for (const auto& i : background_music_list) {
        if (i.second != nullptr) {
            keys_to_delete.push_back(i.first);
        }
    }

    for (const auto& key : keys_to_delete) {
        auto it = background_music_list.find(key);
        if (it != background_music_list.end() && it->second != nullptr) {
            delete it->second;
            background_music_list.erase(it);
        }
    }

    keys_to_delete.clear();

    for (const auto& i : sound_effect_list) {
        if (i.second != nullptr) {
            keys_to_delete.push_back(i.first);
        }
    }

    for (const auto& key : keys_to_delete) {
        auto it = sound_effect_list.find(key);
        if (it != sound_effect_list.end() && it->second != nullptr) {
            delete it->second;
            sound_effect_list.erase(it);
        }
    }

}
