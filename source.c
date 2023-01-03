#include "header.h"

#define N 10

struct jseznam {
    struct jseznam *dalsi;
    int value;
    char* key;
  };

void rotuj(uint8_t valec);
void my_itoa(char r[], int n);

int has(char *key);
jseznam* nastav(char* key, int value);
jseznam* vyhledej(char *key);

jseznam *hastable[N] = {NULL};

unsigned long cas = 0;
unsigned long cas1 = 0;
long randomcislo;

const byte chery[8] = {
  0b00000111,
  0b00000010,
  0b00000100,
  0b00001110,
  0b00011111,
  0b00011111,
  0b00011111,
  0b00001110,
};

const byte citron[8] = {
  0b00001110,
  0b00000010,
  0b00001110,
  0b00011111,
  0b00011111,
  0b00001110,
  0b00000000,
  0b00000000
};

const byte heart[8] = {
  0b00000000,
  0b00000000,
  0b00011011,
  0b00011111,
  0b00011111,
  0b00011111,
  0b00001110,
  0b00000100
};

const byte bell[8] = {
  0b00000100,
  0b00001010,
  0b00001110,
  0b00011111,
  0b00011111,
  0b00011111,
  0b00000100,
  0b00000000
};

const byte star[8] = {
  0b00000100,
  0b00010101,
  0b00001110,
  0b00011111,
  0b00001110,
  0b00010101,
  0b00000100,
  0b00000000
};

const byte trnka[8] = {
  ~0b00000010,
  ~0b00000100,
  ~0b00001000,
  ~0b00000100,
  ~0b00000010,
  ~0b00000100,
  ~0b00001000,
  ~0b00000000
};

char *kola[3] = {
  "@0123$A45#",
  "5231#A04@$",
  "012345@#$A"
};

enum Stavy {tri, dva, jedna, nic};
Stavy stav = tri;

uint8_t kola_indexy[3][3] = {
  {2,1,0},
  {2,1,0},
  {2,1,0}
};

const uint8_t kola_poziceX[3] = {7,9,11};
const uint8_t kola_poziceY[3] = {0,1,2};
char kola_symboly[3];

char vyhra[3];
jseznam *ptr;
uint32_t pocitadlo = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(5));
  hd44Init();
  SetColor(1);

  CreateChar(0,chery);
  CreateChar(1,citron);
  CreateChar(2,heart);
  CreateChar(3,bell);
  CreateChar(4,star);
  CreateChar(5,trnka);

  SetLocation(6,1);
  hd44WriteData('>'); 
  SetLocation(12,1);
  hd44WriteData('<');

  ptr = nastav("@@@",1000);
  ptr = nastav("#@#",500);
  ptr = nastav("000",600);
  ptr = nastav("0@0",600);
  ptr = nastav("00@",600);
  ptr = nastav("@00",600);
  ptr = nastav("0$0",600);
  ptr = nastav("00$",600);
  ptr = nastav("$00",600);
  ptr = nastav("111",400);
  ptr = nastav("1@1",400);
  ptr = nastav("11@",400);
  ptr = nastav("@11",400);
  ptr = nastav("1$1",400);
  ptr = nastav("11$",400);
  ptr = nastav("$11",400);
  ptr = nastav("222",500);
  ptr = nastav("@22",500);
  ptr = nastav("2@2",500);
  ptr = nastav("22@",500);
  ptr = nastav("$22",500);
  ptr = nastav("2$2",500);
  ptr = nastav("22$",500);
  ptr = nastav("333",700);
  ptr = nastav("3@3",700);
  ptr = nastav("@33",700);
  ptr = nastav("33@",700);
  ptr = nastav("3$3",700);
  ptr = nastav("$33",700);
  ptr = nastav("33$",700);
  ptr = nastav("444",900);
  ptr = nastav("44@",900);
  ptr = nastav("@44",900);
  ptr = nastav("4@4",900);
  ptr = nastav("44$",900);
  ptr = nastav("$44",900);
  ptr = nastav("4$4",900);
  ptr = nastav("555",100);
  ptr = nastav("@55",100);
  ptr = nastav("5@5",100);
  ptr = nastav("55@",100);
  ptr = nastav("$55",100);
  ptr = nastav("5$5",100);
  ptr = nastav("55$",100);
  ptr = nastav("666",130);
  ptr = nastav("@66",130);
  ptr = nastav("6@6",130);
  ptr = nastav("66@",130);
  ptr = nastav("$66",130);
  ptr = nastav("6$6",130);
  ptr = nastav("66$",130);
  ptr = nastav("777",140);
  ptr = nastav("@77",140);
  ptr = nastav("7@7",140);
  ptr = nastav("77@",140);
  ptr = nastav("$77",140);
  ptr = nastav("7$7",140);
  ptr = nastav("77$",140);
  ptr = nastav("888",120);
  ptr = nastav("@88",120);
  ptr = nastav("8@8",120);
  ptr = nastav("88@",120);
  ptr = nastav("$88",120);
  ptr = nastav("8$8",120);
  ptr = nastav("88$",120);
  ptr = nastav("#99",500);
  ptr = nastav("9#9",500);
  ptr = nastav("99#",500);
  ptr = nastav("$99",500);
  ptr = nastav("9$9",500);
  ptr = nastav("99$",500);
  ptr = nastav("999",500);
  ptr = nastav("@AA",150);
  ptr = nastav("A@A",150);
  ptr = nastav("AA@",150);
  ptr = nastav("###",400);
  ptr = nastav("@##",200);
  ptr = nastav("#@#",400);
  ptr = nastav("##@",400);
  ptr = nastav("$$$",300);
  ptr = nastav("@$$",300);
  ptr = nastav("$@$",300);
  ptr = nastav("$$@",300);
  
  /*for(int i = 0; i < 10; i++){
    for(ptr = hastable[i]; ptr != NULL; ptr = ptr->dalsi){
      if(ptr == NULL) break;
      SetLocation(0,0);
      LcdPrint(ptr->key);
      delay(700);
      Serial.println(ptr->key);
    }
  }*/

  
}

long castka = 1000;
char zbytek_castka[4];

void loop() {
  // put your main code here, to run repeatedly:

  while(pocitadlo++ < 10000){
  
  switch(stav){

    case tri: {
      cas = millis();
      randomcislo = random(30);
      while(millis() - cas < randomcislo*100){
        rotuj(0);
        
      }
      stav = dva;
    }
    break;
    
    case dva: {
      cas = millis();
      randomcislo = random(22);
      while(millis() - cas < randomcislo*10){
        rotuj(1);
      }
      stav = jedna;
    }
    break;

    case jedna: {
      cas = millis();
      randomcislo = random(14);
      while(millis() - cas < randomcislo * 10){
        rotuj(2);
        
      }
      stav = tri;
      //Serial.println(vyhra);
      ptr = vyhledej(vyhra);
      Serial.println(vyhra);
      if(ptr){
        castka += ptr->value / 1.5;
        SetLocation(13,1);
        LcdPrint("win");
        delay(700);
        SetLocation(13,1);
        LcdPrint("   ");
        //Serial.println(ptr->key);
      }
      else castka -= 20; //delay(500);//Serial.println("null");

     my_itoa(zbytek_castka, castka);
     SetLocation(16,3);
     LcdPrint(zbytek_castka);
     //Serial.println(castka);
    }
    break;

    case nic: {
    }
    break;
    default: {}
  }
 
  //delay(1000);
  }

  //Serial.println("konec");


}


void my_itoa(char r[], int n){
 
    int delka, i = 0;
    int pom = n;
    
    for(delka = 0; pom /= 10; delka++);
    
    delka++;
    i = delka;
    
    do{
        r[--i] = n % 10 + '0';
    }while(n /= 10);
    
    r[delka] = '\0';
}


void rotuj(uint8_t val){

  uint8_t valec = val & 0x03;
  for(uint8_t i = 0; i < 3; i++){
    for(uint8_t j = valec; j < 3; j++){
      
      SetLocation(kola_poziceX[j], kola_poziceY[i]);
      kola_symboly[j] = kola[j][kola_indexy[j][i]];

      if(i == 1)
        vyhra[j] = kola_symboly[j];
      
      if(isdigit(kola_symboly[j])){
        kola_symboly[j] = kola_symboly[j] - '0';
      }
      kola_indexy[j][i] = (kola_indexy[j][i] + 1) % 10;
      hd44WriteData(kola_symboly[j]);
    }
   vyhra[3] = '\0';
  }
  delay(733);
}


int has(char *key){
  /*long hashod;
  for(int i = 0; *key != '\0'; key++)
    hashod = *key + 31*hashod;
  return hashod % N;*/
  
  long hashod = (key[0] * 100) + (key[1] * 10) + key[2];
  return hashod % 10;
}

jseznam* vyhledej(char *key){
  
  jseznam* uj;
  
  for(uj = hastable[has(key)]; uj != NULL; uj = uj->dalsi){
    if(strcmp(key, uj->key) == 0) 
      return uj;
  }
  return NULL;
}

jseznam* nastav(char* key, int value){
  
  jseznam * uj;
  long hashod;
  
  if((uj = vyhledej(key)) == NULL){
    
    uj = (struct jseznam*)malloc(sizeof(*uj));
    if(uj == NULL || (uj->key = strdup(key)) == NULL)
      return NULL;
    hashod = has(key);
    //Serial.println(hashod);
    uj->dalsi = hastable[hashod];
    hastable[hashod] = uj;
  }
    //free((void*) uj->value);
    uj->value = value;
  //if((uj->value = strdup(value)) == NULL) 
    //return NULL;
  return uj;
}
