# Sử dụng giao thức MQTT PROTOCOL và Config wifi qua Webserver

![License](https://scontent.fhan2-1.fna.fbcdn.net/v/t1.0-1/c40.153.520.520/s320x320/15181675_394645134200025_2359352422408378338_n.jpg?oh=64de01ad112e361f1d599492432ee739&oe=58EC488E)

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
## Tiến hành
- Việc làm này nhằm kết nối wifi cho ESP8266 , sau khi connect được với eps8266 bằng địa chỉ trên với 
- SSID : là tên wifi cần connect cho esp8266 , PASS : là mật khẩu wifi cần connect .
- Nếu địa chỉ báo OK có nghĩa connect thành công , còn FALSE tức là không thành công . 
- Sau khi connect thành công , hệ thống kết nối với MQTT BROKER . và sẽ thực hiện bắn bản tin và nhận về bản tin trên thiết bị

## License

Project is licensed under the MIT license.

Copyright (C) 2017 Dat Thanh Vu dattv@hachi.com.vn This software is provided 'as-is', without any express or implied warranty.
