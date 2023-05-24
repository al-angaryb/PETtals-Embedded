#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/http_client.h"

#define WIFI_SSID "NETGEAR60"
#define WIFI_PASSWORD "smilingviolin151"

//#define HOST "http://10.0.0.58/login"
//#define PORT 80
#define MAX_PETS 10
#define MAX_ID_PER_PET 10

char petBuff[1000];
uint32_t country = CYW43_COUNTRY_USA;
uint32_t auth = CYW43_AUTH_WPA2_MIXED_PSK;


typedef struct {
    char name[50];
    char ids[MAX_ID_PER_PET][50];
    char schedule[500];
    int id_count;
}petData;

typedef struct {
    int day;
    char time[6];
} DayAndTime;

typedef struct {
    petData* pets;
    int pet_count;
} Data;

petData pets[MAX_PETS];
Data input;

bool can_go_outside(petData* pets, int pet_count, char* time, int current_day_of_week, char* tag_id) {
    // Assuming time is in "HH:MM" format
    int current_hour, current_minute;
    sscanf(time, "%d:%d", &current_hour, &current_minute);
    int time_now = current_hour * 60 + current_minute;

    // Find the pet by tag id
    for (int i = 0; i < pet_count; i++) {
        for (int j = 0; j < pets[i].id_count; j++) {
            if (strcmp(pets[i].ids[j], tag_id) == 0) {
            // Found the pet, now parse its schedule
            int start_hour, start_minute, end_hour, end_minute;
            bool days[7];
            sscanf(pets[i].schedule, "{TimeOfDay(%d:%d) TimeOfDay(%d:%d) %d %d %d %d %d %d %d }",
            &start_hour, &start_minute, &end_hour, &end_minute,
            &days[0], &days[1], &days[2], &days[3],
            &days[4], &days[5], &days[6]);

            int start_time = start_hour * 60 + start_minute;
            int end_time = end_hour * 60 + end_minute;

                if (time_now >= start_time && time_now <= end_time && days[current_day_of_week]) {
                    return true;
                }
            }
        }
    }
    return false;
}

DayAndTime parse_day_and_time(const char* str) {
    DayAndTime result;
    memset(&result, 0, sizeof(DayAndTime));

    // Parse the day of the week and time
    sscanf(str, "%d %5s", &result.day, result.time);

    return result;
}

Data build_from_json(char data[1000]) {
    Data output;
    petData pets[10]; // assuming max 10 pets
    int pet_count = 0;
    int schedule_line = 0;

    char* line = strtok(data, "\n");
    while(line) {
        if (strstr(line, "Pet Name:") != NULL) {
            sscanf(line, "Pet Name: %s", pets[pet_count].name);
            pets[pet_count].id_count = 0;
            schedule_line = 0; // reset the schedule_line flag
        }
        else if (strstr(line, "Pet ID:") != NULL) {
            sscanf(line, "Pet ID: %s", pets[pet_count].ids[pets[pet_count].id_count]);
            pets[pet_count].id_count++;
        }
        else if (strstr(line, "Pet Schedules:") != NULL) {
            schedule_line = 1; // set the schedule_line flag
        }
        else if (schedule_line) {
            // If the schedule_line flag is set, this line contains the schedule
            strncpy(pets[pet_count].schedule, line, sizeof(pets[pet_count].schedule) - 1);
            schedule_line = 0; // reset the schedule_line flag
        }
        else if (strstr(line, "------------------") != NULL) {
            pet_count++;
        }
        line = strtok(NULL, "\n");
    }
    output.pets = pets;
    output.pet_count = pet_count;
    return output;  
}


int wifi_setup(const char* hostname, ip_addr_t *ip, ip_addr_t *mask, ip_addr_t *gw){
    if(cyw43_arch_init_with_country(country)){
        return 1;
    }
    cyw43_arch_enable_sta_mode();
    if(hostname != NULL){
        netif_set_hostname(netif_default, hostname);
    }
    if(cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD, auth)){
        return 2;
    }
    int flashrate = 1000;
    int status = CYW43_LINK_UP + 1;
    while(status >= 0 && status != CYW43_LINK_UP){
        int new_status = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);
        if(new_status != status){
            status = new_status;
            flashrate = flashrate/(status+1);
            printf("connect status: %d %d\n", status, flashrate);
        }
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(flashrate);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        if(status < 0){
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        }else{
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            if(ip != NULL){
                netif_set_ipaddr(netif_default, ip);
            }if(mask != NULL){
                netif_set_netmask(netif_default, mask);
            }if(gw != NULL){
                netif_set_gw(netif_default, gw);
            }
        }
    }
    return status; 
}

void result(void *arg, httpc_result_t httpc_result, u32_t rx_content_len, u32_t srv_res, err_t err)
{
    printf("transfer complete\n");
    printf("local result=%d\n", httpc_result);
    printf("http result=%d\n", srv_res);
}

err_t headers(httpc_state_t *connection, void *arg, struct pbuf *hdr, u16_t hdr_len, u32_t content_len)
{
    printf("Headers recieved\n");
    printf("content length=%d\n", content_len);
    printf("header length %d\n", hdr_len);

    pbuf_copy_partial(hdr, petBuff, hdr->tot_len, 0);
    printf("headers \n");
    printf("%s ", petBuff);
    return ERR_OK;
}

err_t body(void *arg, struct altcp_pcb *conn, struct pbuf *p, err_t err)
{
    printf("body \n");
    pbuf_copy_partial(p, petBuff, p->tot_len, 0);
    
    printf("%s \n", petBuff);

    input = build_from_json(petBuff);
    petData* pets = input.pets;
    int pet_count = input.pet_count;


    return ERR_OK;
}

int main()
{
    stdio_init_all();

    wifi_setup("PETTALS", NULL, NULL, NULL);
    uint16_t port = 8880;
    httpc_connection_t settings;
    settings.result_fn = result;
    settings.headers_done_fn = headers;

    err_t err = httpc_get_file_dns(
        "10.0.0.58",
        8880,
        "/login",
        &settings,
        body,
        NULL,
        NULL);

    printf("status %d \n", err);

    sleep_ms(5000);
    
    while (true)
    {
        sleep_ms(500);
    }

}