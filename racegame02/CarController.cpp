#include "CarController.hpp"
#include<fstream>


void CarController::update(float dt,const CarStatus& carsta,float& SPEED)
{
    // --- 入力 ---
    float accel = 0.f;
    float brake = 0.f;
    float driftspin = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        accel = carsta.ACCELLATE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        brake = carsta.BRAKE;
    if (accel == carsta.ACCELLATE && brake == carsta.BRAKE) {
        driftspin = 0.3;
        brake = accel / carsta.WEIGHT;
        if (SPEED != 0) {
            //ドリフト状態
            
        }
        else {
            //その場回転

        }
    }


    // --- 回転（速度に比例した旋回） ---
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        camAngle -= carsta.TURN_SPEED * dt * (SPEED / carsta.MAX_SPEED + driftspin);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        camAngle += carsta.TURN_SPEED * dt * (SPEED / carsta.MAX_SPEED + driftspin);

    // ---- forward / right ----
    sf::Vector2f forward(std::cos(camAngle), std::sin(camAngle));
    sf::Vector2f right(-forward.y, forward.x);

    // ---- 速度分解 ----
    float fwdSpeed = forward.x * velocity.x + forward.y * velocity.y;
    float sideSpeed = right.x * velocity.x + right.y * velocity.y;

    // ---- 前向き加速 ----
    fwdSpeed += accel * dt;

    // ---- ブレーキ ----
    if (fwdSpeed > 0) fwdSpeed -= brake * carsta.WEIGHT * dt;

    // ---- 摩擦（自然減速） ----
    if (fwdSpeed > 0) fwdSpeed -= carsta.FRICTION * carsta.WEIGHT * dt;

    // ---- Clamp ----
    if (fwdSpeed > carsta.MAX_SPEED) fwdSpeed = carsta.MAX_SPEED;
    if (fwdSpeed < 0) fwdSpeed = 0;

    // ---- 横滑り減衰 ----
    sideSpeed *= 0.90f;

    // ---- velocity再合成 ----
    velocity = forward * fwdSpeed + right * sideSpeed;

    // ---- UI用スピード ----
    SPEED = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    // ---- 位置更新 ----
    camX += velocity.x * dt;
    camY += velocity.y * dt;
}

CarController::CarController(){}