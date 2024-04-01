
#include <motionDataCalculator.h>  // Motion values library
// *** SPFD5408 change -- Begin
#include <SPFD5408_Adafruit_GFX.h>     // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h>  // Hardware-specific library
#include <SPFD5408_TouchScreen.h>
//#include <TimeLib.h> // Para manejar fechas y horas
// *** SPFD5408 change -- End

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

#define YP A1  //--> must be an analog pin, use "An" notation!
#define XM A2  //--> must be an analog pin, use "An" notation!
#define YM 7   //--> can be a digital pin
#define XP 6   //--> can be a digital pin

//Calibrate Values
#define TS_MINX 175
#define TS_MINY 130
#define TS_MAXX 900
#define TS_MAXY 825

// For better pressure precision, we need to know the resistance
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

// Assign human-readable names to some common 16-bit color values:
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BOXSIZE 80
#define PENRADIUS 3
#define MINPRESSURE 1
#define MAXPRESSURE 1000

int Color_Tachometer;
float i = 0;
float j = 0;
float Radio = 0.0;
int hours = 0;
int minutes = 0;
char timeString[6];
float prevel = 0;
float Pre_Velo_AVG = 0;
float Pre_Velo_MAX = 0;
float Pre_Distance = 0;
bool Unit = 0;  // 0 = Km y Km/H; 1 = Mi y Mi/H
bool PreUnit;

// Tacómetro
int centerX = 170;
int centerY = 130;
int radius = 50;
int maxAngle = 180;
int minAngle = 0;

SensorHallEffect sensor;
FSMVariables fsmVariables;
MotionData motionData;

/*Multiples FSM*/
typedef enum {
  Main_menu1,
  Main_menu2,
  Config_R,
  Config_H,
  Motion_A,
} STATE_T;

STATE_T state = Main_menu1;

void setup() {
  tft.reset();
  tft.begin(0x9341);   // SDFP5408
  tft.setRotation(3);  // Need for the Mega, please changed for your choice or rotation initial
  Home_Interface();
  tft.fillScreen(WHITE);

  // Inicializamos el objeto de "fsmVariables":
  initializeFSMVariables(&fsmVariables);

  // Inicializamos el objeto de "motionData":
  initializeMotionData(&motionData);

  // Inicializamos el objeto de "sensor":
  initializeSensorHallEffect(&sensor, 52);
}

void loop() {

  // Obtenemos los valores para calcular el MCU:
  calculateMotionDataFSM(&sensor, &fsmVariables, &motionData);

  // Maquina de estados para el controll del TouchScreen:
  Always_print_time();  // En Main_menu1, Main_menu2, Config_R,

  //Animacion de bicicleta
  Animation();
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  switch (state) {

    case Main_menu1:

      tft.fillRoundRect(BOXSIZE * 0.7, BOXSIZE, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, BLACK);  // Caja de radio
      tft.setCursor(BOXSIZE * 0.75, BOXSIZE * 1.2);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.println("Radio");

      tft.fillRoundRect(BOXSIZE * 2.2, BOXSIZE, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, BLACK);  // Caja de tiempo
      tft.setCursor(BOXSIZE * 2.35, BOXSIZE * 1.2);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.println("Time");

      tft.fillRoundRect(BOXSIZE * 0.95, BOXSIZE * 1.8, BOXSIZE * 2.2, BOXSIZE, 15, BLACK);  // Caja de Motion Analytics
      tft.setCursor(BOXSIZE * 1.38, BOXSIZE * 2);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.println("Motion");
      tft.setCursor(BOXSIZE * 1.05, BOXSIZE * 2.4);
      tft.setTextSize(3);
      tft.setTextColor(WHITE);
      tft.println("Analytics");

      Button_menu();

      state = Main_menu2;
      break;

    case Main_menu2:

      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

        p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());


        if (p.y > 150 && p.x < (BOXSIZE * 0.5)) {
          Menu();
          state = Main_menu1;
        } else if (((p.y > BOXSIZE) && (p.y < BOXSIZE * 1.7)) && ((p.x > BOXSIZE * 0.7) && (p.x < BOXSIZE * 1.8))) {
          tft.fillScreen(WHITE);
          Button_menu();
          tft.fillRoundRect(BOXSIZE * 0.7, BOXSIZE * 2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, BLACK);  // Rellenar caja con esquinas redondeadas
          tft.fillRoundRect(BOXSIZE * 2.2, BOXSIZE * 2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, BLACK);  // Rellenar caja con esquinas redondeadas

          tft.setCursor(202, 70);
          tft.setTextSize(3);
          tft.setTextColor(BLACK);
          tft.println("m");

          tft.setCursor(BOXSIZE * 0.9, BOXSIZE * 2.2);
          tft.setTextSize(2);
          tft.setTextColor(WHITE);
          tft.println("-0.01");
          tft.setCursor(BOXSIZE * 2.4, BOXSIZE * 2.2);
          tft.setTextSize(2);
          tft.setTextColor(WHITE);
          tft.println("+0.01");
          tft.setCursor(100, 30);
          tft.setTextSize(5);
          tft.setTextColor(BLACK);
          tft.println("Radio");

          tft.setCursor(130, 70);
          tft.setTextSize(3);
          tft.setTextColor(BLACK);
          tft.println(Radio);

          state = Config_R;

        } else if ((p.y > BOXSIZE) && (p.y < BOXSIZE * 1.7) && (p.x > BOXSIZE * 2.2) && (p.x < BOXSIZE * 3.2)) {
          tft.fillScreen(WHITE);
          Button_menu();

          tft.setCursor(70, 10);
          tft.setTextSize(4);
          tft.setTextColor(BLACK);
          tft.println("Set Time");

          tft.fillRoundRect(BOXSIZE * 0.7, BOXSIZE * 1.2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, BLACK);  // Boton izquierdo superior
          tft.setCursor(BOXSIZE, BOXSIZE * 1.4);
          tft.setTextSize(2);
          tft.setTextColor(WHITE);
          tft.println("+1 h");

          tft.fillRoundRect(BOXSIZE * 0.7, BOXSIZE * 2.2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, BLACK);  // Boton izquierdo inferior
          tft.setCursor(BOXSIZE, BOXSIZE * 2.4);
          tft.setTextSize(2);
          tft.setTextColor(WHITE);
          tft.println("-1 h");

          tft.fillRoundRect(BOXSIZE * 2.2, BOXSIZE * 1.2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, BLACK);  // Boton derecho superior
          tft.setCursor(BOXSIZE * 2.5, BOXSIZE * 1.4);
          tft.setTextSize(2);
          tft.setTextColor(WHITE);
          tft.println("+1 m");

          tft.fillRoundRect(BOXSIZE * 2.2, BOXSIZE * 2.2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, BLACK);  // Boton derecho inferior
          tft.setCursor(BOXSIZE * 2.5, BOXSIZE * 2.4);
          tft.setTextSize(2);
          tft.setTextColor(WHITE);
          tft.println("+1 m");

          tft.setCursor(120, 50);
          tft.setTextSize(3);
          tft.setTextColor(BLACK);
          sprintf(timeString, "%02d:%02d", hours, minutes);
          tft.print(timeString);

          state = Config_H;
        } else if ((p.y > BOXSIZE * 1.8) && (p.y < BOXSIZE * 2.8) && (p.x > BOXSIZE * 0.95) && (p.x < BOXSIZE * 3.15)) {
          tft.fillScreen(WHITE);

          Button_units();
          Button_menu();

          tft.fillCircle(centerX, centerY, radius + 15, BLACK);
          tft.fillCircle(centerX, centerY, radius + 10, WHITE);

          tft.fillRect(centerX - 70, centerY + 2, radius * 2.8, radius * 1.28, WHITE);

          tft.setTextSize(2);
          tft.setTextColor(BLACK);
          tft.setCursor(centerX - 80, centerY);
          tft.print("0");
          tft.setCursor(centerX - 10, centerY - 80);
          tft.print("30");
          tft.setCursor(centerX + 70, centerY);
          tft.print("60");

          tft.setTextSize(2);
          tft.setTextColor(BLACK);
          tft.setCursor(50, 200);
          tft.print("Vel Max");
          tft.setCursor(50, 220);  //Poner un mancha para actualizar la velocidad maxima en esta posicion
          tft.print(motionData.maxVelocity);
          tft.print("Km/h");

          tft.setTextSize(2);
          tft.setTextColor(BLACK);
          tft.setCursor(50, 10);
          tft.print("Vel AVG");
          tft.setCursor(50, 30);  //Poner un mancha para actualizar la velocidad maxima en esta posicion
          tft.print(motionData.averageVelocity);
          tft.print("Km/h");

          tft.setTextSize(2);
          tft.setTextColor(BLACK);
          tft.setCursor(220, 200);
          tft.print("Distance");
          tft.setCursor(220, 220);  //Poner un mancha para actualizar la velocidad maxima en esta posicion
          tft.print(motionData.distance);
          tft.print("Km");

          state = Motion_A;
        }
      }

      break;

    case Config_R:
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

        p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

        if (p.y > 150 && p.x < (BOXSIZE * 0.5)) {
          tft.fillScreen(WHITE);
          state = Main_menu1;
        } else {

          Config_Radio();
          state = Config_R;
        }
      }
      break;

    case Config_H:
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

        p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

        if (p.y > 150 && p.x < (BOXSIZE * 0.5)) {
          tft.fillScreen(WHITE);
          state = Main_menu1;
        } else {
          Config_Time();
          state = Config_H;
        }
      }
      break;

    case Motion_A:

      unsigned long currentMillis = millis();

      // Only update screen and handle touch input every 100 milliseconds
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

        p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

        if (p.y > 150 && p.x < (BOXSIZE * 0.5)) {
          tft.fillScreen(WHITE);
          state = Main_menu1;
        }
      }
      Motion_Analytics();
      state = Motion_A;
      break;
  }
}



void Motion_Analytics() {

  PreUnit = Unit;
  //vel = Valor que retorne la funcion readvel
  //Velo_AVG = Valor que retorne la funcion Calcule_Velocity_Average;
  //Velo_MAX = Valor que retore la funcion Calcule_Velocity_Max;
  //Distance = Valor que retorne la funcion Calcule_Distance;

  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    if (((p.x > 0) && (p.x < BOXSIZE * 0.5)) && ((p.y > 30) && (p.y < (BOXSIZE * 1.4) + 30))) {
      (Unit == 0) ? (Unit = 1) : (Unit = 0);
      tft.drawRoundRect(0, 30, BOXSIZE * 0.5, BOXSIZE * 1.4, 15, GREEN);
    }
  }

  int angle = map(motionData.linearVelocity, 0, 60, minAngle, maxAngle);

  // Calcular las coordenadas finales de las líneas
  int x1 = centerX + radius * -cos(angle * PI / 180);         // Ajustar el ángulo de inicio
  int y1 = centerY + radius * -sin(angle * PI / 180);         // Ajustar el ángulo de inicio
  int x2 = centerX + (radius - 20) * -cos(angle * PI / 180);  // Ajustar el largo de la línea (el doble de largo)
  int y2 = centerY + (radius - 20) * -sin(angle * PI / 180);  // Ajustar el largo de la línea (el doble de largo)

  // Calcular las coordenadas finales de las líneas ligeramente desplazadas
  int lineOffset = 8;                                                 // Ajustar el grosor de la línea (la distancia entre las líneas)
  int x3 = centerX + (radius - lineOffset) * -cos(angle * PI / 180);  // Ajustar el grosor de la línea
  int y3 = centerY + (radius - lineOffset) * -sin(angle * PI / 180);  // Ajustar el grosor de la línea
  int x4 = centerX + (radius - 30) * -cos(angle * PI / 180);          // Ajustar el largo de la línea (el doble de largo)
  int y4 = centerY + (radius - 30) * -sin(angle * PI / 180);          // Ajustar el largo de la línea (el doble de largo)


  if ((prevel != motionData.linearVelocity) || (PreUnit != Unit)) {
    // Borrar el tacómetro anterior
    tft.fillCircle(centerX, centerY, radius + 10, WHITE);

  } else {
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.setCursor(centerX - 30, centerY + 2);

    if (Unit == 0) {
      tft.print(motionData.linearVelocity);
      tft.print("Km/h");
    } else if (Unit == 1) {
      tft.print(motionData.linearVelocity / 1.609);
      tft.print("Mi/h");
    }

    if ((motionData.linearVelocity > 0) && (motionData.linearVelocity < 20)) {
      Color_Tachometer = GREEN;
    } else if ((motionData.linearVelocity > 20) && (motionData.linearVelocity < 40)) {
      Color_Tachometer = YELLOW;
    } else if (motionData.linearVelocity > 40) {
      Color_Tachometer = RED;
    }

    tft.drawLine(x1, y1, x2, y2, Color_Tachometer);
    tft.drawLine(x1, y1, x3, y3, Color_Tachometer);
    tft.drawLine(x3, y3, x4, y4, Color_Tachometer);
  }

  //Actualizacion de Velocidad MAX
  if ((Pre_Velo_MAX != motionData.maxVelocity) || (PreUnit != Unit)) {
    // Borrar la velocidad anterior
    tft.fillRect(50, 220, 100, 15, WHITE);

  } else {
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.setCursor(50, 220);
    //HACER CONDICIONAL PARA CAMBIAR DE UNIDADES
    if (Unit == 0) {
      tft.print(motionData.maxVelocity);
      tft.print("Km/h");
    } else if (Unit == 1) {
      tft.print(motionData.maxVelocity / 1.609);
      tft.print("Mi/h");
    }
  }

  //Actualizacion de Velocidad AVG
  if ((Pre_Velo_AVG != motionData.averageVelocity) || (PreUnit != Unit)) {
    // Borrar la velocidad anterior
    tft.fillRect(50, 30, 100, 15, WHITE);

  } else {
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.setCursor(50, 30);
    //HACER CONDICIONAL PARA CAMBIAR DE UNIDADES
    if (Unit == 0) {
      tft.print(motionData.averageVelocity);
      tft.print("Km/h");
    } else if (Unit == 1) {
      tft.print(motionData.averageVelocity / 1.609);
      tft.print("Mi/h");
    }
  }

  //Actualizacion de Distancia
  if ((Pre_Distance != motionData.distance) || (PreUnit != Unit)) {
    // Borrar la distancia anterior
    tft.fillRect(220, 220, 100, 15, WHITE);

  } else {
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.setCursor(220, 220);
    //HACER CONDICIONAL PARA CAMBIAR DE UNIDADES
    if (Unit == 0) {
      tft.print(motionData.distance);
      tft.print("km");
    } else if (Unit == 1) {
      tft.print(motionData.distance / 1.609);
      tft.print("mi");
    }
  }

  prevel = motionData.linearVelocity;

  Pre_Velo_AVG = motionData.averageVelocity;
  Pre_Velo_MAX = motionData.maxVelocity;
  Pre_Distance = motionData.distance;
}


void Menu() {


  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);


  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    ;

    if ((p.y > 150) && (p.x < (BOXSIZE * 0.5))) tft.drawRoundRect(0, 150, BOXSIZE * 0.5, BOXSIZE * 1.2, 15, BLACK);
  }
}


void Config_Time() {
  // Almacenar los valores originales de horas y minutos
  int oldhours = hours;
  int oldminutes = minutes;

  // Imprimir la hora formateada en la pantalla TFT
  sprintf(timeString, "%02d:%02d", hours, minutes);
  tft.setCursor(120, 50);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.print(timeString);


  // Leer la entrada del usuario
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    // Procesar la entrada del usuario y actualizar las horas y los minutos
    if ((p.x > BOXSIZE * 0.7 && p.x < BOXSIZE * 1.9) && (p.y > (BOXSIZE * 1.2) && p.y < (BOXSIZE * 1.9))) {  // Izquierda Superior
      hours += 1;
      if (hours >= 24) hours = 0;                                                                                     // Ajuste para que las horas estén en el rango de 0 a 23
      tft.drawRoundRect(BOXSIZE * 0.7, BOXSIZE * 1.2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, GREEN);                       // Marco
    } else if ((p.x > BOXSIZE * 0.7 && p.x < (BOXSIZE * 1.9)) && (p.y > (BOXSIZE * 2.2) && p.y < (BOXSIZE * 2.9))) {  // Izquierda Inferior
      hours -= 1;
      if (hours < 0) hours = 23;                                                                                      // Ajuste para que las horas estén en el rango de 0 a 23
      tft.drawRoundRect(BOXSIZE * 0.7, BOXSIZE * 2.2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, RED);                         // Marco
    } else if ((p.x > BOXSIZE * 2.2 && p.x < (BOXSIZE * 3.4)) && (p.y > (BOXSIZE * 1.2) && p.y < (BOXSIZE * 1.9))) {  // Derecha Superior
      minutes += 1;
      if (minutes >= 60) {
        minutes = 0;
        hours += 1;                  // Incrementar las horas cuando los minutos llegan a 60
        if (hours >= 24) hours = 0;  // Ajuste para que las horas estén en el rango de 0 a 23
      }
      tft.drawRoundRect(BOXSIZE * 2.2, BOXSIZE * 1.2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, GREEN);                       // Marco
    } else if ((p.x > BOXSIZE * 2.2 && p.x < (BOXSIZE * 3.4)) && (p.y > (BOXSIZE * 2.2) && p.y < (BOXSIZE * 2.9))) {  // Derecha Inferior
      minutes -= 1;
      if (minutes < 0) {
        minutes = 59;
        hours -= 1;                 // Decrementar las horas cuando los minutos llegan a -1
        if (hours < 0) hours = 23;  // Ajuste para que las horas estén en el rango de 0 a 23
      }
      tft.drawRoundRect(BOXSIZE * 2.2, BOXSIZE * 2.2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, RED);  // Marco
    }
  }

  // Verificar si ha habido cambios en las horas o los minutos
  if ((oldhours != hours) || (oldminutes != minutes)) {
    // Borrar el área donde se imprimió el valor anterior de tiempo
    int timeWidth = 100;  // 6 caracteres (HH:MM) con tamaño de fuente 3
    tft.fillRect(120, 50, timeWidth, 25, WHITE);

    // Imprimir el nuevo valor de tiempo
    sprintf(timeString, "%02d:%02d", hours, minutes);
    tft.setCursor(120, 50);
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    tft.print(timeString);
  }
}




// Wait one touch

TSPoint waitOneTouch() {

  // wait 1 touch to exit function

  TSPoint p;

  do {
    p = ts.getPoint();

    pinMode(XM, OUTPUT);  //Pins configures again for TFT control
    pinMode(YP, OUTPUT);

  } while ((p.z < MINPRESSURE) || (p.z > MAXPRESSURE));

  return p;
}


void drawBorder() {

  // Draw a border

  uint16_t width = tft.width() - 1;
  uint16_t height = tft.height() - 1;
  uint8_t border = 10;

  tft.fillScreen(RED);
  tft.fillRoundRect(border, border, (width - border * 2), (height - border * 2), 15, WHITE);
}

void Home_Interface() {
  //Home interface
  tft.fillScreen(WHITE);
  tft.setCursor(70, 50);
  tft.setTextSize(3);
  tft.setTextColor(GREEN);
  tft.println("Welcome to");
  tft.setCursor(20, 85);
  tft.println("Bicycle Computer");
  tft.setCursor(70, 150);
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.println("Tap To Continue");
  waitOneTouch();
}

void Config_Radio() {

  float oldradio = Radio;

  // Imprimir el nuevo valor de Radio
  tft.setCursor(130, 70);
  tft.setTextSize(3);
  tft.setTextColor(BLACK);
  tft.println(Radio);

  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);


  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {


    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());

    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    if ((p.x > BOXSIZE * 0.7 && p.x < (BOXSIZE * 1.9)) && (p.y > (BOXSIZE * 2) && p.y < (BOXSIZE * 2.7))) {
      Radio -= 0.01;
      if (Radio < 0) Radio = 0;

      tft.drawRoundRect(BOXSIZE * 0.7, BOXSIZE * 2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, RED);
    } else if ((p.x > BOXSIZE * 2.2 && p.x < (BOXSIZE * 3.4)) && (p.y > (BOXSIZE * 2) && p.y < (BOXSIZE * 2.7))) {
      Radio += 0.01;
      tft.drawRoundRect(BOXSIZE * 2.2, BOXSIZE * 2, BOXSIZE * 1.2, BOXSIZE * 0.7, 15, GREEN);
    }
  }


  if (oldradio != Radio) {
    // Calcular el ancho del texto basado en el tamaño de la fuente y la longitud del texto
    int oldRadioWidth = 18 * String(Radio).length();  // Suponiendo un ancho aproximado por carácter

    // Borrar el área donde se imprime el valor anterior de Radio
    tft.fillRect(130, 70, oldRadioWidth, 25, WHITE);
    tft.setCursor(130, 70);
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    tft.println(Radio);
  }
}

void Button_menu() {
  tft.fillRoundRect(0, 150, BOXSIZE * 0.5, BOXSIZE * 1.2, 15, GREEN);
  tft.setCursor(13, 160);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("M");
  tft.setCursor(13, 180);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("E");
  tft.setCursor(13, 200);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("N");
  tft.setCursor(13, 220);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("U");
}

void Button_units() {
  tft.fillRoundRect(0, 30, BOXSIZE * 0.5, BOXSIZE * 1.4, 15, BLUE);
  tft.setCursor(13, 40);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.println("U");
  tft.setCursor(13, 60);
  tft.setTextColor(WHITE);
  tft.println("N");
  tft.setCursor(13, 80);
  tft.setTextColor(WHITE);
  tft.println("I");
  tft.setCursor(13, 100);
  tft.setTextColor(WHITE);
  tft.println("T");
  tft.setCursor(13, 120);
  tft.setTextColor(WHITE);
  tft.println("S");
}

void Always_print_time() {
  static unsigned long lastMinuteUpdate1 = 0;
  sprintf(timeString, "%02d:%02d", hours, minutes);
  int flagtime = 0;
  if ((millis() - lastMinuteUpdate1) >= 60000) {  //Ajustar a 60000 pero para las pruebas dejarlo
    flagtime = 1;
    lastMinuteUpdate1 = millis();
    minutes += 1;
    if (minutes >= 60) {
      hours += 1;
      minutes = 0;                 // Reiniciar los minutos a 0
      if (hours >= 24) hours = 0;  // Reiniciar las horas a 0 si alcanzan las 24
    }
  }

  if ((state == Main_menu1 || state == Main_menu2 || state == Config_R || state == Motion_A) && (flagtime)) {
    int timeWidth = 100;  // 6 caracteres (HH:MM) con tamaño de fuente 3
    tft.fillRect(230, 10, timeWidth, 25, WHITE);

  } else if (state == Main_menu1 || state == Main_menu2 || state == Config_R || state == Motion_A) {
    //Muestra siempre la hora
    tft.setCursor(230, 10);
    tft.setTextSize(3);
    tft.setTextColor(BLACK);
    tft.print(timeString);  //
  }
}

void Animation() {
  static unsigned long lastMinuteUpdate2 = 0;
  static unsigned long positionmov = 0;
  int flagtime2 = 0;

  if ((millis() - lastMinuteUpdate2) >= 1000) {
    flagtime2 = 1;
    lastMinuteUpdate2 = millis();
    (positionmov >= 14) ? (positionmov = 0) : (positionmov += 1);
  }


  if ((state == Main_menu1 || state == Main_menu2) && (flagtime2)) {  // Mancha por si el tiempo cambia
    tft.fillRect(BOXSIZE * 0.15, BOXSIZE * 0.45, BOXSIZE * 3.9, BOXSIZE * 0.5, WHITE);

  } else if (state == Main_menu1 || state == Main_menu2) {  //imprime

    tft.setTextSize(1);
    tft.setTextColor(BLACK);

    (positionmov == 0) ? (tft.setCursor(BOXSIZE * 0.15, BOXSIZE * 0.56)) : tft.setCursor(BOXSIZE * positionmov * 0.2, BOXSIZE * 0.56);
    tft.print(" O     ___/ ");
    (positionmov == 0) ? (tft.setCursor(BOXSIZE * 0.15, BOXSIZE * 0.65)) : tft.setCursor(BOXSIZE * positionmov * 0.2, BOXSIZE * 0.65);
    tft.print("/|\\   /   \\ ");
    (positionmov == 0) ? (tft.setCursor(BOXSIZE * 0.15, BOXSIZE * 0.74)) : tft.setCursor(BOXSIZE * positionmov * 0.2, BOXSIZE * 0.74);
    tft.print("/ \\  O     O ");
  }
}