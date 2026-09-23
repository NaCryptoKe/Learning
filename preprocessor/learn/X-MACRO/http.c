#define HTTP_STATUS_CODE \
    X(OK) \
    X(MOVED) \
    X(NOT_FOUND)\
    X(SERVER_ERROR)

#define X(name) #name,
typedef enum {
  HTTP_STATUS_CODE
} status_codes;
#undef X

#define X(name) #name,
const char *HTTP_status[] = {
  HTTP_STATUS_CODE
};
#undef X

int main(void)
{
  return 0;
}
