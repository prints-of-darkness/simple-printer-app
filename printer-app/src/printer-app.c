#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct {
	char* printer_resolution;
	char* print_darkness;
	char* document_format;
	char* media_col;
	char* printer_darkness;
	char* print_speed;
	char* label_mode;
	char* color_mode;
}attr;

//static const char* const ipp_preason_strings[] =
//{					// Strings for each bit
//  // "none" is implied for no bits set
//  "other",
//  "cover-open",
//  "input-tray-missing",
//  "marker-supply-empty",
//  "marker-supply-low",
//  "marker-waste-almost-full",
//  "marker-waste-full",
//  "media-empty",
//  "media-jam",
//  "media-low",
//  "media-needed",
//  "moving-to-paused",
//  "paused",
//  "spool-area-full",
//  "toner-empty",
//  "toner-low"
//};

int populate_attr(attr *s);
int print_attr(attr *s);

int main(int argc, char *argv[])
{
	//system("/home/matt/Documents/github/ippeveprinter/helper-scripts/log_env.sh");

	if(argc != 2)
		return 1; //check for one arg

	attr MyAttr;
	if(populate_attr(&MyAttr) != 0)
		return 1;

	if(print_attr(&MyAttr) != 0)
		return 1;

    //char message[1024];

    // Example Paper Jam (Error)
//    snprintf(message, sizeof(message),
//             "ATTR: printer-alert="
//             "{"
//             "alert-code=1001,"
//             "alert-severity=error,"
//             "alert-description='Paper Jam in Tray 1',"
//             "alert-location='Tray 1'"
//             "}\n");
    //fprintf(stderr, "%s", message);
	fprintf(stderr, "STATE: %s\n", "cover-open");
    fflush(stderr);

	sleep(4);

//    snprintf(message, sizeof(message),
//             "ATTR: printer-alert="
//             "{"
//             "alert-code=0000,"
//             "alert-severity=none,"
//             "alert-description=none,"
//             "alert-location=none"
//             "}\n");
    //fprintf(stderr, "%s", message);
	fprintf(stderr, "STATE: -%s\n", "cover-open");
	fflush(stderr);

	sleep(4);

	return 1; //abort

	return 0;
}

int populate_attr(attr *s)
{
	if((s->printer_resolution = getenv("IPP_PRINTER_RESOLUTION")) == NULL) {
		if((s->printer_resolution = getenv("IPP_PRINTER_RESOLUTION_DEFAULT")) == NULL) {
			fprintf(stderr, "INFO:Resolution not set\n");
			return 1;
		}
	}

	if((s->print_darkness = getenv("IPP_PRINT_DARKNESS")) == NULL) {
		if((s->print_darkness = getenv("IPP_PRINT_DARKNESS_DEFAULT")) == NULL) {
			fprintf(stderr, "INFO:Print Darkness not set\n");
			return 1;
		}
	}

	if((s->document_format = getenv("IPP_DOCUMENT_FORMAT_SUPPLIED")) == NULL) {
		if((s->document_format = getenv("IPP_DOCUMENT_FORMAT_DEFAULT")) == NULL) {
			fprintf(stderr, "INFO:Document Format not set\n");
			return 1;
		}
	}

	if((s->color_mode = getenv("IPP_PRINT_COLOR_MODE")) == NULL) {
		if((s->color_mode = getenv("IPP_PRINT_COLOR_MODE_DEFAULT")) == NULL) {
			fprintf(stderr, "INFO:Color Mode not set\n");
			return 1;
		}
	}

	if((s->media_col = getenv("IPP_MEDIA_COL")) == NULL) {
		if((s->media_col = getenv("IPP_MEDIA_COL_DEFAULT")) == NULL) {
			fprintf(stderr, "INFO:Media Col not set\n");
			return 1;
		}
	}

	if((s->printer_darkness = getenv("IPP_PRINTER_DARKNESS_CONFIGURED")) == NULL) {
		if((s->printer_darkness = getenv("IPP_PRINTER_DARKNESS_DEFAULT")) == NULL) {
			fprintf(stderr, "INFO:Printer Darkness not set\n");
			return 1;
		}
	}

	if((s->print_speed = getenv("IPP_PRINT_SPEED")) == NULL) {
		if((s->print_speed = getenv("IPP_PRINT_SPEED_DEFAULT")) == NULL) {
			fprintf(stderr, "INFO:Print Speed not set\n");
			return 1;
		}
	}

	if((s->label_mode = getenv("IPP_LABEL_MODE_CONFIGURED")) == NULL) {
		if((s->label_mode = getenv("IPP_LABEL_MODE_DEFAULT")) == NULL) {
			fprintf(stderr, "INFO:Label Mode not set\n");
			return 1;
		}
	}

	fflush(stderr);
	return 0;
}

int print_attr(attr *s)
{
	fprintf(stderr, "INFO:Document format: %s\n", s->document_format);
	fprintf(stderr, "INFO:Label mode: %s\n", s->label_mode);
	fprintf(stderr, "INFO:Media col: %s\n", s->media_col);
	fprintf(stderr, "INFO:Print darkness: %s\n", s->print_darkness);
	fprintf(stderr, "INFO:Print speed: %s\n", s->print_speed);
	fprintf(stderr, "INFO:Printer darkness: %s\n", s->printer_darkness);
	fprintf(stderr, "INFO:Printer resolution: %s\n", s->printer_resolution);
	fprintf(stderr, "INFO:Color mode: %s\n", s->color_mode);

	return 0;
}

