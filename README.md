# Iot-machine-status-firmware
## Thay đổi device code, ap ssid, device password
1. device code: 
    - file __access_point.h__
    - thay đổi giá trị __DEVICE_CODE__
2. AP SSID: 
    - file __access_point.h__
    - thay đổi giá trị __APSSID__
3. device password: 
    - file __access_point.h__
    - thay đổi giá trị __DEVICE_PASSWORD__

## Thay đổi địa chỉ IP server
1. broker:
    - file: __client_mqtt.cpp__
    - thay đổi giá trị __broker[]__
    
## Thay đổi MQTT Credential
1. username & password:
    - file: __client_mqtt.cpp__
    - thay đổi giá trị __"admin" & "mMjAeR8xZYZKzzwP"__ *dòng 90*