#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct Device {
    char name[30];
    int type;

    union {
        float temperature;
        int pressure;
        float voltage;
    } reading;
};


void process_device(struct Device *device, void (*callback)(struct Device*)) {
    callback(device);
}



void temperature_monitor(struct Device *device) {
    printf("Device: %s | Temperature: %.2f °C\n",
           device->name, device->reading.temperature);
}


void pressure_monitor(struct Device *device) {
    printf("Device: %s | Pressure: %d Pa\n",
           device->name, device->reading.pressure);
}


void battery_monitor(struct Device *device) {
    printf("Device: %s | Battery Voltage: %.2f V\n",
           device->name, device->reading.voltage);
}



void device_status(struct Device *device) {

    if (device->type == 0 && device->reading.temperature > 50)
        printf("WARNING: %s temperature too high!\n", device->name);

    if (device->type == 1 && device->reading.pressure > 1500)
        printf("WARNING: %s pressure too high!\n", device->name);

    if (device->type == 2 && device->reading.voltage < 3.3)
        printf("WARNING: %s battery low!\n", device->name);
}



int main() {

    srand(time(NULL));

    int device_count = 10;

    struct Device *devices = malloc(device_count * sizeof(struct Device));

    if (devices == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }



    for (int i = 0; i < device_count; i++) {

        sprintf(devices[i].name, "Device_%d", i + 1);

        devices[i].type = rand() % 3;

        if (devices[i].type == 0) {
            devices[i].reading.temperature = (rand() % 800) / 10.0;
        }

        else if (devices[i].type == 1) {
            devices[i].reading.pressure = rand() % 2000;
        }

        else {
            devices[i].reading.voltage = (rand() % 500) / 100.0;
        }

    }


    printf("\n=== Device Monitoring Simulation ===\n\n");



    struct Device *ptr = devices;

    for (int i = 0; i < device_count; i++) {

        if (ptr->type == 0) {
            process_device(ptr, temperature_monitor);
        }

        else if (ptr->type == 1) {
            process_device(ptr, pressure_monitor);
        }

        else {
            process_device(ptr, battery_monitor);
        }

        process_device(ptr, device_status);

        ptr++;
    }



    free(devices);

    return 0;
}