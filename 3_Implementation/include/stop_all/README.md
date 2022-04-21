void stop_all() {

  PORTD&=~(1<<DDD7);
  
   PORTD&=~(1<<DDD6);
   
   PORTB&=~(1<<DDD1);
   
   PORTB&=~(1<<DDD0);
    
}
