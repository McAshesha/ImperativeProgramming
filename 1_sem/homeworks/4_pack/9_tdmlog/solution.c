#include <limits.h>
#include <stdio.h>
#include <string.h>

struct VideoData
{
    char file_name[256];   // Stores the video file name
    int total_frames, total_decode_time;  // Tracks the total number of frames and the total time to decode all frames
    int last_decode_time;  // Stores the decode time of the last decoded frame
    int min_decode_time, max_decode_time;  // Stores the minimum and maximum times to decode individual frames
    double avg_decode_time;  // Stores the average time to decode a frame
    int start_time, end_time;  // Stores the start and end times of the video
};

// Helper function to return the maximum of two integers
int max(int a, int b)
{
    return a > b ? a : b;
}

// Helper function to return the minimum of two integers
int min(int a, int b)
{
    return a < b ? a : b;
}

// Function to process log lines and collect video statistics
void collect_statistics(char *line, struct VideoData *video_data, int *video_playing)
{
    int sec, millisec, microsec;

    // If the log indicates the opening of a new video file
    if (strstr(line, "Opened file"))
    {
        // Extract the file name from the log line
        char *start = strstr(line, "Opened file") + strlen("Opened file");
        while (*start == ' ')
        {  // Skip any leading spaces
            start++;
        }

        char *newline = strchr(start, '\n');  // Find the newline character
        if (newline)
        {
            *newline = '\0';  // Replace it with a null terminator to end the string
        }

        strcpy(video_data->file_name, start);  // Store the file name

        // Initialize video data fields
        video_data->total_frames = 0;
        video_data->total_decode_time = 0;
        video_data->last_decode_time = 0;
        video_data->min_decode_time = INT_MAX;
        video_data->max_decode_time = INT_MIN;
        video_data->start_time = 0;
        video_data->end_time = 0;

    }    // If a video is playing and a frame is decoded
    else if (*video_playing && strstr(line, "Packet decoded"))
    {
        // Extract the time taken to decode the packet
        sscanf(strstr(line, "Packet decoded"), "Packet decoded in %d.%d ms", &millisec, &microsec);
        video_data->last_decode_time = millisec * 1000 + microsec;  // Convert time to microseconds

    }    // If a frame is converted to RGBA format
    else if (*video_playing && strstr(line, "Converted to RGBA"))
    {
        // Extract the time taken to convert to RGBA
        sscanf(strstr(line, "Converted to RGBA"), "Converted to RGBA in %d.%d ms", &millisec, &microsec);

        video_data->total_frames++;  // Increment the frame count

        int converted_time = millisec * 1000 + microsec;  // Convert time to microseconds
        converted_time += video_data->last_decode_time;  // Add decode time to total processing time
        video_data->total_decode_time += converted_time;  // Update total decode time

        // Update min and max decode times
        video_data->min_decode_time = min(video_data->min_decode_time, converted_time);
        video_data->max_decode_time = max(video_data->max_decode_time, converted_time);

    }    // If the first frame of the video is decoded
    else if (strstr(line, "Decoded first frame"))
    {
        *video_playing = 1;  // Mark that a video is now playing
        // Extract the start time from the log
        sscanf(line, "%d.%d.%d", &sec, &millisec, &microsec);
        video_data->start_time = (sec * 1000 + millisec) * 1000 + microsec;  // Convert to microseconds

    }    // If the video ends
    else if (strstr(line, "Video ended"))
    {
        // Extract the end time from the log
        sscanf(line, "%d.%d.%d", &sec, &millisec, &microsec);
        video_data->end_time = (sec * 1000 + millisec) * 1000 + microsec;  // Convert to microseconds

        // Calculate the average decode time for the video
        video_data->avg_decode_time = (double)video_data->total_decode_time / video_data->total_frames;

        // Print the statistics of the video
        printf("Video \"%s\":\n", video_data->file_name);
        printf("  Total frames: %d\n", video_data->total_frames);
        printf("  Total decode time: %.3f ms\n", video_data->total_decode_time / 1000.0);
        printf("  Actual playback time: %.3f ms\n", (video_data->end_time - video_data->start_time) / 1000.0);
        printf("  Min/avg/max decode time: %.3f/%.3f/%.3f ms\n\n",
            video_data->min_decode_time / 1000.0,
            video_data->avg_decode_time / 1000.0,
            video_data->max_decode_time / 1000.0);

        *video_playing = 0;  // Mark that the video is no longer playing
    }
}

int main() {
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    struct VideoData video_data;  // Structure to hold video data
    char line[1024];  // Buffer to store each line of the log
    int video_playing = 0;  // Flag to indicate if a video is currently playing

    // Read each line of the input and process it
    while (fgets(line, sizeof(line), stdin)) {
        collect_statistics(line, &video_data, &video_playing);
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;  // Exit the program
}
