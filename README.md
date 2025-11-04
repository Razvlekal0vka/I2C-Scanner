# I2C Scanner для ESP32-C3
# I2C Scanner for ESP32-C3

[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/yourusername/I2C-Scanner)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

## Описание / Description

I2C Scanner - это инструмент для сканирования и обнаружения I2C устройств, подключенных к ESP32-C3 SuperMini. Программа автоматически сканирует все возможные I2C адреса (0x01-0x7F) и определяет типы подключенных устройств.

I2C Scanner is a tool for scanning and detecting I2C devices connected to ESP32-C3 SuperMini. The program automatically scans all possible I2C addresses (0x01-0x7F) and identifies the types of connected devices.

### Возможности / Features

- ✅ Полное сканирование всех I2C адресов (0x01-0x7F) / Full scan of all I2C addresses (0x01-0x7F)
- ✅ Автоматическое определение типов устройств / Automatic device type identification
- ✅ Поддержка устройств в спящем режиме (MPU-6050) / Support for devices in sleep mode (MPU-6050)
- ✅ Визуальная индикация прогресса через LED / Visual progress indication via LED
- ✅ Расширенная диагностика устройств через WHO_AM_I регистры / Extended device diagnostics via WHO_AM_I registers
- ✅ Подробная статистика сканирования / Detailed scan statistics

### Поддерживаемые устройства / Supported Devices

#### I2C устройства (обнаруживаются сканером) / I2C Devices (detected by scanner)

- **MPU-6050** - Гироскоп и акселерометр (0x68, 0x69) / Gyroscope and accelerometer (0x68, 0x69)
- **LIS3DSH** - Трехосевой акселерометр (0x18, 0x19) / 3-axis accelerometer (0x18, 0x19)
- **DS1307** - Модуль часов реального времени (0x48) / Real-time clock module (0x48)
- **EEPROM 24C32** - Энергонезависимая память (0x50) / Non-volatile memory (0x50)
- **BMP280** - Датчик давления и температуры (0x76, 0x77) / Pressure and temperature sensor (0x76, 0x77)
- **OLED SSD1306** - OLED дисплей I2C (0x3C, 0x3D) / OLED display I2C (0x3C, 0x3D)

#### ⚠️ SPI устройства (НЕ обнаруживаются I2C сканером) / SPI Devices (NOT detected by I2C scanner)

**Важно:** Этот сканер работает только с I2C устройствами! Устройства с интерфейсом SPI (CS, DC, RES пины) не могут быть обнаружены.

**Important:** This scanner works only with I2C devices! Devices with SPI interface (CS, DC, RES pins) cannot be detected.

К SPI устройствам относятся / SPI devices include:
- Дисплеи 80x160, 240x240, 320x240 пикселей (ST7735, ILI9341, ST7789) / Displays 80x160, 240x240, 320x240 pixels (ST7735, ILI9341, ST7789)
- Дисплеи с пинами CS, DC, RES, BLK / Displays with CS, DC, RES, BLK pins
- Для работы требуют библиотеки Adafruit_GFX, Adafruit_ST7735 и т.д. / Require Adafruit_GFX, Adafruit_ST7735 libraries, etc.

## Требования / Requirements

### Оборудование / Hardware

- ESP32-C3 SuperMini (или совместимая плата) / ESP32-C3 SuperMini (or compatible board)
- I2C устройства для тестирования / I2C devices for testing
- Соединительные провода / Connection wires

### Программное обеспечение / Software

- Arduino IDE 2.0 или выше / Arduino IDE 2.0 or higher
- ESP32 Board Support Package (ESP32 BSP) / ESP32 Board Support Package
- Библиотека Wire (входит в стандартную поставку Arduino) / Wire library (included with Arduino)

## Установка / Installation

### 1. Установка ESP32 BSP / Install ESP32 BSP

1. Откройте Arduino IDE / Open Arduino IDE
2. Перейдите в **File → Preferences** / Go to **File → Preferences**
3. В поле "Additional Board Manager URLs" добавьте: / In "Additional Board Manager URLs" field add:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Перейдите в **Tools → Board → Boards Manager** / Go to **Tools → Board → Boards Manager**
5. Найдите "ESP32" и установите / Search for "ESP32" and install

### 2. Настройка платы / Board Configuration

1. Выберите плату: **Tools → Board → ESP32 Arduino → ESP32C3 Dev Module** / Select board: **Tools → Board → ESP32 Arduino → ESP32C3 Dev Module**
2. Установите параметры: / Set parameters:
   - **CPU Frequency**: 160MHz (WiFi)
   - **Flash Size**: 4MB
   - **Partition Scheme**: Default
   - **Upload Speed**: 921600

### 3. Загрузка программы / Upload Program

1. Откройте файл `I2C_Scanner/I2C_Scanner.ino` / Open file `I2C_Scanner/I2C_Scanner.ino`
2. Подключите ESP32-C3 к компьютеру через USB / Connect ESP32-C3 to computer via USB
3. Выберите порт: **Tools → Port** / Select port: **Tools → Port**
4. Нажмите кнопку "Upload" (→) / Click "Upload" button (→)

## Использование / Usage

### Подключение устройств / Device Connection

```
ESP32-C3 SuperMini    I2C Device
─────────────────     ──────────
GPIO4 (SDA)      →    SDA
GPIO5 (SCL)      →    SCL
3.3V             →    VCC
GND              →    GND
```

**Примечание:** По умолчанию используются GPIO4 (SDA) и GPIO5 (SCL). Альтернативные пины GPIO8 и GPIO9 можно использовать, раскомментировав соответствующие строки в коде. / **Note:** By default, GPIO4 (SDA) and GPIO5 (SCL) are used. Alternative pins GPIO8 and GPIO9 can be used by uncommenting the corresponding lines in the code.

### Запуск сканирования / Running Scan

1. Откройте Serial Monitor (**Tools → Serial Monitor**) / Open Serial Monitor (**Tools → Serial Monitor**)
2. Установите скорость: **115200 baud** / Set speed: **115200 baud**
3. Нажмите кнопку Reset на ESP32-C3 или перезагрузите плату / Press Reset button on ESP32-C3 or restart the board
4. Дождитесь завершения сканирования / Wait for scan to complete

### Пример вывода / Example Output

```
=== I2C Scanner для ESP32-C3 ===
SDA=GPIO4, SCL=GPIO5
Сканирование адресов 0x01-0x7F...

✓ Найдено устройство на адресе 0x68 (104) - MPU-6050 (подтверждён WHO_AM_I=0x68)
✓ Найдено устройство на адресе 0x3C (60) - OLED SSD1306

=== Результат сканирования ===
⏱️  Время сканирования: 1250 мс
📊 Проверено адресов: 126 (99% от всех возможных)
✅ Найдено устройств: 2
📈 Плотность устройств: 1%
```

## Настройка / Configuration

### Изменение I2C пинов / Changing I2C Pins

В начале файла `I2C_Scanner.ino` можно изменить пины: / At the beginning of `I2C_Scanner.ino` file you can change pins:

```cpp
// Default pins / Пины по умолчанию
#define SDA_PIN 4  // GPIO4
#define SCL_PIN 5  // GPIO5

// Alternative pins / Альтернативные пины (раскомментируйте для использования)
// Uncomment to use alternative pins
//#define SDA_PIN 8  // GPIO8
//#define SCL_PIN 9  // GPIO9
```

### Изменение скорости I2C / Changing I2C Speed

По умолчанию используется 100 кГц. Для изменения скорости найдите строку: / Default is 100 kHz. To change speed, find the line:

```cpp
Wire.setClock(100000); // 100 kHz / 100 кГц
```

Допустимые значения: 100000 (100 кГц), 400000 (400 кГц), 1000000 (1 МГц) / Valid values: 100000 (100 kHz), 400000 (400 kHz), 1000000 (1 MHz)

## Структура проекта / Project Structure

```
I2C-Scanner/
├── I2C_Scanner/
│   └── I2C_Scanner.ino    # Основной файл программы / Main program file
├── README.md               # Документация / Documentation
├── CHANGELOG.md            # История изменений / Changelog
├── LICENSE                 # Лицензия MIT / MIT License
├── VERSION                 # Версия проекта / Project version
└── .gitignore             # Игнорируемые файлы Git / Git ignored files
```

## Устранение неполадок / Troubleshooting

### Устройства не обнаружены / Devices Not Detected

1. **Проверьте подключение** / **Check connections:**
   - SDA → GPIO4 (или GPIO8)
   - SCL → GPIO5 (или GPIO9)
   - VCC → 3.3V (не 5V!)
   - GND → GND

2. **Проверьте общий GND** / **Check common GND:**
   - Все устройства должны иметь общую землю / All devices must share common ground

3. **Проверьте питание** / **Check power:**
   - ESP32-C3 работает на 3.3V / ESP32-C3 operates on 3.3V
   - Убедитесь, что устройства получают питание / Ensure devices receive power

4. **Проверьте подтягивающие резисторы** / **Check pull-up resistors:**
   - I2C шина требует подтягивающих резисторов 4.7 кОм на SDA и SCL / I2C bus requires 4.7 kΩ pull-up resistors on SDA and SCL
   - Многие модули имеют встроенные резисторы / Many modules have built-in resistors

### ⚠️ Устройство не обнаружено, но имеет пины CS, DC, RES / Device Not Detected but Has CS, DC, RES Pins

**Проблема:** Если ваше устройство имеет пины CS (Chip Select), DC (Data/Command), RES (Reset), BLK (Backlight), то это **SPI устройство**, а не I2C!

**Problem:** If your device has CS (Chip Select), DC (Data/Command), RES (Reset), BLK (Backlight) pins, then it's a **SPI device**, not I2C!

**Решение / Solution:**

1. **Это нормально!** I2C сканер не может обнаружить SPI устройства, так как это разные протоколы связи.
   - I2C использует 2 линии (SDA, SCL)
   - SPI использует минимум 4 линии (MOSI, SCK, CS, DC) + опционально RES, BLK

2. **Для работы с SPI дисплеем 80x160:**
   - Используйте библиотеки: `Adafruit_GFX` и `Adafruit_ST7735` (или `Adafruit_ST7789` для ST7789)
   - Подключение для ESP32-C3:
     ```
     Дисплей    ESP32-C3
     ───────    ────────
     VCC    →   3.3V
     GND    →   GND
     SCL    →   GPIO10 (SCK)
     SDA    →   GPIO11 (MOSI)
     RES    →   GPIO12
     DC     →   GPIO13
     CS     →   GPIO14
     BLK    →   GPIO15 (или через резистор к 3.3V)
     ```

3. **Пример кода для SPI дисплея:**
   ```cpp
   #include <Adafruit_GFX.h>
   #include <Adafruit_ST7735.h>
   
   #define TFT_CS    14
   #define TFT_RST   12
   #define TFT_DC    13
   Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
   
   void setup() {
     tft.initR(INITR_BLACKTAB);
     tft.fillScreen(ST77XX_BLACK);
     tft.setTextColor(ST77XX_WHITE);
     tft.setTextSize(2);
     tft.println("Hello!");
   }
   ```

**1. This is normal!** I2C scanner cannot detect SPI devices, as they are different communication protocols.
   - I2C uses 2 lines (SDA, SCL)
   - SPI uses at least 4 lines (MOSI, SCK, CS, DC) + optionally RES, BLK

**2. To work with 80x160 SPI display:**
   - Use libraries: `Adafruit_GFX` and `Adafruit_ST7735` (or `Adafruit_ST7789` for ST7789)
   - Connection for ESP32-C3:
     ```
     Display    ESP32-C3
     ───────    ────────
     VCC    →   3.3V
     GND    →   GND
     SCL    →   GPIO10 (SCK)
     SDA    →   GPIO11 (MOSI)
     RES    →   GPIO12
     DC     →   GPIO13
     CS     →   GPIO14
     BLK    →   GPIO15 (or through resistor to 3.3V)
     ```

**3. Example code for SPI display:**
   ```cpp
   #include <Adafruit_GFX.h>
   #include <Adafruit_ST7735.h>
   
   #define TFT_CS    14
   #define TFT_RST   12
   #define TFT_DC    13
   Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
   
   void setup() {
     tft.initR(INITR_BLACKTAB);
     tft.fillScreen(ST77XX_BLACK);
     tft.setTextColor(ST77XX_WHITE);
     tft.setTextSize(2);
     tft.println("Hello!");
   }
   ```

### Ошибки компиляции / Compilation Errors

- Убедитесь, что установлен ESP32 BSP / Ensure ESP32 BSP is installed
- Проверьте версию Arduino IDE (должна быть 2.0+) / Check Arduino IDE version (should be 2.0+)
- Убедитесь, что выбран правильный тип платы / Ensure correct board type is selected

## Версии / Versions

### v1.0.0 (Текущая / Current)
- Первый релиз / First release
- Полное сканирование I2C адресов / Full I2C address scanning
- Поддержка основных устройств / Support for main devices
- Расширенная диагностика MPU-6050 и LIS3DSH / Extended diagnostics for MPU-6050 and LIS3DSH
- Визуальная индикация прогресса / Visual progress indication

## Лицензия / License

MIT License - см. файл LICENSE для деталей / see LICENSE file for details

## Автор / Author

Создано для ESP32-C3 SuperMini / Created for ESP32-C3 SuperMini

## Благодарности / Acknowledgments

- ESP32 Arduino Community
- Arduino Wire Library

## Вклад в проект / Contributing

Приветствуются любые улучшения и предложения! / Any improvements and suggestions are welcome!

1. Форкните репозиторий / Fork the repository
2. Создайте ветку для новой функции / Create a branch for your feature
3. Внесите изменения / Make your changes
4. Создайте Pull Request / Create a Pull Request

---

**Примечание:** Этот проект создан для ESP32-C3 SuperMini, но может работать с другими платами ESP32 при соответствующей настройке пинов. / **Note:** This project is created for ESP32-C3 SuperMini, but can work with other ESP32 boards with appropriate pin configuration.

