/* _strcpy:  copy t to s; pointer version 2 */
void _strcpy(char *s, char *t) {
    while ((*s++ = *t++) != '\0') { }
}