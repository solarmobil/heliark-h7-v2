/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gps.c
  * @brief   GPS driver (UART DMA based)
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

/* Includes ------------------------------------------------------------------*/
#include "gps.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "cmsis_os.h"
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define GPS_DMA_BUF_SIZE   1024
#define GPS_LINE_BUF_SIZE  128
/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */


static uint8_t  gpsDmaBuf[GPS_DMA_BUF_SIZE];
static uint16_t gpsDmaOldPos;

static uint8_t gpsLine[GPS_LINE_BUF_SIZE];
static uint8_t gpsLineIdx;

static gps_t gpsData;
static uint8_t gpsNewData;

extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart3;

extern osMutexId_t gpsmutexHandle;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static void GPS_ProcessLine(char *line);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void GPS_Init(void)
{

  gpsDmaOldPos = 0U;
  gpsLineIdx = 0U;
  gpsNewData = 0U;


  HAL_UART_Receive_DMA(&huart7, gpsDmaBuf, GPS_DMA_BUF_SIZE);

}

void GPS_Task(void)
{
  uint16_t dmaPos =
    GPS_DMA_BUF_SIZE - __HAL_DMA_GET_COUNTER(huart7.hdmarx);

  while (gpsDmaOldPos != dmaPos)
  {
    uint8_t b = gpsDmaBuf[gpsDmaOldPos++];
    if (gpsDmaOldPos >= GPS_DMA_BUF_SIZE)
      gpsDmaOldPos = 0U;

    if (b == '\n')
    {
      gpsLine[gpsLineIdx] = '\0';
      GPS_ProcessLine((char *)gpsLine);
      gpsLineIdx = 0U;
    }
    else if (b != '\r')
    {
      if (gpsLineIdx < GPS_LINE_BUF_SIZE - 1U)
        gpsLine[gpsLineIdx++] = b;
      else
        gpsLineIdx = 0U;
    }
  }
}

uint8_t GPS_GetData(gps_t *out)
{
  //osMutexAcquire(gpsmutexHandle, osWaitForever);
  if (!gpsNewData)
    return 0U;
  //taskENTER_CRITICAL();
  *out = gpsData;

  gpsNewData = 0U;
 // taskEXIT_CRITICAL();
  //osMutexRelease(gpsmutexHandle);
  return 1U;

}

static uint8_t GPS_ChecksumValid(const char *sentence)
{
    if (sentence[0] != '$')
        return 0;

    uint8_t checksum = 0;
    const char *p = sentence + 1;

    while (*p && *p != '*')
        checksum ^= *p++;

    if (*p != '*')
        return 0;

    uint8_t received = (uint8_t)strtol(p + 1, NULL, 16);

    return (checksum == received);
}
static void GPS_ProcessLine(char *line)
{
    if (!GPS_ChecksumValid(line))
        return;

    if (strncmp(line, "$GNRMC", 6) != 0 &&
        strncmp(line, "$GPRMC", 6) != 0)
        return;

    /* Remove checksum part */
    char *asterisk = strchr(line, '*');
    if (asterisk)
        *asterisk = '\0';

    char *p = line;
    char *fieldStart;
    uint8_t field = 0;

    while (*p)
    {
        fieldStart = p;

        /* Move until comma or end */
        while (*p && *p != ',')
            p++;

        /* Temporarily terminate field */
        if (*p == ',')
        {
            *p = '\0';
            p++;
        }

        switch (field)
        {
            case 1:  // Time
                strncpy(gpsData.time, fieldStart, sizeof(gpsData.time)-1);
                gpsData.time[sizeof(gpsData.time)-1] = '\0';
                break;

            case 2:  // Status
                gpsData.status = fieldStart[0];
                break;

            case 3:  // Latitude
                strncpy(gpsData.lat, fieldStart, sizeof(gpsData.lat)-1);
                gpsData.lat[sizeof(gpsData.lat)-1] = '\0';
                break;

            case 4:  // N/S
                gpsData.latHem = fieldStart[0];
                break;

            case 5:  // Longitude
                strncpy(gpsData.lon, fieldStart, sizeof(gpsData.lon)-1);
                gpsData.lon[sizeof(gpsData.lon)-1] = '\0';
                break;

            case 6:  // E/W
                gpsData.lonHem = fieldStart[0];
                break;

            case 7:  // Speed (knots)
                strncpy(gpsData.speed, fieldStart, sizeof(gpsData.speed)-1);
                gpsData.speed[sizeof(gpsData.speed)-1] = '\0';
                break;

            case 9:  // Date
                strncpy(gpsData.date, fieldStart, sizeof(gpsData.date)-1);
                gpsData.date[sizeof(gpsData.date)-1] = '\0';
                break;
        }

        field++;
    }

    if (gpsData.status == 'A')   // Only valid fix
        gpsNewData = 1U;
}
/* ---- GPS configuration commands ---- */

static const char PMTK_SET_NMEA[] =
"$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28\r\n";

static const char PMTK_FIX_3HZ[] =
"$PMTK300,333,0,0,0,0*2E\r\n";

static const char PMTK_NMEA_3HZ[] =
"$PMTK220,333*2D\r\n";

void GPS_Setup3Hz(void)
{
  HAL_UART_Transmit(&huart7, (uint8_t *)PMTK_SET_NMEA,
                    strlen(PMTK_SET_NMEA), HAL_MAX_DELAY);
  HAL_Delay(100);

  HAL_UART_Transmit(&huart7, (uint8_t *)PMTK_FIX_3HZ,
                    strlen(PMTK_FIX_3HZ), HAL_MAX_DELAY);
  HAL_Delay(100);

  HAL_UART_Transmit(&huart7, (uint8_t *)PMTK_NMEA_3HZ,
                    strlen(PMTK_NMEA_3HZ), HAL_MAX_DELAY);
}

/* USER CODE END 0 */
