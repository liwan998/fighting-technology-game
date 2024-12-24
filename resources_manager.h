#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include <QObject>
#include<unordered_map>
#include "atlas.h"
//单例资源管理器
class Resources_manager : public QObject
{
    Q_OBJECT 
public:
    static Resources_manager* instance();

    void load();

    Atlas* find_atlas(const QString& id)const;
    QImage* find_image(const QString& id)const;

private:
    static Resources_manager* manager;

    std::unordered_map<QString, Atlas*>atlases_pool;
    std::unordered_map<QString, QImage*>image_pool;

private:
    Resources_manager();
    ~Resources_manager();

    void load_atlas_image(); //保存动画帧序列在一张图片上的

    void flip_atlas(const QString& src_id, const QString dst_id);

};

#endif // RESOURCES_MANAGER_H
