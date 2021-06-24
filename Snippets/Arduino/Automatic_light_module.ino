//Използвани библиотеки
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit GFX.h>
#include <Adafruit SSD1306.h>

//Дефиниция на дисплеят
#define OLED RESET 4
Adafruit SSD1306 display (OLED RESET);
#if (SSD1306 LCDHEIGHT != 64)
#error(“Height incorrect, please fix Adafruit_SSD1306.h!”);
#endif

//Дефиниция на сензора за осветеност
BH1750 lightMeter; 

//setup функцията се извиква веднъж преди започването на основния цикъл
void setup()
{
    //Започва връзка с порт 9600
    Serial.begin(9600);

    //Инициализация на програмата
    Display.begin(SSD1306_SWITCHCAPVCC, Ox3c);
    Display.clearDisplay();
    Wire.begin();
    lightMeter.begin();

    //Задаване на настройките на дисплея
    Display.setTextSize(2);
    Display.setTextColor (WHITE);
    Display.setCursor(0, 0);
    Display.println(“BH1750”);
    Display.display();

    //Комуникация с конзолата
    Serial.println (F(“BH1750 Test begin”));

    //Включването на портовете на светодиода
    pinMode(9, OUTPUT); //червено
    pinMode(10, OUTPUT); //зелено
    pinMode(11, OUTPUT); //синьо
}

//Основният цикъл на програмата
void loop()
{
    //Стойността на осветеността
    unsigned int light = lightMeter.readLightLevel();

    //Извеждане на стойността на осветеност на дисплея
    Display.clearDisplay();
    Display.setCursor(0, 0);
    Display.println(“Light:”);
    Display.print(light);
    Display.print(“ 18”);
    Display.setCursor(0, 48);

    //Проверява дали е тъмно или светло
    if(light < 40)
    {
        digitalWrite(9, HIGH);
        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        //Включва лампата при стойност по-малка от 40 lx
        display.println(“Status:ON”);
    }
    else
    {
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        //Изключва при стойност равна или по-голяма от 40 lx
        display.println(“Status: OFF”);
    }

    //Обновява дисплея с новата информация
    Display.display();
    //Забавя цикъла с една секунда
    Delay(1000);
}
