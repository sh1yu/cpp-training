//
// Created by psy on 2022/6/12.
//
#include <stdlib.h>

#include "handler.h"

void http_handler(struct evhttp_request *request, void *arg) {

    // 打印uri
    const struct evhttp_uri *evhttp_uri = evhttp_request_get_evhttp_uri(request);
    char uri[8192];
    evhttp_uri_join((struct evhttp_uri *) evhttp_uri, uri, 8192);
    printf("accept request url:%s\n", uri);
    // 将uri解码并打印
    char *decoded_uri = evhttp_decode_uri(uri);
    printf("decoded_uri=%s\n", decoded_uri);
    free(decoded_uri);

    //解析uri参数
    struct evkeyvalq params;
    evhttp_parse_query_str(uri, &params);
    printf("q=%s\n", evhttp_find_header(&params, "q"));
    printf("s=%s\n", evhttp_find_header(&params, "s"));

    //打印请求header
    struct evkeyvalq *headers = evhttp_request_get_input_headers(request);
    for (struct evkeyval *header = headers->tqh_first; header; header = header->next.tqe_next) {
        printf("    %s: %s\n", header->key, header->value);
    }

    //获取POST数据
    size_t post_size = evbuffer_get_length(request->input_buffer);
    unsigned char *post_data = evbuffer_pullup(request->input_buffer, -1);
    printf("post_data size: %ld, post_data=%s\n", post_size, post_data);

    //设置响应header
    evhttp_add_header(request->output_headers, "Server", MYMETHOD_SIGNATURE);
    evhttp_add_header(request->output_headers, "Content-Type", "text/plain; charset=UTF-8");
    evhttp_add_header(request->output_headers, "Connection", "close");

    //构建一个buf，用于返回的body
    struct evbuffer *evbuf = evbuffer_new();
    evbuffer_add_printf(evbuf, "Server response. Your request url is %s", uri);

    //将返回body的buf发送出去
    evhttp_send_reply(request, HTTP_OK, "OK", evbuf);

    //释放evbuf
    evbuffer_free(evbuf);
}

