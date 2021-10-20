#include "Nintendo.h"
#include <NintendoSwitchControlLibrary.h>

// Define a Gamecube Controller and a Console
CGamecubeController GamecubeController1(7);

// definitions
#define pinLed LED_BUILTIN
//ここの値は各自調整してください
#define SnapBackThreshold 70 //跳ね戻りを判定するための閾値
#define xaxismin 30 //スティックx座標の(おおまかな)最小値
#define xaxismax 220 //スティックx座標の最大値
#define yaxismin 20 //スティックy座標の最小値
#define yaxismax 205 //スティックy座標の最大値
#define cxaxismin 55 //Cスティックx座標の最小値
#define cxaxismax 225 //Cスティックx座標の最大値
#define cyaxismin 20 //Cスティックy座標の最小値
#define cyaxismax 195 //Cスティックy座標の最大値

void setup()
{
  // Set up debug led
  pinMode(pinLed, OUTPUT);
}

bool snaplx0flag = false;
bool snaplx255flag = false;
bool snaply0flag = false;
bool snaply255flag = false;
bool snapcx0flag = false;
bool snapcx255flag = false;
bool snapcy0flag = false;
bool snapcy255flag = false;
uint8_t lx;
uint8_t ly;
uint8_t cx;
uint8_t cy;

void loop()
{
    if (!GamecubeController1.read()) {
      Serial.println(F("Error reading Gamecube controller 1."));
      digitalWrite(pinLed, HIGH);
      delay(1000);
      return;
    } else {
        digitalWrite(pinLed, LOW);
    }

    // Get the data of each controller
    auto r1 = GamecubeController1.getReport();

    if (r1.a) {
        SwitchControlLibrary().pressButton(Button::A);
    } else {
        SwitchControlLibrary().releaseButton(Button::A);
    }

    if (r1.b) {
        SwitchControlLibrary().pressButton(Button::B);
    } else {
        SwitchControlLibrary().releaseButton(Button::B);
    }

    if (r1.x) {
        SwitchControlLibrary().pressButton(Button::X);
    } else {
        SwitchControlLibrary().releaseButton(Button::X);
    }

    if (r1.y) {
        SwitchControlLibrary().pressButton(Button::Y);
    } else {
        SwitchControlLibrary().releaseButton(Button::Y);
    }

    if (r1.start) {
        SwitchControlLibrary().pressButton(Button::PLUS);
    } else {
        SwitchControlLibrary().releaseButton(Button::PLUS);
    }

    //if (r1.dup && r1.dright) {
    //    SwitchControlLibrary().pressButton(Hat::UP_RIGHT);
    //} else if (r1.dup && r1.dleft) {
    //    SwitchControlLibrary().pressButton(Hat::UP_LEFT);
    //} else if (r1.ddown && r1.dright) {
    //    SwitchControlLibrary().pressButton(Hat::DOWN_RIGHT);
    //} else if (r1.ddown && r1.dleft) {
    //    SwitchControlLibrary().pressButton(Hat::DOWN_LEFT);
    //} else 
    if (r1.dup) {
        SwitchControlLibrary().pressHatButton(Hat::UP);
    }
    if (r1.dright) {
        SwitchControlLibrary().pressHatButton(Hat::RIGHT);
    }
    if (r1.ddown) {
        SwitchControlLibrary().pressHatButton(Hat::DOWN);
    }
    if (r1.dleft) {
        SwitchControlLibrary().pressHatButton(Hat::LEFT);
    }
    if (!r1.dup && !r1.dright && !r1.dleft && !r1.ddown) {
        SwitchControlLibrary().releaseHatButton();
    }

    if (r1.z) {
        SwitchControlLibrary().pressButton(Button::ZR);
    } else {
        SwitchControlLibrary().releaseButton(Button::ZR);
    }

    if (r1.l) {
        SwitchControlLibrary().pressButton(Button::L);
    } else {
        SwitchControlLibrary().releaseButton(Button::L);
    }

    if (r1.r) {
        SwitchControlLibrary().pressButton(Button::R);
    } else {
        SwitchControlLibrary().releaseButton(Button::R);
    }

    if (r1.xAxis >= xaxismax) {
        snaplx255flag = true;
        lx = r1.xAxis;
    } else if (r1.xAxis <= xaxismin) {
        snaplx0flag = true;
        lx = r1.xAxis;
    } else if (snaplx255flag && r1.xAxis < 108 && r1.xAxis > 128 - SnapBackThreshold) {
        snaplx255flag = false;
        lx = 128;
    } else if (snaplx0flag && r1.xAxis > 148 && r1.xAxis < 128 + SnapBackThreshold) {
        snaplx0flag = false;
        lx = 128;
    } else {
        snaplx255flag = false;
        snaplx0flag = false;
        lx = r1.xAxis;
    }

    if (r1.yAxis == yaxismax) {
        snaply255flag = true;
        ly = 128 - (r1.yAxis - 128);
    } else if (r1.yAxis == yaxismin) {
        snaply0flag = true;
        ly = 128 + (128 - r1.yAxis);
    } else if (snaply255flag && r1.yAxis < 108 && r1.yAxis > 128 - SnapBackThreshold) {
        snaply255flag = false;
        ly = 128;
    } else if (snaply0flag && r1.yAxis > 148 && r1.yAxis < 128 + SnapBackThreshold) {
        snaply0flag = false;
        ly = 128;
    } else {
        snaply255flag = false;
        snaply0flag = false;
        if (r1.yAxis >= 129) {
            ly = 128 - (r1.yAxis - 128);
        } else if (r1.yAxis <= 127) {
            ly = 128 + (128 - r1.yAxis);
        } else {
            ly = r1.yAxis;
        }
    }

    SwitchControlLibrary().moveLeftStick(lx, ly);

    if (r1.cxAxis == cxaxismax) {
        snapcx255flag = true;
        cx = r1.cxAxis;
    } else if (r1.cxAxis == cxaxismin) {
        snapcx0flag = true;
        cx = r1.cxAxis;
    } else if (snapcx255flag && r1.cxAxis < 108 && r1.cxAxis > 128 - SnapBackThreshold) {
        snapcx255flag = false;
        cx = 128;
    } else if (snapcx0flag && r1.cxAxis > 148 && r1.cxAxis < 128 + SnapBackThreshold) {
        snapcx0flag = false;
        cx = 128;
    } else {
        snapcx255flag = false;
        snapcx0flag = false;
        cx = r1.cxAxis;
    }

    if (r1.cyAxis == cyaxismax) {
        snapcy255flag = true;
        cy = 128 - (r1.cyAxis - 128);
    } else if (r1.cyAxis == cyaxismin) {
        snapcy0flag = true;
        cy = 128 + (128 - r1.cyAxis);
    } else if (snapcy255flag && r1.cyAxis < 108 && r1.cyAxis > 128 - SnapBackThreshold) {
        snapcy255flag = false;
        cy = 128;
    } else if (snapcy0flag && r1.cyAxis > 148 && r1.cyAxis < 128 + SnapBackThreshold) {
        snapcy0flag = false;
        cy = 128;
    } else {
        snapcy255flag = false;
        snapcy0flag = false;
        if (r1.cyAxis >= 129) {
            cy = 128 - (r1.cyAxis - 128);
        } else if (r1.cyAxis <= 127) {
            cy = 128 + (128 - r1.cyAxis);
        } else {
            cy = r1.cyAxis;
        }
    }
    SwitchControlLibrary().moveRightStick(cx, cy);
    SwitchControlLibrary().sendReport();
    //ToDo
    //諸々の処理時間を鑑みて13にしてるが16.6666...ms毎のswitchの読み取りに合わせたい
    delay(13);
}
