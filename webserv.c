#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_events.h>
#include <model.h>

extern void save_screenshot2 (void);

#define BUFSIZE 18096
#define PI 3.14159265

SDL_Thread *thread_webserv = NULL;


void webserv_child_dump_screen (int fd) {
	static char buffer[BUFSIZE + 1];
	int file_fd;
	long len;
	long ret;
	save_screenshot2();
	if ((file_fd = open("/tmp/dump.png",O_RDONLY)) == -1) {
		return;
	}
	len = lseek(file_fd, (off_t)0, SEEK_END);
	lseek(file_fd, (off_t)0, SEEK_SET);
	sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", len, "image/png");
	write(fd, buffer, strlen(buffer));
	while ((ret = read(file_fd, buffer, BUFSIZE)) > 0) {
		write(fd,buffer,ret);
	}
}

void webserv_child_dump_modeldata (int fd) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[100];

	content[0] = 0;
	sprintf(tmp_str, "name=%s\n", ModelData.name);
	strcat(content, tmp_str);
	sprintf(tmp_str, "image=%s\n", ModelData.image);
	strcat(content, tmp_str);
	sprintf(tmp_str, "modeltype=%i\n", ModelData.modeltype);
	strcat(content, tmp_str);
	sprintf(tmp_str, "teletype=%i\n", ModelData.teletype);
	strcat(content, tmp_str);
	sprintf(tmp_str, "teledevice=%s\n", ModelData.teledevice);
	strcat(content, tmp_str);
	sprintf(tmp_str, "telebaud=%i\n", ModelData.telebaud);
	strcat(content, tmp_str);
	sprintf(tmp_str, "telebtaddr=%s\n", ModelData.telebtaddr);
	strcat(content, tmp_str);
	sprintf(tmp_str, "telebtpin=%s\n", ModelData.telebtpin);
	strcat(content, tmp_str);
	sprintf(tmp_str, "mode=%i\n", ModelData.mode);
	strcat(content, tmp_str);
	sprintf(tmp_str, "status=%i\n", ModelData.status);
	strcat(content, tmp_str);
	sprintf(tmp_str, "armed=%i\n", ModelData.armed);
	strcat(content, tmp_str);
	sprintf(tmp_str, "heartbeat=%i\n", ModelData.heartbeat);
	strcat(content, tmp_str);
	sprintf(tmp_str, "heartbeat_rc=%i\n", ModelData.heartbeat_rc);
	strcat(content, tmp_str);
	sprintf(tmp_str, "found_rc=%i\n", ModelData.found_rc);
	strcat(content, tmp_str);
	sprintf(tmp_str, "p_lat=%f\n", ModelData.p_lat);
	strcat(content, tmp_str);
	sprintf(tmp_str, "p_long=%f\n", ModelData.p_long);
	strcat(content, tmp_str);
	sprintf(tmp_str, "p_alt=%f\n", ModelData.p_alt);
	strcat(content, tmp_str);
	sprintf(tmp_str, "alt_offset=%f\n", ModelData.alt_offset);
	strcat(content, tmp_str);
	sprintf(tmp_str, "baro=%f\n", ModelData.baro);
	strcat(content, tmp_str);
	sprintf(tmp_str, "pitch=%f\n", ModelData.pitch);
	strcat(content, tmp_str);
	sprintf(tmp_str, "roll=%f\n", ModelData.roll);
	strcat(content, tmp_str);
	sprintf(tmp_str, "yaw=%f\n", ModelData.yaw);
	strcat(content, tmp_str);
	sprintf(tmp_str, "speed=%f\n", ModelData.speed);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage=%f\n", ModelData.voltage);
	strcat(content, tmp_str);
	sprintf(tmp_str, "load=%f\n", ModelData.load);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gpsfix=%i\n", ModelData.gpsfix);
	strcat(content, tmp_str);
	sprintf(tmp_str, "numSat=%i\n", ModelData.numSat);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[0]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[1]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[2]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[3]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[4]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[5]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[6]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[7]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[8]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[9]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[10]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[11]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[12]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[13]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[14]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "radio=%i\n", ModelData.radio[15]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "acc_x=%f\n", ModelData.acc_x);
	strcat(content, tmp_str);
	sprintf(tmp_str, "acc_y=%f\n", ModelData.acc_y);
	strcat(content, tmp_str);
	sprintf(tmp_str, "acc_z=%f\n", ModelData.acc_z);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gyro_x=%f\n", ModelData.gyro_x);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gyro_y=%f\n", ModelData.gyro_y);
	strcat(content, tmp_str);
	sprintf(tmp_str, "gyro_z=%f\n", ModelData.gyro_z);
	strcat(content, tmp_str);
	sprintf(tmp_str, "rssi_rx=%i\n", ModelData.rssi_rx);
	strcat(content, tmp_str);
	sprintf(tmp_str, "rssi_tx=%i\n", ModelData.rssi_tx);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_rx=%f\n", ModelData.voltage_rx);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[0]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[1]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[2]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[3]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[4]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "voltage_zell=%f\n", ModelData.voltage_zell[5]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "temperature=%i\n", ModelData.temperature[0]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "temperature=%i\n", ModelData.temperature[1]);
	strcat(content, tmp_str);
	sprintf(tmp_str, "ampere=%f\n", ModelData.ampere);
	strcat(content, tmp_str);
	sprintf(tmp_str, "sysid=%i\n", ModelData.sysid);
	strcat(content, tmp_str);
	sprintf(tmp_str, "compid=%i\n", ModelData.compid);
	strcat(content, tmp_str);

	sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));

}

void webserv_child_draw_hud (int fd) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[100];

	content[0] = 0;

	strcat(content, "<!DOCTYPE HTML>");
	strcat(content, "<html>");
	strcat(content, "  <head>");
	strcat(content, "    <style>");
	strcat(content, "      body {");
	strcat(content, "        margin: 0px;");
	strcat(content, "        padding: 0px;");
	strcat(content, "      }");
	strcat(content, "    </style>");
	strcat(content, "  </head>");
	strcat(content, "  <body>");
	strcat(content, "    <canvas id=\"myCanvas\" width=\"800\" height=\"600\"></canvas>");
	strcat(content, "    <script>");
	strcat(content, "      var canvas = document.getElementById('myCanvas');");
	strcat(content, "      var context = canvas.getContext('2d');");
	strcat(content, "      var centerX = canvas.width / 2;");
	strcat(content, "      var centerY = canvas.height / 2;");
	strcat(content, "      var radius = 170;");
	strcat(content, "      context.beginPath();");

	sprintf(tmp_str, "      context.arc(centerX, centerY, radius, %f, %f, false);", ModelData.roll * PI / 180.0, ModelData.roll * PI / 180.0 + PI);
	strcat(content, tmp_str);

	strcat(content, "      context.fillStyle = 'green';");
	strcat(content, "      context.fill();");
	strcat(content, "      context.lineWidth = 5;");
	strcat(content, "      context.strokeStyle = '#003300';");
	strcat(content, "      context.stroke();");
	strcat(content, "    </script>");
	strcat(content, "  </body>");
	strcat(content, "</html>");

	sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}

void webserv_child_show_lonlat (int fd) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	sprintf(content, "%f, %f", ModelData.p_long, ModelData.p_lat);
	sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/plain");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));
}


void webserv_child_show_map (int fd) {
	static char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[512];
	content[0] = 0;
	strcat(content, "<html><head><title>MultiGCS</title><script language=\"Javascript\">\n");
	strcat(content, "function xmlhttpGet() {\n");
	strcat(content, "    var xmlHttpReq = false;\n");
	strcat(content, "    var self = this;\n");
	strcat(content, "    if (window.XMLHttpRequest) {\n");
	strcat(content, "        self.xmlHttpReq = new XMLHttpRequest();\n");
	strcat(content, "    } else if (window.ActiveXObject) {\n");
	strcat(content, "        self.xmlHttpReq = new ActiveXObject(\"Microsoft.XMLHTTP\");\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.open('GET', \"/lonlat\", true);\n");
	strcat(content, "    self.xmlHttpReq.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\n");
	strcat(content, "    self.xmlHttpReq.onreadystatechange = function() {\n");
	strcat(content, "        if (self.xmlHttpReq.readyState == 4) {\n");
	strcat(content, "            updatepage(self.xmlHttpReq.responseText);\n");
	strcat(content, "        }\n");
	strcat(content, "    }\n");
	strcat(content, "    self.xmlHttpReq.send();\n");
	strcat(content, "    setTimeout(xmlhttpGet, 5000);\n");
	strcat(content, "}\n");
	strcat(content, "function updatepage(str){\n");
	strcat(content, "    var data = str.split(',')\n");
	strcat(content, "    lonLat = new OpenLayers.LonLat(data[0], data[1]).transform(new OpenLayers.Projection(\"EPSG:4326\"),map.getProjectionObject());\n");
	strcat(content, "    markers.addMarker(new OpenLayers.Marker(lonLat));\n");
	strcat(content, "    map.setCenter (lonLat, zoom);\n");
	strcat(content, "}\n");
	strcat(content, "</script></head><body>\n");
	strcat(content, "<style type=\"text/css\">\n");
	strcat(content, "body {\n");
	strcat(content, "	background-color:#000000;\n");
	strcat(content, "	color:#FFFFFF;\n");
	strcat(content, "}\n");
	strcat(content, "#mapdiv {\n");
	strcat(content, "    width: 50%;\n");
	strcat(content, "    height: 90%;\n");
	strcat(content, "    position: absolute;\n");
	strcat(content, "    right: 10px;\n");
	strcat(content, "    float: none;\n");
	strcat(content, "}\n");
	strcat(content, "</style>\n");
	strcat(content, "<div class=\"mapdiv\" id=\"mapdiv\"></div>\n");
	strcat(content, "<p onclick='JavaScript:xmlhttpGet();'>[UPDATE]</p>\n");
	strcat(content, "    <canvas id=\"myCanvas\" width=\"640\" height=\"480\"></canvas>");
	strcat(content, "    <script>");
	strcat(content, "	function drawMeter(context, x, y, r, a, b, c) {\n");
	strcat(content, "		var centerX = x;\n");
	strcat(content, "		var centerY = y;\n");
	strcat(content, "		endA = 3.141593 + (3.141593 / 180.0 * a);\n");
	strcat(content, "		endB = 3.141593 + (3.141593 / 180.0 * (a + b));\n");
	strcat(content, "		endC = 3.141593 + (3.141593 / 180.0 * (a + b + c));\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.arc(centerX, centerY, r, 3.141593, endA, false);\n");
	strcat(content, "		context.lineWidth = 10;\n");
	strcat(content, "		context.strokeStyle = 'red';\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.arc(centerX, centerY, r, endA, endB, false);\n");
	strcat(content, "		context.lineWidth = 10;\n");
	strcat(content, "		context.strokeStyle = 'yellow';\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.arc(centerX, centerY, r, endB, endC, false);\n");
	strcat(content, "		context.lineWidth = 10;\n");
	strcat(content, "		context.strokeStyle = 'green';\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "	}\n");
	strcat(content, "	function drawPointer(context, x, y, r, v) {\n");
	strcat(content, "		var centerX = x;\n");
	strcat(content, "		var centerY = y;\n");
	strcat(content, "		A = 3.141593 + (3.141593 / 180.0 * v);\n");
	strcat(content, "		context.beginPath();\n");
	strcat(content, "		context.arc(centerX, centerY, r / 2.0, A - 0.02, A + 0.02, false);\n");
	strcat(content, "		context.lineWidth = r;\n");
	strcat(content, "		context.strokeStyle = 'white';\n");
	strcat(content, "		context.stroke();\n");
	strcat(content, "	}\n");
	strcat(content, "	var canvas = document.getElementById('myCanvas');\n");
	strcat(content, "	var context = canvas.getContext('2d');\n");
	strcat(content, "	drawMeter(context, 100, 100, 70, 45, 45, 90);\n");
	sprintf(tmp_str, "	drawPointer(context, 100, 100, 70, %f);\n", ModelData.roll + 90.0);
	strcat(content, tmp_str);
	strcat(content, "	drawMeter(context, 100, 200, 70, 45, 45, 90);\n");
	sprintf(tmp_str, "	drawPointer(context, 100, 200, 70, %f);\n", ModelData.pitch + 90.0);
	strcat(content, tmp_str);
	strcat(content, "    </script>\n");
	strcat(content, "<script src=\"http://www.openlayers.org/api/OpenLayers.js\"></script><script>\n");
	strcat(content, "map = new OpenLayers.Map(\"mapdiv\");\n");
	strcat(content, "map.addLayer(new OpenLayers.Layer.OSM());\n");
	sprintf(tmp_str, "var lonLat = new OpenLayers.LonLat( %f ,%f ).transform(new OpenLayers.Projection(\"EPSG:4326\"),map.getProjectionObject());\n", ModelData.p_long, ModelData.p_lat);
	strcat(content, tmp_str);
	strcat(content, "var zoom=16;\n");
	strcat(content, "var markers = new OpenLayers.Layer.Markers( \"Markers\" );\n");
	strcat(content, "map.addLayer(markers);\n");
	strcat(content, "markers.addMarker(new OpenLayers.Marker(lonLat));\n");
	strcat(content, "map.setCenter (lonLat, zoom);\n");
//	strcat(content, "setTimeout(xmlhttpGet, 5000);\n");
	strcat(content, "</script></body></html>\n");

	sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/html");
	write(fd, buffer, strlen(buffer));
	write(fd, content, strlen(content));

}

void webserv_child (int fd, int hit) {
	long ret;
	char buffer[BUFSIZE + 1];
	char content[BUFSIZE + 1];
	char tmp_str[BUFSIZE + 1];

	SDL_Delay(10);

	int size = 0;
	ret = read(fd, buffer + size, BUFSIZE);

	printf("###########################\n");
	printf("webserv:\n");
	printf("###########################\n");
	printf("%s\n", buffer);
	printf("###########################\n");

	if (strncmp(buffer,"POST ", 5) == 0 || strncmp(buffer,"post ", 5) == 0) {
		if (strncmp(buffer + 5,"/setdata", 8) == 0) {



			int n = 0;
			int l = 0;
			int l2 = 0;
			int start = 0;
			for (n = 5; n < strlen(buffer); n++) {
				if (buffer[n] == '\n') {
					strncpy(tmp_str, buffer + n + 1, 99);
					tmp_str[99] = 0;
					l2 = strlen(tmp_str);
					for (l = 0; l < l2; l++) {
						if (tmp_str[l] == '=') {
							tmp_str[l] = 0;
							start = l + 1;
						} else if (tmp_str[l] == '\n') {
							tmp_str[l] = 0;
							break;
						}
					}
					printf("## %s ### %s (%i)##\n", tmp_str, tmp_str + start, start);

					if (strcmp(tmp_str, "name") == 0) {
						strcpy(ModelData.name, tmp_str + start);
					} else if (strcmp(tmp_str, "image") == 0) {
						strcpy(ModelData.image, tmp_str + start);
					} else if (strcmp(tmp_str, "modeltype") == 0) {
						ModelData.modeltype = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "teletype") == 0) {
						ModelData.teletype = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "teledevice") == 0) {
						strcpy(ModelData.teledevice, tmp_str + start);
					} else if (strcmp(tmp_str, "telebaud") == 0) {
						ModelData.telebaud = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "telebtaddr") == 0) {
						strcpy(ModelData.telebtaddr, tmp_str + start);
					} else if (strcmp(tmp_str, "telebtpin") == 0) {
						strcpy(ModelData.telebtpin, tmp_str + start);
					} else if (strcmp(tmp_str, "mode") == 0) {
						ModelData.mode = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "status") == 0) {
						ModelData.status = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "armed") == 0) {
						ModelData.armed = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "heartbeat") == 0) {
						ModelData.heartbeat = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "heartbeat_rc") == 0) {
						ModelData.heartbeat_rc = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "found_rc") == 0) {
						ModelData.found_rc = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "p_lat") == 0) {
						ModelData.p_lat = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "p_long") == 0) {
						ModelData.p_long = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "p_alt") == 0) {
						ModelData.p_alt = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "alt_offset") == 0) {
						ModelData.alt_offset = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "baro") == 0) {
						ModelData.baro = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "pitch") == 0) {
						ModelData.pitch = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "roll") == 0) {
						ModelData.roll = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "yaw") == 0) {
						ModelData.yaw = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "speed") == 0) {
						ModelData.speed = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "voltage") == 0) {
						ModelData.voltage = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "load") == 0) {
						ModelData.load = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "gpsfix") == 0) {
						ModelData.gpsfix = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "numSat") == 0) {
						ModelData.numSat = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio1") == 0) {

printf("### set radio1: %i ##\n", atoi(tmp_str + start));
						ModelData.radio[0] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio2") == 0) {
						ModelData.radio[1] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio3") == 0) {
						ModelData.radio[2] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio4") == 0) {
						ModelData.radio[3] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio5") == 0) {
						ModelData.radio[4] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio6") == 0) {
						ModelData.radio[5] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio7") == 0) {
						ModelData.radio[6] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio8") == 0) {
						ModelData.radio[7] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio9") == 0) {
						ModelData.radio[8] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio10") == 0) {
						ModelData.radio[9] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio11") == 0) {
						ModelData.radio[10] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio12") == 0) {
						ModelData.radio[11] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio13") == 0) {
						ModelData.radio[12] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio14") == 0) {
						ModelData.radio[13] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio15") == 0) {
						ModelData.radio[14] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "radio16") == 0) {
						ModelData.radio[15] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "acc_x") == 0) {
						ModelData.acc_x = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "acc_y") == 0) {
						ModelData.acc_y = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "acc_z") == 0) {
						ModelData.acc_z = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "gyro_x") == 0) {
						ModelData.gyro_x = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "gyro_y") == 0) {
						ModelData.gyro_y = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "gyro_z") == 0) {
						ModelData.gyro_z = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "rssi_rx") == 0) {
						ModelData.rssi_rx = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "rssi_tx") == 0) {
						ModelData.rssi_tx = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "voltage_rx") == 0) {
						ModelData.voltage_rx = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "voltage_zell1") == 0) {
						ModelData.voltage_zell[0] = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "voltage_zell2") == 0) {
						ModelData.voltage_zell[1] = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "voltage_zell3") == 0) {
						ModelData.voltage_zell[2] = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "voltage_zell4") == 0) {
						ModelData.voltage_zell[3] = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "voltage_zell5") == 0) {
						ModelData.voltage_zell[4] = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "voltage_zell6") == 0) {
						ModelData.voltage_zell[5] = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "temperature1") == 0) {
						ModelData.temperature[0] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "temperature2") == 0) {
						ModelData.temperature[1] = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "ampere") == 0) {
						ModelData.ampere = atof(tmp_str + start);
					} else if (strcmp(tmp_str, "sysid") == 0) {
						ModelData.sysid = atoi(tmp_str + start);
					} else if (strcmp(tmp_str, "compid") == 0) {
						ModelData.compid = atoi(tmp_str + start);
					}



				}
			}



			sprintf(content, "OK\n");
			sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/plain");
			write(fd, buffer, strlen(buffer));
			write(fd, content, strlen(content));


		} else {
			sprintf(content, "UNKNOWN\n");
			sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/plain");
			write(fd, buffer, strlen(buffer));
			write(fd, content, strlen(content));
		}
	} else if (strncmp(buffer,"GET ", 4) == 0 || strncmp(buffer,"get ", 4) == 0) {
		if (strncmp(buffer + 4,"/modeldata", 10) == 0) {
			webserv_child_dump_modeldata(fd);
		} else if (strncmp(buffer + 4,"/screenshot", 11) == 0) {
			webserv_child_dump_screen(fd);
		} else if (strncmp(buffer + 4,"/hud", 4) == 0) {
			webserv_child_draw_hud(fd);
		} else if (strncmp(buffer + 4,"/map", 4) == 0) {
			webserv_child_show_map(fd);
		} else if (strncmp(buffer + 4,"/lonlat", 7) == 0) {
			webserv_child_show_lonlat(fd);
		} else if (strncmp(buffer + 4,"/setdata", 8) == 0) {
			webserv_child_show_lonlat(fd);
		} else {
			sprintf(content, "UNKNOWN\n");
			sprintf(buffer,"HTTP/1.1 200 OK\nServer: multigcs\nContent-Length: %ld\nConnection: close\nContent-Type: %s\n\n", strlen(content), "text/plain");
			write(fd, buffer, strlen(buffer));
			write(fd, content, strlen(content));
		}
	}

	close(fd);
	return;
}

int webserv_thread (void *data) {
	int pid;
	int listenfd;
	int socketfd;
	int hit;
	socklen_t length;
	static struct sockaddr_in cli_addr;
	static struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(8080);

	if ((listenfd = socket(AF_INET, SOCK_STREAM,0)) < 0) {
		return(1);
	}
	if (bind(listenfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
		return(1);
	}
	if (listen(listenfd,64) < 0) {
		return(1);
	}
	for (hit = 1;; hit++) {
		length = sizeof(cli_addr);
		if ((socketfd = accept(listenfd, (struct sockaddr *)&cli_addr, &length)) < 0) {
			return(1);
		}

printf("incomming: %i\n", hit);

		webserv_child(socketfd,hit);

/*
		if ((pid = fork()) < 0) {
			return(1);
		} else {
			if (pid == 0) {
				close(listenfd);
				webserv_child(socketfd,hit);
			} else {
				close(socketfd);
			}
		}

*/
	}

	printf("** exit thread webserv\n");
	return(0);
}

void webserv_init (void) {
	printf("Init Webserv-Thread\n");
	thread_webserv = SDL_CreateThread(webserv_thread, NULL);
	if (thread_webserv == NULL) {
		fprintf(stderr, "Webserv-Thread konnte nicht gestartet werden: %s\n", SDL_GetError());
	}
}

void webserv_exit (void) {
	printf("* webserv-thread kill\n");
	SDL_KillThread(thread_webserv);
}
