// med_box.cpp
#include "med_box.h"
#include "config.h"
#include "net_mqtt.h"
#include "reed_sensor.h"
#include "confirm_button.h"

#include <Arduino.h>

namespace {

// ======== TRẠNG THÁI NGHIỆP VỤ ========
bool doorOpen          = false;  // nắp hiện tại
bool confirmedThisOpen = false;  // đã confirm trong lần mở này chưa

unsigned int doseCountToday = 0;

bool postConfirmArmed = false;   // đã gài nhắc sau confirm?
unsigned long confirmMs = 0;     // thời điểm confirm
bool buzzerIsOn = false;

// ======== HÀM TIỆN ÍCH ========
void setBuzzer(bool on) {
  buzzerIsOn = on;
  if (BUZZER_ACTIVE_LOW) {
    digitalWrite(PIN_BUZZER, on ? LOW : HIGH);
  } else {
    digitalWrite(PIN_BUZZER, on ? HIGH : LOW);
  }
}

void updateLed() {
  // LED sáng khi nắp MỞ và chưa xác nhận
  digitalWrite(PIN_LED, (doorOpen && !confirmedThisOpen) ? HIGH : LOW);
}

void printDoseCount() {
  Serial.print(F("So lan da uong (chua reset theo ngay): "));
  Serial.println(doseCountToday);
}

void onDoorOpened() {
  doorOpen = true;
  confirmedThisOpen = false;

  Serial.println(F("Nap MO. LED sang cho xac nhan."));
  mqtt.publish(TOPIC_DOOR, "OPEN", true);

  if (postConfirmArmed || buzzerIsOn) {
    postConfirmArmed = false;
    setBuzzer(false);
    Serial.println(F("Buzzer tat vi nap MO."));
  }

  updateLed();
}

void onDoorClosed() {
  doorOpen = false;
  Serial.println(F("Nap DONG."));
  mqtt.publish(TOPIC_DOOR, "CLOSED", true);
  updateLed();
}

void handleConfirmPress() {
  // 1) Chỉ xác nhận khi nắp đang mở
  if (!doorOpen) {
    Serial.println(F("Khong the xac nhan: Nap DONG."));
    return;
  }

  // 2) Chỉ được xác nhận 1 lần cho mỗi lần mở
  if (confirmedThisOpen) {
    Serial.println(F("Lan MO nay da xac nhan roi."));
    return;
  }

  // 3) Xác nhận hợp lệ
  confirmedThisOpen = true;
  Serial.println(F("XAC NHAN: Da uong thuoc."));
  updateLed();

  // Tăng bộ đếm liều
  doseCountToday++;
  char buf[16];
  snprintf(buf, sizeof(buf), "%u", doseCountToday);
  mqtt.publish(TOPIC_DOSE, buf, true);
  mqtt.publish(TOPIC_CONFIRM, "TAKEN", false);
  printDoseCount();

  // Gài nhắc sau 10 giây
  postConfirmArmed = true;
  confirmMs = millis();
  setBuzzer(false);

  Serial.println(F("Da gai nhac: Sau 10s neu nap DONG thi buzzer keu den khi MO nap."));
}

void handlePostConfirmBuzzer() {
  if (!postConfirmArmed) return;

  unsigned long now = millis();
  if (now - confirmMs < REMINDER_DELAY_MS) return;

  if (doorOpen) {
    // sau 10s mà nắp vẫn mở -> không nhắc
    postConfirmArmed = false;
    setBuzzer(false);
    return;
  }

  if (!buzzerIsOn) {
    setBuzzer(true);
    Serial.println(F("Buzzer keu nhac. MO nap de tat."));
  }
}

} // namespace

// ======== API PUBLIC ========

void med_setup() {
  Serial.println(F("=== KIEM THU HOP THUOC (MED BOX) ==="));

  reed_init(PIN_REED);
  button_init(PIN_BUTTON);

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  digitalWrite(PIN_LED, LOW);
  setBuzzer(false);

  doorOpen = reed_isOpen();
  confirmedThisOpen = false;
  updateLed();

  Serial.print(F("Trang thai nap ban dau: "));
  Serial.println(doorOpen ? F("MO") : F("DONG"));

  printDoseCount();
}

void med_loop() {
  // 1) Cập nhật trạng thái nắp
  if (reed_update()) {
    if (reed_isOpen()) {
      onDoorOpened();
    } else {
      onDoorClosed();
    }
  }

  // 2) Xử lý nút nhấn xác nhận
  if (button_update()) {
    handleConfirmPress();
  }

  // 3) Xử lý nhắc nhở bằng buzzer
  handlePostConfirmBuzzer();

  // 4) Nếu nắp mở trong lúc buzzer đang kêu thì tắt luôn
  if (buzzerIsOn && doorOpen) {
    postConfirmArmed = false;
    setBuzzer(false);
    Serial.println(F("Buzzer tat vi nap MO."));
  }
}
