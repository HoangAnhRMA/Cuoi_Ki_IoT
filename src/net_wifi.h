#pragma once

// Khởi động WiFi (gọi trong setup)
void wifi_connect();

// Gọi định kỳ trong loop để đảm bảo luôn có WiFi
void wifi_loop();
