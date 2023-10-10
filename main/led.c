#include "led.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "task_common.h"

// Configuration for led gpio
static void led_gpio_config(void)
{
    /*
    pinMode(GPIO_NUM_LED, 1);
    */
    gpio_config_t led_config = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLDOWN_DISABLE,
        .pin_bit_mask = (1ULL << GPIO_NUM_LED)};

    gpio_config(&led_config);
}

static void led_task(void)
{
    while (1)
    {
        /**
         *digitalWrite(GPIO_NUM_LED, 1);
         */
        gpio_set_level(GPIO_NUM_LED, 1);
        printf("led on\n");

        // delay(1000);
        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME));

        gpio_set_level(GPIO_NUM_LED, 0);
        printf("led off\n");

        // delay(1000);
        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME));
    }
    vTaskDelay(pdMS_TO_TICKS(100));
}

void led_app(void)
{
    led_gpio_config();
    xTaskCreatePinnedToCore(led_task, "Led task", LED_TASK_STACK_SIZE, NULL, LED_TASK_PRIORITY, NULL, LED_TASK_CORE_ID);
}
