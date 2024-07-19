#include <PID_v1.h>


#define skrajny_lewo 15
#define lewo 26
#define prosto 27
#define prawo 28
#define skrajny_prawo 29
#define silnik_prawy_k 0
#define silnik_prawy_v 1
#define silnik_lewy_k 2
#define silnik_lewy_v 3

int max_speed=120
int prug=750 //czy wykryto tasme 
double Kp=2 , Ki=0 , Kd=0 // wartosci do regulacji PID-u 
//regulować w kolejności Kp,Ki,Kd. Ki i Kd najpierew na 0 czyli wylaczne 


double Setpoint, Output, Input, v_prawy, v_lewy;
PID robotPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT)

void setup() {
  //set pinów
pinMode(skrajny_lewo,INPUT);
pinMode(lewo,INPUT);
pinMode(prosto,INPUT);
pinMode(prawo, INPUT );
pinMode(skrajny_prawo, INPUT );
pinMode(silnik_p_k,OUTPUT);
pinMode(silnik_p_v,OUTPUT);
pinMode(silnik_l_k,OUTPUT);
pinMode(silnik_l_v,OUTPUT);
// 
Input=128 // !!! tasma na start musi być pod diodą prosto jak nie bedzie dzialac to skopiowac kod od zczytywania inputa z loopa
Setpoint=128
robotPID.SetMode(AUTOMATIC);
}

void loop() {
  //zczytanie wejscia ustalenie Inputa
if (analogRead(prosto)>=prug){
  Input=128;
}else
if (analogRead(lewo)>=prug){
  Input=64;
}else
if (analogRead(prawo)>=prug){
  Input=192;
}else
if (analogRead(skrajny_lewo)>=prug){
  Input=0;
}else 
if (analogRead(skrajny_prawo)>=prug){
  Input=255;
} 

  //PID
//robotPID.SetSampleTime(SampleTime) domyślne PID liczy co 200mS czyli 5 razy na sekunde ale mozna to zmienic.
robotPID.Compute();


}
  //wyslanie sygnalu do silnikow TODO 
digitalWrite(silnik_p_k,LOW); // na razie kola beda sie krecic tylko do przodu
digitalWrite(silnik_l_k,LOW);
if (Output==0){
analogWrite(silnik_p_v,max_speed);
analogWrite(silnik_l_v,max_speed);
}else
if(Output>0){
v_prawy=max_speed*(Output/255);
analogWrite(silnik_p_v,v_prawy);
analogWrite(silnik_l_v,max_speed);
}else
if(Output<0){
v_lewy=max_speed*(Output/255);
analogWrite(silnik_p_v,max_speed);
analogWrite(silnik_l_v,v_lewy);
}