#include <stdio.h>

#include "TinyGPS++.h"

#include "gpgga.h"
#include "gpgll.h"
#include "gpgsa.h"
#include "gpgsv.h"
#include "gprmc.h"
#include "gptxt.h"
#include "gpvtg.h"
#include "nmea.h"

void libnmea_example()
{
    char fmt_buf[32];
    nmea_s *data;

    char *start = "$GPRMC,170058.89,V,3554.928,N,08002.496,W,9.4,1.57,050521,,E*41\r\n";
    size_t length = strlen(start);

    data = nmea_parse(start, length, 0);
    if (data == NULL)
    {
        printf("Failed to parse the sentence!\n");
        printf("  Type: %.5s (%d)\n", start + 1, nmea_get_type(start));
    }
    else
    {
        if (data->errors != 0)
        {
            printf("WARN: The sentence struct contains parse errors!\n");
        }

        if (NMEA_GPGGA == data->type)
        {
            printf("GPGGA sentence\n");
            nmea_gpgga_s *gpgga = (nmea_gpgga_s *)data;
            printf("Number of satellites: %d\n", gpgga->n_satellites);
            printf("Altitude: %f %c\n", gpgga->altitude,
                   gpgga->altitude_unit);
        }

        if (NMEA_GPGLL == data->type)
        {
            printf("GPGLL sentence\n");
            nmea_gpgll_s *pos = (nmea_gpgll_s *)data;
            printf("Longitude:\n");
            printf("  Degrees: %d\n", pos->longitude.degrees);
            printf("  Minutes: %f\n", pos->longitude.minutes);
            printf("  Cardinal: %c\n", (char)pos->longitude.cardinal);
            printf("Latitude:\n");
            printf("  Degrees: %d\n", pos->latitude.degrees);
            printf("  Minutes: %f\n", pos->latitude.minutes);
            printf("  Cardinal: %c\n", (char)pos->latitude.cardinal);
            strftime(fmt_buf, sizeof(fmt_buf), "%H:%M:%S", &pos->time);
            printf("Time: %s\n", fmt_buf);
        }

        if (NMEA_GPRMC == data->type)
        {
            printf("GPRMC sentence\n");
            nmea_gprmc_s *pos = (nmea_gprmc_s *)data;
            printf("Longitude:\n");
            printf("  Degrees: %d\n", pos->longitude.degrees);
            printf("  Minutes: %f\n", pos->longitude.minutes);
            printf("  Cardinal: %c\n", (char)pos->longitude.cardinal);
            printf("Latitude:\n");
            printf("  Degrees: %d\n", pos->latitude.degrees);
            printf("  Minutes: %f\n", pos->latitude.minutes);
            printf("  Cardinal: %c\n", (char)pos->latitude.cardinal);
            strftime(fmt_buf, sizeof(fmt_buf), "%d %b %T %Y", &pos->date_time);
            printf("Date & Time: %s\n", fmt_buf);
            printf("Speed, in Knots: %f\n", pos->gndspd_knots);
            printf("Track, in degrees: %f\n", pos->track_deg);
            printf("Magnetic Variation:\n");
            printf("  Degrees: %f\n", pos->magvar_deg);
            printf("  Cardinal: %c\n", (char)pos->magvar_cardinal);
            double adjusted_course = pos->track_deg;
            if (NMEA_CARDINAL_DIR_EAST == pos->magvar_cardinal)
            {
                adjusted_course -= pos->magvar_deg;
            }
            else if (NMEA_CARDINAL_DIR_WEST == pos->magvar_cardinal)
            {
                adjusted_course += pos->magvar_deg;
            }
            else
            {
                printf("Invalid Magnetic Variation Direction!\n");
            }

            printf("Adjusted Track (heading): %f\n", adjusted_course);
        }

        if (NMEA_GPGSA == data->type)
        {
            nmea_gpgsa_s *gpgsa = (nmea_gpgsa_s *)data;

            printf("GPGSA Sentence:\n");
            printf("  Mode: %c\n", gpgsa->mode);
            printf("  Fix:  %d\n", gpgsa->fixtype);
            printf("  PDOP: %.2lf\n", gpgsa->pdop);
            printf("  HDOP: %.2lf\n", gpgsa->hdop);
            printf("  VDOP: %.2lf\n", gpgsa->vdop);
        }

        if (NMEA_GPGSV == data->type)
        {
            nmea_gpgsv_s *gpgsv = (nmea_gpgsv_s *)data;

            printf("GPGSV Sentence:\n");
            printf("  Num: %d\n", gpgsv->sentences);
            printf("  ID:  %d\n", gpgsv->sentence_number);
            printf("  SV:  %d\n", gpgsv->satellites);
            printf("  #1:  %d %d %d %d\n", gpgsv->sat[0].prn, gpgsv->sat[0].elevation, gpgsv->sat[0].azimuth, gpgsv->sat[0].snr);
            printf("  #2:  %d %d %d %d\n", gpgsv->sat[1].prn, gpgsv->sat[1].elevation, gpgsv->sat[1].azimuth, gpgsv->sat[1].snr);
            printf("  #3:  %d %d %d %d\n", gpgsv->sat[2].prn, gpgsv->sat[2].elevation, gpgsv->sat[2].azimuth, gpgsv->sat[2].snr);
            printf("  #4:  %d %d %d %d\n", gpgsv->sat[3].prn, gpgsv->sat[3].elevation, gpgsv->sat[3].azimuth, gpgsv->sat[3].snr);
        }

        if (NMEA_GPTXT == data->type)
        {
            nmea_gptxt_s *gptxt = (nmea_gptxt_s *)data;

            printf("GPTXT Sentence:\n");
            printf("  ID: %d %d %d\n", gptxt->id_00, gptxt->id_01, gptxt->id_02);
            printf("  %s\n", gptxt->text);
        }

        if (NMEA_GPVTG == data->type)
        {
            nmea_gpvtg_s *gpvtg = (nmea_gpvtg_s *)data;

            printf("GPVTG Sentence:\n");
            printf("  Track [deg]:   %.2lf\n", gpvtg->track_deg);
            printf("  Speed [kmph]:  %.2lf\n", gpvtg->gndspd_kmph);
            printf("  Speed [knots]: %.2lf\n", gpvtg->gndspd_knots);
        }

        nmea_free(data);
    }
}

TinyGPSPlus gps;

void displayInfo()
{
    printf("Location: ");
    if (gps.location.isValid())
    {
        printf("%f", gps.location.lat());
        printf(",");
        printf("%f", gps.location.lng());
    }
    else
    {
        printf("INVALID");
    }

    printf("  Date/Time: ");
    if (gps.date.isValid())
    {
        printf("%u", gps.date.month());
        printf("/");
        printf("%u", gps.date.day());
        printf("/");
        printf("%u", gps.date.year());
    }
    else
    {
        printf("INVALID");
    }

    printf(" ");
    if (gps.time.isValid())
    {
        if (gps.time.hour() < 10)
            printf("0");
        printf("%u", gps.time.hour());
        printf(":");
        if (gps.time.minute() < 10)
            printf("0");
        printf("%u", gps.time.minute());
        printf(":");
        if (gps.time.second() < 10)
            printf("0");
        printf("%u", gps.time.second());
        printf(".");
        if (gps.time.centisecond() < 10)
            printf("0");
        printf("%u", gps.time.centisecond());
    }
    else
    {
        printf("INVALID");
    }

    printf("\n");
}

void tinygpsplus_example()
{
    const char *gpsStream =
        "$GPRMC,045103.000,A,3014.1984,N,09749.2872,W,0.67,161.46,030913,,,A*7C\r\n"
        "$GPGGA,045104.000,3014.1985,N,09749.2873,W,1,09,1.2,211.6,M,-22.5,M,,0000*62\r\n"
        "$GPRMC,045200.000,A,3014.3820,N,09748.9514,W,36.88,65.02,030913,,,A*77\r\n"
        "$GPGGA,045201.000,3014.3864,N,09748.9411,W,1,10,1.2,200.8,M,-22.5,M,,0000*6C\r\n"
        "$GPRMC,045251.000,A,3014.4275,N,09749.0626,W,0.51,217.94,030913,,,A*7D\r\n"
        "$GPGGA,045252.000,3014.4273,N,09749.0628,W,1,09,1.3,206.9,M,-22.5,M,,0000*6F\r\n";

    while (*gpsStream)
        if (gps.encode(*gpsStream++))
            displayInfo();
}

extern "C" void app_main(void)
{
    libnmea_example();
    tinygpsplus_example();
}
