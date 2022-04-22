void go_right() {

   PORTD|=(1<<DDD7);
   
  PORTD|=(1<<DDD6);
  
   PORTB&=~(1<<DDB1);
   
  PORTB&=~(1<<DDB0);
 
}
