#include <rtthread.h>
#include "board.h"

#ifdef RT_USING_SPI
#include "stm32f20x_40x_spi.h"

/*
SPI2_MOSI: PB15
SPI2_MISO: PB14
SPI2_SCK : PB13

CS0: PG10  SPI FLASH
CS1: PB12  TOUCH
CS2: PG7   WIFI
*/
static void rt_hw_spi2_init(void)
{
    /* register spi bus */
    {
        static struct stm32_spi_bus stm32_spi;
        GPIO_InitTypeDef GPIO_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        /*!< SPI SCK pin configuration */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        /* Connect alternate function */
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

        stm32_spi_register(SPI2, &stm32_spi, "spi2");
    }

    /* attach cs */
    {
        static struct rt_spi_device spi_device;
        static struct stm32_spi_cs  spi_cs;

        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        /* spi21: PG10 */
        spi_cs.GPIOx = GPIOG;
        spi_cs.GPIO_Pin = GPIO_Pin_10;
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

        GPIO_InitStructure.GPIO_Pin = spi_cs.GPIO_Pin;
        GPIO_SetBits(spi_cs.GPIOx, spi_cs.GPIO_Pin);
        GPIO_Init(spi_cs.GPIOx, &GPIO_InitStructure);

        rt_spi_bus_attach_device(&spi_device, "spi20", "spi2", (void*)&spi_cs);
    }

    /* attach cs */
    {
        static struct rt_spi_device spi_device;
        static struct stm32_spi_cs  spi_cs;

        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        /* spi21: PB12 */
        spi_cs.GPIOx = GPIOB;
        spi_cs.GPIO_Pin = GPIO_Pin_12;
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

        GPIO_InitStructure.GPIO_Pin = spi_cs.GPIO_Pin;
        GPIO_SetBits(spi_cs.GPIOx, spi_cs.GPIO_Pin);
        GPIO_Init(spi_cs.GPIOx, &GPIO_InitStructure);

        rt_spi_bus_attach_device(&spi_device, "spi21", "spi2", (void*)&spi_cs);
    }

    /* attach cs */
    {
        static struct rt_spi_device spi_device;
        static struct stm32_spi_cs  spi_cs;

        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        /* spi20: PG7 */
        spi_cs.GPIOx = GPIOG;
        spi_cs.GPIO_Pin = GPIO_Pin_7;
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

        GPIO_InitStructure.GPIO_Pin = spi_cs.GPIO_Pin;
        GPIO_SetBits(spi_cs.GPIOx, spi_cs.GPIO_Pin);
        GPIO_Init(spi_cs.GPIOx, &GPIO_InitStructure);

        rt_spi_bus_attach_device(&spi_device, "spi22", "spi2", (void*)&spi_cs);
    }
}
#endif


void platform_init(void)
{
#ifdef RT_USING_SPI
    rt_hw_spi2_init();
#endif
}