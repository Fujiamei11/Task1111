//
// Created by 23263 on 2026/11/23.
//
#include "servo.h"
#include"tim.h"

// 角度转CCR映射函数，就是你图片里的，已经改成文档推荐的安全版本（0→550，180→2450）
uint16_t AngleToCCR(float angle)
{
    if (angle < 0.0f)
        angle = 0.0f;
    if (angle > 180.0f)
        angle = 180.0f;

    // 预留余量，不碰500、2500极限脉宽
    return (uint16_t)(550.0f + angle / 180.0f * 1900.0f);
}

// 直接设置舵机角度
void Servo_SetAngle(float angle)
{
    uint16_t ccr_val = AngleToCCR(angle);
    // 这里htim2、通道4是你之前用的PWM，按你自己的定时器修改！
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, ccr_val);
}