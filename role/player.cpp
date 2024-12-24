#include "player.h"

Player::Player(QObject *parent)
    : Character{parent}
{
    timer_roll.set_wait_time(CD_ROLL);
    timer_roll.set_one_shot(true);
    timer_roll.set_on_timeout([&](){
        is_roll_cd=false;
    });
}

Player::~Player()
{
}

void Player::key_Press(QKeyEvent &event)
{
    if(!is_key_control||hp<=0) return;
    if(player_selects==Player::Player_select::left){
        switch (event.key()) {
        case Qt::Key_A:
            is_left_key_down=true;
            break;
        case Qt::Key_D:
            is_right_key_down=true;
            break;
        case Qt::Key_W:
            is_jump_key_down=true;
            break;
        case Qt::Key_S:
            is_roll_key_down=true;
            break;
        case Qt::Key_J:
            is_attack_key_down=true;
            break;
        case Qt::Key_E:
            is_skill_key_down=true;
            break;
        case Qt::Key_Q:
            //is_ultimate_key_down=true;
            break;
        default:
            break;
        }
    }else{
        switch (event.key()) {
        case Qt::Key_Left:
            is_left_key_down=true;
            break;
        case Qt::Key_Right:
            is_right_key_down=true;
            break;
        case Qt::Key_Up:
            is_jump_key_down=true;
            break;
        case Qt::Key_Down:
            is_roll_key_down=true;
            break;
        case Qt::Key_1:
            is_attack_key_down=true;
            break;
        case Qt::Key_2:
            is_skill_key_down=true;
            break;
        case Qt::Key_3:
            //is_ultimate_key_down=true;
            break;
        default:
            break;
        }
    }
    Character::key_Press(event);
}

void Player::key_Release(QKeyEvent &event)
{
    if(hp<=0) return;
    if(player_selects==Player::Player_select::left){
        switch (event.key()) {
        case Qt::Key_A:
            is_left_key_down=false;
            break;
        case Qt::Key_D:
            is_right_key_down=false;
            break;
        case Qt::Key_W:
            is_jump_key_down=false;
            break;
        case Qt::Key_S:
            is_roll_key_down=false;
            break;
        case Qt::Key_J:
            is_attack_key_down=false;
            break;
        case Qt::Key_E:
            is_skill_key_down=false;
            break;
        case Qt::Key_Q:
            //is_ultimate_key_down=false;
            break;
        default:
            break;
        }
    }else{
        switch (event.key()) {
        case Qt::Key_Left:
            is_left_key_down=false;
            break;
        case Qt::Key_Right:
            is_right_key_down=false;
            break;
        case Qt::Key_Up:
            is_jump_key_down=false;
            break;
        case Qt::Key_Down:
            is_roll_key_down=false;
            break;
        case Qt::Key_1:
            is_attack_key_down=false;
            break;
        case Qt::Key_2:
            is_skill_key_down=false;
            break;
        case Qt::Key_3:
            //is_ultimate_key_down=false;
            break;
        default:
            break;
        }
    }
    Character::key_Release(event);
}

Player::Player_select Player::getPlayer_selects() const
{
    return player_selects;
}

void Player::setPlayer_selects(Player_select newPlayer_selects)
{
    player_selects = newPlayer_selects;
}

void Player::on_update(float delta)
{

    if (hp > 0 && !is_roll) {
        velocity.setX(get_move_axis() * SPEED_RUN);
    }

    if (get_move_axis()!=0) {
        is_facing_left = (get_move_axis() < 0);
    }

    timer_roll.on_update(delta);
    timer_attack.on_update(delta);
    timer_skill.on_update(delta);
    //timer_ultimate.on_update(delta);
    Character::on_update(delta);

}

void Player::on_render(QPainter &painter)
{
    Character::on_render(painter);
}

void Player::on_jump()
{
    Character::on_jump();
}

void Player::on_roll()
{
    Character::on_roll();
    timer_roll.restart();
    is_roll_cd = true;
}

void Player::on_attack()
{
    Character::on_attack();
    timer_attack.restart();
    is_attack_cd=true;
}

void Player::on_skill()
{
    Character::on_skill();
    timer_skill.restart();
    is_skill_cd=true;
}

// void Player::on_ultimate()
// {
//     timer_ultimate.restart();
//     is_ultimate_cd=true;
// }

void Player::on_hurt()
{

}

void Player::on_dead()
{

}

const bool Player::can_attack() const
{
    return !is_attack_cd && !is_attack && is_attack_key_down;
}

const bool Player::can_skill() const
{
    return !is_skill_cd && !is_skill && is_skill_key_down;
}

const bool Player::can_jump() const
{
    return is_on_floor() && is_jump_key_down;
}

const bool Player::can_roll() const
{
    return !is_roll_cd && !is_roll && is_roll_key_down;
}

void Player::setIs_key_control(bool newIs_key_control)
{
    is_key_control = newIs_key_control;
    if(newIs_key_control==false){
        clear_button();//
    }
}

void Player::clear_button()
{
    is_left_key_down = false;
    is_right_key_down = false;
    is_jump_key_down = false;
    is_roll_key_down = false;
    is_attack_key_down = false;
    is_skill_key_down = false;
    //is_ultimate_key_down=false;

}
