#include <stdlib.h>
#include <string.h>
#include "telemetria.h"

/*
 * Serializa relatorio em buffer alocado dinamicamente.
 * Retorna ponteiro para buffer ou NULL se falhar malloc().
 */
void *serializar_relato(const Relatorio *src)
{
    size_t total = sizeof(Relatorio) + src->nome_len;
    void *buf = malloc(total);
    if (!buf) return NULL;
    memcpy(buf, src, total);
    return buf;
}

/*
 * Desserializa buffer para nova struct alocada.
 * Preenche *out com ponteiro ou NULL se falhar malloc().
 */
void desserializar_relato(const void *buf, Relatorio **out)
{
    const uint8_t *b = buf;
    uint8_t len = b[offsetof(Relatorio, nome_len)];
    size_t total = sizeof(Relatorio) + len;
    Relatorio *r = malloc(total);
    if (!r) { *out = NULL; return; }
    memcpy(r, buf, total);
    *out = r;
}
