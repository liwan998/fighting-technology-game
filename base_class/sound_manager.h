#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <QObject>
#include<unordered_map>
#include<QMediaPlayer>

class Sound_manager : public QObject
{
    Q_OBJECT
public:
    static Sound_manager*instance();

    void load();

    QMediaPlayer* find_background_music(std::string id);
    QMediaPlayer* find_sound_effect(std::string id);

private:
    Sound_manager()=default;
    ~Sound_manager();

private:
    static Sound_manager *manager;
    std::unordered_map<std::string,QMediaPlayer*> background_music_list;
    std::unordered_map<std::string,QMediaPlayer*> sound_effect_list;
};

#endif // SOUND_MANAGER_H
