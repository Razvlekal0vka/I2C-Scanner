#include <Wire.h>

// ESP32-C3 SuperMini I2C pins (default)
// ESP32-C3 SuperMini I2C пины (по умолчанию)
#define SDA_PIN 4  // GPIO4
#define SCL_PIN 5  // GPIO5
//#define SDA_PIN 8  // GPIO8 - SDA (alternative pin)
//#define SCL_PIN 9  // GPIO9 - SCL (alternative pin)
#define LED_PIN 8  // Built-in LED ESP32-C3 SuperMini / Встроенный светодиод ESP32-C3 SuperMini

void setup() {
  Serial.begin(115200);
  // Wait for Serial Monitor connection / Ждём подключения Serial Monitor
  while (!Serial);
  
  Serial.println("\n=== I2C Scanner для ESP32-C3 ===");
  Serial.print("SDA=GPIO"); Serial.print(SDA_PIN);
  Serial.print(", SCL=GPIO"); Serial.println(SCL_PIN);
  Serial.println("Сканирование адресов 0x01-0x7F...\n");
  
  // Initialize I2C with custom pins / Инициализация I2C с кастомными пинами
  Wire.begin(SDA_PIN, SCL_PIN);
  // 100 kHz for reliability / 100 кГц для надёжности
  Wire.setClock(100000);
  
  // LED setup / Настройка светодиода
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  int found = 0;
  // 0x01 to 0x7E / 0x01 до 0x7E
  int total = 126;
  unsigned long startTime = millis();
  
  Serial.println("Прогресс сканирования:");
  Serial.println("0%   25%  50%  75%  100%");
  Serial.println("|----|----|----|----|");
  Serial.println("💡 Светодиод мигает при проверке каждого адреса");
  Serial.println("🔍 Расширенное сканирование: пробуждение спящих устройств\n");
  
  for (int addr = 1; addr < 127; addr++) {
    // Blink LED when checking each address / Мигаем светодиодом при проверке каждого адреса
    digitalWrite(LED_PIN, HIGH);
    // Short delay for visible blinking / Короткая задержка для видимости мигания
    delay(5);
    // Show progress every 5% / Показываем прогресс каждые 5%
    if (addr % 6 == 0) {
      int progress = (addr * 100) / total;
      Serial.print("█");
    }
    
    bool deviceFound = false;
    String deviceType = "Неизвестное устройство";
    
    // Standard I2C check / Стандартная проверка I2C
    Wire.beginTransmission(addr);
    int error = Wire.endTransmission();
    
    // Turn off LED after check / Выключаем светодиод после проверки
    digitalWrite(LED_PIN, LOW);
    
    if (error == 0) {
      deviceFound = true;
      
      // Special check for MPU-6050 (0x68 or 0x69) / Специальная проверка для MPU-6050 (0x68 или 0x69)
      if (addr == 0x68 || addr == 0x69) {
        // Try to wake up MPU-6050 (write 0x00 to PWR_MGMT_1 register 0x6B)
        // Пытаемся пробудить MPU-6050 (записываем 0x00 в PWR_MGMT_1 регистр 0x6B)
        Wire.beginTransmission(addr);
        Wire.write(0x6B);  // PWR_MGMT_1
        Wire.write(0x00);   // Exit sleep mode / Выход из спящего режима
        if (Wire.endTransmission() == 0) {
          // Give time to wake up / Даём время на пробуждение
          delay(10);
          
          // Try to read WHO_AM_I register (0x75) / Пытаемся прочитать WHO_AM_I регистр (0x75)
          Wire.beginTransmission(addr);
          Wire.write(0x75);
          // repeated start / повторный старт
          if (Wire.endTransmission(false) == 0) {
            if (Wire.requestFrom(addr, 1) == 1) {
              uint8_t whoAmI = Wire.read();
              if (whoAmI == 0x68) {
                deviceType = "MPU-6050 (подтверждён WHO_AM_I=0x68)";
                deviceFound = true;
              } else {
                deviceType = "Возможно MPU-6050 (WHO_AM_I=0x" + String(whoAmI, HEX) + ")";
                deviceFound = true;
              }
            }
          }
        }
        
        // If standard check passed but WHO_AM_I wasn't read / Если стандартная проверка прошла, но WHO_AM_I не прочитался
        if (deviceType == "Неизвестное устройство") {
          deviceType = "MPU-6050 (возможно в спящем режиме)";
        }
      } 
      // Special check for LIS3DSH (0x18 or 0x19) / Специальная проверка для LIS3DSH (0x18 или 0x19)
      else if (addr == 0x18 || addr == 0x19) {
        // Try to read WHO_AM_I register (0x0F) / Пытаемся прочитать WHO_AM_I регистр (0x0F)
        Wire.beginTransmission(addr);
        Wire.write(0x0F);  // WHO_AM_I register
        // repeated start / повторный старт
        if (Wire.endTransmission(false) == 0) {
          if (Wire.requestFrom(addr, 1) == 1) {
            uint8_t whoAmI = Wire.read();
            if (whoAmI == 0x33) {
              deviceType = "LIS3DSH (подтверждён WHO_AM_I=0x33)";
              deviceFound = true;
            } else {
              deviceType = "Возможно LIS3DSH (WHO_AM_I=0x" + String(whoAmI, HEX) + ")";
              deviceFound = true;
            }
          }
        }
        
        // If standard check passed but WHO_AM_I wasn't read / Если стандартная проверка прошла, но WHO_AM_I не прочитался
        if (deviceType == "Неизвестное устройство") {
          deviceType = "Возможно LIS3DSH";
        }
      } 
      // Identify other device types / Определяем другие типы устройств
      else if (addr == 0x48) {
        deviceType = "DS1307 (RTC)";
      } else if (addr == 0x50) {
        deviceType = "EEPROM 24C32";
      } else if (addr == 0x76 || addr == 0x77) {
        deviceType = "BMP280";
      } else if (addr == 0x3C || addr == 0x3D) {
        deviceType = "OLED SSD1306";
      }
      
      if (deviceFound) {
        Serial.print("\n✓ Найдено устройство на адресе 0x");
        if (addr < 16) Serial.print("0");
        Serial.print(addr, HEX);
        Serial.print(" (");
        Serial.print(addr);
        Serial.print(") - ");
        Serial.println(deviceType);
        found++;
      }
    } else if (error == 4) {
      Serial.print("\n? Неизвестная ошибка на адресе 0x");
      if (addr < 16) Serial.print("0");
      Serial.print(addr, HEX);
      Serial.println();
    }
  }
  
  unsigned long scanTime = millis() - startTime;
  
  Serial.println("\n\n=== Результат сканирования ===");
  Serial.print("⏱️  Время сканирования: ");
  Serial.print(scanTime);
  Serial.println(" мс");
  
  Serial.print("📊 Проверено адресов: ");
  Serial.print(total);
  Serial.print(" (");
  Serial.print((total * 100) / 127);
  Serial.println("% от всех возможных)");
  
  if (found == 0) {
    Serial.println("❌ Устройства не найдены!");
    Serial.println("\n🔧 Возможные причины:");
    Serial.println("• SDA/SCL подключены неправильно (SDA→GPIO4, SCL→GPIO5)");
    Serial.println("• Нет общего GND между платами");
    Serial.println("• Устройства не получают питание (3.3V для ESP32-C3)");
    Serial.println("• Плохое качество соединений");
    Serial.println("• Устройства повреждены");
    Serial.println("\n⚠️  ВАЖНО: Это I2C сканер!");
    Serial.println("   Устройства с интерфейсом SPI (CS, DC, RES пины)");
    Serial.println("   не могут быть обнаружены I2C сканером!");
    Serial.println("   SPI дисплеи (80x160, ST7735, ILI9341 и т.д.)");
    Serial.println("   требуют отдельной библиотеки для работы.");
    Serial.println("\n⚠️  IMPORTANT: This is I2C scanner!");
    Serial.println("   Devices with SPI interface (CS, DC, RES pins)");
    Serial.println("   cannot be detected by I2C scanner!");
    Serial.println("   SPI displays (80x160, ST7735, ILI9341, etc.)");
    Serial.println("   require separate library to work.");
  } else {
    Serial.print("✅ Найдено устройств: ");
    Serial.println(found);
    Serial.print("📈 Плотность устройств: ");
    Serial.print((found * 100) / total);
    Serial.println("%");
  }
  
  Serial.println("\n=== Справочник устройств ===");
  Serial.println("I2C устройства (обнаруживаются этим сканером):");
  Serial.println("0x68 - MPU-6050 (по умолчанию)");
  Serial.println("0x69 - MPU-6050 (если ADO к VCC)");
  Serial.println("0x18 - LIS3DSH (если SDO/SA0 к GND)");
  Serial.println("0x19 - LIS3DSH (если SDO/SA0 к VCC)");
  Serial.println("0x48 - DS1307 (RTC)");
  Serial.println("0x50 - EEPROM 24C32");
  Serial.println("0x76 - BMP280");
  Serial.println("0x77 - BMP280");
  Serial.println("0x3C - OLED SSD1306 (I2C)");
  Serial.println("0x3D - OLED SSD1306 (I2C)");
  Serial.println("\n⚠️  SPI устройства (НЕ обнаруживаются I2C сканером):");
  Serial.println("   • Дисплеи 80x160, 240x240, 320x240 (ST7735, ILI9341)");
  Serial.println("   • Дисплеи с пинами CS, DC, RES, BLK");
  Serial.println("   • Требуют библиотеки Adafruit_GFX, Adafruit_ST7735 и т.д.");
  Serial.println("\n=== Device Reference ===");
  Serial.println("I2C devices (detected by this scanner):");
  Serial.println("0x68 - MPU-6050 (default)");
  Serial.println("0x69 - MPU-6050 (if ADO to VCC)");
  Serial.println("0x18 - LIS3DSH (if SDO/SA0 to GND)");
  Serial.println("0x19 - LIS3DSH (if SDO/SA0 to VCC)");
  Serial.println("0x48 - DS1307 (RTC)");
  Serial.println("0x50 - EEPROM 24C32");
  Serial.println("0x76 - BMP280");
  Serial.println("0x77 - BMP280");
  Serial.println("0x3C - OLED SSD1306 (I2C)");
  Serial.println("0x3D - OLED SSD1306 (I2C)");
  Serial.println("\n⚠️  SPI devices (NOT detected by I2C scanner):");
  Serial.println("   • Displays 80x160, 240x240, 320x240 (ST7735, ILI9341)");
  Serial.println("   • Displays with CS, DC, RES, BLK pins");
  Serial.println("   • Require Adafruit_GFX, Adafruit_ST7735 libraries, etc.");
  
  Serial.println("\n🔄 Перезапустите для повторного сканирования");
}

void loop() {
  // Nothing to do in loop / Ничего не делаем в loop
  delay(1000);
}
