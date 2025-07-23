#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
dht DHT;
DS3231  rtc(SDA, SCL);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const int Rele1Uv = 2;
const int Rele2Aquecedor = 3;
const int Rele3BombaInterna  = 4;
const int Rele4BombaExterna = 5;
const int NivelBaixo = 6;
const int NivelAlto  = 7;
uint32_t timer = 0;
int control = 0;
Time dataehora;
int hora;
int minuto;
bool encher, esvaziar = false;
int Alto; 
int Baixo;
bool a_cheio, a_vazio;

long tempext;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  lcd.begin(20, 4);
  pinMode(8, OUTPUT);
  pinMode(Rele1Uv, OUTPUT);
  pinMode(Rele2Aquecedor, OUTPUT);
  pinMode(Rele3BombaInterna, OUTPUT);
  pinMode(Rele4BombaExterna, OUTPUT);
  pinMode(NivelAlto, INPUT);
  pinMode(NivelBaixo, INPUT);
  digitalWrite(Rele1Uv, HIGH);//inicia desacionado o rele
  digitalWrite(Rele2Aquecedor, HIGH);//inicia desacionado o rele
  digitalWrite(Rele3BombaInterna, HIGH); //inicia desacionado o rele
  digitalWrite(Rele4BombaExterna, HIGH);//inicia desacionado o rele
//rtc.setDOW(WEDNESDAY);     // Altere o dia da semana SUNDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY e SATURDAY
//rtc.setTime(17, 32, 0);     // Altere o tempo (formato de 24horas)
//rtc.setDate(03, 8, 2021);   // Dia, mês, Ano

}

void loop() {
  dataehora = rtc.getTime();
  lcd.setCursor(0, 0);
  lcd.print("HORA ");
  lcd.setCursor(5, 0);
  lcd.print(rtc.getTimeStr());
  hora = dataehora.hour;
  minuto = dataehora.min;
  Baixo = digitalRead(NivelBaixo);
  Alto = digitalRead(NivelAlto);
  Troca();
  
  
  lcd.setCursor(0, 1);
  lcd.print("Temp.Externa: ");
  lcd.print(tempext);
  
  

  switch (control)    {
    case 0: {
        lcd.setCursor(0, 2);
        lcd.print(rtc.getDateStr());
        lcd.setCursor(10,2);
        lcd.print (" - ");
        temporizador(1);
        break;
      }
    case 1: {
        lcd.setCursor(13, 2);
        lcd.print(rtc.getDOWStr());
        temporizador(2);
        break;
      }
    case 2: {
        tempext == lcd.print(rtc.getTemp());
        temporizador(3);
        break;
      }
      
      case 3:{
             lcd.setCursor(0,3);
             lcd.print("Temp.Interna:");
             DHT.read11(A0);
             lcd.print(DHT.temperature);
             lcd.print(" C ");
             temporizador(4);
             break; 
      }
       case 4: {
            lcd.setCursor(0,4);     
                                    
            if (DHT.temperature  < 28) { //se no instante que hora atual for igual a hora da variavel
              digitalWrite(Rele2Aquecedor, LOW);//aciona rele
              lcd.print("Aquecedor ON!       ");
            } else {  //senao
              digitalWrite(Rele2Aquecedor, HIGH); //desaciona o rele
              lcd.print("Aquecedor OFF!      ");
            }  
            
            temporizador(5);
            break; 
       }
       case 5:{
          lcd.setCursor (13,0);
          
        if (hora == 21 ){
          digitalWrite(Rele1Uv, LOW);
          lcd.print(" UV:ON");
        }else{
               digitalWrite(Rele1Uv, HIGH);
               lcd.print(" UV:OFF");         
          }
          lcd.setCursor(0, 1);
          lcd.print("Temp.Externa: ");
          lcd.print(tempext);
          temporizador(6);
          break; 
        }
        case 6:{
          lcd.setCursor(0,3);
          lcd.print("Nivel:");
          lcd.print(Alto);
          lcd.print(Baixo);
          if(Alto == 0 && Baixo == 0) {
            lcd.setCursor(6,3);
            lcd.print("Vazio        ");
            a_vazio = true;
            a_cheio = false;
          }else if (Alto == 0 && Baixo == 1){
            lcd.setCursor(6,3);
            lcd.print("Medio       ");
          }else {
            lcd.setCursor(6,3);
            lcd.print("Cheio        ");   
            a_cheio = true;
            a_vazio = false;      
          }

          temporizador(0);
          break;
      
        }
               
       }
  }
void temporizador(int x) {
  if (millis() - timer >= 1500) {
    control = x;
    timer = millis(); // Atualiza a referência
  }
}

void Troca()
  {
    if (rtc.getDOWStr() == "Sabado" && hora ==  22)
      {        
        if (minuto == 35)
        {
          if (a_cheio == true){
            esvaziar = true;             
          }
        } 
      }
      
  if (esvaziar == true)
    {
      digitalWrite(Rele3BombaInterna, LOW);
      if (a_vazio == true){
        encher = true;
        esvaziar = false;        
      }
    }
    else
    {
      digitalWrite(Rele3BombaInterna, HIGH);
    }

  if (encher == true){
     digitalWrite(Rele4BombaExterna, HIGH);
     if (a_cheio == true){
      encher = false;
     }else{
      digitalWrite(Rele4BombaExterna, LOW);
     }
  }
}
 
