#ifndef _IAS_H_
#define _IAS_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IAS_API __attribute__ ((visibility ("default"))) 

IAS_API int ias_hello(char *subject);
IAS_API int ias_goodbye(char *subject);
int ias_hidden(void);

#ifdef __cplusplus
}
#endif

#endif

