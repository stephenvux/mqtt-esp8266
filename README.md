# Sử dụng giao thức MQTT PROTOCOL và Config wifi qua Webserver

![License](https://img.shields.io/github/license/openkitten/mongokitten.svg)

Đây là một ví dụ đơn giản việc sử dụng giao thức MQTT
- [Strand](https://github.com/qutheory/Strand) for fetching server responses without blocking the thread
- Our own [BSON](https://github.com/OpenKitten/BSON) library, which is also 100% native Swift
- Our own [MD5](https://github.com/CryptoKitten/MD5), [SHA1](https://github.com/CryptoKitten/SHA1) and [SCRAM](https://github.com/CryptoKitten/SCRAM) libraries in 100% Swift

## Tài liệu hướng dẫn

Tài liệu có thể đọc ở đây [here](http://datthanhvu.com).


## Yêu cầu

- Cần có một MQTT broker ( có thể test free server test.mosquitto.org )  
- Có kiến thức căn bản về lập trình nhúng , cũng như ngôn ngữ javascript .

Chú ý : Không hỗ trợ tất cả các version , đề nghị update phiên bản mới nhất

#### Chạy ứng dụng
``` ESP8266 ```
# Tutorial

## Setup Arduino ide / PlatformIO

### Install esp8266 on arduino ide

### Unzip folder and run it.

## Hướng dẫn sử dụng

Cài đặt môi trường cho MQTT và đặt mặt khẩu cho esp8266

```C++
const char WiFiAPPSK[] = "datthanhvu"; //Đổi mật khẩu hoặc để trống " "
const char* mqtt_server = "iot.eclipse.org"; // Có thể sử dụng localhost
```

Sau đó Run dự án lên , hãy connect thiết bị của bạn với wifi trên eps8266 .  Sau đó thực hiện xong , gõ địa chỉ sau vào máy tính
```C++
http://192.168.4.1/configwifi?ssid=1334e23&pass=1545678 //ssid : tên wifi bạn muốn connect cho eps8266 , pass : mật khẩu của wifi bạn muốn connect cho eps8266
```

## License

Project is licensed under the MIT license.

Copyright (C) 2017 Dat Thanh Vu dattv@hachi.com.vn This software is provided 'as-is', without any express or implied warranty.
