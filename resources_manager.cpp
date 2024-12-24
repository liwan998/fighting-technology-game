#include "resources_manager.h"
#include <QImage>
#include<QDebug>

//Q_GLOBAL_STATIC(Resources_manager, globalResourcesManager)多线程的化启用确保单例实现是线程安全的

struct ImageResInfo {
    QString id;
    QString path;
};

struct AtlasResInfo {
    QString id;
    QString path;
    int num_fram = 0;
};

struct Atlas_image_ResInfo{
    QString id;
    QString path;
    int num_w;
    int num_h;
    float zoom;   //缩放系数
};

static const QVector<ImageResInfo>image_info_list = {
    //游戏界面
    {"background","./resource/background.png"},
    //开始界面
    {"start_title","./resource/start/title.png"},
    {"start_background0","./resource/start/background0.png"},
    {"start_background1","./resource/start/background1.png"},
    {"start_background2","./resource/start/background2.png"},
    //选则界面
    {"select_background0","./resource/select/background0.png"},
    {"select_background1","./resource/select/background1.png"},
    {"select_background2","./resource/select/background2.png"},
    {"select_background3","./resource/select/background3.png"},
    {"select_background4","./resource/select/background4.png"},
    //女王红心子弹
    {"queen_small_bullet","./resource/queen/bullet/0.png"},
    {"queen_big_bullet","./resource/queen/bullet/big0.png"},

};

static const QVector<Atlas_image_ResInfo>atlas_image_info_list = {
    {"a","./resource/effects/acid_spit_core_sheet.png",4,4,0.5},
};

static const QVector<AtlasResInfo> atlas_info_list = {
    //海贼
    {"pirate_attack_right","./resource/pirate/attack/%1.png",21},
    {"pirate_dead_right","./resource/pirate/dead/%1.png",2},
    {"pirate_fall_right","./resource/pirate/fall/%1.png",4},
    {"pirate_idle_right","./resource/pirate/idle/%1.png",12},
    {"pirate_jump_right","./resource/pirate/jump/%1.png",5},
    {"pirate_roll_right","./resource/pirate/roll/%1.png",7},
    {"pirate_run_right","./resource/pirate/run/%1.png",10},
    {"pirate_skill_right","./resource/pirate/skill/%1.png",40},

    {"pirate_show","./resource/pirate/show/%1.png",84},

    //女王
    {"queen_attack_right","./resource/queen/attack/%1.png",27},
    {"queen_dead_right","./resource/queen/dead/%1.png",12},
    {"queen_fall_right","./resource/queen/fall/%1.png",6},
    {"queen_idle_right","./resource/queen/idle/%1.png",12},
    {"queen_jump_right","./resource/queen/jump/%1.png",6},
    {"queen_roll_right","./resource/queen/roll/%1.png",5},
    {"queen_run_right","./resource/queen/run/%1.png",10},
    {"queen_skill_right","./resource/queen/skill/%1.png",22},

    {"queen_show","./resource/queen/show/%1.png",75},
    {"queen_small_bullet","./resource/queen/bullet/%1.png",3},
    {"queen_big_bullet","./resource/queen/bullet/big%1.png",3},

};

Resources_manager* Resources_manager::manager = nullptr;// 静态成员变量初始化

Resources_manager* Resources_manager::instance()// 单例模式：获取实例
{
    if (!manager) {
        manager = new Resources_manager();
    }
    return manager;
}

void Resources_manager::load()// 加载资源
{
    for (const auto& info : image_info_list) {  //加载图片
        QImage* image = new QImage(info.path);
        image_pool[info.id] = image;
    }

    for (const auto& info : atlas_info_list) {  //加载图集
        Atlas* atlas = new Atlas();
        atlas->load_from_file(info.path, info.num_fram);

        bool allImagesValid = true;
        for (int i = 0; i < atlas->get_size(); i++) {
            QImage* image = atlas->get_image(i);
            if (!image->bits()) {
                allImagesValid = false;
                break;
            }
        }
        if (allImagesValid) {
            atlases_pool[info.id] = atlas;
        } else {
            delete atlas; // 删除无效的图集
            qDebug() << "图集中无效的图片:" << info.path;
        }
    }
    load_atlas_image();
    //翻转图集并储存
    {//海贼
        flip_atlas("pirate_attack_right", "pirate_attack_left");
        flip_atlas("pirate_dead_right","pirate_dead_left");
        flip_atlas("pirate_fall_right", "pirate_fall_left");
        flip_atlas("pirate_idle_right", "pirate_idle_left");
        flip_atlas("pirate_jump_right", "pirate_jump_left");
        flip_atlas("pirate_roll_right", "pirate_roll_left");
        flip_atlas("pirate_run_right", "pirate_run_left");
        flip_atlas("pirate_skill_right", "pirate_skill_left");
    }
    {//女王
        flip_atlas("queen_attack_right","queen_attack_left");
        flip_atlas("queen_dead_right","queen_dead_left");
        flip_atlas("queen_fall_right","queen_fall_left");
        flip_atlas("queen_idle_right","queen_idle_left");
        flip_atlas("queen_jump_right","queen_jump_left");
        flip_atlas("queen_roll_right","queen_roll_left");
        flip_atlas("queen_run_right","queen_run_left");
        flip_atlas("queen_skill_right","queen_skill_left");
    }
}

Atlas *Resources_manager::find_atlas(const QString &id) const// 查找图集
{
    const auto& it = atlases_pool.find(id);
    if (it != atlases_pool.end()) {
        return it->second;
    }
    return nullptr;
}

QImage *Resources_manager::find_image(const QString &id) const  //查找图片
{
    const auto& itor = image_pool.find(id);
    if (itor == image_pool.end()) {
        return nullptr;
    }
    return itor->second;
}

Resources_manager::Resources_manager()
{}

Resources_manager::~Resources_manager()
{
    // 释放所有资源
    for (auto& pair : atlases_pool) {
        delete pair.second;
    }
    atlases_pool.clear();
}

void Resources_manager::load_atlas_image()
{
    for(const auto&info:atlas_image_info_list){
        Atlas* atlas = new Atlas();
        atlas->load_from_file(info.path,info.num_w,info.num_h,info.zoom);
        bool allImagesValid = true;
        for (int i = 0; i < atlas->get_size(); i++) {
            QImage* image = atlas->get_image(i);
            if (!image->bits()) {
                allImagesValid = false;
                break;
            }
        }
        if (allImagesValid) {
            atlases_pool[info.id] = atlas;
        } else {
            delete atlas; // 删除无效的图集
            qDebug() << "图集中无效的图片:" << info.path;
        }
    }

}

void Resources_manager::flip_atlas(const QString &src_id, const QString dst_id)// 翻转图集资源
{
    auto it = atlases_pool.find(src_id);
    if (it != atlases_pool.end()) {
        Atlas* src_atlas = it->second;
        Atlas* dst_atlas = new Atlas();
        int size=src_atlas->get_size();
        for(int i=0;i<size;i++){
            QImage* src_img = src_atlas->get_image(i);
            if (src_img) {
                QImage img = src_img->mirrored(true, false);    //水平翻转
                dst_atlas->add_image(new QImage(img)); // 确保添加新的 QImage 实例
            }
        }
        atlases_pool[dst_id] = dst_atlas; // 存储翻转后的图集
    }else{
        qDebug()<<"没有源图集:"<<src_id;
    }
}