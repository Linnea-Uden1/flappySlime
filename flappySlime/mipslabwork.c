/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
#include <stdbool.h>


#define timeP ((80000000 / 256) / 100) // 100 ms
int mytime = 0x5957;
int prime = 1234567;

volatile int *trisE = (volatile int *)0xbf886100;
volatile int* portE = (volatile int*) 0xbf886110;


char textstring[] = "text, more text, and even more text!";
int timeoutcount = 0;
int count = 0;
int offset = 28;
int current_x = 110;
int current_x2 = 105;
int current_y = 122;
int current_y2 = 127;
int count2 = 0;
int i;
bool alive = false;
int flappy_direction = 5; //1 = neråt , -1 = uppåt , beroende på om man håller in knappen så ska detta ändra, om värdet är större accelererar den. 
bool press = false; 
int gameState = 0; 
bool firstTime = true; 
bool move = true;
int slimeindex; 
bool start = true;
/* Interrupt Service Routine */
void user_isr(void)
{
  // if (IFS(0) & 0x80000)//Check if interrupt is caused by switch 4
  // {
  //   IFS(0) = (IFS(0) & 0xff7fffff);
  //   count++;
  //   *portE = (*portE & 0xffffff00) | count;
  // }

  if (IFS(0) & 0x100)
  {
    IFSCLR(0) = IFS(0) & 0xffff7fff;
    timeoutcount++;
    
    if(timeoutcount == 10){
      timeoutcount = 0;
      

      if (gameState == 0)//Meny
      {
        
        display_clear();
        draw_icon(titleslime_row, titleslime_col,178);
        draw_icon(mainstart_row,mainstart_col,59);
        
        if(firstTime){
          move_icon(flappyrow,flappycol,flappyrow_border,flappycol_border,16,12,1,0);
          firstTime = false;
        }
        draw_icon(flappyrow,flappycol,16);
        if (getbtns() == 4 && start)
        {
          gameState = 1; 
           firstTime = true;
        }
        
      }

      if (gameState == 1) //Starta spelet 
      {
        
        display_clear();
        draw_icon(flappyrow, flappycol, 16);
        draw_border(0);
        draw_border(31);
        

        if (firstTime)
        {
          display_clear();
          draw_border(0);
          draw_border(31);
          draw_icon(flappyrow, flappycol, 16);
          delay(5000);
          firstTime = false;
          flappy_direction = -1;
        }
        if (getbtns() == 4 && !firstTime)
        {
          flappy_direction = 2; 
          display_clear();
          draw_border(0);
          draw_border(31);
          draw_icon(flappyrow, flappycol, 16);
          alive = true;
          slimeindex -= 2; 
        }
        else{
          display_clear();
           draw_border(0);
          draw_border(31);
          draw_icon(flappyrow, flappycol, 16);
          flappy_direction = -1;  
          slimeindex ++; 
        }
        move_icon(flappyrow, flappycol, flappyrow_border, flappycol_border,16,12,-flappy_direction,0);
        if (alive)
          {
              count2++;
              draw_icon(pipe1_row,pipe1_col,28);
              draw_icon(pipe2_row,pipe2_col,22);
              draw_icon(pipe3_row,pipe3_col,18);
              draw_icon(pipe4_row,pipe4_col,26);
              draw_icon(pipe5_row,pipe5_col,38);  
              // draw_icon(pipe6_row,pipe6_col,48);
              draw_icon(pipe7_row,pipe7_col,14);
              draw_icon(pipe8_row,pipe8_col,46);
              draw_icon(pipe9_row,pipe9_col,10);

              move_titlescrean(pipe1_row,pipe1_col,28, 0,-1);
              move_titlescrean(pipe2_row,pipe2_col,22, 0,-1);
              move_titlescrean(pipe3_row,pipe3_col,18, 0,-1);
              move_titlescrean(pipe4_row,pipe4_col,26, 0,-1);
              move_titlescrean(pipe5_row,pipe5_col,38, 0,-1);
              move_titlescrean(pipe6_row,pipe6_col,48, 0,-1);
              move_titlescrean(pipe7_row,pipe7_col,14, 0,-1);
              move_titlescrean(pipe8_row,pipe8_col,46, 0,-1);
              move_titlescrean(pipe9_row,pipe9_col,10, 0,-1); 
              if (count2 > 120 &&count2 < 278)
              {
              }
              else if(count2 == 128){
                // display_clear();
                move_titlescrean(pipe1_row,pipe1_col,28, 0,180);
              }else if(count2 == 158) {
                move_titlescrean(pipe2_row,pipe2_col,22, 0,180);
                move_titlescrean(pipe3_row,pipe3_col,18, 0,180);
              }else if(count2 == 188){
                move_titlescrean(pipe5_row,pipe5_col,38, 0,180);
                move_titlescrean(pipe5_row,pipe5_col,38, 0,180);
                // move_titlescrean(pipe6_row,pipe6_col,48, 0,180);
              }else if(count2 == 218){
                move_titlescrean(pipe4_row,pipe4_col,26, 0,180);
                move_titlescrean(pipe7_row,pipe7_col,14, 0,180);

              }
              else if(count2 == 248){
                move_titlescrean(pipe8_row,pipe8_col,46, 0,180);
                count2 = 98;

              }            
          }
           
          if (check_collision() 
              || check_collisionpipes(pipe1_row, pipe1_col, 28) 
              || check_collisionpipes(pipe2_row, pipe2_col, 22)
              || check_collisionpipes(pipe3_row, pipe3_col, 18)
              || check_collisionpipes(pipe4_row, pipe4_col, 26) 
              || check_collisionpipes(pipe5_row, pipe5_col, 38) 
              // || check_collisionpipes(pipe6_row, pipe6_col, 48)
              || check_collisionpipes(pipe7_row, pipe7_col, 14)
              || check_collisionpipes(pipe8_row, pipe8_col, 46)
              || check_collisionpipes(pipe9_row, pipe9_col, 10) )
          {
            display_clear();
              move_titlescrean(pipe1_row,pipe1_col,28, 0,count2);
              move_titlescrean(pipe2_row,pipe2_col,22, 0,count2);
              move_titlescrean(pipe3_row,pipe3_col,18, 0,count2);
              move_titlescrean(pipe4_row,pipe4_col,26, 0,count2);
              move_titlescrean(pipe5_row,pipe5_col,38, 0,count2);
              move_titlescrean(pipe6_row,pipe6_col,48, 0,count2);
              move_titlescrean(pipe7_row,pipe7_col,14, 0,count2);
              move_titlescrean(pipe8_row,pipe8_col,46, 0,count2);
              move_titlescrean(pipe9_row,pipe9_col,10, 0,count2); 
              alive = false; 
              count2 = 0;
              display_clear();
              gameState = 3; 
            
          }
            

        }      

        
      }
      
      if (gameState == 3) //GameOver 
      {
       
        // draw_icon(main_row,main_col,42);
        if(move){
          display_clear();
          move_titlescrean(gameover_row, gameover_col, 235, -5, 0);
          move_titlescrean(restart_row,restart_col,103,-3,-2);
          move_titlescrean(flappyrow2,flappycol2,16,-1,-4);

          move = false;
        }
        draw_icon(gameover_row, gameover_col,235);
        draw_icon(restart_row, restart_col,103);        
        // draw_icon(main_row,main_col,42);
        draw_icon(flappyrow2,flappycol2,16);



        if(getbtns() == 2){  
           
            display_clear();
            move_icon(flappyrow, flappycol, flappyrow_border, flappycol_border,16,12,-slimeindex,0); 
            firstTime = true;
            slimeindex = 0;
            gameState = 1;
            display_clear(); 
          } 
      }      
   }      
}

/* Lab-specific initialization goes here */
void labinit(void)
{
  //Switch 4 interrupt
  *trisE = 0x00 & *trisE;//Sets portE to output, LED lights
  TRISDSET = 0x800; //Sets switch 4 to input
  IPC(4) = 0x7 << 2 | 0x3; //Prioritet
  IEC(0) = (IEC(0) | 0x80000); //Enable switch 4 interrupt


  //Timer2
  TMR2 = 0;          // Initalize timer 2
  T2CONSET = 0x0070; // Set to prescale 1:256
  PR2 = timeP;
  T2CONSET = 0x8000;

  IPCSET(2) = 6;
  IECSET(0) = 0x100;

  enable_interrupt();

  move_titlescrean(pipe1_row,pipe1_col,28, 0,0);
  move_titlescrean(pipe2_row,pipe2_col,22, 0,30);
  move_titlescrean(pipe3_row,pipe3_col,18, 0,30);
  move_titlescrean(pipe5_row,pipe5_col,38, 0,60);  
  move_titlescrean(pipe9_row,pipe9_col,10, 0,60);  
  // move_titlescrean(pipe6_row,pipe6_col,48, 0,60);
  move_titlescrean(pipe4_row,pipe4_col,26, 0,90);
  move_titlescrean(pipe7_row,pipe7_col,14, 0,90);
  move_titlescrean(pipe8_row,pipe8_col,46, 0,120);



  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  prime = nextprime(prime);

}
