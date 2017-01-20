/**
 * @author Antonio Paya
 */
void setup() {
  pinMode(3,OUTPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
}

void loop() {
  if(digitalRead(4) == HIGH && digitalRead(5) == LOW){
      digitalWrite(13,HIGH);
      analogWrite(3,HIGH);
  }else{
      digitalWrite(13,LOW);
      analogWrite(3,LOW);  
  }
}
