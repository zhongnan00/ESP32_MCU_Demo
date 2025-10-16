// /**
//  * @file wifi.cpp
//  * @author chao.liu (chao.liu2@medtronic.com)
//  * @brief 
//  * @version 0.1
//  * @date 2025-10-15
//  * 
//  * @copyright Copyright (c) 2025
//  * 
//  */

// #include <WiFi.h>
// #include "wifi.h"

// const char* ssid = "your_ssid";
// const char* password = "your_password";

// WiFiServer wifi_server(80); // create a server object listening on port 80

// void wifi_init()
// {
//     WiFi.begin(ssid, password);
// }

// void wifi_task_run()
// {
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         /* code */
//         delay(500);
//         Serial.println("Connecting to WiFi..");
//     }

//     Serial.println("Connected to WiFi");
//     Serial.println(WiFi.localIP());
//     Serial.println("Starting web server..");
    
//     wifi_server.begin(); // start the server    
//     WiFiClient client = wifi_server.available(); // wait for client to connect

//     if (client)
//     {
//         Serial.println("Client connected");
//         String currentLine = "";
//         while (client.connected())
//         {
//             if (client.available())
//             {
//                 char c = client.read();
//                 Serial.write(c);
//                 if (c == '\n')
//                 {
//                     // Serial.println(currentLine);
//                     if (currentLine.startsWith("GET"))
//                     {
//                         // handle HTTP request
//                         if (currentLine.endsWith(".html"))
//                         {

//                         }
//                         else if (currentLine.endsWith(".css"))
//                         {

//                         }
//                         else if (currentLine.endsWith(".js"))
//                         {

//                         }
//                     }
//                     currentLine = "";
//                 }
//                 else if (c != '\r')
//                 {
//                     currentLine += c;
//                 }
//             }
//         }

//         client.stop(); // close the connection
//         Serial.println("Client disconnected");
//     }
// }
