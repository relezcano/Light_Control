
/* Light Control Arduino Ethernet
 controla el encendido o apagado de los Pin 2,3,4 ,5 y 6 del Arduino.
 */

#include <SPI.h>
#include <Ethernet.h>
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   // Direccion Fisica MAC
byte ip[] = { 192, 168, 1, 50 };                       // IP Local que usted debe configurar - 192.168.0.50
byte gateway[] = { 192, 168, 1, 1 };                   // Puerta de enlace - 192.168.1.1 en mi red / 192.168.0.1 en otras redes.
byte subnet[] = { 255, 255, 255, 0 };                  // Mascara de Sub Red
EthernetServer server(80);                             // Se usa el puerto 80 del servidor     
String readString;

void setup() {

  Serial.begin(9600);  // Inicializa el puerto serial 
    
  pinMode(2, OUTPUT);        // Se configura como salidas los puertos del 2 al 6
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
 
  Ethernet.begin(mac, ip, gateway, subnet); // Inicializa la conexion Ethernet y el servidor
  server.begin();
  Serial.print F("El Servidor es: ");
  Serial.println(Ethernet.localIP());    // Imprime la direccion IP Local
}


void loop() {
  // Crea una conexion Cliente
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //Lee caracter por caracter HTTP
        if (readString.length() < 100) {
          //Almacena los caracteres a un String
          readString += c;
          
         }

         // si el requerimiento HTTP fue finalizado
         if (c == '\n') {          
           Serial.println(readString); //Imprime en el monitor serial
     
           client.println (F("HTTP/1.1 200 OK"));           //envia una nueva pagina en codigo HTML
           client.println (F("Content-Type: text/html"));
           client.println();     
           client.println (F("<html>"));
           client.println (F("<head>"));
           client.println (F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"));
           client.println (F("<meta http-equiv=\"refresh\" content=\"30\">"));
           client.println (F("<style type=\"text/css\">body {font-family: Georgia; color: #ffffff; background-color: #0077b3} h5 {margin-right: 300px} h6 {margin-left: 290px; font-size: 14px} a {font-size: 16px; border-radius: 10px; padding: 5px; border-color: black; border-style: solid; background-color: #b3e6ff; text-decoration: none} </style>"));
           client.println (F("<TITLE>Domotica - Control de luces</TITLE>"));
           client.println (F("</head>"));
           
           client.println (F("<body>"));
           client.println (F("<hr />"));
           client.println (F("<div style=\"text-align: center\">"));
           client.println (F("<h1>Software para el control de luces</h1>"));
           client.println (F("<h2><em>Encienda o apague las luces presionando los botones</em></h2>"));
           client.println (F("<br>"));

           
           client.println (F("<a href=\"/?button2on\"\"><strong> Encender Luz PA 1</strong></a>"));           // construye en la pagina cada uno de los botones
           client.println (F("<a style='margin-left: 10px' href=\"/?button2off\"\"><strong> Apagar Luz PA 1</strong></a>"));   // pinmode2
           
           if (digitalRead(2)==HIGH){
            client.println (F("<h5>ON</h5>"));
           } else {
            client.println (F("<h6>OFF</h6>"));
           }

           
           client.println (F("<a href=\"/?button3on\"\"><strong> Encender Luz PA 2</strong></a>"));        // pinmode3
           client.println (F("<a style='margin-left: 10px' href=\"/?button3off\"\"><strong> Apagar Luz PA 2</strong></a>"));  
           
           if (digitalRead(3)==HIGH){
            client.println (F("<h5>ON</h5>"));
           } else {
            client.println (F("<h6>OFF</h6>"));
           }

            
           client.println (F("<a href=\"/?button5on\"\"><strong> Encender Luz PB</strong></a>"));       //pinmode5
           client.println (F("<a style='margin-left: 10px' href=\"/?button5off\"\"><strong> Apagar Luz PB</strong></a>")); 
           
           if (digitalRead(5)==HIGH){
            client.println (F("<h5>ON</h5>"));
           } else {
            client.println (F("<h6>OFF</h6>"));
           }
              
            
           client.println (F("<a href=\"/?button6on\"\"><strong> Encender Puerta</strong></a>"));        //pinmode6          
           client.println (F("<a style='margin-left: 10px' href=\"/?button6off\"\"><strong> Apagar Puerta </strong></a>"));
           
           if (digitalRead(6)==HIGH){
            client.println (F("<h5>ON</h5>"));
           } else {
            client.println (F("<h6>OFF</h6>"));
           }


           client.println (F("<a href=\"/?button7on\"\"><strong> Encender Todo</strong></a>"));        //pinmode2,3,5,6          
           client.println (F("<a style='margin-left: 10px' href=\"/?button7off\"\"><strong> Apagar Todo </strong></a>"));
           
           if (digitalRead(2)==HIGH && digitalRead(3)==HIGH && digitalRead(5)==HIGH && digitalRead(6)==HIGH){
            client.println (F("<h5>ON</h5>"));
           } else {
            client.println (F("<h6>OFF</h6>"));
           }   
           
           client.println (F("</div>"));
           client.println (F("<hr />"));
           client.println (F("<p>Hecho por: Ignacio Bressa y Ramiro Lezcano.<br>Sistemas 2.<br>Instituto Superior Capacitas.<br>Laboratorio de Lenguajes II.<br>Ciclo Lectivo: 2018</p>"));   
           client.println (F("</body>"));
           client.println (F("</html>"));
     
           delay(1);
           //detiene el cliente servidor
           client.stop();
           
           //control del arduino si un boton es presionado
                   
           if (readString.indexOf("?button2on") >0){
               digitalWrite(2, HIGH);
           }
           if (readString.indexOf("?button2off") >0){
               digitalWrite(2, LOW);
           }
           if (readString.indexOf("?button3on") >0){
               digitalWrite(3, HIGH);
           }
           if (readString.indexOf("?button3off") >0){
               digitalWrite(3, LOW);
           }
           
            if (readString.indexOf("?button5on") >0){
               digitalWrite(5, HIGH);
           }
           if (readString.indexOf("?button5off") >0){
               digitalWrite(5, LOW);
           }
           
           if (readString.indexOf("?button6on") >0){
               digitalWrite(6, HIGH);
           }
           if (readString.indexOf("?button6off") >0){
               digitalWrite(6, LOW);
           }

           if (readString.indexOf("?button7on") >0){
               digitalWrite(2, HIGH);
               digitalWrite(3, HIGH);
               digitalWrite(5, HIGH);
               digitalWrite(6, HIGH);
           }
           if (readString.indexOf("?button7off") >0){
               digitalWrite(2, LOW);
               digitalWrite(3, LOW);
               digitalWrite(5, LOW);
               digitalWrite(6, LOW);
           }
            // Limpia el String(Cadena de Caracteres para una nueva lectura
            readString="";  
           
         }
       }
    }
}
}
