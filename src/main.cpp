#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definir el pin donde está conectado el DHT
#define DHTPIN 14 // GPIO 14

// Seleccionar el tipo de sensor DHT11 o DHT22
#define DHTTYPE DHT22   // DHT 22 (AM2302), para DHT11 usa DHT11

DHT dht(DHTPIN, DHTTYPE);

// Configuración de la pantalla OLED
#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED
#define SCREEN_HEIGHT 64 // Altura de la pantalla OLED

// Dirección I2C de la pantalla OLED puede variar, comúnmente 0x3C
#define OLED_RESET 23 // GPIO 16
#define SCREEN_ADDRESS 0x3C 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  dht.begin();


  // Inicializar la comunicación I2C
  Wire.begin(21, 22); // SDA: GPIO 21, SCL: GPIO 22

  // Inicializar la pantalla OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // No seguir si la pantalla falla
  }
  display.display();
  delay(2000); // Esperar para que la pantalla se estabilice
  display.clearDisplay();
}

void loop() {
  // Esperar unos segundos entre lecturas
  delay(2000);

  // Leer la humedad
  float h = dht.readHumidity();
  // Leer la temperatura en Celsius (por defecto)
  float t = dht.readTemperature();

  // Chequear si alguna lectura falla y salir temprano para intentar de nuevo.
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  // Mostrar las lecturas en el monitor serie
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  
  // Limpiar la pantalla
  display.clearDisplay();

  // Configurar el texto para la pantalla
  display.setTextSize(1);      // Tamaño del texto
  display.setTextColor(SSD1306_WHITE); // Color del texto

  // Mostrar la humedad
  display.setCursor(0, 35);
  display.print(F("Humedad: "));
  display.print(h);
  display.print(F("%"));

  // Mostrar la temperatura
  display.setCursor(0, 45);
  display.print(F("Temp: "));
  display.print(t);
  display.print(F("°C"));

  // Enviar el buffer a la pantalla
  display.display();
}
