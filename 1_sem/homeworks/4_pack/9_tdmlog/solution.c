#include <limits.h>
#include <stdio.h>
#include <string.h>

struct VideoData
{
	char file_name[256];
	int total_frames, total_decode_time;
	int last_decode_time;
	int min_decode_time, max_decode_time;
	double avg_decode_time;
	int start_time, end_time;
};

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

void collect_statistics(char *line, struct VideoData *video_data, int *video_playing)
{
	int sec, millisec, microsec;

	if (strstr(line, "Opened file"))
	{
		char *start = strstr(line, "Opened file") + strlen("Opened file");
		while (*start == ' ')
		{
			start++;
		}

		char *newline = strchr(start, '\n');
		if (newline)
		{
			*newline = '\0';
		}

		strcpy(video_data->file_name, start);

		video_data->total_frames = 0;
		video_data->total_decode_time = 0;
		video_data->last_decode_time = 0;
		video_data->min_decode_time = INT_MAX;
		video_data->max_decode_time = INT_MIN;
		video_data->start_time = 0;
		video_data->end_time = 0;

	}
	else if (*video_playing && strstr(line, "Packet decoded"))
	{
		sscanf(strstr(line, "Packet decoded"),
			"Packet decoded in %d.%d ms",
			&millisec, &microsec);

		video_data->last_decode_time = millisec * 1000 + microsec;

	}
	else if (*video_playing && strstr(line, "Converted to RGBA"))
	{
		sscanf(strstr(line, "Converted to RGBA"), "Converted to RGBA in %d.%d ms",
				&millisec, &microsec);

		video_data->total_frames++;

		int converted_time = millisec * 1000 + microsec;

		converted_time += video_data->last_decode_time;
		video_data->total_decode_time += converted_time;

		video_data->min_decode_time = min(video_data->min_decode_time, converted_time);
		video_data->max_decode_time = max(video_data->max_decode_time, converted_time);

	}
	else if (strstr(line, "Decoded first frame"))
	{

		*video_playing = 1;
		sscanf(line, "%d.%d.%d", &sec, &millisec, &microsec);
		video_data->start_time = (sec * 1000 + millisec) * 1000 + microsec;

	}
	else if (strstr(line, "Video ended"))
	{

		sscanf(line, "%d.%d.%d", &sec, &millisec, &microsec);
		video_data->end_time = (sec * 1000 + millisec) * 1000 + microsec;

		video_data->avg_decode_time = (double) video_data->total_decode_time
				/ video_data->total_frames;

		printf("Video \"%s\":\n",
			video_data->file_name);
		printf("  Total frames: %d\n",
			video_data->total_frames);
		printf("  Total decode time: %.3f ms\n",
				video_data->total_decode_time / 1000.0);
		printf("  Actual playback time: %.3f ms\n",
				(video_data->end_time - video_data->start_time) / 1000.0);
		printf("  Min/avg/max decode time: %.3f/%.3f/%.3f ms\n\n",
			video_data->min_decode_time / 1000.0,
			video_data->avg_decode_time / 1000.0,
			video_data->max_decode_time / 1000.0);

		*video_playing = 0;
	}
}

int main()
{
	/* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	struct VideoData video_data;
	char line[1024];
	int video_playing = 0;

	while (fgets(line, sizeof(line), stdin))
	{
		collect_statistics(line, &video_data, &video_playing);
	}

	/* Close the file streams for input and output */
	fclose(stdin);
	fclose(stdout);

	return 0;
}