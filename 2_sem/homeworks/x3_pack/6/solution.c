#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    uint8_t *data;
    size_t length;
    size_t capacity;
} BsonBuffer;

void bson_buffer_init(BsonBuffer *buf) {
    buf->data = NULL;
    buf->length = 0;
    buf->capacity = 0;
}

void bson_buffer_append(BsonBuffer *buf, const void *data, size_t len) {
    if (buf->length + len > buf->capacity) {
        size_t new_cap = buf->capacity * 2;
        if (new_cap < buf->length + len) {
            new_cap = buf->length + len;
        }
        if (new_cap < 16) {
            new_cap = 16;
        }
        uint8_t *new_data = realloc(buf->data, new_cap);
        if (!new_data) {
            perror("realloc failed");
            exit(1);
        }
        buf->data = new_data;
        buf->capacity = new_cap;
    }
    memcpy(buf->data + buf->length, data, len);
    buf->length += len;
}

void write_int32_le(BsonBuffer *buf, int32_t value) {
    uint8_t bytes[4];
    bytes[0] = (uint8_t)(value & 0xFF);
    bytes[1] = (uint8_t)((value >> 8) & 0xFF);
    bytes[2] = (uint8_t)((value >> 16) & 0xFF);
    bytes[3] = (uint8_t)((value >> 24) & 0xFF);
    bson_buffer_append(buf, bytes, 4);
}

void write_double_le(BsonBuffer *buf, double value) {
    union {
        double d;
        uint64_t i;
    } u;
    u.d = value;
    uint8_t bytes[8];
    for (int i = 0; i < 8; i++) {
        bytes[i] = (u.i >> (i * 8)) & 0xFF;
    }
    bson_buffer_append(buf, bytes, 8);
}

void json_to_bson(json_object *jso, BsonBuffer *parent_buf, const char *key);

BsonBuffer generate_bson_document(json_object *jso, int is_array) {
    BsonBuffer doc_buf;
    bson_buffer_init(&doc_buf);

    uint8_t size_placeholder[4] = {0};
    bson_buffer_append(&doc_buf, size_placeholder, 4);

    if (is_array) {
        size_t array_len = json_object_array_length(jso);
        for (size_t i = 0; i < array_len; i++) {
            json_object *elem = json_object_array_get_idx(jso, i);
            char index_str[20];
            snprintf(index_str, sizeof(index_str), "%zu", i);
            json_to_bson(elem, &doc_buf, index_str);
        }
    } else {
        json_object_object_foreach(jso, key, val) {
            json_to_bson(val, &doc_buf, key);
        }
    }

    uint8_t terminator = 0;
    bson_buffer_append(&doc_buf, &terminator, 1);

    int32_t total_size = doc_buf.length;
    memcpy(doc_buf.data, &total_size, 4);

    return doc_buf;
}

void json_to_bson(json_object *jso, BsonBuffer *parent_buf, const char *key) {
    enum json_type type = json_object_get_type(jso);

    switch (type) {
        case json_type_object: {
            BsonBuffer doc_buf = generate_bson_document(jso, 0);
            uint8_t bson_type = 0x03;
            bson_buffer_append(parent_buf, &bson_type, 1);
            bson_buffer_append(parent_buf, key, strlen(key) + 1);
            bson_buffer_append(parent_buf, doc_buf.data, doc_buf.length);
            free(doc_buf.data);
            break;
        }
        case json_type_array: {
            BsonBuffer doc_buf = generate_bson_document(jso, 1);
            uint8_t bson_type = 0x04;
            bson_buffer_append(parent_buf, &bson_type, 1);
            bson_buffer_append(parent_buf, key, strlen(key) + 1);
            bson_buffer_append(parent_buf, doc_buf.data, doc_buf.length);
            free(doc_buf.data);
            break;
        }
        case json_type_string: {
            const char *str = json_object_get_string(jso);
            size_t len = strlen(str);
            uint8_t bson_type = 0x02;
            bson_buffer_append(parent_buf, &bson_type, 1);
            bson_buffer_append(parent_buf, key, strlen(key) + 1);
            write_int32_le(parent_buf, len + 1);
            bson_buffer_append(parent_buf, str, len);
            bson_buffer_append(parent_buf, "\x00", 1);
            break;
        }
        case json_type_int:
        case json_type_double: {
            double d = json_object_get_double(jso);
            uint8_t bson_type = 0x01;
            bson_buffer_append(parent_buf, &bson_type, 1);
            bson_buffer_append(parent_buf, key, strlen(key) + 1);
            write_double_le(parent_buf, d);
            break;
        }
        case json_type_boolean: {
            json_bool b = json_object_get_boolean(jso);
            uint8_t bson_type = 0x08;
            bson_buffer_append(parent_buf, &bson_type, 1);
            bson_buffer_append(parent_buf, key, strlen(key) + 1);
            uint8_t val = b ? 1 : 0;
            bson_buffer_append(parent_buf, &val, 1);
            break;
        }
        case json_type_null: {
            uint8_t bson_type = 0x0A;
            bson_buffer_append(parent_buf, &bson_type, 1);
            bson_buffer_append(parent_buf, key, strlen(key) + 1);
            break;
        }
        default: {
            fprintf(stderr, "Unsupported JSON type: %d\n", type);
            exit(1);
        }
    }
}

int main() {
    const char *input_filename = "input.txt";
    const char *output_filename = "output.bin";

    FILE *fp = fopen(input_filename, "rb");
    if (!fp) {
        perror("Failed to open input file");
        return 1;
    }
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *json_str = malloc(file_size + 1);
    if (!json_str) {
        perror("malloc failed");
        fclose(fp);
        return 1;
    }
    size_t read_size = fread(json_str, 1, file_size, fp);
    if (read_size != (size_t)file_size) {
        perror("fread failed");
        free(json_str);
        fclose(fp);
        return 1;
    }
    json_str[file_size] = '\0';
    fclose(fp);

    json_object *root = json_tokener_parse(json_str);
    free(json_str);
    if (!root) {
        fprintf(stderr, "Failed to parse JSON\n");
        return 1;
    }

    int is_array = json_object_get_type(root) == json_type_array;
    BsonBuffer root_doc = generate_bson_document(root, is_array);

    FILE *out_fp = fopen(output_filename, "wb");
    if (!out_fp) {
        perror("Failed to open output file");
        json_object_put(root);
        free(root_doc.data);
        return 1;
    }
    size_t written = fwrite(root_doc.data, 1, root_doc.length, out_fp);
    if (written != root_doc.length) {
        perror("fwrite failed");
        fclose(out_fp);
        json_object_put(root);
        free(root_doc.data);
        return 1;
    }
    fclose(out_fp);

    json_object_put(root);
    free(root_doc.data);

    return 0;
}