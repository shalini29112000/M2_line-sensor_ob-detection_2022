void go_forward() {

  PORTD|=(1<<DDD7);  //F1
  
  PORTD|=(1<<DDD6);   //B1
  
  PORTB|=(1<<DDB1);   //B2
  
  PORTB|=(1<<DDB0);   //F2

  
}
