#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

void die(const char *s);
void enableRawMode();
void disableRawMode();

#ifdef __cplusplus
}
#endif

#endif