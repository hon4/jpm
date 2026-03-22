#include "gzdecompress.h"
#include <stdio.h>
#include <zlib.h>

int gzdecompress(const char *gzfile, const char *outfile) {
    gzFile gz = gzopen(gzfile, "rb");
    if (!gz) {
        fprintf(stderr, "Failed to open gzip file: %s\n", gzfile);
        return -1;
    }

    FILE *out = fopen(outfile, "wb");
    if (!out) {
        fprintf(stderr, "Failed to open output file: %s\n", outfile);
        gzclose(gz);
        return -2;
    }

    char buf[4096];
    int n;
    while ((n = gzread(gz, buf, sizeof(buf))) > 0) {
        if (fwrite(buf, 1, n, out) != (size_t)n) {
            fprintf(stderr, "Failed to write to output file\n");
            gzclose(gz);
            fclose(out);
            return -3;
        }
    }

    if (n < 0) {
        int err;
        const char *msg = gzerror(gz, &err);
        fprintf(stderr, "Error during decompression: %s\n", msg);
        gzclose(gz);
        fclose(out);
        return -4;
    }

    gzclose(gz);
    fclose(out);
    return 0;  /* success */
}