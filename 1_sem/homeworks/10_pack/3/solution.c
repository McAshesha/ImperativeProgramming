#include <stdio.h>
#include <stdlib.h>

int hex_to_int(char c)
{
    if ('0' <= c && c <= '9')
    {
        return c - '0';
    }
    return c - 'A' + 10;
}

typedef struct
{
    int *data;
    int start, end, size, capacity;
} RingBuffer;

RingBuffer *create_buffer(int capacity)
{
    RingBuffer *buffer = (RingBuffer *) malloc(sizeof(RingBuffer));
    buffer->data = (int *) malloc(sizeof(int) * capacity);
    buffer->start = buffer->end = buffer->size = 0;
    buffer->capacity = capacity;
    return buffer;
}

void destroy_buffer(RingBuffer *buffer)
{
    free(buffer->data);
    free(buffer);
}

void push(RingBuffer *buffer, int value, int bottom)
{
    if (buffer->size == buffer->capacity)
    {
        return;
    }
    if (bottom)
    {
        buffer->start = (buffer->start - 1 + buffer->capacity) % buffer->capacity;
        buffer->data[buffer->start] = value;
    }
    else
    {
        buffer->data[buffer->end] = value;
        buffer->end = (buffer->end + 1) % buffer->capacity;
    }
    buffer->size++;
}

int pop(RingBuffer *buffer, int bottom)
{
    if (buffer->size == 0)
    {
        return 0;
    }
    int value;
    if (bottom)
    {
        value = buffer->data[buffer->start];
        buffer->start = (buffer->start + 1) % buffer->capacity;
    }
    else
    {
        buffer->end = (buffer->end - 1 + buffer->capacity) % buffer->capacity;
        value = buffer->data[buffer->end];
    }
    buffer->size--;
    return value;
}

void print_buffer(RingBuffer *buffer)
{
    printf("%d", buffer->size);
    int idx = buffer->start;
    for (int i = 0; i < buffer->size; i++)
    {
        printf(" %d", buffer->data[idx]);
        idx = (idx + 1) % buffer->capacity;
    }
    printf("\n");
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    char *operations = (char *) malloc(sizeof(char) * M + 1);
    if (M > 0)
    {
        scanf("%s", operations);
    }

    RingBuffer *left = create_buffer(2 * N + 1);
    RingBuffer *right = create_buffer(2 * N + 1);

    for (int i = 1; i <= N; i ++)
    {
        push(left, i, 0);
    }
    for (int i = 1; i <= N; i++)
    {
        push(right, -i, 0);
    }

    for (int i = 0; i < M; i++)
    {
        int op = hex_to_int(operations[i]);
        int from_right = (op & 0b1000) >> 3;
        int from_bottom = (op & 0b0100) >> 2;
        int to_right = (op & 0b0010) >> 1;
        int to_bottom = (op & 0b0001);
        RingBuffer *from = from_right ? right : left;
        RingBuffer *to = to_right ? right : left;

        if (from->size == 0)
        {
            continue;
        }

        int card = pop(from, !from_bottom);
        push(to, card, !to_bottom);
    }

    print_buffer(left);
    print_buffer(right);

    destroy_buffer(left);
    destroy_buffer(right);
    free(operations);

    return 0;
}
