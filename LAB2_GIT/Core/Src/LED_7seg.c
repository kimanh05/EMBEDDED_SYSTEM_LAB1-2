/*
 * LED_7seg.c
 *
 *  Created on: Oct 1, 2026
 *      Author: kiman
 */


#include "LED_7seg.h"

/* hspi1 được CubeMX sinh trong main.c */
extern SPI_HandleTypeDef hspi1;


/*
 * U15 - 74HC595 điều khiển segment
 *
 * Bit 7 -> a
 * Bit 6 -> b
 * Bit 5 -> c
 * Bit 4 -> d
 * Bit 3 -> e
 * Bit 2 -> f
 * Bit 1 -> g
 * Bit 0 -> dp
 *
 * Các segment active LOW.
 */

/* Mã hiển thị số 0 -> 9, active LOW */
static const uint8_t SEGMENT_CODE[10] =
{
    0x03,   // 0
    0x9F,   // 1
    0x25,   // 2
    0x0D,   // 3
    0x99,   // 4
    0x49,   // 5
    0x41,   // 6
    0x1F,   // 7
    0x01,   // 8
    0x09    // 9
};


/*
 * U14 - 74HC595 điều khiển chọn LED
 *
 * Q7 -> LED4
 * Q6 -> LED1
 * Q5 -> LED2
 * Q4 -> LED3
 * Q3 -> COLON
 * Q2 -> LED8
 * Q1 -> LED7
 * Q0 -> LED6
 *
 * Active LOW.
 */

/* position 0,1,2,3 tương ứng LED từ trái sang phải */
static const uint8_t DIGIT_SELECT[4] =
{
    (1 << 6),     // LED1
    (1 << 5),     // LED2
    (1 << 4),     // LED3
    (1 << 7)      // LED4
};


/* Buffer hiển thị 4 LED */
static volatile uint8_t led_buffer[4] =
{
    0xFF,
    0xFF,
    0xFF,
    0xFF
};

static volatile uint8_t colon_status = 0;

/* Bit 0,1,2 tương ứng LED6,7,8 đang bật */
static volatile uint8_t auxiliary_led = 0;

static uint8_t scan_position = 0;


/* --------------------------------------------------------- */
/* Gửi 16 bit tới 2 IC 74HC595                              */
/* --------------------------------------------------------- */
static void LED7_SendData(uint8_t control, uint8_t segment)
{
    uint8_t data[2];

    /*
     * U15 nhận MOSI trước, SDO của U15 nối sang U14.
     *
     * Sau 16 clock:
     * byte đầu tiên nằm ở U14
     * byte thứ hai nằm ở U15
     */
    data[0] = control;
    data[1] = segment;

    /* Hạ latch trước khi shift dữ liệu */
    HAL_GPIO_WritePin(LD_LATCH_GPIO_Port,
                      LD_LATCH_Pin,
                      GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1,
                     data,
                     2,
                     10);

    /* Cạnh lên latch dữ liệu ra output */
    HAL_GPIO_WritePin(LD_LATCH_GPIO_Port,
                      LD_LATCH_Pin,
                      GPIO_PIN_SET);
}


/* --------------------------------------------------------- */
/* Khởi tạo LED 7 đoạn                                      */
/* --------------------------------------------------------- */
void LED7_init(void)
{
    scan_position = 0;
    colon_status = 0;
    auxiliary_led = 0;

    for (uint8_t i = 0; i < 4; i++)
    {
        led_buffer[i] = 0xFF;
    }

    HAL_GPIO_WritePin(LD_LATCH_GPIO_Port,
                      LD_LATCH_Pin,
                      GPIO_PIN_SET);

    /* Tắt tất cả LED lúc khởi động */
    LED7_SendData(0xFF, 0xFF);
}


/* --------------------------------------------------------- */
/* Quét 4 LED 7 đoạn                                        */
/* Gọi hàm này mỗi 1 ms                                     */
/* --------------------------------------------------------- */
void LED7_Scan(void)
{
    uint8_t control = 0xFF;

    /* Chọn 1 trong 4 LED - active LOW */
    control &= ~DIGIT_SELECT[scan_position];

    /* Colon */
    if (colon_status)
    {
        control &= ~(1 << 3);
    }

    /* LED6, LED7, LED8 */
    control &= ~auxiliary_led;

    /* Xuất dữ liệu */
    LED7_SendData(control,
                  led_buffer[scan_position]);

    /* Chuyển sang LED kế tiếp */
    scan_position++;

    if (scan_position >= 4)
    {
        scan_position = 0;
    }
}


/* --------------------------------------------------------- */
/* Đặt số cho một vị trí                                    */
/* position: 0 -> 3                                         */
/* show_dot: 0 = không chấm, 1 = có chấm                    */
/* --------------------------------------------------------- */
void LED7_SetDigit(int num,
                   int position,
                   uint8_t show_dot)
{
    if (position < 0 || position > 3)
    {
        return;
    }

    uint8_t value;

    if (num >= 0 && num <= 9)
    {
        value = SEGMENT_CODE[num];
    }
    else
    {
        /* Blank */
        value = 0xFF;
    }

    /* Decimal point active LOW */
    if (show_dot)
    {
        value &= ~0x01;
    }
    else
    {
        value |= 0x01;
    }

    led_buffer[position] = value;
}


/* --------------------------------------------------------- */
/* Bật/tắt dấu hai chấm                                     */
/* --------------------------------------------------------- */
void LED7_SetColon(uint8_t status)
{
    colon_status = (status != 0);
}


/* --------------------------------------------------------- */
/* Điều khiển LED6, LED7, LED8                              */
/* index = 6, 7 hoặc 8                                      */
/* --------------------------------------------------------- */
void LED_On(uint8_t index)
{
    switch (index)
    {
        case 6:
            auxiliary_led |= (1 << 0);
            break;

        case 7:
            auxiliary_led |= (1 << 1);
            break;

        case 8:
            auxiliary_led |= (1 << 2);
            break;

        default:
            break;
    }
}


void LED_Off(uint8_t index)
{
    switch (index)
    {
        case 6:
            auxiliary_led &= ~(1 << 0);
            break;

        case 7:
            auxiliary_led &= ~(1 << 1);
            break;

        case 8:
            auxiliary_led &= ~(1 << 2);
            break;

        default:
            break;
    }
}
