# MSP430FR5994


```c

//  Vin= 1V-3V -----------------
//     |      |                 |
//    10K     |                 |
//     |      |                 |
//     |      |                 |
//     -------| A2=2/3Vin   P5.1|-> SPI Data Out (UCB1SOMI)
//     |      |                 |
//     10K    |             P5.0|<- SPI Data In (UCB1SIMO)
//     |      |             P5.2|-> SPI Serial Clock Out (UCB1CLK)
//     |      |             P5.3|<- SPI Slave Select (UCB1STE)
//     -------| A3=1/3Vin   P2.5|--> UART UCA1TXD
//     |      |             P2.6|--> UART UCA1RXD
//    10K     |             P1.0|-->LED
//     |      |                 |
//    GND

//  --------------------------------------------------------------------------
//  UART Communication Protocol (only applicable for standalone mode)
//  --------------------------------------------------------------------------
//  [COMMAND] <data> <data> <data> <data>
//
//  COMMANDS:                                     RESPONSES:
//  RTC_READ_TIME =      00h                      00h XXh XXh XXh XXh
//  RTC_WRITE_TIME =     01h XXh XXh XXh XXh
//  RTC_READ_THR_HIGH =  02h                      02h XXh XXh XXh XXh
//  RTC_READ_THR_LOW =   03h                      03h XXh XXh XXh XXh
//  ADC_READ_THR_HIGH =  04h                      04h XXh XXh
//  ADC_READ_THR_LOW =   05h                      05h XXh XXh
//  ADC_WRITE_THR_HIGH = 06h XXh XXh
//  ADC_WRITE_THR_LOW =  07h XXh XXh
//
```


|  Function                   | REF Link  |
|  ---------------------------| --------  |
| Solar_LED_MPPT_Charger      | https://github.com/circuitvalley/Solar_LED_MPPT_Charger |
| SMBUS LIB                   | https://www.ti.com/tool/MSP430-SMBUS#downloads| 
| Ti MSP430FR5994 Documetaion | https://dev.ti.com/tirex/explore/node?node=A__AMwsQ36ncmEHzBjPlhXZZg__msp430ware__IOGqZri__LATEST|
| FloripaSat                  | https://github.com/orgs/floripasat/repositories?q=eps|
| FloripaSat 2                | https://github.com/orgs/floripasat/repositories?q=eps|
| UWCubesat                   | https://github.com/orgs/floripasat/repositories?q=eps|
| Oresat                      | https://github.com/oresat/oresat-batteries , https://github.com/oresat/oresat-battery-testing|
| MAX7219 8x8 LED(SPI) |  |
| SD Card(SPI) | |
| TCA9548A I2C Multiplexer 8 | |
|SPI Trip document | https://medium.com/weiting-tw/%E6%8A%80%E8%A1%93%E7%AD%86%E8%A8%98-spi%E9%80%9A%E8%A8%8A%E5%8D%94%E5%AE%9A%E6%93%8D%E4%BD%9C-a9c6f4b8462a|
| build linux kernel by yocto| https://www.linkedin.com/pulse/yocto-embedded-linux-building-your-own-first-image-raspberry-haddad/|
|Intro to Embedded Linux Part 5 - How to Enable I2C in the Yocto Project| https://www.digikey.com/en/maker/projects/intro-to-embedded-linux-part-5-how-to-enable-i2c-in-the-yocto-project/6843bbf9a83c4c96888fccada1e7aedf|
|Yocto Tutorial  | https://www.youtube.com/watch?v=VFRrbMVboyE&list=PLwqS94HTEwpQmgL1UsSwNk_2tQdzq3eVJ&index=50|
| msp430_max7219 Project|https://github.com/evilbetty/msp430_max7219_ledmatrix|
| adc1115| https://www.taiwaniot.com.tw/product/ads1115-%E8%B6%85%E5%B0%8F%E5%9E%8B16%E4%BD%8D%E7%B2%BE%E5%AF%86%E6%A8%A1%E6%95%B8%E8%BD%89%E6%8F%9B%E5%99%A8adc-%E9%96%8B%E7%99%BC%E6%9D%BF%E6%A8%A1%E7%B5%84/|
| embe project | https://bugworkshop.blogspot.com/2018/11/diy-esp32esp32-ov7670-al422b.html|
| MSP430 WatchDog api | https://blog.csdn.net/k331922164/article/details/108135881|
| MSP430FR5994 SPI | https://blog.csdn.net/wo4fisher/article/details/124586449|
