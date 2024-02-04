#include "json.h"
#include "ctype.h"
#define JSON_ARRAY_END ']'
#define JSON_COMMA ','
#define JSON_NULL_CHAR '\0'
typedef struct {
    char* c;
    unsigned int size;
    unsigned int pos;
} JSON;

bool is_valid_json(char* str, int size){
    JSON json;
    json.c = str;
    json.size = size;
    json.pos = 0;
    char c = getNextNonWhitespaceChar(&json);
    if (c!='{' && c!= '[') return false;
    if (!parse_type(&json)) return false;
    if (getNextNonWhitespaceChar != JSON_NULL_CHAR) return false;
    return true;
}

char j_get(JSON* json){
    if (json->pos < json->size) return json->c[json->pos];
    else return JSON_NULL_CHAR;
}

char peek(JSON* json){
    if (json->pos+1 < json->size) return json->c[json->pos+1];
    else return JSON_NULL_CHAR;
}

bool compare(JSON* json, const char* word){
    int i = 0;
    while (true){
        if (word[i]==JSON_NULL_CHAR) break;
        if (json->pos+i >= json->size || json->c[i]!=word[i]) return false;
        i++;
    }
    return true;
}

void advance_by(JSON* json, int i){
    json->pos += i;
}

void advance(JSON* json){
    json->pos++;
};

// Renamed for clarity
char getNextNonWhitespaceChar(JSON* json) {
    char c = j_get(json);
    while (json->pos < json->size && isspace(c)) {
        advance(json);
        c = j_get(json);
    }
    return c;
}

bool parse_type(JSON* json){
    char c = getNextNonWhitespaceChar(json);
    switch (c){
        case '{':{
            if (!parse_dict(json)) return false;
            break;
        };
        case '[':{
            if (!parse_array(json)) return false;
            break;
        };
        case 't':{
            if (!compare(json, "true")) return false;
            advance_by(json, 4);
            break;
        };
        case 'f':{
            if (!compare(json, "false")) return false;
            break;
        };
        case 'n':{
            // Check for null
            if (!compare(json, "null")) return false;
            advance_by(json, 4);
            break;
        };
        case '"':{
            advance(json);
            if (!parse_string(json)) return false;
            break;
        };
        default:{
            // parse int
            if ((c>='0' && c<='9')|| c=='-'){
                if (c == '-') advance;
                if (!parse_num(json)) return false;
            } else {
                return false;
            }
            break;
        }
    }
    return true;
}

bool parse_key_value(JSON* json){
    if (!parse_key(json)) return false;
    if (getNextNonWhitespaceChar(json)!=':') return false;
    advance(json);
    if (!parse_type(json)) return false;
    return true;
}

bool parse_num(JSON* json){
    char c = getNextNonWhitespaceChar(json);
    while (c>='0' && c<='9'){
        advance(json);
        c = j_get(json);
    }
    if (c == '.') {
        advance(json);
        c = j_get(json);
        while (c>='0' && c<= '9'){
            advance(json);
            c = j_get(json);
        }
    }
    return true;

}

bool parse_string(JSON* json){
    // Advance until we get to '"' or '\'
    char c = j_get(json);
    while (true){
        if (c == JSON_NULL_CHAR) return false;
        else if (c == '\\'){
            char next = peek(json);
            if (next == '"' || next == '\\' || next == 'n' || next == 't') advance(json);
            else return false;
        } else if (c == '"') break;
        advance(json);
        c = j_get(json);
    }
    advance(json);
    return true;
}

char parse_alpha_numeric(JSON* json){
    char c = j_get(json);
    while (isalnum(c) || isspace(c)) {
        advance(json);
        c = j_get(json);
    };
    return c;
}

bool parse_key(JSON* json){
    if (getNextNonWhitespaceChar(json) != '"') return false;
    advance(json);
    if (parse_alpha_numeric(json) != '"') return false;
    advance(json);
    return true;

}
bool parse_array(JSON* json) {
    while (true) {
        char c = getNextNonWhitespaceChar(json);
        if (c == JSON_ARRAY_END) break;
        if (c == JSON_NULL_CHAR || !parse_type(json)) return false;

        char nextChar = getNextNonWhitespaceChar(json);
        if (nextChar == JSON_ARRAY_END) break;
        if (nextChar != JSON_COMMA) return false;
    }
    advance(json); // Move past the closing bracket
    return true;
}

bool parse_dict(JSON* json){
    if (!parse_key_value(json)) return false;
    if (getNextNonWhitespaceChar(json) != '}') return false;
    advance(json);
    return true;
}

#undef JSON_ARRAY_END
#undef JSON_COMMA
#undef JSON_NULL_CHAR