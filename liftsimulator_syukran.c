//===========================================================================================
//          Universiti Teknologi Petronas | EDB2063 Microprocessor | January 2018
//===========================================================================================
//	Group Name		: B3 
//     -Main Programmmer (Leader): Syukran Soleh
//     -Hardware  : Loo Lok Huen +  Muhammad Arif 
//     
//	Project				: Lift Simulation
//===========================================================================================

#include <18f452.h>

//============================================================================================
//	Configuration/Variable
//============================================================================================
#use delay (clock=4000000)
#fuses HS,NOWDT

int initialize_1,count_up,count_down,p,k,j,i=0;

int seg1_code[3] = {0x06,               //1
                    0x5B,               //2
                    0x4F};              //3

int testRoutine[10] = {0x06,            //1
                       0x5B,            //2
                       0x4F,            //3
                       0x66,            //4
                       0x6D,            //5
                       0x7D,            //6
                       0x07,            //7
                       0x7F,            //8
                       0x6F,            //9
                       0x3F};           //0

int data[1],data_2[1];
int status = 0;
int oldfloor = 0;
int newfloor = 0;
//============================================================================================
//	Declaration of function
//============================================================================================
void lift_up (void);                                                    //motor up 
void lift_down (void);                                                  //motor down
void lift_stop (void);                                                  //motor off
void door_close(void);                                                  //door close (  |  )
void door_open(void;                                                    //door open  (|   |)
void led1(void);                                                        //LED blue 1 ON
void led2(void);                                                        //LED blue 2 ON
void led3(void);                                                        //LED blue 3 ON
void led_low(void);                                                     //LED blue 123 OFF
void upAnime(void);                                                     //Going up animation
void downAnime(void);                                                   //Going down animation
void keepdooropen(void);


//============================================================================================
//	main function of the program
//============================================================================================

void main(){

  for(p=0;p<=9; p++){                                                   //testRoutine
   output_d(testRoutine[p]);                                            //7segment at PORTD
   output_c(testRoutine[p]);                                            //7segment at PORTC
   output_b(testRoutine[p]);                                            //7segment at PORTB
   delay_ms(500);
  }
  led1();                                                               //LED 1 light up
  delay_ms(500);
  led2();                                                               //LED 2 light up
  delay_ms(500);
  led3();                                                               //LED 3 light up
  delay_ms(500); 
  led_low();
  output_c(0);
  output_d(0);
  output_b(0);
  

  
  
while(1){
   initialize_1 = 0;
 
       
   while(TRUE){                                                     //Select floor level
      door_open();
		delay_ms(3000);
		keepdooropen();
		door_close();
		oldfloor = newfloor;
		while(input(PIN_A1)){
      if(!input(PIN_A0)){
          i++;
          delay_ms(100);
         if (i==3) { i=0;}
       }
			if (!input(PIN_A2)){   //if user wanted the door to opehn
				keepdooropen();
				delay_ms(500);
				door_close();}
       output_b(seg1_code[i]);                                      //7segment at PORTD
      delay_ms(200);
      
      j=i;
      k=i;
		newfloor = i;
		}

// assign floor
	
   
    
      if(newfloor > oldfloor){                                        //Confirm and going up
      
       if (initialize_1 ==0 ){                                      //For first going up only
         door_close();                                              //Display door is closed
	     lift_up();                                                 //DC motor rotate
         
         for (count_up=status;count_up<=j;count_up++){
			output_d(seg1_code[count_up]);
            delay_ms(1000);
            output_d(0x00);
            delay_ms(1000);
			upAnime();
            
         }
         status = j;
         output_d(seg1_code[j]);
         lift_stop();
         door_open();
         led_low();
         if ( j == 0 ){ led1();}
         if ( j == 1 ){ led2();}
         if ( j == 2 ){ led3();}
         data[0] = j;
		oldfloor = newfloor;
         break;
      }
      
       else if ( initialize_1 == 1 ) {                              //For the next going up 
        
          data_2[0] = k;
          door_close();
         lift_up();

      for (count_up=status;count_up<=k;count_up++){
			output_d(seg1_code[count_up]);
            delay_ms(1000);
            output_d(0x00);
            delay_ms(1000);
			upAnime();
            
         }
         status = j;
         output_d(0);
         delay_ms(1000);
         output_d(seg1_code[data_2[0]]);
         output_d(0);

         output_d(seg1_code[k]);
         lift_stop();
         door_open();
         led_low();
         if ( k == 0 ){ led1();}
         if ( k == 1 ){ led2();}
         if ( k == 2 ){ led3();}
         data[0] = j;
		oldfloor = newfloor;
         break;
         } 
      }

         if(newfloor < oldfloor){                                     //Confirm and going down
        
         door_close();
         lift_down();      
         
         output_d(0x00);

         for (count_down=status;count_down>=j;count_down-- ){
			output_d(seg1_code[count_down]);
            delay_ms(1000);
            output_d(0x00);
            delay_ms(1000);
			downAnime();
            if (count_down == j){ break;}
            
         }
         status = j;
         output_d(seg1_code[k]);
         lift_stop();
         door_open();
         data_2[0] = k;
         led_low();
         if ( k == 0 ){ led1();}
         if ( k == 1 ){ led2();}
         if ( k == 2 ){ led3();}
         initialize_1 = 1;
		oldfloor = newfloor;
          break;
      }
   }
}
}

//============================================================================================
//	List of function 
//============================================================================================

void lift_up (void){
   output_high(PIN_C6);
   output_low(PIN_C7);
}   

void lift_down (void){
   output_high(PIN_C7);
   output_low(PIN_C6);
}   

void lift_stop (void){
   output_low(PIN_C6);
   output_low(PIN_C7);
}


void door_close(void){
   output_C(0);
   output_high(PIN_C1);
}

void door_open(void){
   output_C(0);
   output_high(PIN_C0);
}      

void led1 (void){
 output_high(PIN_E0);
}
 
void led2 (void) {
 output_high(PIN_E0);
 output_high(PIN_E1);
}
 
void led3 (void){
 output_high(PIN_E0);
 output_high(PIN_E1);
 output_high(PIN_E2);
}
 
void led_low(void){
 output_low(PIN_E0);
 output_low(PIN_E1);
 output_low(PIN_E2);
}

void upAnime(void){
 output_d(0);
 output_high(PIN_D3);
 delay_ms(500);
 output_low(PIN_D3);

 output_high(PIN_D2);
 output_high(PIN_D4);
 delay_ms(500);
 output_low(PIN_D2);
 output_low(PIN_D4);

 output_high(PIN_D6);
 delay_ms(500);
 output_low(PIN_D6);

 output_high(PIN_D1);
 output_high(PIN_D5);
 delay_ms(500);
 output_low(PIN_D1);
 output_low(PIN_D5);

 output_high(PIN_D0);
 delay_ms(500);
 output_low(PIN_D0);
}

void downAnime(void){
 output_d(0);
 
 output_high(PIN_D0);
 delay_ms(500);
 output_low(PIN_D0);

 output_high(PIN_D1);
 output_high(PIN_D5);
 delay_ms(500);
 output_low(PIN_D1);
 output_low(PIN_D5);

 output_high(PIN_D6);
 delay_ms(500);
 output_low(PIN_D6);

 output_high(PIN_D2);
 output_high(PIN_D4);
 delay_ms(500);
 output_low(PIN_D2);
 output_low(PIN_D4);

 output_high(PIN_D3);
 delay_ms(500);
 output_low(PIN_D3);
 
 

}

void keepdooropen(void)
{
	while(!input(PIN_A2))
	{
		delay_ms(1000);
		door_open();
		delay_ms(1000);
	}
}