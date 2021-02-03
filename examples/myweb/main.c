// Copyright (c) 2020 Cesanta Software Limited
// All rights reserved

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "mongoose.h"

void stopWpa()
{
   system("sudo pkill -f wpa_supplicant");
}
void createCfgFile(char *ssid, char *pass)
{
 system("sudo chmod 666 /etc/wpa_supplicant/wpa_supplicant.conf");
 system("echo \"ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev\" > /etc/wpa_supplicant/wpa_supplicant.conf");
 system("echo \"update_config=1\" >> /etc/wpa_supplicant/wpa_supplicant.conf");
 system("echo \"country=US\r\n\" >> /etc/wpa_supplicant/wpa_supplicant.conf");
  char buf[100];
sprintf(buf, "sudo wpa_passphrase %s %s >> /etc/wpa_supplicant/wpa_supplicant.conf", ssid, pass);
printf("buf is %s\r\n", buf);
 system(buf);

  
}
void startWpa()
{
   system("sudo wpa_supplicant -B -Dnl80211,wext -iwlan0 -c/etc/wpa_supplicant/wpa_supplicant.conf &");
}

void trim (char *cs)
{
  char *p;
  size_t len = strlen(cs);
  for (p = cs + len - 1; isspace (*p); --p) /* nothing */ ;
  p[1] = '\0';
  for (p = cs; isspace (*p); ++p) /* nothing */ ;
  memmove (cs, p, len - (size_t) (p - cs) + 1);
}

int saveDTBHost(char *host, char *port, char *name, char *user, char *pass) {
  FILE *f = fopen("dtb.cfg", "w");
  if (!f) {
    printf("Error opening file\n");
    return -1;
  }
  fprintf(f, "host: %s\n", host);
  fprintf(f, "port: %s\n", port);
  fprintf(f, "database: %s\n", name);
  fprintf(f, "user: %s\n", user);
  fprintf(f, "password: %s\n", pass);
  fclose(f);
}

void getDTBCfg(char *host, char *port, char *name, char *user, char *pass) {
  FILE *f;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *pch;
  f = fopen("dtb.cfg", "r");
  if (!f) {
    printf("Error opening file\n");
    return -1;
  }
  int i = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    printf("Retrieved line of length %zu:\n", read);
    printf("line is %s", line);
    pch = strtok(line, ":");
    if (pch != NULL) {
      printf("%s\n", pch);
      switch(i)
      {
        case 0:
        pch = strtok(NULL, ":");
        trim(pch);
        printf("len of %s is %u\n", pch, strlen(pch));
        strcpy(host, pch);
        break;
        case 1:
        pch = strtok(NULL, ":");
        trim(pch);
        printf("len of %s is %u\n", pch, strlen(pch));
        strcpy(port, pch);
        break;
        case 2:
        pch = strtok(NULL, ":");
        trim(pch);
        printf("len of %s is %u\n", pch, strlen(pch));
        strcpy(name, pch);
        break;
        case 3:
        pch = strtok(NULL, ":");
        trim(pch);
        printf("len of %s is %u\n", pch, strlen(pch));
        strcpy(user, pch);
        break;
        case 4:
        pch = strtok(NULL, ":");
        trim(pch);
        printf("len of %s is %u\n", pch, strlen(pch));
        strcpy(pass, pch);
        break;
      }
      i++;
    }
    
  }

  fclose(f);
  if (line) free(line);
}

// HTTP request handler function. It implements the following endpoints:
//   /api/video1 - hangs forever, returns MJPEG video stream
//   all other URI - serves web_root/ directory
static void cb(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if (mg_http_match_uri(hm, "/demourl")) {
      char *s = "hello world";  // stringify_config(&s_config);
      printf("Get mesage demourl\r\n");
      mg_printf(c, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s\n",
                (int) strlen(s) + 1, s);
      // free(s);
    } else if (mg_http_match_uri(hm, "/getcfg")) {
      char host[50] = {0}, port[5]={0}, name[20]={0}, user[10]={0}, password[20]={0};
      printf("Got http body :\r\n");
      // printf("%.*s", (int) hm->message.len, hm->message.ptr);
      printf("%s\r\n", hm->message.ptr);
      getDTBCfg(host, port, name, user, password);
      printf("got host is: %s\r\n", host);
      printf("got port is: %s\r\n", port);
      printf("got name is: %s\r\n", name);
      printf("got user is: %s\r\n", user);
      printf("got pass is: %s\r\n", password);
      mg_http_reply(c, 200, "", "{\"host\": \"%s\", \
      \"port\": \"%s\", \
      \"database\": \"%s\", \
      \"user\": \"%s\", \
      \"password\": \"%s\" \
      }\n", host, port, name, user, password);
    }else if (mg_http_match_uri(hm, "/cfgdatabase")) {
      char cmd[100] = {0};
      printf("Got http body :\r\n");
      // printf("%.*s", (int) hm->message.len, hm->message.ptr);
      printf("%s\r\n", hm->message.ptr);
      mg_http_get_var(&hm->body, "users", cmd, 100);
      printf("got value user is: %s\r\n", cmd);
      saveDTBHost("192.168.1.2", "1234", "test", "rooot", "23434");
      
      getDTBCfg(cmd, NULL, NULL, NULL, NULL);
      printf("got host is: %s\r\n", cmd);
      mg_printf(c, "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");
      //mg_http_reply(c, 200, "", "{\"host\": \"%s\"}\n", cmd);
    } else if (mg_http_match_uri(hm, "/setwifi.asp")) {
      printf("Got http body len %d:\r\n", hm->body.len);
      
      printf("%s\r\n", hm->body.ptr);

      char ssid[50] = {0}, password[20]={0};
      int data_len;
      int ret;
      mg_http_get_var(&hm->body, "pwd", password, 100);
      printf("got value password is: %s\r\n", password);
      ret = mg_http_get_var(&hm->body, "ssid", ssid, 100);
      if(ret >= 0){
        printf("got value user is: %s\r\n", ssid);
        stopWpa();
        sleep(1);
        createCfgFile(ssid, password);
        startWpa();
      }
      mg_printf(c, "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n");
    } else if (mg_http_match_uri(hm, "/api/config/watch")) {
      c->label[0] = 'W';  // Mark ourselves as a config watcher
      mg_printf(c, "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
    } else {
      struct mg_http_serve_opts opts = {.root_dir = "web_root"};
      mg_http_serve_dir(c, ev_data, &opts);
    }
  }
}

int main(void) {
  struct mg_mgr mgr;

  mg_mgr_init(&mgr);
  mg_http_listen(&mgr, "http://0.0.0.0:8000", cb, NULL);

  for (;;) mg_mgr_poll(&mgr, 50);

  mg_mgr_free(&mgr);

  return 0;
}
