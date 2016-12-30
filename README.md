# Sử dụng giao thức MQTT PROTOCOL và Config wifi qua Webserver

![License](http://datthanhvu.com)

Đây là một ví dụ đơn giản việc sử dụng giao thức MQTT
- [Tác giả](http://datthanhvu.com) 
- [Facebook](https://www.facebook.com/datthanhvu98) 

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
```URL
http://192.168.4.1/configwifi?ssid=1334e23&pass=1545678
```

## License

Project is licensed under the MIT license.

Copyright (C) 2017 Dat Thanh Vu dattv@hachi.com.vn This software is provided 'as-is', without any express or implied warranty.
