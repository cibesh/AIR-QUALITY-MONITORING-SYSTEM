#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
const int gas1 = A0;
const int gas2 = A1;
const int buzzer = 4;

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd_string("    WELCOME      ","__________________");
  delay(1000);
  pinMode(gas1,INPUT);
  pinMode(gas2,INPUT);
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW);
  Serial.begin(9600);
  delay(100);
}
int gas1_flag = 0, gas2_flag = 0;
int wait_ms = 0;
void loop()
{
  int read_gas1 = analogRead(gas1);
  int read_gas2 = analogRead(gas2);

  int read_gas1_ppm = map(read_gas1,0,300,100,700);
  int read_gas2_ppm = map(read_gas2,0,300,100,700);

  lcd.clear();
  lcd.print("C02: ");
  lcd.print(read_gas2_ppm);
  lcd.print(" PPM");
  lcd.setCursor(0,1);
  lcd.print("A.QTY: ");
  lcd.print(read_gas1_ppm);
  lcd.print(" PPM");
  delay(200);
  wait_ms++;

  if(read_gas1_ppm > 400 && gas1_flag == 0)
  {
    digitalWrite(buzzer,HIGH);
    delay(3000);
    digitalWrite(buzzer,LOW);
    gas1_flag = 1;
  }
  if(read_gas1_ppm < 400 && gas1_flag == 1)gas1_flag = 0;

  if(read_gas2_ppm > 400 && gas2_flag == 0)
  {
    digitalWrite(buzzer,HIGH);
    delay(3000);
    digitalWrite(buzzer,LOW);
    gas2_flag = 1;
  }
  if(read_gas2_ppm < 400 && gas2_flag == 1)gas2_flag = 0;

  if( wait_ms >= 20)
  {
    Serial.print(read_gas2_ppm);
    Serial.print(",");
    Serial.print(read_gas1_ppm);
    Serial.println(",");
    delay(100);
    wait_ms = 0;

  }
 

}
void lcd_string(String word1,String word2)
{
  lcd.clear();
  lcd.print(word1);
  lcd.setCursor(0,1);
  lcd.print(word2);
}