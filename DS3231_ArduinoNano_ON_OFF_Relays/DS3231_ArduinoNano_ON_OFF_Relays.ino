#include <DS3231.h>//Memanggil RTC3231 Library
#include <Wire.h>  // i2C Conection Library
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
// Init DS3231
DS3231  rtc(SDA, SCL);
Time  t;
// Init lcd1602_i2c
LiquidCrystal_I2C lcd(0x27,16,2);

int btn_menu = 7; int menu_val;
int btn_up = 6; int up_val;
int btn_down = 5; int down_val;
int default_val = 1;  
int relay1 = 9; int relay2 = 10;

int pointer_val = 0; int column_pointer = 5; int row = 0;
int options_var = 0; int menucontrol_var = 0;
int sumcounters =0;

//SETUP DATE,MONTH,YEAR
int day = 9; int month = 12; int yearng = 2; int yeartr = 0; int yearch = 2; int yeardv = 2; int year_sum = 0; 
//SETUP hour
int hour = 0 ; int minute = 0; int second = 0;

int ton1 = 0; int pon1 = 0; int tof1 = 0; int pof1 = 0; //ACTION 1
int ton2 = 0; int pon2 = 0; int tof2 = 0; int pof2 = 0; //ACTION 2
int ton3 = 0; int pon3 = 0; int tof3 = 0; int pof3 = 0; //ACTION 3
int re1 = 1; int re2 = 1; int re3 = 1;

void main_screen(){
  lcd.setCursor(0,0);
  lcd.print("DATE: ");
  lcd.setCursor(0,1);
  lcd.print("TIME: ");
  lcd.setCursor(6,0);
  lcd.print(rtc.getDateStr());
  lcd.setCursor(6,1);
  lcd.print(rtc.getTimeStr());  
}

void menu_options(){
  if(options_var == 0){
    lcd.clear();
    lcd.print(">BACK");
    lcd.setCursor(0, 1);
    lcd.print(" DATE");
  }
  else if (options_var == 1)
  {
    lcd.clear();
    lcd.print(" BACK");
    lcd.setCursor(0, 1);
    lcd.print(">DATE");    
  }
  else if (options_var == 2)
  {
    lcd.clear();
    lcd.print(">TIME");
    lcd.setCursor(0, 1);
    lcd.print(" CONTROL ");   
  }
  else if (options_var == 3)
  {
    lcd.clear();
    lcd.print(" TIME ");
    lcd.setCursor(0, 1);
    lcd.print(">CONTROL");    
  }
}

void choose_options(){
    switch (options_var){
        case 0:
            //BACK
            break;
        case 1:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("SETUP DATE");
            lcd.setCursor(12,1);
            lcd.print("BACK");      
            break;
        case 2:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("SETUP HOUR");
            lcd.setCursor(12,1);
            lcd.print("BACK");       
            break;
        case 3:
            // COMMAND pointer_valL
            break;       
    }
}

void menu_control(){
    if (menucontrol_var == 0){
        lcd.clear();
        lcd.print(">BACK");
        lcd.setCursor(0, 1);
        lcd.print(" ACTION 1");  
    }
    else if (menucontrol_var == 1){
        lcd.clear();
        lcd.print(" BACK");
        lcd.setCursor(0, 1);
        lcd.print(">ACTION 1");    
    }
    else if (menucontrol_var == 2){
        lcd.clear();
        lcd.print(">ACTION 2");
        lcd.setCursor(0, 1);
        lcd.print(" ACTION 3");    
    }
    else if (menucontrol_var == 3){
        lcd.clear();
        lcd.print(" ACTION 2");
        lcd.setCursor(0, 1);
        lcd.print(">ACTION 3");    
    } 
}

void choose_menucontrol(){
    switch (menucontrol_var) {
        case 0:
            //BACK
            break;
        case 1:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("TON: ");
            lcd.setCursor(11,0);
            lcd.print("RE: ");      
            lcd.setCursor(0,1);
            lcd.print("TOF: ");
            lcd.setCursor(12,1);
            lcd.print("BACK");
            break;
        case 2:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("TON: ");
            lcd.setCursor(11,0);
            lcd.print("RE: ");      
            lcd.setCursor(0,1);
            lcd.print("TOF: ");
            lcd.setCursor(12,1);
            lcd.print("BACK");     
            break;
        case 3:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("TON: ");
            lcd.setCursor(11,0);
            lcd.print("RE: ");      
            lcd.setCursor(0,1);
            lcd.print("TOF: ");
            lcd.setCursor(12,1);
            lcd.print("BACK");     
            break;
    }
}

void Showset(int &ton, int &pon, int &tof, int &pof, int &re){
    if (ton < 10){
        lcd.setCursor(5,0); lcd.print("0");
        lcd.setCursor(6,0); lcd.print(ton);
    }else{
        lcd.setCursor(5,0); lcd.print(ton);}
    
    lcd.setCursor(7,0); lcd.print(":");

    if (pon < 10){
        lcd.setCursor(8,0); lcd.print("0"); 
        lcd.setCursor(9,0); lcd.print(pon);
    }else{
        lcd.setCursor(8,0); lcd.print(pon);}    
    
    lcd.setCursor(14,0); lcd.print(re); //relay 

    if (tof < 10){
        lcd.setCursor(5,1); lcd.print("0");
        lcd.setCursor(6,1); lcd.print(tof);
    }else{
        lcd.setCursor(5,1); lcd.print(tof);}
    
    lcd.setCursor(7,1); lcd.print(":");

    if (pof < 10){
        lcd.setCursor(8,1); lcd.print("0"); 
        lcd.setCursor(9,1); lcd.print(pof);
    }else{
    lcd.setCursor(8,1); lcd.print(pof);}    

    lcd.setCursor(column_pointer, row); 
    lcd.cursor();
    delay(50);   
}



void on(int &relay){
    if(relay == 1){
        if (digitalRead(relay1) == LOW)
            digitalWrite(relay1, HIGH);
        else digitalWrite(relay1, HIGH);  }

    else if(relay == 2){
      if (digitalRead(relay2) == LOW)
        digitalWrite(relay2, HIGH);
      else digitalWrite(relay2, HIGH);  }

    else if(relay == 3){
      if (digitalRead(relay1) == LOW)
        digitalWrite(relay1, HIGH);
      else digitalWrite(relay1, HIGH);
      if (digitalRead(relay2) == LOW)
        digitalWrite(relay2, HIGH);
      else digitalWrite(relay2, HIGH); } 
}

void off(int &relay){
    if(relay == 1){
      if (digitalRead(relay1) == HIGH)
        digitalWrite(relay1, LOW);
      else digitalWrite(relay1, LOW); }
    
    else if(relay == 2){
      if (digitalRead(relay2) == HIGH)
        digitalWrite(relay2, LOW);
      else digitalWrite(relay2, LOW); }    
    
    else if(relay == 3){
      if (digitalRead(relay1) == HIGH)
        digitalWrite(relay1, LOW);
      else digitalWrite(relay1, LOW);
      if (digitalRead(relay2) == HIGH)
        digitalWrite(relay2, LOW);
      else digitalWrite(relay2, LOW); }        
}

void Add_Relay(int &relay){
    relay ++;
    if (relay > 3)
        relay = 1;
}

void Min_Relay(int &relay){
    relay --;
    if (relay < 1)
        relay = 3;
}

void Add_Hour(int &ton, int &tof){ //Hour on/off
    if (row == 0){ //GI??? ON 
        ton ++;
        if (ton > 23)
        ton = 0; } 
    else if (row == 1){ //GI??? OFF
        tof ++;
        if (tof > 23)
        tof = 0; }
}

void Add_Min(int &pon, int &pof){ //Minute on/off
    if (row == 0){ //PH??T ON
        pon ++;
        if (pon > 59)
        pon = 0; } 
    else if (row == 1){ //PH??T OFF
        pof ++;
        if (pof > 59)
        pof = 0; }
}

void Min_Hour(int &ton, int &tof){ //Hour on/off
    if (row == 0){ //GI??? ON 
        ton --;
        if (ton < 0)
        ton = 23; } 
    else if (row == 1){ //GI??? OFF
        tof --;
        if (tof < 0)
        tof = 23; }
}

void Min_Min(int &pon, int &pof){ //Minute on/off
    if (row == 0){ //PH??T ON
        pon --;
        if (pon < 0)
        pon = 59; } 
    else if (row == 1){ //PH??T OFF
        pof --;
        if (pof < 0)
        pof = 59; }
}


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    rtc.begin();

    lcd.init();
    lcd.backlight();

    pinMode(btn_up, INPUT_PULLUP);
    pinMode(btn_down, INPUT_PULLUP);
    pinMode(btn_menu, INPUT_PULLUP);
    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  t = rtc.getTime();  

  up_val = digitalRead(btn_up);
  down_val = digitalRead(btn_down);
  menu_val = digitalRead(btn_menu);

//  Up_btn();
     if (up_val != default_val){ //UP_BTN
        if (up_val == 0) // When pressed the button
        {
            if (sumcounters == 1) {   // UP IN MENU_OPTIONS 
                if (options_var >= 3){      
                    options_var = 0;  
                }else{
                    options_var++;  
                }   
                menu_options();
            }
            
            else if (sumcounters == 2) {    //+ Con tr??? Set Date/hour v?? l??n Menu ??i???u khi???n
                if(options_var == 1 or options_var == 2) // + CON TR??? ??? SET DATE v?? hour
                {
                    pointer_val ++;
                    if (pointer_val > 15)
                        pointer_val = 0;
                }
                else if(options_var == 3) //L??n ??? MENU ??I???U KHI???N
                {
                    menucontrol_var ++;
                    if (menucontrol_var > 3)
                        menucontrol_var = 0;
                    menu_control();
                }
            }

            else if (sumcounters == 3) {  
                if(options_var == 1) // - ??? NG??Y, TH??NG, N??M
                {
                    if ((pointer_val == 0 or pointer_val == 1)){ //NG??Y
                        day --;
                        if (day < 1)
                            day = 31;}
                    else if ((pointer_val == 3 or pointer_val == 4)){ //TH??NG
                        month --;
                        if (month < 1)
                            month = 12;}
                    else if (pointer_val == 6){ //N??M NGH??N
                        yearng --;
                        if (yearng < 0)
                            yearng = 9;}
                    else if (pointer_val == 7){ //N??M TR??M
                        yeartr --;
                        if (yeartr < 0)
                            yeartr = 9;}
                    else if (pointer_val == 8){ //N??M CH???C
                        yearch --;
                        if (yearch < 0)
                            yearch = 9;}
                    else if (pointer_val == 9){ //N??M ????N V???
                        yeardv --;
                        if (yeardv < 0)
                            yeardv = 9;}
                }

                else if(options_var == 2) // - ??? GI??? : PH??T : GI??Y
                {
                    if ((pointer_val == 0 or pointer_val == 1)){ //GI???
                        hour --;
                        if (hour < 0)
                            hour = 23;}
                    else if ((pointer_val == 3 or pointer_val == 4)){ //PH??T
                        minute --;
                        if (minute < 0)
                            minute = 59;}
                    else if ((pointer_val == 6 or pointer_val == 7)){ //GI??Y
                        second --;
                        if (second < 0)
                            second = 59;}
                }

                else if(options_var == 3) // + CON TR??? ??? ??I???U KHI???N
                {
                    column_pointer ++;
                    if (row == 0){
                        if (column_pointer > 15) { 
                            column_pointer = 5;
                            row = 1;}
                    } else {
                        if (column_pointer > 15) {
                            column_pointer = 5;
                            row = 0;}       
                    }
                }
            }
            
            else if (sumcounters == 4 && options_var == 3) {// - ??I???U KHI???N | GI??? ON - OFF, RELAY
                if(column_pointer == 5 or column_pointer == 6) //- Gi??? ON/OFF
                {
                    if(menucontrol_var == 1) //Gi??? 1
                        Min_Hour(ton1, tof1);
                    else if(menucontrol_var == 2) //Gi??? 2
                        Min_Hour(ton2, tof2);
                    else if(menucontrol_var == 3) //Gi??? 3
                        Min_Hour(ton3, tof3);                             
                }
                else if(column_pointer == 8 or column_pointer == 9) //- Ph??t ON/OFF
                {
                    if(menucontrol_var == 1) //Ph??t 1
                        Min_Min(pon1, pof1);
                    else if(menucontrol_var == 2) //Ph??t 2
                        Min_Min(pon2, pof2);
                    else if(menucontrol_var == 3) //Ph??t 3
                        Min_Min(pon3, pof3);                          
                }                               

                else if(row == 0 && column_pointer == 14) // - RELAY (ch???n relay on/off)
                {
                    if(menucontrol_var == 1) //L???nh 1
                        Min_Relay(re1);
                    else if (menucontrol_var == 2) //L???nh 2
                        Min_Relay(re2);
                    else if (menucontrol_var == 3) //L???nh 3
                        Min_Relay(re3);                    
                }                         
            }                                         
            delay(200);
        }
        default_val = up_val;
    }     
    
//  Down_btn();
   if (down_val != default_val) {// N??T XU???NG
        if (down_val == 0) {//Khi nh???n n??t xu???ng
            if (sumcounters == 1) {   // XU???NG ??? MENU T???NG
                if (options_var <= 0) { 
                    options_var = 3;  
                } else { 
                    options_var--; }
                menu_options();
            }
            
            else if (sumcounters == 2) {  //- Con tr??? Set Date/hour v?? Xu???ng Menu ??i???u khi???n
                if(options_var == 1 or options_var == 2) {// - CON TR??? ??? SET DATE v?? hour
                    pointer_val --;
                    if (pointer_val < 0)
                    pointer_val = 15;
                }
                else if(options_var == 3) { //Xu???ng ??? MENU ??I???U KHI???N
                    menucontrol_var --;
                    if (menucontrol_var < 0)
                    menucontrol_var = 3;
                    menu_control();
                }
            }

            else if (sumcounters == 3) {
            
                if(options_var == 1)  // + ??? NG??Y, TH??NG, N??M
                {
                    if (pointer_val == 0 or pointer_val == 1){ // + NG??Y ??? DATE
                    day ++;
                    if (day > 31)
                        day = 1;}
                    else if (pointer_val == 3 or pointer_val == 4){ // + TH??NG ??? DATE
                    month ++;
                    if (month > 12)
                        month = 1;}
                    else if (pointer_val == 6){ // + N??M NGH??N
                    yearng ++;
                    if (yearng > 9)
                        yearng = 0;}
                    else if (pointer_val == 7){// + N??M TR??M
                    yeartr ++;
                    if (yeartr > 9)
                        yeartr = 0;}
                    else if (pointer_val == 8){// + N??M CH???C
                    yearch ++;
                    if (yearch > 9)
                        yearch = 0;}
                    else if (pointer_val == 9){// + N??M ????N V???
                    yeardv ++;
                    if (yeardv > 9)
                        yeardv = 0;}
                }

                else if(options_var == 2) //+ ??? GI??? : PH??T :GI??Y
                {
                    if (pointer_val == 0 or pointer_val == 1){ //GI???
                    hour ++;
                    if (hour > 23)
                        hour = 0;}
                    else if (pointer_val == 3 or pointer_val == 4){ //PH??T
                    minute ++;
                    if (minute > 59)
                        minute = 0;}
                    else if (pointer_val == 6 or pointer_val == 7){ //GI??Y
                    second ++;
                    if (second > 59)
                        second = 0;}
                }

                else if(options_var == 3) // - CON TR??? ??? ??I???U KHI???N
                {
                    column_pointer --;
                    if (row
                     == 0){
                    if (column_pointer < 5)
                    { column_pointer = 15;
                        row
                         = 1;}
                    } else {
                    if (column_pointer < 5)
                    { column_pointer = 15;
                        row = 0;}        
                    } 
                }
            } 

            else if (sumcounters == 4 && options_var == 3) //+ ??I???U KHI???N | GI??? ON - OFF, RELAY
            {
                if(column_pointer == 5 or column_pointer == 6) //+ Gi??? ON/OFF
                {
                    if(menucontrol_var == 1) //Gi??? 1
                    Add_Hour(ton1, tof1);
                    else if(menucontrol_var == 2) //Gi??? 2
                    Add_Hour(ton2, tof2);
                    else if(menucontrol_var == 3) //Gi??? 3
                    Add_Hour(ton3, tof3);                            
                }
                else if(column_pointer == 8 or column_pointer == 9) //+ Ph??t ON/OFF
                {
                    if(menucontrol_var == 1) //Ph??t 1
                    Add_Min(pon1, pof1);
                    else if(menucontrol_var == 2) //Ph??t 2
                    Add_Min(pon2, pof2);
                    else if(menucontrol_var == 3) //Ph??t 3
                    Add_Min(pon3, pof3);                             
                }                        

                else if(row
                == 0 && column_pointer == 14) // + RELAY (ch???n relay on/off)
                {
                    if(menucontrol_var == 1) //L???nh 1
                    Add_Relay(re1);
                    else if (menucontrol_var == 2) //L???nh 2
                    Add_Relay(re2);
                    else if (menucontrol_var == 3) //L???nh 3
                    Add_Relay(re3);                 
                }                    
            }                                                  

            delay(200);
        }
        default_val = down_val;
    }
    
//  Menu_btn();
 if (menu_val != default_val)  {   // N??T MENU
        if (menu_val == 0) {//Khi nh???n n??t
            sumcounters ++;
            if (sumcounters == 1) {//??? menu t???ng
                menu_options(); 
            }

            else if (sumcounters == 2) {
                if(options_var == 0) //Nh???n BACK t??? Menu t???ng v??? m??n h??nh
                {
                    sumcounters = 0;
                    main_screen(); 
                }
                else if(options_var == 1 or options_var == 2) // ch???n menu t???ng DATE or hour
                {
                    choose_options();
                }
                else if(options_var == 3) //Menu ??I???U KHI???N
                {
                    menu_control();
                }
            }                                           

            else if (sumcounters == 3) {
                if((options_var == 2 or options_var == 1) && 
                    (pointer_val == 12 or pointer_val == 13 or pointer_val == 14 or pointer_val == 15)) // Tho??t t??? SET DATE or hour ra
                {
                    sumcounters = 1;
                    options_var = 0;
                    pointer_val = 0;
                    menu_options();
                    lcd.noCursor();
                }
                else if(options_var == 3 && menucontrol_var == 0) //t??? Menu ??I???U KHI???N v??? Menu T???NG
                {
                    sumcounters = 1;
                    menucontrol_var = 0;
                    menu_options();
                }
                else if(options_var == 3 && (menucontrol_var == 1 or menucontrol_var == 2 
                        or menucontrol_var == 3 or menucontrol_var == 4 or menucontrol_var == 5)) //ch???n menu ??K
                {
                    choose_menucontrol();
                }
            }  

            else if (sumcounters == 4) {//Tho??t CON TR???
                if(options_var == 1) //Tho??t CON TR??? t??? SET DATE ra
                {
                    sumcounters = 2;
                    choose_options();
                }
                else if(options_var == 2) //Tho??t CON TR??? t??? SET hour ra
                {
                    sumcounters = 2;
                    choose_options(); 
                }
                else if (options_var == 3) //Tho??t t??? SET BT ra menu b??o th???c
                {
                    if((column_pointer == 12 or column_pointer == 13 or column_pointer == 14 or column_pointer == 15) && row == 1)
                    {
                    menu_control();
                    sumcounters = 2;
                    options_var = 3;
                    column_pointer = 5;
                    row = 0;
                    lcd.noCursor();
                    }
                }
            }       
            
            else if (sumcounters == 5 && options_var == 3 && (menucontrol_var == 1 or menucontrol_var == 2
                    or menucontrol_var == 3 or menucontrol_var == 4 or menucontrol_var == 5))  //T??? CON TR??? ??K ch???c n??ng SET ra
            {
                choose_menucontrol();
                sumcounters = 3;
            }

            delay(100);
        }
        default_val = menu_val;
    }
    
//  Screen();
        if (sumcounters == 0 && options_var == 0) // M??N H??NH
    {
    main_screen();
    lcd.noCursor();

//    re1 = 1; re2 = 3; re3 = 2;  //RELAY

//    ton1 = 10; pon1 = 29; tof1 = 10; pof1 = 30; // 1 
//    ton2 = 10; pon2 = 30; tof2 = 10; pof2 = 31; // 1, 2
//    ton3 = 10; pon3 = 31; tof3 = 10; pof3 = 32; // 2

    if(t.sec == 2) //ON
    {
        if(t.hour == ton1 && t.min == pon1) //L???NH 1
        on(re1);
        else if(t.hour == ton2 && t.min == pon2) //L???NH 2
        on(re2);
        else if(t.hour == ton3 && t.min == pon3) //L???NH 3
        on(re3);           
    }
    if(t.sec == 1) //OFF
    {
        if(t.hour == tof1 && t.min == pof1) //L???NH 1
        off(re1);
        else if(t.hour == tof2 && t.min == pof2) //L???NH 2
        off(re2);
        else if(t.hour == tof3 && t.min == pof3) //L???NH 3
        off(re3);  
    }      
    }

    else if ((sumcounters == 2 or sumcounters == 3) && options_var != 3) //SETUP DATE / TIME
    {
    if(options_var == 1) //DATE
    {
        if (day < 10){
        lcd.setCursor(0,1); lcd.print("0");
        lcd.setCursor(1,1); lcd.print(day);
        } else {
        lcd.setCursor(0,1); lcd.print(day);    
        }
        lcd.setCursor(2,1); lcd.print("/");
        if (month < 10){
        lcd.setCursor(3,1); lcd.print("0"); 
        lcd.setCursor(4,1); lcd.print(month);
        } else {
        lcd.setCursor(3,1); lcd.print(month);    
        }
        lcd.setCursor(5,1); lcd.print("/"); 
        lcd.setCursor(6,1); lcd.print(yearng); lcd.setCursor(7,1); lcd.print(yeartr);
        lcd.setCursor(8,1); lcd.print(yearch); lcd.setCursor(9,1); lcd.print(yeardv);  
        year_sum = (yearng * 1000) + (yeartr * 100) + (yearch * 10) + yeardv;

        lcd.setCursor(pointer_val, 1); 
        lcd.cursor();
        delay(50);  

        rtc.setDate(day, month, year_sum);
    }
    else if (options_var == 2) //TIME
    {
        if (hour < 10){
        lcd.setCursor(0,1); lcd.print("0");
        lcd.setCursor(1,1); lcd.print(hour);
        } else {
        lcd.setCursor(0,1); lcd.print(hour);
        }
        lcd.setCursor(2,1); lcd.print(":");
        if (minute < 10){
        lcd.setCursor(3,1); lcd.print("0"); 
        lcd.setCursor(4,1); lcd.print(minute);
        } else {
        lcd.setCursor(3,1); lcd.print(minute);    
        }  
        lcd.setCursor(5,1); lcd.print(":");
        if (second < 10){
        lcd.setCursor(6,1); lcd.print("0"); 
        lcd.setCursor(7,1); lcd.print(second);
        } else {
        lcd.setCursor(6,1); lcd.print(second);    
        }

        lcd.setCursor(pointer_val, 1); 
        lcd.cursor();
        delay(50);

        rtc.setTime(hour, minute, second); 
    }
    }

    else if ((sumcounters == 3 or sumcounters == 4) && options_var == 3) //Hi???n th??? SETUP ON/OFF
    { 
    if(menucontrol_var == 1) //L???nh 1
        Showset(ton1, pon1, tof1, pof1, re1);     
    else if(menucontrol_var == 2) //L???nh 2
        Showset(ton2, pon2, tof2, pof2, re2);  
    else if(menucontrol_var == 3) //L???nh 3
        Showset(ton3, pon3, tof3, pof3, re3);           
    }

    Serial.print("?????m t???ng: "); Serial.print(sumcounters); Serial.print("    ");
    Serial.print("+/- t???ng: "); Serial.print(options_var); Serial.print("    ");
    Serial.print("CT ??i???u khi???n: "); Serial.print(column_pointer); Serial.print("    ");
    Serial.print("H??ng: "); Serial.print(row); Serial.print("    ");   
    Serial.print("+/- menu b??o th???c: "); Serial.print(menucontrol_var); Serial.print("    ");
    Serial.print("Con tr???: "); Serial.println(pointer_val);
    
}
