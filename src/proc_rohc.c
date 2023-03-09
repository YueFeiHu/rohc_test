#include "proc_rohc.h"
#include "comp.h"
#include "decomp.h"
#include <string.h>
#define MAX_INPUT_LEN 1000
#define VAR_LENGTH 50

static struct sc_rohc *compressor = NULL;
static struct sd_rohc *decompressor = NULL;

int get_token(char *dest, char *src, int *ppos, int len, int *eof, int mode)
{
	int ofs = 0;
	src += *ppos;
	while (*src != 0 && *src != '\n' && *src != '=' && ofs + 1 < VAR_LENGTH && *ppos < len)
	{
		*dest = *src;
		dest++;
		src++;
		ppos[0]++;
		ofs++;
	}

	*dest = 0;

	switch (*src)
	{
	case 0:
		*eof = 1;
		break;
	case '\n':
		if (mode == 0)
			return 0;
		ppos[0]++;
		break;
	case '=':
		if (mode == 1)
			return 0;
		ppos[0]++;
		break;
	}

	if (*ppos >= len)
		*eof = 1;

	return 1;
}

static void rohc_parser(char *buffer, int len)
{
	int pos = 0; //, value;
	int eof = 0;
	char var[VAR_LENGTH], val[VAR_LENGTH];

	while (!eof)
	{
		if (!get_token(var, buffer, &pos, len, &eof, 0))
		{
			rohc_debugf(2, "rohc_proc_parser: get_token 1 failed\n");
			return;
		}

		if (eof)
		{
			rohc_debugf(2, "rohc_proc_parser: eof failed\n");
			break;
		}

		if (!get_token(val, buffer, &pos, len, &eof, 1))
		{
			rohc_debugf(2, "rohc_proc_parser: get_token 2 failed\n");
			return;
		}

		rohc_debugf(0, "rohc_proc_parser: '%s'='%s'\n", var, val);
		if (compressor && decompressor)
		{
			if (strcmp(var, "MRRU") == 0)
			{
				// anropa motsvarande funktion
				// mrru, segmentering, aktiva profiler.. max_cid, large_cid, feedback_freq, connection_type
				rohc_c_set_mrru(compressor, simple_strtol(val, 0, 10));
			}
			else if (strcmp(var, "MAX_CID") == 0)
			{
				rohc_c_set_max_cid(compressor, simple_strtol(val, 0, 10));
			}
			else if (strcmp(var, "LARGE_CID") == 0)
			{
				rohc_c_set_large_cid(compressor, simple_strtol(val, 0, 10));
			}
			else if (strcmp(var, "CONNECTION_TYPE") == 0)
			{
				rohc_c_set_connection_type(compressor, simple_strtol(val, 0, 10));
			}
			else if (strcmp(var, "FEEDBACK_FREQ") == 0)
			{
				usergui_interactions(decompressor, simple_strtol(val, 0, 10));
			}
			else if (strcmp(var, "ROHC_ENABLE") == 0)
			{
				rohc_debugf(0, "rohc_enable\n");

				if (strcmp(val, "YES") == 0)
				{
					rohc_debugf(0, "rohc_enable=yes\n");
					// enable compression..
					rohc_c_set_enable(compressor, 1);
				}
				else if (strcmp(val, "NO") == 0)
				{
					rohc_debugf(0, "rohc_enable=no\n");
					// disable compression..
					rohc_c_set_enable(compressor, 0);
				}
			}
		}
		else
		{
			rohc_debugf(0, "Tried to set value in rohc, but rohc is not allocated yet\n");
		}
	}
}

void rohc_proc_set(struct sc_rohc *c, struct sd_rohc *d)
{
	compressor = c;
	decompressor = d;
}

int rohc_proc_init(void)
{
	rohc_debugf(1, "ROHC: ---- PROC LOADED ----\n");
	return 0;
}

void rohc_proc_remove(void)
{
	rohc_debugf(1, "ROHC: ---- PROC REMOVED ----\n");
}
