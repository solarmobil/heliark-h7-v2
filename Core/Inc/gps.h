/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gps.h
  * @brief   Header for gps.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#ifndef __GPS_H
#define __GPS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* USER CODE BEGIN ET */
typedef struct
{
  char time[16];
  char date[8];
  char lat[16];
  char lon[16];
  char speed[16];
  char latHem;
  char lonHem;
  char status;
} gps_t;
/* USER CODE END ET */

/* USER CODE BEGIN EFP */
void GPS_Init(void);
void GPS_Task(void);
uint8_t GPS_GetData(gps_t *out);
void GPS_Setup3Hz(void);
/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __GPS_H */
