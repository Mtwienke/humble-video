#define OVERRIDE_VQ_NBEST
void vq_nbest(spx_word16_t *in, const spx_word16_t *codebook, int len, int entries, spx_word32_t *E, int N, int *nbest, spx_word32_t *best_dist, char *stack)
{
    for (int i = 0; i < entries; i += 4)
    {
        spx_word32_t dist1 = 0, dist2 = 0, dist3 = 0, dist4 = 0;

        for (int j = 0; j < len; j++)
        {
            spx_word16_t input = in[j];
            dist1 += input * codebook[j];
            dist2 += input * codebook[len + j];
            dist3 += input * codebook[2 * len + j];
            dist4 += input * codebook[3 * len + j];
        }

        dist1 = (*E++ * 0.5f) - dist1;
        if (dist1 < *best_dist || i == 0)
        {
            *best_dist = dist1;
            *nbest = i;
        }
        dist2 = (*E++ * 0.5f) - dist2;
        if (dist2 < *best_dist)
        {
            *best_dist = dist2;
            *nbest = i + 1;
        }
        dist3 = (*E++ * 0.5f) - dist3;
        if (dist3 < *best_dist)
        {
            *best_dist = dist3;
            *nbest = i + 2;
        }
        dist4 = (*E++ * 0.5f) - dist4;
        if (dist4 < *best_dist)
        {
            *best_dist = dist4;
            *nbest = i + 3;
        }

        codebook += 4 * len;
    }
}
