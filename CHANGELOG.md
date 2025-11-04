# История изменений / Changelog

Все значимые изменения в этом проекте будут документироваться в этом файле.

All notable changes to this project will be documented in this file.

Формат основан на [Keep a Changelog](https://keepachangelog.com/ru/1.0.0/),
и этот проект придерживается [Semantic Versioning](https://semver.org/lang/ru/).

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/).

## [1.0.0] - 2024-01-XX

### Добавлено / Added
- Первый релиз I2C Scanner для ESP32-C3 / First release of I2C Scanner for ESP32-C3
- Полное сканирование всех I2C адресов (0x01-0x7F) / Full scan of all I2C addresses (0x01-0x7F)
- Автоматическое определение типов устройств / Automatic device type identification
- Поддержка устройств в спящем режиме (MPU-6050) / Support for devices in sleep mode (MPU-6050)
- Визуальная индикация прогресса через LED / Visual progress indication via LED
- Расширенная диагностика устройств через WHO_AM_I регистры / Extended device diagnostics via WHO_AM_I registers
- Подробная статистика сканирования / Detailed scan statistics
- Поддержка следующих устройств / Support for the following devices:
  - MPU-6050 (гироскоп и акселерометр) / MPU-6050 (gyroscope and accelerometer)
  - LIS3DSH (трехосевой акселерометр) / LIS3DSH (3-axis accelerometer)
  - DS1307 (модуль часов реального времени) / DS1307 (real-time clock module)
  - EEPROM 24C32 (энергонезависимая память) / EEPROM 24C32 (non-volatile memory)
  - BMP280 (датчик давления и температуры) / BMP280 (pressure and temperature sensor)
  - OLED SSD1306 (OLED дисплей) / OLED SSD1306 (OLED display)
- Двуязычная документация (русский/английский) / Bilingual documentation (Russian/English)
- Двуязычные комментарии в коде / Bilingual code comments
- README с полной документацией / README with full documentation
- CHANGELOG для отслеживания изменений / CHANGELOG for tracking changes
- LICENSE файл (MIT License) / LICENSE file (MIT License)
- .gitignore для Arduino проектов / .gitignore for Arduino projects

### Технические детали / Technical Details
- Используется стандартная библиотека Wire для I2C / Uses standard Wire library for I2C
- Настраиваемые пины SDA/SCL (по умолчанию GPIO4/GPIO5) / Configurable SDA/SCL pins (default GPIO4/GPIO5)
- Скорость I2C: 100 кГц (по умолчанию) / I2C speed: 100 kHz (default)
- Поддержка альтернативных пинов GPIO8/GPIO9 / Support for alternative pins GPIO8/GPIO9

---

## Формат версий / Version Format

Проект использует семантическое версионирование (Semantic Versioning): MAJOR.MINOR.PATCH

The project uses semantic versioning: MAJOR.MINOR.PATCH

- **MAJOR** - несовместимые изменения API / incompatible API changes
- **MINOR** - новая функциональность с обратной совместимостью / new functionality with backward compatibility
- **PATCH** - исправления ошибок с обратной совместимостью / bug fixes with backward compatibility

---

[1.0.0]: https://github.com/Razvlekal0vka/I2C-Scanner/releases/tag/v1.0.0

