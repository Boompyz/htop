#include "TempMeter.h"
#include "CRT.h"

int TempMeter_attributes[] = {
    TEMP
};

static void TempMeter_updateValues(Meter *this, char* buffer, int len) {
    FILE *tempFile = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    double val;
    fscanf(tempFile, "%lf", &val);
    xSnprintf(buffer, len, "%.4lf", val/1000);
    fseek(tempFile, 0, SEEK_SET);
    fclose(tempFile);
}

MeterClass TempMeter_class = {
    .super = {
        .extends = Class(Meter),
        .delete = Meter_delete
    },
    .updateValues = TempMeter_updateValues,
    .defaultMode = TEXT_METERMODE,
    .maxItems = 1,
    .total = 100.0,
    .attributes = TempMeter_attributes,
    .name = "Temp",
    .uiName = "Temp",
    .caption = "Temp: "
};
