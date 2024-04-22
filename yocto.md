

| topic | URL|
|  ---------------------------| --------  |
| opkg | https://blog.csdn.net/qq_41453285/article/details/102523263|
| 2C Driver (Part 1) - 使用 Device Tree 來找 Driver | https://ithelp.ithome.com.tw/articles/10244211|
| 在 i.MX 8QuadXPlus 上使用 Yocto 建置 Linux 系統 2 |https://e61983.github.io/2021-09-02-yocto-with-imx8qxp-2/|

```c
/dts-v1/;
/plugin/;
/*
opkg install

vcdbg
*/
/ {
    compatible = "brcm,bcm2835";
    fragment@0 {
        target = <&i2c1>;
        __overlay__ {
            #address-cells = <1>;
            #size-cells = <0>;
            arduino-i2c@8 {
                compatible = "arduino";
                reg = <0x8>;
            };
        };
    };
};
```